#include "paintattributedialog.h"
#include "ui_paintattributedialog.h"
#include <qmessagebox.h>
#include <qdebug.h>
#pragma execution_character_set("utf-8")

paintAttributeDialog::paintAttributeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::paintAttributeDialog)
{
    ui->setupUi(this);
}

paintAttributeDialog::~paintAttributeDialog()
{
    delete ui;
}

void paintAttributeDialog::setRecentMessage(QString str,int size)
{
    QString s=QString::number(size/1024.0,'f',1);
    s.append("KB");
    ui->labSize->setText(s);
    ui->labDate->setText(str);
}

void paintAttributeDialog::on_buttonBox_accepted()
{
    if (ui->btnBla->isChecked())
    {
        int i=QMessageBox::warning(this,"画图","转换为黑白图像后将无法撤销。"
                                           "该操作可能会影响当前文件，导致部分信息丢失",
                             QString("确认"),QString("取消"));
        if (!i){
            bw=1;
        }else {
            bw=0;
        }
    }
}

Attribute::sizeType paintAttributeDialog::getSt() const
{
    return st;
}

bool paintAttributeDialog::getBw() const
{
    return bw;
}

QSize paintAttributeDialog::getSize()
{
    return QSize(ui->lineEdit->text().toDouble(),ui->lineEdit_2->text().toDouble());
}

void paintAttributeDialog::on_btnInch_clicked()
{
    qreal w=ui->lineEdit->text().toDouble();
    qreal h=ui->lineEdit_2->text().toDouble();
    if (st==Attribute::pix){
        ui->lineEdit->setText(QString::number(w/120,'f',2));
        ui->lineEdit_2->setText(QString::number(h/120,'f',2));
    }else if(st==Attribute::cm){
        ui->lineEdit->setText(QString::number(w/2.54,'f',2));
        ui->lineEdit_2->setText(QString::number(h/2.54,'f',2));
    }
    st=Attribute::inch;
    ui->btnCm->setChecked(false);
    ui->btnPix->setChecked(false);
}

void paintAttributeDialog::on_btnCm_clicked()
{
    qreal w=ui->lineEdit->text().toDouble();
    qreal h=ui->lineEdit_2->text().toDouble();
    if (st==Attribute::pix){
        ui->lineEdit->setText(QString::number(w/120*2.54,'f',2));
        ui->lineEdit_2->setText(QString::number(h/120*2.54,'f',2));
    }else if(st==Attribute::inch){
        ui->lineEdit->setText(QString::number(w*2.54,'f',2));
        ui->lineEdit_2->setText(QString::number(h*2.54,'f',2));
    }
    st=Attribute::cm;
    ui->btnInch->setChecked(false);
    ui->btnPix->setChecked(false);
}

void paintAttributeDialog::on_btnPix_clicked()
{
    qreal w=ui->lineEdit->text().toDouble();
    qreal h=ui->lineEdit_2->text().toDouble();
    if (st==Attribute::inch){
        ui->lineEdit->setText(QString::number(int(w*120)));
        ui->lineEdit_2->setText(QString::number(int(h*120)));
    }else if(st==Attribute::cm){
        ui->lineEdit->setText(QString::number(int(w/2.54*120)));
        ui->lineEdit_2->setText(QString::number(int(h/2.54*120)));
    }
    st=Attribute::pix;
    ui->btnInch->setChecked(false);
    ui->btnCm->setChecked(false);
}

void paintAttributeDialog::on_btnBla_clicked()
{
    ui->btnWhi->setChecked(false);
}

void paintAttributeDialog::on_btnWhi_clicked()
{
    ui->btnBla->setChecked(false);
}
