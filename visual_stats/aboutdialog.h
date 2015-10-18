#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <memory>
#include <QDialog>
#include <QTimer>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

    void paintEvent(QPaintEvent *);

private slots:
    void onMove();

private:
    Ui::AboutDialog *ui;
    std::shared_ptr<QTimer> m_timer;
    int m_angel;
    int m_EOffset;
    int m_AOffset;
    int m_COffset;

    void drawLetterE(QPainter& painter);
    void drawLetterA(QPainter& painter);
    void drawLetterC(QPainter& painter);
};

#endif // ABOUTDIALOG_H
