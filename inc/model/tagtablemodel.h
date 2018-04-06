#ifndef TAGTABLEMODEL_H
#define TAGTABLEMODEL_H

#include <QAbstractTableModel>

#include <iostream>

#include "audiodisk.h"

class TagTableModel : public QAbstractTableModel {
    Q_OBJECT
private:
    AudioDisk* disk_;

public:
    TagTableModel();
    ~TagTableModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void set_disk(AudioDisk* disk);

    AudioDisk* disk() { return disk_; }
};

#endif // TAGTABLEMODEL_H