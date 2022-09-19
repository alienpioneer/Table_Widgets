/*====================================== Solystic =======================================
|
| File: TableModel.h
|
| Description: Custom model to be used with QTableView :
|              - create a QTableView and set the model;
|              - For convenience, use only "user" functions;
|              - All the table operations are made through the model;
|              - Call all the functions on the model itself and not on table->model() (returns abstract object)
|
| Application : TOP2000 Italy-> 2022
|
+=======================================================================================*/
#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QColor>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = nullptr);

    // USER FUNCTIONS
    bool setCellData(const int row,const int column, const QString data);
    bool setCellColor(const int row,const int column, const QColor color);

    //! Overloaded function for protected rowCount().
    int  rowCount();
    //! Overloaded function for protected columnCount().
    int  columnCount();
    //! Inserts "count" rows from a specified row index
    bool insertRows(int beginRow, int count);
    //! Inserts "count" columns from a specified column index
    bool insertColumns(const int beginColumn,const int count);
    //! Clear all the rows from the table
    bool clearAllRows();
    //! Use alternating color for the columns
    void useAlternateColumnColor(const bool state);
    //! Use alternating color for the columns
    void useAlternateRowColor(const bool state);
    //! Use a different color for the first column
    void useFirstColumnColor(const bool state);
    //! Set alternating color for the columns
    void setAlternateColumnColor(const QColor color);
    //! Set alternating color for the rows
    void setAlternateRowColor(const QColor color);
    //! Set a different color for the first column
    void setFirstColumnColor(const QColor color);
    /*! Sets the list with the header labels.
        Using this function will automatically set the number of rows/columns accordingly.
        Set the vertical header first !*/
    bool setHeaderLabels(const QStringList headerLabels, Qt::Orientation orientation);
    /*! Overloaded function for setHeaderLabels().
        Using this function will automatically set the number of columns accordingly.*/
    bool setHorizontalHeader(const QStringList headerLabels);
    /*! Overloaded function for setHeaderLabels().
        Using this function will automatically set the number of rows accordingly.*/
    bool setVerticalHeader(const QStringList headerLabels);
    //! Set horizontal header background color. Not working Win10
    bool setHorizontalHeaderBkgColor(const QColor color);
    //! Set vertical header background color
    bool setVerticalHeaderBkgColor(const QColor color);
    //! Replace all header labels
    void resetHeaderLabels(const QStringList headerLabels, Qt::Orientation orientation);
    //! Replace horizontal header labels.Overloaded function
    void resetHorizontalHeader(const QStringList headerLabels);
    //! Replace vertical header labels.Overloaded function
    void resetVerticalHeader(const QStringList headerLabels);
    /*! Replace the horizontal header labels from "beginColumn" to "count" */
    void replaceHorizontalHeaderLabels(const int beginColumn,const int count, const QStringList headerLabels);
    /*! Replace the vertical header labels from "beginRow" to "count" */
    void replaceVerticalHeaderLabels(const int beginRow,const int count, const QStringList headerLabels);
    //! Remove the "count" number of rows beginning at index "beginRows"
    //bool removeRows(const int beginRow,const int count);
    //! Remove the "count" number of columns beginning at index "beginColumn"
    //bool removeColumns(const int beginColumn,const int count);

    // QAbstractItemModel interface
protected:
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
    bool removeColumns(int column, int count, const QModelIndex &parent) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool hasChildren(const QModelIndex &parent) const override;

private:
    void refreshAlternateColumnColor();
    void refreshAlternateRowColor();
    void refreshFirstColumnColor();

    void debugBkgColors(int row, QString msg);

private:
    int m_rowCount;
    int m_columnCount;

    bool m_useColumnAltColor;
    bool m_useRowAltColor;
    bool m_useFirstColumnColor;

    QStringList             m_horizontalHeaderLabels;
    QStringList             m_verticalHeaderLabels;

    QColor                  m_defaultBkgColor;
    QColor                  m_foregroundColor;
    QColor                  m_altColumnColor;
    QColor                  m_altRowColor;
    QColor                  m_horizontalHeaderBkgColor;
    QColor                  m_verticalHeaderBkgColor;
    QColor                  m_headerForegroundColor;
    QColor                  m_firstColumnBkgColor;

    QList<QStringList>      m_data;
    QList<QList<QColor>>    m_bkgColors;
    QList<QList<QColor>>    m_foregroundColors;
};

#endif // TABLEMODEL_H
