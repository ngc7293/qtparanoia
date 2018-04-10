# qtparanoia

Qt application for ripping CDs with libparanoia (in-development).
Aims to be light, simple and efficient.

Planned features are:

- Ripping CDs (mostly works)
- Automatically converting WAV files to different formats (via ffmpeg/flac)
- Reading CDInfo (works)
- Editing of tags while CD is ripping (and automatically save them to files) (via TagLib, probably)
- Eventually, ability to easily rip multiples CDs at once

What I'm not planning to do:

- A fully-fledged tag editor (puddletag is a thing)
- Getting CD info from online sources

## Requirements

Right now:

- `libcdio-dev libcdio-cdda-dev libcdio-paranoia-dev`
- Qt >= 5.9 (I have not tested on lower versions)

Eventually:

- `ffmpeg`
- `flac`
- `libtag1-dev` (TagLib)