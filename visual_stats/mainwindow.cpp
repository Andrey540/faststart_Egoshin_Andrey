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
#include "insertcommand.h"
#include "deletecommand.h"

static const qreal M_PI = 3.14159265358979323846;

const int RADIUS = 100;
const int RADIUS_LABEL = 130;
const int CENTER_CHART_X = 650 + RADIUS;
const int CENTER_CHART_Y = 150 + RADIUS;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_chartColors.push_back(Qt::gray);
    m_chartColors.push_back(Qt::red);
    m_chartColors.push_back(Qt::green);
    m_chartColors.push_back(Qt::blue);
    m_chartColors.push_back(Qt::cyan);
    m_chartColors.push_back(Qt::magenta);
    m_chartColors.push_back(Qt::yellow);

    m_angle = -1;

    setMouseTracking(true);

    m_tableModel = std::make_shared<StatsTableModel>();
    m_proxyModel = std::make_shared<QSortFilterProxyModel>(new QSortFilterProxyModel(this));
    connect(m_proxyModel.get(), SIGNAL(layoutChanged()), this, SLOT(onModelChanged()));

    m_proxyModel->setSourceModel(m_tableModel.get());
    m_ui->tableData->setModel(m_proxyModel.get());
    m_ui->tableData->setAlternatingRowColors(true);
    m_ui->tableData->setSortingEnabled(true);

    m_ui->newDocument->setShortcut(QKeySequence(QKeySequence::New));
    m_ui->openDocument->setShortcut(QKeySequence(QKeySequence::Open));
    m_ui->saveDocument->setShortcut(QKeySequence(QKeySequence::Save));
    m_ui->saveDocumentAs->setShortcut(QKeySequence(QKeySequence::SaveAs));

    m_document.reset(new StatsDocument(this, *m_tableModel));
    m_commandStack.reset(new QUndoStack());
}

MainWindow::~MainWindow()
{    
    delete m_ui;
}

void MainWindow::on_newDocument_triggered()
{
    saveNotSavedDocumentChanges();
    m_document->createNew();
}

void MainWindow::on_saveDocument_triggered()
{
    m_document->save();
}

void MainWindow::on_openDocument_triggered()
{
    saveNotSavedDocumentChanges();
    m_document->open();
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
     event->accept();
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
        std::unique_ptr<SaveChangesDialog> dialog(new SaveChangesDialog(this));
        connect(dialog.get(), SIGNAL(doSave(bool)), this, SLOT(onDoSave(bool)));
        dialog->exec();
    }
}

void MainWindow::onDoSave(bool needSave)
{
    if (needSave)
    {
        m_document->save();
    }
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

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();

    int dx = x - CENTER_CHART_X;
    int dy = y - CENTER_CHART_Y;

    int angle = atan2(dy, dx) * 180 / M_PI * -1;
    if (angle < 0)
    {
        angle = 360 + angle;
    }

    int xR = RADIUS * cos(angle * M_PI / 180) + CENTER_CHART_X;
    int yR = -1 * RADIUS * sin(angle * M_PI / 180) + CENTER_CHART_Y;

    int prevAngle = m_angle;

    if (angle >= 0 && angle < 90)
    {
        m_angle = ((x >= CENTER_CHART_X && x <= xR) && (y <= CENTER_CHART_Y && y >= yR)) ?
                    angle : -1;
    }
    else if (angle >= 90 && angle < 180)
    {
        m_angle = ((x <= CENTER_CHART_X && x >= xR) && (y <= CENTER_CHART_Y && y >= yR)) ?
                    angle : -1;
    }
    else if (angle >= 180 && angle < 270)
    {
        m_angle = ((x <= CENTER_CHART_X && x >= xR) && (y >= CENTER_CHART_Y && y <= yR)) ?
                    angle : -1;
    }
    else if (angle >= 270 && angle < 360)
    {
        m_angle = ((x >= CENTER_CHART_X && x <= xR) && (y >= CENTER_CHART_Y && y <= yR)) ?
                    angle : -1;
    }

    if ((m_angle > 0) || (prevAngle > 0 && m_angle < 0))
    {
        update();
    }
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
        paintChartSegment(painter, sum, position, statsModel.key(i), statsModel.value(i), color);
        position += statsModel.value(i);
    }
}

void MainWindow::paintChartSegment(QPainter &painter, int sum, int position, const QString& name, int value, QColor color)
{
    QRectF rectangle(CENTER_CHART_X - RADIUS, CENTER_CHART_Y - RADIUS, RADIUS * 2, RADIUS * 2);
    int startAngle = calcAngel(sum, position);
    int spanAngle = calcAngel(sum, value);

    if (m_angle >= startAngle && m_angle < startAngle + spanAngle)
    {
        color = color.light();
    }

    painter.setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(color, Qt::SolidPattern));
    painter.drawPie(rectangle, startAngle * 16, spanAngle * 16);

    QString label = name + ", " + QString::number(100 * value / sum) + "%";
    addLabel(painter, startAngle, startAngle + spanAngle, label);
}

void MainWindow::addLabel(QPainter &painter, int startAngle, int endAngle, const QString& label)
{
    int middleAngel = (startAngle + endAngle) / 2;
    int shift = 30;
    if (middleAngel > 90 && middleAngel < 270)
    {
        shift *= -1;
    }
    int x1 = RADIUS * cos(middleAngel * M_PI / 180) + CENTER_CHART_X;
    int x2 = RADIUS_LABEL * cos(middleAngel * M_PI / 180) + CENTER_CHART_X;
    int y1 = -1 * RADIUS * sin(middleAngel * M_PI / 180) + CENTER_CHART_Y;
    int y2 = -1 * RADIUS_LABEL * sin(middleAngel * M_PI / 180) + CENTER_CHART_Y;

    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(x1, y1, x2, y2);
    painter.drawLine(x2, y2, x2 + shift, y2);
    int xText = (shift > 0) ? x2 : (x2 + shift);
    painter.drawText(xText, y2 - 10, label);
}

int MainWindow::calcAngel(int sum, int position)
{
    return position * 360 / sum;
}
