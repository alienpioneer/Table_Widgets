#include "MainWindow.h"
#include "TableModel.h"
#include "ProxyModel.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(QRect(0, 0, 600, 400));

    QWidget* tableWidget = new QWidget(this);
    tableWidget->setLayout(new QHBoxLayout());
    tableWidget->setGeometry(50,50,500,300);
    tableWidget->layout()->setMargin(0);
    tableWidget->layout()->setSpacing(0);

    QList<QString> headers = { "A", "B", "C", "D"};

///---------------------------------------------------- TABLE VIEW ---------------------------------------------------------

    QTableView* tableView = new QTableView(this);
    {
    //tableView->setStyleSheet("QTableView QHeaderView { color: white;qproperty-highlightSections: false; }\
    //                         QTableView QHeaderView::section {padding: 0 4px; background-color: #999;  border: 1px solid #777;}\
    //                         QTableView QHeaderView::section:horizontal { height:28px;border-left:1px solid #AAA; border-top:none; }\
    //                         QTableView QHeaderView::section:horizontal:last { border-right: none; }\
    //                         QTableView QHeaderView::section:vertical { border-top: 1px solid #AAA; border-left:none; }\
    //                         QTableView QHeaderView::section:vertical:last  { border-bottom: none; }\
    //                         QScrollBar {background-color: #D8D8D8;border:none; } \
    //                         QScrollBar::handle {border: 1px solid #999;border-bottom-color: #666;border-right-color:#666;border-radius: 4px;\
    //                                             background: url(qrc:/scrollbar_handle.png) center center no-repeat; \
    //                                             background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #E4E4E4, stop:0.5 #D9D9D9, stop:0.501 #D3D3D3)}");

    //tableView->setStyleSheet("QTableView QHeaderView::section {padding: 0 4px; background-color: #999;  border: 1px solid #777; }\
    //                          QTableView QHeaderView::section:horizontal { height:28px;border-left:1px solid #AAA; border-top:none; }\
    //                          QTableView QHeaderView::section:horizontal:last { border-right: none; }");

    tableWidget->layout()->addWidget(tableView);

    tableView->setSelectionMode( QAbstractItemView::NoSelection );
    tableView->setEditTriggers( QAbstractItemView::NoEditTriggers );

    //tableView->verticalHeader()->hide();
    //table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // All Equal
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionsClickable(false);
    tableView->verticalHeader()->setSectionsClickable(false);
    tableView->horizontalHeader()->setDefaultAlignment( Qt::AlignCenter | Qt::AlignVCenter );
    tableView->setSizeAdjustPolicy( QAbstractScrollArea::AdjustToContents );
    }

    TableModel* model = new TableModel(this);
    ProxyModel* proxy = new ProxyModel(this);

    proxy->setSourceModel(model);
    tableView->setModel(proxy);


    // Call these functions directly on the custom the model
    // The table->model() will return an abstract model
    model->setHeaderLabels(headers, Qt::Horizontal);

    // Test Header Color - Not Working ?
    if(false)
    {
         model->setHorizontalHeaderBkgColor(QColor(166,50,60));
    }

    if(false)
    {
        model->setAlternateColumnColor(QColor(250,232,122));
        model->useAlternateColumnColor(true);
    }

    if(false)
    {
        model->setAlternateRowColor(QColor(250,120,122));
        model->useAlternateRowColor(true);
    }

    if(true)
    {
        model->setFirstColumnColor(QColor(250,232,122));
        model->useFirstColumnColor(true);
    }

    // Insert Rows
    if(true)
    {
        model->insertRows(0,10);

        for( int i =0; i < model->rowCount(); i++ )
        {
            for( int j =0; j < model->columnCount(); j++ )
            {
                model->setCellData(i,j,QString::number(i)+QString::number(j));
            }
        }
    }

    // Insert Columns
    if(true)
    {
        model->insertColumns(1,2);
        model->replaceHorizontalHeaderLabels(1,2,{"E","F"});
    }

    // Test first column color
    if(false)
    {
        for( int i =0; i < model->rowCount(); i++ )
        {
            for( int j =0; j < model->columnCount(); j++ )
            {
                if (i == 2 || i == 3)
                {
                    model->setCellColor(i,0,QColor(250,120,30));
                    model->setCellColor(i,2,QColor(250,120,30));
                    model->setCellColor(i,3,QColor(250,120,30));
                }
            }
        }
    }

    if(false)
    {
        model->removeRows(1,3);
    }

    if(false)
    {
        model->removeColumns(1,1);
        model->removeColumns(3,1);
    }

    // Test  SetItemData
    if(false)
    {
        QMap<int, QVariant> roles;
        roles.insert(Qt::ItemDataRole::BackgroundRole,QColor(250,232,122));
        model->setItemData(model->index(1,2),roles);
    }

    // Performance test
    if(false)
    {
        auto t0 = std::chrono::high_resolution_clock::now();

        model->insertRows(0,2000);
        for( int i =0; i < 2000; i++ )
        {
            for( int j =0; j < 4; j++ )
            {
                model->setCellData(i,j,QString::number(i));
                model->setCellColor(i,j,QColor(255,123,124));
            }
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        qDebug() << "Table Updates took" <<  std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " ms" ;
    }

    // Test Clear
    if(false)
    {
        model->clearAllRows();
    }

///---------------------------------------------------- TABLE WIDGET ---------------------------------------------------------

    if (false)
    {
        QTableWidget* table = new QTableWidget(this);
        tableWidget->layout()->addWidget(table);
        table->setStyleSheet("QTableView {border: 1px solid #666;gridline-color: #DDD;qproperty-iconSize: 48px 48px;} "\
                             "QTableView QHeaderView::section:horizontal{ border-left: 1px solid #AAA; border-top:none; } "\
                             "QTableView QHeaderView::section:horizontal:last  { border-right: none; } "\
                             "QScrollBar {background-color: #D8D8D8;border:none; } ");
    //                         "QScrollBar:handle {border: 1px solid #999;border-bottom-color: #666;\
    //                                             border-right-color:#666;border-radius: 4px; \
    //                                             background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #E4E4E4, stop:0.5 #D9D9D9, stop:0.501 #D3D3D3); }");

        table->setSelectionBehavior( QAbstractItemView::SelectRows );
        table->setSelectionMode( QAbstractItemView::NoSelection );   // lignes sélectionables
        table->setEditTriggers( QAbstractItemView::NoEditTriggers ); // lignes non éditables
        table->verticalHeader()->hide();
        table->setFocusPolicy(Qt::NoFocus);
        table->horizontalHeader()->setDefaultAlignment( Qt::AlignLeft | Qt::AlignVCenter );
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->setSizeAdjustPolicy( QAbstractScrollArea::AdjustToContents ); // s'ajuste au contenu en largeur
        table->setColumnCount( 4);
        table->setHorizontalHeaderLabels( headers );

        table->setRowCount( 2000 );

        for( int i =0; i < 2000; i++ )
        {
            for( int j =0; j < 4; j++ )
            {
                 table->setItem( i, j, new QTableWidgetItem( QString::number(i) ) );
                 table->item(i,j)->setBackground(QBrush(QColor(255,123,124)));
            }
        }

        auto t0 = std::chrono::high_resolution_clock::now();

        for( int i =2000; i < 3000; i++ )
        {
            table->insertRow(i);

            for( int j =0; j < 4; j++ )
            {
                 table->setItem( i, j, new QTableWidgetItem( QString::number(i) ) );
                 table->item(i,j)->setBackground(QBrush(QColor(255,123,124)));
            }
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        qDebug() << "Table Updates took" <<  std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " ms" ;
    }

}

MainWindow::~MainWindow()
{
}
