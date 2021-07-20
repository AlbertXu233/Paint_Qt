#ifndef PAINTATTRIBUTEDIALOG_H
#define PAINTATTRIBUTEDIALOG_H

#include <QDialog>

namespace Ui {
class paintAttributeDialog;
}
namespace Attribute {
enum sizeType{
    pix=0,
    cm=1,
    inch=2
};
}
class paintAttributeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit paintAttributeDialog(QWidget *parent = nullptr);
    ~paintAttributeDialog();
    void setRecentMessage(QString str,int size);
    bool getBw() const;
    QSize getSize();
    Attribute::sizeType getSt() const;

private slots:

    void on_buttonBox_accepted();

    void on_btnInch_clicked();

    void on_btnCm_clicked();

    void on_btnPix_clicked();

    void on_btnBla_clicked();

    void on_btnWhi_clicked();

private:
    Ui::paintAttributeDialog *ui;
    bool bw=0;
    Attribute::sizeType st=Attribute::pix;
};

#endif // PAINTATTRIBUTEDIALOG_H
