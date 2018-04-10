#include "tasks/paranoiatask.h"

#include <iostream>

#include <cdio/paranoia.h>

#include <QDir>
#include <QTextStream>

ParanoiaTask::ParanoiaTask(AudioDisk* disk)
    : disk_(disk)
{
}

ParanoiaTask::~ParanoiaTask()
{
}

void ParanoiaTask::run()
{
    QDir dir(QDir::current());
    QTextStream stream;

    QString album_folder;
    stream.setString(&album_folder);
    stream << disk_->title() << " (" << disk_->year() << ")";

    // Create directories
    dir.mkdir(disk_->artist());
    if (!dir.cd(disk_->artist())) {
        emit done(1);
        return;
    }
    dir.mkdir(album_folder);
    if (!dir.cd(album_folder)) {
        emit done(1);
        return;
    }

    // Open drive and init paranoia
    cdrom_drive_t* drive = cdio_cddap_identify(disk_->device().toStdString().c_str(), 1, NULL);
    cdda_verbose_set(drive, CDDA_MESSAGE_PRINTIT, CDDA_MESSAGE_PRINTIT);
    cdda_open(drive);
    cdrom_paranoia_t* cdrom = paranoia_init(drive);

    // Get sector count
    lsn_t first_lsn = cdda_disc_firstsector(drive);
    lsn_t last_lsn = cdda_disc_lastsector(drive);
    lsn_t cursor = first_lsn;
    emit started(last_lsn);

    // For each track
    for (Track* track : disk_->tracks()) {
        emit trackChanged(track->num());

        // Get track boundaries
        first_lsn = cdda_track_firstsector(drive, track->num());
        last_lsn = cdda_track_lastsector(drive, track->num());
        unsigned int byte_count = (last_lsn - first_lsn + 1) * CDIO_CD_FRAMESIZE_RAW;

        // File in the format '00 title.wav'
        QString track_file;
        stream.setString(&track_file);
        stream << qSetFieldWidth(2) << qSetPadChar('0') << track->num() << qSetFieldWidth(0) << " " << track->title() << ".wav";
        track_file = dir.absoluteFilePath(track_file);

        // Open file and write header
        std::ofstream file(track_file.toStdString(), std::ofstream::binary | std::ofstream::app | std::ofstream::out);
        writeWavHeader(file, byte_count);

        for (cursor = first_lsn; cursor <= last_lsn; cursor++) {
            // Read sector
            int16_t* p_readbuf = paranoia_read_limited(cdrom, NULL, 30);

            // Get errors
            char* psz_err = cdda_errors(drive);
            char* psz_mes = cdda_messages(drive);

            // TODO: Display errors in a log maybe? Via signals
            if (psz_mes || psz_err)
                std::cerr << psz_err << psz_mes << std::endl;

            if (psz_err)
                free(psz_err);
            if (psz_mes)
                free(psz_mes);

            if (!p_readbuf) {
                std::cerr << "paranoia read error" << std::endl;
                break;
            }

            char* temp = (char*)p_readbuf;
            file.write(temp, CDIO_CD_FRAMESIZE_RAW);

            // Dont signal too often
            if (cursor % 100 == 0)
                emit progress(cursor);

            if (is_stopped()) {
                file.close();
                paranoia_free(cdrom);
                cdda_close(drive);
                emit done(1);
                return;
            }
        }

        file.close();
    }

    paranoia_free(cdrom);
    cdda_close(drive);
}

void ParanoiaTask::writeWavHeader(std::ofstream& file, unsigned int byte_count)
{
    // clang-format off
    const int wave_chunk_length   = byte_count + 44 - 8;
    const int format_chunk_length = 16;
    const int compression_code    = 1;
    const int number_of_channels  = 2;
    const int sample_rate         = 44100;  // Hz
    const int block_align         = sample_rate * 2 * 2;
    const int significant_bps     = 4;
    const int extra_format_bytes  = 16;
    // clang-format on

    file.write("RIFF", 4);
    file.write((char*)&wave_chunk_length, 4);
    file.write("WAVEfmt ", 8);
    file.write((char*)&format_chunk_length, 4);
    file.write((char*)&compression_code, 2);
    file.write((char*)&number_of_channels, 2);
    file.write((char*)&sample_rate, 4);
    file.write((char*)&block_align, 4);
    file.write((char*)&significant_bps, 2);
    file.write((char*)&extra_format_bytes, 2);
    file.write("data", 4);
    file.write((char*)&byte_count, 4);
}