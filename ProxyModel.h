#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QIdentityProxyModel>

class ProxyModel : public QIdentityProxyModel
{
    Q_OBJECT
public:
    explicit ProxyModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // PROXYMODEL_H
