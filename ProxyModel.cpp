#include "ProxyModel.h"
#include "qbrush.h"
#include <QDebug>

ProxyModel::ProxyModel(QObject *parent)
    : QIdentityProxyModel{parent}
{

}

QVariant ProxyModel::data(const QModelIndex &index, int role) const
{
    return QIdentityProxyModel::data(index, role);
}

QVariant ProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(section == 0 && orientation == Qt::Horizontal)
    {
        QBrush brush = QIdentityProxyModel::headerData(0,  Qt::Horizontal, Qt::BackgroundRole).value<QBrush>();
        qDebug() << brush.color().name();
    }
    return QIdentityProxyModel::headerData(section, orientation, role);
}
