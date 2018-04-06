#include "model/tagtablemodel.h"

#include <QVariant>
#include <QAbstractTableModel>

TagTableModel::TagTableModel()
{
    disk_ = nullptr;
}

TagTableModel::~TagTableModel()
{
    delete disk_;
}

int TagTableModel::rowCount(const QModelIndex& parent) const 
{
    return (disk_ != nullptr ? disk_->trackcount() : 0);
}

int TagTableModel::columnCount(const QModelIndex& parent) const
{
    return 3;
}

void TagTableModel::set_disk(AudioDisk* disk)
{
    emit beginResetModel();
    disk_ = disk;
    emit endResetModel();
}

QVariant TagTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Title");
            case 1:
                return QString("Artist");
            case 2:
                return QString("Status");
            }
        } else {
            return QString("%02").arg(section);
        }
    }
    return QVariant();
}

QVariant TagTableModel::data(const QModelIndex &index, int role) const
{
    if (disk_ == nullptr) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        Track* t = disk_->track(index.row());

        switch (index.column()) {
        case 0:
            return t->title();
            break;
        case 1: 
            return t->artist();
            break;
        case 2: 
            return "pending";
            break;
        }
    }
    return QVariant();
}