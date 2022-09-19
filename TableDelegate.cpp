#include "TableDelegate.h"

TableDelegate::TableDelegate(QWidget *parent)
    : QItemDelegate{parent}
{

}

QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return nullptr;
}

void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void TableDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}
