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
#include "insertcommand.h"
#include "deletecommand.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_tableModel = std::make_shared<StatsTableModel>();
    m_proxyModel = std::make_shared<QSortFilterProxyModel>(new QSortFilterProxyModel(this));
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
