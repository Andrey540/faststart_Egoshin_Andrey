#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "statstablemodel.h"
#include "statsdocument.h"
#include "insertrowdialog.h"
#include "aboutdialog.h"
#include "savechangesdialog.h"
#include <QTableView>
#include <QDebug>
#include <unordered_set>
#include <QMessageBox>
#include <QResizeEvent>
#include <QPainter>
#include <QMatrix>
#include <QTimer>
#include <QTime>
#include "insertcommand.h"
#include "deletecommand.h"
#include "editcommand.h"

static const qreal M_PI = 3.14159265358979323846;

const int RADIUS = 100;
const int RADIUS_LABEL = 130;
const int CENTER_CHART_X = 650 + RADIUS;
const int CENTER_CHART_Y = 150 + RADIUS;
const int CHART_X_3D = 650;
const int CHART_Y_3D = 150;
const int CHART_HEIGHT = 20;
const int ROTATION_SPEED = 50;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_chartColors.push_back(Qt::red);
    m_chartColors.push_back(Qt::green);
    m_chartColors.push_back(Qt::blue);
    m_chartColors.push_back(Qt::cyan);
    m_chartColors.push_back(Qt::magenta);
    m_chartColors.push_back(Qt::yellow);

    setMouseTracking(true);

    m_tableModel = std::make_shared<StatsTableModel>();
    m_proxyModel =  new QSortFilterProxyModel(this);
    connect(m_proxyModel, SIGNAL(layoutChanged()), this, SLOT(onModelChanged()));

    m_proxyModel->setSourceModel(m_tableModel.get());
    m_ui->tableData->setModel(m_proxyModel);
    m_ui->tableData->setAlternatingRowColors(true);
    m_ui->tableData->setSortingEnabled(true);

    m_ui->newDocument->setShortcut(QKeySequence(QKeySequence::New));
    m_ui->openDocument->setShortcut(QKeySequence(QKeySequence::Open));
    m_ui->saveDocument->setShortcut(QKeySequence(QKeySequence::Save));
    m_ui->saveDocumentAs->setShortcut(QKeySequence(QKeySequence::SaveAs));

    m_document.reset(new StatsDocument(this, *m_tableModel));
    m_commandStack.reset(new QUndoStack());
    connect(m_tableModel.get(), SIGNAL(rowChanged(int, QString, int)), this, SLOT(onRowChanged(int, QString, int)));

    m_time = std::make_shared<QTime>();
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onRotate()));
    m_timer->start(50);
    m_time->start();
}

MainWindow::~MainWindow()
{    
    delete m_ui;
}

void MainWindow::on_newDocument_triggered()
{
    saveNotSavedDocumentChanges();
    if (!m_actionCanceled)
    {
        m_document->createNew();
    }
}

void MainWindow::on_saveDocument_triggered()
{
    m_document->save();
}

void MainWindow::on_openDocument_triggered()
{
    saveNotSavedDocumentChanges();
    if (!m_actionCanceled)
    {
        m_document->open();
    }
}

void MainWindow::on_saveDocumentAs_triggered()
{
    m_document->saveAs();
}

void MainWindow::on_showTable_triggered()
{
}

void MainWindow::on_showDiagram_triggered()
{
}

void MainWindow::on_actionAbout_triggered()
{
    std::unique_ptr<AboutDialog> dialog(new AboutDialog(this));
    dialog->exec();
}

void MainWindow::on_actionInsertRow_triggered()
{
    std::unique_ptr<InsertRowDialog> dialog(new InsertRowDialog(this));
    connect(dialog.get(), SIGNAL(rowReady(QString, int)), this, SLOT(onRowReady(QString, int)));
    dialog->exec();
}

void MainWindow::onRowReady(QString text, int value)
{
    m_commandStack->push(new InsertCommand(m_tableModel, text, value));
}

void MainWindow::onModelChanged()
{
    update();
}

void MainWindow::on_actionDeleteRow_triggered()
{
    std::set<int> deletedRows;
    for (const auto &index : m_ui->tableData->selectedTableIndexes())
    {
        auto proxyItem = m_proxyModel->mapToSource(index);
        deletedRows.insert(proxyItem.row());
    }

    auto statsModel = m_tableModel->statsModel();
    for (int i = statsModel.size() - 1; i >= 0; --i)
    {
        if (deletedRows.count(i))
        {
            m_commandStack->push(new DeleteCommand(m_tableModel, i));
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
 {
     saveNotSavedDocumentChanges();
     if (!m_actionCanceled)
     {
        event->setAccepted(true);
     }
     else
     {
         event->setAccepted(false);
     }
 }

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QRect tableArea = QRect(QPoint(0, 0), event->size());
    m_ui->tableData->setGeometry(tableArea);
}

void MainWindow::saveNotSavedDocumentChanges()
{
    if (m_document->isModelChanged())
    {
        m_actionCanceled = false;
        std::unique_ptr<SaveChangesDialog> dialog(new SaveChangesDialog(this));
        connect(dialog.get(), SIGNAL(doSave(bool)), this, SLOT(onDoSave(bool)));
        connect(dialog.get(), SIGNAL(doCancel()), this, SLOT(onDoCancel()));
        dialog->exec();
    }
}

void MainWindow::onRowChanged(int index, QString text, int value)
{
    m_commandStack->push(new EditCommand(m_tableModel, index, text, value));
}

void MainWindow::onDoSave(bool needSave)
{
    if (needSave)
    {
        m_document->save();
    }
}

void MainWindow::onDoCancel()
{
    m_actionCanceled = true;
}

void MainWindow::on_actionUndo_triggered()
{
    m_commandStack->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    m_commandStack->redo();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    paintChart(painter);    
}

void MainWindow::paintChart(QPainter &painter)
{
    auto statsModel = m_tableModel->statsModel();
    int sum = 0;
    for (size_t i = 0, n = statsModel.size(); i < n; ++i)
    {
        sum += statsModel.value(i);
    }
    int position = 0;
    for (size_t i = 0, n = statsModel.size(); i < n; ++i)
    {
        QColor color = m_chartColors[i % m_chartColors.size()];
        paintChartSegment(painter, sum, position, statsModel.value(i), color);
        position += statsModel.value(i);
    }
}

void MainWindow::paintChartSegment(QPainter &painter, int sum, int position, int value, QColor color)
{
    QRectF rectangle(CENTER_CHART_X - RADIUS, CENTER_CHART_Y - RADIUS * cos(60 * M_PI / 180), RADIUS * 2, cos(60 * M_PI / 180) * RADIUS * 2);
    int startAngle = calcAngel(sum, position) + m_angle;
    int spanAngle = calcAngel(sum, value);

    if (m_angle >= startAngle && m_angle < startAngle + spanAngle)
    {
        color = color.light();
    }

    addBottomPart(painter, startAngle, spanAngle, color);

    painter.setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(color, Qt::SolidPattern));
    painter.drawPie(rectangle, startAngle * 16, spanAngle * 16);    
}

void MainWindow::addBottomPart(QPainter &painter, int startAngle, int spanAngle, QColor color)
{
    startAngle = startAngle % 360;
    if ((startAngle < 180) && (startAngle + spanAngle < 180))
    {
        return;
    }
    if (startAngle < 180)
    {
        spanAngle = spanAngle - (180 - startAngle);
        startAngle = 180;
    }
    if (startAngle + spanAngle > 360)
    {
        if (startAngle + spanAngle > 540)
        {
            addBottomPart(painter, 180, (startAngle + spanAngle) % 360 - 180, color);
        }
        spanAngle = 360 - startAngle;
    }

    startAngle = (startAngle < 180) ? 180 : startAngle;
    QRectF rectangle(CENTER_CHART_X - RADIUS, CENTER_CHART_Y - RADIUS * cos(60 * M_PI / 180), RADIUS * 2, cos(60 * M_PI / 180) * RADIUS * 2);
    QRectF rectangleBottom(CENTER_CHART_X - RADIUS, CENTER_CHART_Y - RADIUS * cos(60 * M_PI / 180) + CHART_HEIGHT, RADIUS * 2, cos(60 * M_PI / 180) * RADIUS * 2);
    painter.setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(color, Qt::SolidPattern));

    QPainterPath path;

    int x = RADIUS * cos((startAngle + spanAngle) * M_PI / 180) + CENTER_CHART_X;
    int y = -1 * RADIUS * cos(60 * M_PI / 180) * sin((startAngle + spanAngle) * M_PI / 180) + CENTER_CHART_Y;
    int x1 = RADIUS * cos(startAngle * M_PI / 180) + CENTER_CHART_X;
    int y1 = -1 * RADIUS * cos(60 * M_PI / 180) * sin((startAngle) * M_PI / 180) + CENTER_CHART_Y + CHART_HEIGHT;

    path.moveTo(x, y);
    path.arcTo(rectangle, startAngle + spanAngle, -spanAngle);
    path.lineTo(x1, y1);

    path.arcTo(rectangleBottom, startAngle, spanAngle);
    path.lineTo(x, y );

    painter.drawPath(path);
}

void MainWindow::onRotate(){
    m_angle = (m_time->elapsed() / ROTATION_SPEED) % 360;
    update();
}

int MainWindow::calcAngel(int sum, int position)
{
    return (float)position / sum * 360;
}
