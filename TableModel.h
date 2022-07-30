#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QColor>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = nullptr);

    void useAltColumnColor(bool state);     // Use alternating color for the columns
    void useFirstColumnColor(bool state);   // Set a different color for the first columns
    void setAltColumnColor(const QColor color);   // Set alternating color for the columns
    void setFirstColumnColor(const QColor color); // Set a different color for the first column

    bool setCellData(int row, int column, const QString data);
    bool setCellColor(int row, int column, const QColor color);
    bool clear();

    // Set the list with the header labels
    // Using this function will automatically set the number of columns
    bool setHeaderLabels(const QStringList headerLabels, Qt::Orientation orientation);

    // QAbstractItemModel interface
public:
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // Editables
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool insertColumns(int column, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool hasChildren(const QModelIndex &parent) const override;

private:
    void refreshAltColumnColor();
    void refreshFirstColumnColor();

private:
    int m_rowCount;
    int m_columnCount;

    bool m_useColumnAltColor;
    bool m_useFirstColumnColor;

    QStringList             m_headerLabels;

    QColor                  m_defaultBkgColor;
    QColor                  m_foregroundColor;
    QColor                  m_altColumnColor;
    QColor                  m_headerBkgColor;
    QColor                  m_firstColumnBkgColor;

    QList<QStringList>      m_data;
    QList<QList<QColor>>    m_bkgColors;
    QList<QList<QColor>>    m_foregroundColors;

    // QAbstractItemModel interface
public:

};

#endif // TABLEMODEL_H
