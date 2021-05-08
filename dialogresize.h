#ifndef DIALOGRESIZE_H
#define DIALOGRESIZE_H

#include <QDialog>

namespace Ui {
    class dialogResize;
}

class dialogResize : public QDialog
{
    Q_OBJECT
public:
    dialogResize(QWidget *parent = nullptr);
    void setSceneWidth(int value);

    void setSceneHeight(int value);

    bool radioBtnState();

    int getSceneWidth() const;

    int getSceneHeight() const;

    int getVerticalRotate() const;

    int getHorizonRotate() const;
private slots:
    void on_rbtnPixel_clicked();

    void on_rbtnPercent_clicked();

    void on_buttonBox_accepted();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

private:
    Ui::dialogResize *ui;
    int sceneWidth;
    int sceneHeight;
};

#endif // DIALOGRESIZE_H
