#include "TableModel.h"
#include <QBrush>
#include <QDebug>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent),
      m_rowCount(0),
      m_columnCount(0),
      m_useColumnAltColor(false),
      m_useRowAltColor(false),
      m_useFirstColumnColor(false),
      m_defaultBkgColor(QColor(255, 255, 255)),
      m_foregroundColor(QColor(0, 0, 0)),
      m_altColumnColor(QColor(250, 233, 163)),
      m_altRowColor(QColor(250, 233, 163)),
      m_horizontalHeaderBkgColor(QColor(232, 232, 232)),
      m_verticalHeaderBkgColor(QColor(232, 232, 232)),
      m_headerForegroundColor(QColor(0, 0, 0)),
      m_firstColumnBkgColor(QColor(237, 237, 237))
{
}

int TableModel::rowCount()
{
    return rowCount(QModelIndex());
}

int TableModel::columnCount()
{
    return columnCount(QModelIndex());
}

bool TableModel::insertRows(const int beginRow,const int count)
{
    return insertRows(beginRow, count, QModelIndex());
}

bool TableModel::insertColumns(const int beginColumn, const int count)
{
    return insertColumns(beginColumn, count, QModelIndex());
}

bool TableModel::setCellData(const int row, const int column, const QString data)
{
    return setData(index(row,column), data, Qt::DisplayRole);
}

bool TableModel::setCellColor(const int row, const int column, const QColor color)
{
    return setData(index(row,column), QVariant(color.name()), Qt::BackgroundRole);
}

bool TableModel::clearAllRows()
{
    if(m_rowCount > 0)
        return  removeRows(0, m_rowCount, QModelIndex());
    else
        return false;
}

// --------------------------------------- HEADER ---------------------------------------

// Set the list with the header labels
// Using this function will automatically set the number of columns or the number of rows accordingly
bool TableModel::setHeaderLabels(const QStringList headerLabels, Qt::Orientation orientation)
{
    bool result = true;

    for(int i=0; i < headerLabels.size(); i++)
    {
        result = result && setHeaderData(i, orientation, QObject::tr(headerLabels.at(i).toUtf8()), Qt::DisplayRole);
    }

    if(orientation == Qt::Horizontal)
        insertColumns(0, headerLabels.size(), QModelIndex());
    if(orientation == Qt::Vertical)
        insertRows(0, headerLabels.size(), QModelIndex());

    return result;
}

bool TableModel::setHorizontalHeader(const QStringList headerLabels)
{
    return setHeaderLabels(headerLabels, Qt::Horizontal);
}

bool TableModel::setVerticalHeader(const QStringList headerLabels)
{
    return setHeaderLabels(headerLabels, Qt::Vertical);
}

bool TableModel::setHorizontalHeaderBkgColor(const QColor color)
{
    bool result = true;

    for(int i=0; i < m_columnCount; i++)
    {
        result = result && setHeaderData(i, Qt::Horizontal,QVariant(color.name()), Qt::BackgroundRole);
    }
    return result;
}

bool TableModel::setVerticalHeaderBkgColor(const QColor color)
{
    bool result = true;

    for(int i=0; i < m_rowCount; i++)
    {
        result = result && setHeaderData(i, Qt::Vertical, QVariant(color.name()), Qt::BackgroundRole);
    }
    return result;
}

// Replace the header labels
void TableModel::resetHeaderLabels(const QStringList headerLabels, Qt::Orientation orientation)
{
    QStringList header;

    switch (orientation)
    {
        case  Qt::Horizontal:
            header = m_horizontalHeaderLabels;
        break;

        case Qt::Vertical:
            header = m_verticalHeaderLabels;
            break;

        default:;
    }

    if( headerLabels.size() != header.size())
        qWarning() << "TableModel::resetHeaderLabels(): The new header size is different!";

    for(int i=0; i < header.size(); i++)
    {
        header.replace(i, QObject::tr(headerLabels.at(i).toUtf8()));
    }
}

void TableModel::resetHorizontalHeader(const QStringList headerLabels)
{
    return resetHeaderLabels(headerLabels, Qt::Horizontal);
}

void TableModel::resetVerticalHeader(const QStringList headerLabels)
{
    return resetHeaderLabels(headerLabels, Qt::Vertical);
}

void TableModel::replaceHorizontalHeaderLabels(const int beginColumn, const int count, const QStringList headerLabels)
{
    if( beginColumn+count-1 > headerLabels.size())
    {
        qCritical() << "TableModel::replaceHorizontalHeaderLabels(): The size of the header list is bigger than the specified count!";
        return;
    }
    else if ( beginColumn+count < headerLabels.size())
    {
        qWarning() << "TableModel::replaceHorizontalHeaderLabels(): The size of the header list is smaller than the specified count!";
    }

    if( beginColumn+count-1 > m_horizontalHeaderLabels.size())
    {
        qCritical() << "TableModel::replaceHorizontalHeaderLabels(): The size of the resulting header is bigger than the existing header!";
        return;
    }

    int index = 0;
    for(int i=beginColumn; i < beginColumn+count; i++)
    {
        m_horizontalHeaderLabels.replace(i, QObject::tr(headerLabels.at(index).toUtf8()));
        index++;
    }

    emit headerDataChanged(Qt::Horizontal, beginColumn, beginColumn+count-1);
}

void TableModel::replaceVerticalHeaderLabels(const int beginRow, const int count, const QStringList headerLabels)
{
    if( beginRow+count-1 > headerLabels.size())
    {
        qCritical() << "TableModel::replaceVerticalHeaderLabels(): The size of the header list is bigger than the specified count!";
        return;
    }
    else if ( beginRow+count < headerLabels.size())
    {
        qWarning() << "TableModel::replaceVerticalHeaderLabels(): The size of the header list is smaller than the specified count!";
    }

    if( beginRow+count-1 > m_horizontalHeaderLabels.size())
    {
        qCritical() << "TableModel::replaceVerticalHeaderLabels(): The size of the resulting header is bigger than the existing header!";
        return;
    }

    for(int i=0; i<count; i++)
    {
        m_horizontalHeaderLabels.replace(beginRow+i, QObject::tr(headerLabels.at(i).toUtf8()));
    }

    emit headerDataChanged(Qt::Vertical, beginRow, beginRow+count-1);
}

bool TableModel::removeRows(const int beginRow, const int count)
{
    return removeRows(beginRow, count, QModelIndex());
}

bool TableModel::removeColumns(const int beginColumn, const int count)
{
    return removeColumns(beginColumn, count, QModelIndex());
}

// --------------------------------------- ROWS COLUMS ---------------------------------------
int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_rowCount;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_columnCount;
}

// Insert new rows and set data list and color lists for each new row
bool TableModel::insertRows(int beginRow, int count, const QModelIndex &parent)
{
    QList<QColor> bkgColorList;
    QList<QColor> foregroundColorList;
    QStringList   data;
    QVector<int>  roles;

    roles.append({Qt::BackgroundRole,Qt::DisplayRole,Qt::ForegroundRole});

    beginInsertRows(parent, beginRow, beginRow+count-1);

    for(int row =beginRow; row<beginRow+count; row++)
    {
        bkgColorList.clear();
        foregroundColorList.clear();
        data.clear();

        for(int column=0; column < m_columnCount; column++)
        {
            bkgColorList.append(m_defaultBkgColor);
            foregroundColorList.append(m_foregroundColor);
            data.append("");
        }

        m_bkgColors.append(bkgColorList);
        m_foregroundColors.append(foregroundColorList);
        m_data.append(data);
        m_rowCount+=1;

        for(int column=0; column < m_columnCount; column++)
        {
            emit dataChanged(index(row,column),index(row,column), roles);
        }

        setHeaderData(row, Qt::Vertical, QVariant(QString::number(row)), Qt::DisplayRole);
    }

    endInsertRows();

    refreshFirstColumnColor();
    refreshAlternateRowColor();
    refreshAlternateColumnColor();

    return true;
}

// Insert new columnss and set data list and color lists for each new column
bool TableModel::insertColumns(int beginColumn, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, beginColumn, beginColumn+count-1);

    if (m_columnCount != 0)
    {
        QVector<int>  roles;

        roles.append({Qt::BackgroundRole,Qt::DisplayRole,Qt::ForegroundRole});

        for(int row =0; row<m_rowCount; row++)
        {
            for(int column = beginColumn; column < beginColumn+count; column++)
            {
                m_bkgColors[row].insert(beginColumn, m_defaultBkgColor);
                m_foregroundColors[row].insert(beginColumn, m_foregroundColor);
                m_data[row].insert(beginColumn, "");

                emit dataChanged(index(row,column),index(row,column), roles);
            }
        }

        for(int column = beginColumn; column < beginColumn+count; column++)
        {
            setHeaderData(column, Qt::Horizontal, QVariant(""), Qt::DisplayRole);
        }
    }

    m_columnCount+=count;

    endInsertColumns();

    return true;
}

// TODO remove colors, headers, etc
bool TableModel::removeRows(int beginRow, int count, const QModelIndex &parent)
{
    if( beginRow+count > m_rowCount)
    {
        qWarning() << "TableModel::removeRows() Row count to remove is bigger than the column number!";
        return false;
    }

    beginRemoveRows(parent, beginRow, beginRow+count-1);

    for (int i = 0; i < count; ++i) {
        m_data.removeAt(beginRow+i);
    }

    m_rowCount -= count;

    endRemoveRows();
    return true;

}

// TODO remove colors, headers, etc
bool TableModel::removeColumns(int beginColumn, int count, const QModelIndex &parent)
{
    if( beginColumn+count > m_columnCount)
    {
        qWarning() << "TableModel::removeColumns() Column count to remove is bigger than the column number!";
        return false;
    }

    beginRemoveColumns(parent, beginColumn, beginColumn+count-1);

    for (int i = 0; i < count; ++i) {
        m_data.removeAt(beginColumn+i);
    }

    m_columnCount -= count;

    endRemoveColumns();
    return true;
}

// --------------------------------------- COLORS ---------------------------------------
void TableModel::useAlternateColumnColor(const bool state)
{
    m_useColumnAltColor = state;

    refreshAlternateColumnColor();
}

void TableModel::useAlternateRowColor(const bool state)
{
    m_useRowAltColor = state;

    refreshAlternateRowColor();
}

void TableModel::setAlternateColumnColor(const QColor color)
{
    m_altColumnColor = color;

    refreshAlternateColumnColor();
}

void TableModel::setAlternateRowColor(const QColor color)
{
    m_altRowColor = color;

    refreshAlternateRowColor();
}

void TableModel::useFirstColumnColor(const bool state)
{
    m_useFirstColumnColor = state;

    refreshFirstColumnColor();
}

void TableModel::setFirstColumnColor(const QColor color)
{
    m_firstColumnBkgColor = color;

    refreshFirstColumnColor();
}

void TableModel::refreshFirstColumnColor()
{
    if(!m_rowCount || !m_columnCount)
        return;

    QVector<int> role;
    role.append(Qt::BackgroundRole);

    for(int row =0; row<m_rowCount; row++)
    {
        if (m_useFirstColumnColor)
            setData(index(row,0), QVariant(m_firstColumnBkgColor.name()), Qt::BackgroundRole);
    }
}

void TableModel::refreshAlternateColumnColor()
{

    if(!m_rowCount || !m_columnCount)
        return;

    QVector<int> role;
    role.append(Qt::BackgroundRole);

    for(int row=0; row<m_rowCount; row++)
    {
        for(int column=1; column < m_columnCount; column+=2)
        {
            if (m_useColumnAltColor)
                setData(index(row,column), QVariant(m_altColumnColor.name()), Qt::BackgroundRole);
        }
    }
}

void TableModel::refreshAlternateRowColor()
{
    if(!m_rowCount || !m_columnCount)
        return;

    QVector<int> role;
    role.append(Qt::BackgroundRole);

    for(int row=1; row < m_rowCount; row+=2)
    {
        for(int column=0; column < m_columnCount; column++)
        {
            if (m_useRowAltColor)
                setData(index(row,column), QVariant(m_altRowColor.name()), Qt::BackgroundRole);
        }
    }
}

// --------------------------------------- !!! DATA !!! ---------------------------------------

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        qCritical() << "TableModel::data() Index is invalid for role " << role << " !";
        return QVariant();
    }

    if(index.row() < 0 )
    {
        qCritical() << "TableModel::data() Row index negative !";
        return QVariant();
    }

    switch (role)
    {
        case  Qt::DisplayRole:
        case  Qt::EditRole:
            if(index.row() >= m_data.size() )
            {
                qCritical() << "TableModel::data() Row index for data out of range !";
                return QVariant();
            }
            else
                return m_data[index.row()][index.column()];

        case Qt::TextAlignmentRole:
            // TODO To be improved
            return Qt::AlignCenter;

        case Qt::BackgroundRole:
            if(index.row() >= m_bkgColors.size() )
            {
                qCritical() << "TableModel::data() Row index for background colors out of range !";
                return QVariant();
            }
            else
                return QBrush(m_bkgColors.at(index.row()).at(index.column()));

        case Qt::ForegroundRole:
            if(index.row() >= m_foregroundColors.size() )
            {
                qCritical() << "TableModel::data() Row index for foreground colors out of range !";
                return QVariant();
            }
            else
                return QBrush(m_foregroundColors.at(index.row()).at(index.column()));

        case Qt::ToolTipRole:
            return "";

        default:
            return QVariant();
    }

    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) {
        return false;
    }

    bool somethingChanged = false;
    QVector<int> roleChanged ;

    switch (role)
    {
        case Qt::DisplayRole:
            roleChanged.append(Qt::DisplayRole);
        case Qt::EditRole:
        {
            m_data[index.row()][index.column()] = value.toString();

            somethingChanged = true;
            roleChanged.append(Qt::EditRole);
        }
            break;

        //Bkg color
        case Qt::BackgroundRole:
        {
            if(m_useFirstColumnColor && index.column() == 0)
            {
                // Add only the value to the first column color
                QColor bkgColor = QColor(value.toString());
                bkgColor.setHsv(bkgColor.hue(),bkgColor.saturation(), m_firstColumnBkgColor.value());
                m_bkgColors[index.row()][index.column()] = bkgColor;
            }
            else if(m_useColumnAltColor && index.column()!=0 && (index.column()+1)%2 == 0)
            {
                m_bkgColors[index.row()][index.column()] = m_altColumnColor;
            }
            else if(m_useRowAltColor && (index.row()+1)%2 == 0)
            {
                m_bkgColors[index.row()][index.column()] = m_altRowColor;
            }
            else
                m_bkgColors[index.row()][index.column()] = QColor(value.toString());

            roleChanged.append(Qt::BackgroundRole);
            somethingChanged = true;
        }
            break;

        // Text color
        case Qt::ForegroundRole:
        {
            m_foregroundColors[index.row()][index.column()] =  QColor(value.toString());
            roleChanged.append(Qt::ForegroundRole);
            somethingChanged = true;
        }
            break;

        default:
            return false;
    }

    if(somethingChanged)
    {
        emit dataChanged(index,index,roleChanged);
        return true;
    }

    return false;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role)
    {
        case  Qt::DisplayRole:

            if (orientation == Qt::Horizontal)
            {
                if( section < m_horizontalHeaderLabels.size())
                    return m_horizontalHeaderLabels.at(section);
                else
                    qCritical() << "TableModel::headerData() Horizontal Header Data DisplayRole -> Section out of range!";
            }
            else if (orientation == Qt::Vertical)
            {
                if( section < m_verticalHeaderLabels.size())
                    return m_verticalHeaderLabels.at(section);
                else
                    qCritical() << "TableModel::headerData() Vertical Header Data DisplayRole -> Section out of range!";
            }
        break;

        case Qt::TextAlignmentRole:
            return Qt::AlignCenter;

        case Qt::BackgroundRole:
            if (orientation == Qt::Horizontal)
            {
                if( section < m_horizontalHeaderLabels.size())
                    return QBrush(m_horizontalHeaderBkgColor);
                else
                    qCritical() << "TableModel::headerData() Horizontal Header Data BackgroundRole -> Section out of range!";
            }
            else if (orientation == Qt::Vertical)
            {
                if( section < m_verticalHeaderLabels.size())
                    return QBrush(m_verticalHeaderBkgColor);
                else
                    qCritical() << "TableModel::headerData() Vertical Header Data BackgroundRole -> Section out of range!";
            }

        case Qt::ForegroundRole:
            return QBrush(m_headerForegroundColor);

        default:
            return QVariant();
    }

    return QVariant();
}

bool TableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    bool somethingChanged = false;

    if (role == Qt::DisplayRole)
    {
        switch (orientation)
        {
            case  Qt::Horizontal:
                m_horizontalHeaderLabels.insert(section, value.toString());
                somethingChanged = true;
            break;

            case Qt::Vertical:
                m_verticalHeaderLabels.insert(section, value.toString());
                somethingChanged = true;
            break;

            default:;
        }
    }

    if (role == Qt::BackgroundRole)
    {
        switch (orientation)
        {
            case  Qt::Horizontal:
                m_horizontalHeaderBkgColor = QColor(value.toString());
                somethingChanged = true;
            break;

            case Qt::Vertical:
                m_verticalHeaderBkgColor = QColor(value.toString());
                somethingChanged = true;
            break;

            default:;
        }
    }

    if (role == Qt::ForegroundRole)
    {
        m_headerForegroundColor = QColor(value.toString());
        somethingChanged = true;
    }

    if (somethingChanged)
    {
        emit headerDataChanged(orientation, section, section);
        return true;
    }

    return false;
}

// --------------------------------------- FLAGS ETC ---------------------------------------

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QAbstractItemModel::flags(index);
    }
    //return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    //return Qt::NoItemFlags;
    return Qt::NoItemFlags | Qt::ItemIsEditable;
}

bool TableModel::hasChildren(const QModelIndex &parent) const
{
    if(parent.column() == 0)
        return  false;

    return true;
}

void TableModel::debugBkgColors(int row, QString msg)
{
    qDebug() << msg;

    QString colors;

    for(int column=0; column < m_columnCount; column++)
    {
        colors+= m_bkgColors[row][column].name() + "  ";
    }

    qDebug() << colors;
}
