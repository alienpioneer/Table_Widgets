#include "MainWindow.h"
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


    QTableView* tableView = new QTableView(this);
    {
//    table->setStyleSheet("QTableView {border: 1px solid #666;gridline-color: #DDD;qproperty-iconSize: 48px 48px;} "\
//                         "QTableView QHeaderView::section:horizontal{ border-left: 1px solid #AAA; border-top:none; } "\
//                         "QTableView QHeaderView::section:horizontal:last  { border-right: none; } "\
//                         "QScrollBar {background-color: #D8D8D8;border:none; } "\
//                         "QScrollBar::handle {border: 1px solid #999;border-bottom-color: #666;border-right-color:#666;border-radius: 4px;"\
//                         "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #E4E4E4, stop:0.5 #D9D9D9, stop:0.501 #D3D3D3 }");
        tableView->setStyleSheet("QTableView QHeaderView { color: white;qproperty-highlightSections: false; }\
                                  QTableView QHeaderView::section {padding: 0 4px; background-color: #999;  border: 1px solid #777;}\
                                  QTableView QHeaderView::section:horizontal { height:28px;border-left:1px solid #AAA; border-top:none; }\
                                  QTableView QHeaderView::section:horizontal:last { border-right: none; }\
                                  QTableView QHeaderView::section:vertical { border-top: 1px solid #AAA; border-left:none; }\
                                  QTableView QHeaderView::section:vertical:last  { border-bottom: none; }");

        tableWidget->layout()->addWidget(tableView);

        tableView->setSelectionMode( QAbstractItemView::NoSelection );
        tableView->setEditTriggers( QAbstractItemView::NoEditTriggers );

        tableView->verticalHeader()->hide();
        //table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        //table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->horizontalHeader()->setSectionsClickable(false);
        tableView->horizontalHeader()->setDefaultAlignment( Qt::AlignCenter | Qt::AlignVCenter );
        tableView->setSizeAdjustPolicy( QAbstractScrollArea::AdjustToContents );

        TableModel* model = new TableModel(this);
        tableView->setModel(model);

        // Call these functions directly on the custom the model
        // The table->model() will return an abstract model
        model->setHeaderLabels(std::move(headers), Qt::Horizontal);
        model->setAltColumnColor(QColor(250,232,122));
        model->useAltColumnColor(true);
        model->useFirstColumnColor(true);

        auto t0 = std::chrono::high_resolution_clock::now();

        model->insertRows(0,2000, QModelIndex());
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

        //model->clearTable();

        // Set the colors at the beggining
        //model->setFirstColumnColor(QColor(0,255,0));
        //model->setAltColumnColor(QColor(0,0,255));
        //model->useAltColumnColor(false);
        //model->useFirstColumnColor(false);

    }

//    QTableWidget* table = new QTableWidget(this);
//    tableWidget->layout()->addWidget(table);
//    table->setStyleSheet("QTableView {border: 1px solid #666;gridline-color: #DDD;qproperty-iconSize: 48px 48px;} "\
//                         "QTableView QHeaderView::section:horizontal{ border-left: 1px solid #AAA; border-top:none; } "\
//                         "QTableView QHeaderView::section:horizontal:last  { border-right: none; } "\
//                         "QScrollBar {background-color: #D8D8D8;border:none; } ");
////                         "QScrollBar:handle {border: 1px solid #999;border-bottom-color: #666;\
////                                             border-right-color:#666;border-radius: 4px; \
////                                             background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #E4E4E4, stop:0.5 #D9D9D9, stop:0.501 #D3D3D3); }");

//    table->setSelectionBehavior( QAbstractItemView::SelectRows );
//    table->setSelectionMode( QAbstractItemView::NoSelection );   // lignes sélectionables
//    table->setEditTriggers( QAbstractItemView::NoEditTriggers ); // lignes non éditables
//    table->verticalHeader()->hide();
//    table->horizontalHeader()->setDefaultAlignment( Qt::AlignLeft | Qt::AlignVCenter );
//    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    table->setSizeAdjustPolicy( QAbstractScrollArea::AdjustToContents ); // s'ajuste au contenu en largeur
//    table->setColumnCount( 4);
//    table->setHorizontalHeaderLabels( headers );

//    table->setRowCount( 2000 );

//    for( int i =0; i < 2000; i++ )
//    {
//        for( int j =0; j < 4; j++ )
//        {
//             table->setItem( i, j, new QTableWidgetItem( QString::number(i) ) );
//             table->item(i,j)->setBackground(QBrush(QColor(255,123,124)));
//        }
//    }

//    auto t0 = std::chrono::high_resolution_clock::now();

//    for( int i =2000; i < 3000; i++ )
//    {
//        table->insertRow(i);

//        for( int j =0; j < 4; j++ )
//        {
//             table->setItem( i, j, new QTableWidgetItem( QString::number(i) ) );
//             table->item(i,j)->setBackground(QBrush(QColor(255,123,124)));
//        }
//    }

//    auto t1 = std::chrono::high_resolution_clock::now();
//    qDebug() << "Table Updates took" <<  std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " ms" ;

}

MainWindow::~MainWindow()
{
}
