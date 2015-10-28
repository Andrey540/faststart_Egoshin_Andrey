#pragma once

#include <QMainWindow>
#include <QString>
#include <memory>
#include <QUndoStack>
#include <QSortFilterProxyModel>

namespace Ui {
class MainWindow;
}
class StatsTableModel;
class StatsDocument;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_newDocument_triggered();
    void on_saveDocument_triggered();
    void on_openDocument_triggered();
    void on_saveDocumentAs_triggered();
    void on_showTable_triggered();
    void on_showDiagram_triggered();

    void on_actionAbout_triggered();

    void on_actionInsertRow_triggered();
    void onRowReady(QString text, int value);
    void onDoSave(bool needSave);
    void onDoCancel();
    void onRowChanged(int index, QString text, int value);
    void onModelChanged();
    void onRotate();

    void on_actionDeleteRow_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

private:
    void saveNotSavedDocumentChanges();
    void paintChart(QPainter &painter);
    void paintChart3D(QPainter &painter);
    void paintChartSegment(QPainter &painter, int sum, int position, int value, QColor color);
    void addBottomPart(QPainter &painter, int startAngle, int endAngle, QColor color);
    void addLabel(QPainter &painter, int startAngle, int endAngle, const QString& label);
    int calcAngel(int sum, int position);

    std::unique_ptr<QUndoStack> m_commandStack;
    QSortFilterProxyModel *m_proxyModel;
    Ui::MainWindow *m_ui;
    std::shared_ptr<StatsTableModel> m_tableModel;
    std::unique_ptr<StatsDocument> m_document;    
    std::vector<QColor> m_chartColors;
    std::shared_ptr<QTimer> m_timer;
    int m_angle = 0;
    bool m_actionCanceled;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
};
