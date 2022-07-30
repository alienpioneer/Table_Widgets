#include "TableModel.h"
#include <QBrush>
#include <QDebug>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent),
      m_rowCount(0),
      m_columnCount(0),
      m_useColumnAltColor(false),
      m_useFirstColumnColor(false),
      m_defaultBkgColor(QColor(255, 255, 255)),
      m_foregroundColor(QColor(0, 0, 0)),
      m_altColumnColor(QColor(250, 233, 163)),
      m_headerBkgColor(QColor(152, 152, 152)),
      m_firstColumnBkgColor(QColor(237, 237, 237))
{
}


bool TableModel::setCellData(int row, int column,const QString data)
{
    return setData(index(row,column), data, Qt::DisplayRole);
}


bool TableModel::setCellColor(int row, int column,const QColor color)
{
    return setData(index(row,column), QVariant(color.name()), Qt::BackgroundRole);
}


bool TableModel::clear()
{
    if(m_rowCount > 0)
        return  removeRows(0, m_rowCount, QModelIndex());
    else
        return false;
}


// --------------------------------------- HEADER ---------------------------------------
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role)
    {
        case  Qt::DisplayRole:
            if (orientation == Qt::Horizontal)
            {
                if( section < m_headerLabels.size())
                    return m_headerLabels.at(section);
                else
                    qCritical() << "Header Data -> Section out of range!";
            }
        break;

        case Qt::TextAlignmentRole:
            return Qt::AlignCenter;

        case Qt::BackgroundRole:
            return QBrush(m_headerBkgColor);

        case Qt::ForegroundRole:
            return QBrush(m_foregroundColor);

        default:
            return QVariant();
    }

    return QVariant();
}


bool TableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            m_headerLabels.append(value.toString());
            emit headerDataChanged(orientation, section, section);
            return true;
        }
    }

    return false;
}


// Set the list with the header labels
// Using this function will automatically set the number of columns
bool TableModel::setHeaderLabels(const QStringList headerLabels, Qt::Orientation orientation)
{
    bool result = true;

    insertColumns(0, headerLabels.size(), QModelIndex());

    for(int i=0; i < headerLabels.size(); i++)
    {
        result = result && setHeaderData(i, orientation, QObject::tr(headerLabels.at(i).toUtf8()), Qt::DisplayRole);
    }

    return result;
}


// --------------------------------------- ROWS COLUMS ---------------------------------------
int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_rowCount;
}


int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}


// Insert a new row and set data list and color lists for each new row
bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count-1);
    m_rowCount+=count;

    for(int row =0; row<count; row++)
    {
        QList<QColor> bkgColorList;
        QList<QColor> foregroundColorList;
        QStringList   data;

        for(int column=0; column < m_columnCount; column++)
        {
            if (column==0 && m_useFirstColumnColor)
                bkgColorList.append(m_firstColumnBkgColor);
            else if(column!=0 && column%2==0 && m_useColumnAltColor)
                bkgColorList.append(m_altColumnColor);
            else
                bkgColorList.append(m_defaultBkgColor);

            foregroundColorList.append(m_foregroundColor);
            data.append("");
        }

        m_bkgColors.append(bkgColorList);
        m_foregroundColors.append(foregroundColorList);
        m_data.append(data);
    }

    endInsertRows();

    return  true;
}


// CALL Insert columns before insert rows !!!
bool TableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column+count-1);
    m_columnCount+=count;
    endInsertColumns();

    return true;
}


bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count-1);

    for (int i = 0; i < count; ++i) {
        m_data.removeAt(row);
    }

    m_rowCount -= count;
    if (m_rowCount < 0)
    {
        m_rowCount = 0;
        qCritical() << "Row count is negative after remove rows !";
    }
    endRemoveRows();
    return true;
}


// --------------------------------------- !!! DATA !!! ---------------------------------------

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_data.size())
        return QVariant();

    switch (role)
    {
        case  Qt::DisplayRole:
        case  Qt::EditRole:
            return m_data[index.row()][index.column()];
        break;

        case Qt::TextAlignmentRole:
            return Qt::AlignCenter;

        case Qt::BackgroundRole:
            return QBrush(m_bkgColors.at(index.row()).at(index.column()));

        case Qt::ForegroundRole:
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

    switch (role)
    {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
            m_data[index.row()][index.column()] = value.toString();

            somethingChanged = true;
        }
            break;


        case Qt::BackgroundRole:
        {
            if(m_useFirstColumnColor && index.column() == 0)
            {
                QColor bkgColor = QColor(value.toString());
                bkgColor.setHsv(bkgColor.hue(),bkgColor.saturation(), m_firstColumnBkgColor.value());
                m_bkgColors[index.row()][index.column()] = bkgColor;
            }
            else
                m_bkgColors[index.row()][index.column()] = QColor(value.toString());

            somethingChanged = true;
        }
            break;


        case Qt::ForegroundRole:
        {
            m_foregroundColors[index.row()][index.column()] =  QColor(value.toString());
            somethingChanged = true;
        }
            break;

        default:
            return false;
    }

    if(somethingChanged){
        emit dataChanged(index,index);
        return true;
    }

    return false;
}


// --------------------------------------- COLORS ---------------------------------------
void TableModel::useAltColumnColor(bool state)
{
    m_useColumnAltColor = state;

    if(!m_rowCount && !m_columnCount)
        return;

    refreshAltColumnColor();
}


void TableModel::setAltColumnColor(const QColor color)
{
    m_altColumnColor = color;

    if(!m_rowCount && !m_columnCount)
        return;

    refreshAltColumnColor();
}


void TableModel::useFirstColumnColor(bool state)
{
    m_useFirstColumnColor = state;

    if(!m_rowCount && !m_columnCount)
        return;

    refreshFirstColumnColor();
}


void TableModel::setFirstColumnColor(const QColor color)
{
    m_firstColumnBkgColor = color;

    if(!m_rowCount && !m_columnCount)
        return;

    refreshFirstColumnColor();
}


void TableModel::refreshFirstColumnColor()
{
    for(int row =0; row<m_rowCount; row++)
    {
        if (m_useFirstColumnColor)
            m_bkgColors[row][0] = m_firstColumnBkgColor;
        else
            m_bkgColors[row][0] = m_defaultBkgColor;
        //emit dataChanged(index(row,column),index(row,column));
    }
}


void TableModel::refreshAltColumnColor()
{
    for(int row=0; row<m_rowCount; row++)
    {
        for(int column=2; column < m_columnCount; column++)
        {
            if( column%2 ==0)
            {
                if (m_useColumnAltColor)
                    m_bkgColors[row][column] = m_altColumnColor;
                else
                    m_bkgColors[row][column] = m_defaultBkgColor;
                //emit dataChanged(index(row,column),index(row,column));
            }
        }
    }
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
