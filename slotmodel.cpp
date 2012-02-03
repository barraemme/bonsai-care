#include "slotmodel.h"

SlotModel::SlotModel(QObject* parent)
{
}

SlotModel::~SlotModel()
{
}

QVariant SlotModel::data(const QModelIndex &index, int role) const
{
}

Qt::ItemFlags SlotModel::flags(const QModelIndex &index) const
{
}

QVariant SlotModel::headerData(int section, Qt::Orientation orientation, int role) const
{
}

int SlotModel::rowCount(const QModelIndex &parent) const
{
}

bool SlotModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
}

bool SlotModel::createTable(QSqlDatabase &db)
{
}
