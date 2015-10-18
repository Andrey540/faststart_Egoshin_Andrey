#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QPainter>
#include <QTimer>

const int AMPLITUDE = 10;
const int TOP = 70;

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);    

    m_angel = 0;
    m_EOffset = 0;
    m_AOffset = 15;
    m_COffset = 30;

    m_timer = std::make_shared<QTimer>(new QTimer(this));
    connect(m_timer.get(), SIGNAL(timeout()), this, SLOT(onMove()));
    m_timer->start(50);
}

void AboutDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawLetterE(painter);
    drawLetterA(painter);
    drawLetterC(painter);

    m_angel = (m_angel == 359) ? 0 : ++m_angel;
}

void AboutDialog::drawLetterE(QPainter& painter){
    int offset = AMPLITUDE * sin(m_angel +  m_EOffset);
    int top = TOP + offset;
    painter.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawRect(70, top, 50, 15);
    painter.drawRect(70, top, 15, 75);
    painter.drawRect(70, top + 35, 50, 15);
    painter.drawRect(70, top + 70, 50, 15);
}

void AboutDialog::drawLetterA(QPainter& painter){
    int offset = AMPLITUDE * sin(m_angel +  m_AOffset);
    int top = TOP + offset;
    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    QPolygon letterA;
    letterA << QPoint(150, top + 85) << QPoint(185, top) << QPoint(220, top + 85) << QPoint(205, top + 85) <<
               QPoint(185, top + 34) << QPoint(165, top + 85);
    painter.drawPolygon(letterA);
    painter.drawRect(173, top + 50, 25, 15);
}

void AboutDialog::drawLetterC(QPainter& painter){
    int offset = AMPLITUDE * sin(m_angel +  m_COffset);
    int top = TOP + offset;
    painter.setPen(QPen(Qt::yellow, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
    painter.drawRect(250, top, 50, 15);
    painter.drawRect(250, top, 15, 75);
    painter.drawRect(250, top + 70, 50, 15);
}

void AboutDialog::onMove(){
    update();
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
