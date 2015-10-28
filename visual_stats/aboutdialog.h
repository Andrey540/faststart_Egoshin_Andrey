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
    QTimer *m_timer;
    int m_angle = 0;
    int m_EOffset = 0;
    int m_AOffset = 15;
    int m_COffset = 30;

    void drawLetterE(QPainter& painter);
    void drawLetterA(QPainter& painter);
    void drawLetterC(QPainter& painter);
};

#endif // ABOUTDIALOG_H
