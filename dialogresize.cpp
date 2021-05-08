#include "dialogresize.h"
#include "ui_dialogresize.h"
#include <qdebug.h>

dialogResize::dialogResize(QWidget *parent):
    QDialog (parent),
    ui(new Ui::dialogResize)
{
    ui->setupUi(this);
}

void dialogResize::on_rbtnPixel_clicked()
{
    ui->rbtnPercent->setChecked(false);
    ui->lineEdit->setText(QString::number(sceneWidth));
    ui->lineEdit_2->setText(QString::number(sceneHeight));
    ui->lineEdit_3->setText("0");
    ui->lineEdit_4->setText("0");
}

void dialogResize::on_rbtnPercent_clicked()
{
    ui->rbtnPixel->setChecked(false);
    ui->lineEdit->setText("100");
    ui->lineEdit_2->setText("100");
    ui->lineEdit_3->setText("0");
    ui->lineEdit_4->setText("0");
}

int dialogResize::getSceneHeight() const
{
    return sceneHeight;
}

int dialogResize::getVerticalRotate() const
{
    return ui->lineEdit_3->text().toInt();
}

int dialogResize::getHorizonRotate() const
{
    return  ui->lineEdit_4->text().toInt();
}

int dialogResize::getSceneWidth() const
{
    return sceneWidth;
}

void dialogResize::setSceneHeight(int value)
{
    sceneHeight = value;
}

bool dialogResize::radioBtnState()
{
    if (ui->rbtnPercent->isChecked()){
        return true;
    }else {
        return false;
    }
}

void dialogResize::setSceneWidth(int value)
{
    sceneWidth = value;
}

void dialogResize::on_buttonBox_accepted()
{
    sceneWidth=ui->lineEdit->text().toInt();
    sceneHeight=ui->lineEdit_2->text().toInt();
}

void dialogResize::on_lineEdit_textEdited(const QString &arg1)
{
    if (ui->checkBox->isChecked()){
        if (radioBtnState()){
            ui->lineEdit_2->setText(arg1);
        }else {
            qreal value=sceneHeight*arg1.toInt()/qreal(sceneWidth);
            ui->lineEdit_2->setText(QString::number(int(value)));
        }
    }
}

void dialogResize::on_lineEdit_2_textEdited(const QString &arg1)
{
    if (ui->checkBox->isChecked()){
        if (radioBtnState()){
        ui->lineEdit->setText(arg1);
        }else {
            qDebug()<<arg1;
            qreal value=sceneWidth*arg1.toInt()/qreal(sceneHeight);
            ui->lineEdit->setText(QString::number(int(value)));
        }
    }
}
