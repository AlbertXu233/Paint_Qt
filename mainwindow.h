#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "mywidget.h"

#include <QMainWindow>
#include <QWidget>
#include <QPoint>
#include<vector>
#include<qgraphicsscene.h>
#include <QGraphicsView>
#include <qpoint.h>
#include <myitem.h>
#include <gif.h>
#include <qlabel.h>
#include <math.h>

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int i=-1;
    int k=0;
    int lWidth=1;
    int color0;
    int color1;
    int color=color0+color1;
    int c=0;
    int iLast;
    int ListNum=0;
    int funcBrushType=1;
    int bWidth;
//    myWidget *mywidget;
    QPoint startPnt;   //起点
    QPoint endPnt;     //终点
    QPoint sstartPnt;    //按下时的起点
    QPoint eendPnt;    //抬起时的终点
    bool isPressed;    //鼠标是否按下
    bool Tick=false;

    QVector<QPoint> Points;//存放所有的点
    QPolygon pencilLine;
    QVector<QRgb> imgColor;
    QVector<QLine> calliLines;
    QVector<QPoint> airPnts;
    QVector<QPoint> pgPnts;
    QPolygon freeShapeOutline;
    QPolygon freeShapePnts;
    QRect rectOfSel;
    class property itemProperty;

    QImage imgr;
    QImage imgw;
    QPixmap pixr;

    void checkstate(int ii);
    void createSelPopupMenu();
    QGraphicsScene *scene;

    MyItem *mitem;
    MyPathItem *item;
    MyPolylineItem *itemPoly;
    MyLineItem *itemL;
    MyLinesItem *itemLs;
    MyEllipseItem *itemE;
    MyRectItem *itemR;
    MyPolygonItem *itemP;
    MyRoundedItem *itemMR;
    MyEraserItem *itemEraser;
    MyAirBrushItem *itemAirPnts;
    MyPolygonItem *itemPg;
    MyImageItem *itemImage;
    MyRectSelItem *itemRectSel;
    MyFreeShapeSelItem *itemFreeSel;
    myInvertSelItem *itemInSel;

    colorFill *cFill;
    QList<QGraphicsItem*> itemList;
    QList<QGraphicsItem*> itemSel;
    QList<QGraphicsItem*> itemUndo;
    QGraphicsTextItem* itemText;
    qreal rotAngle=0;
    QImage *image;
    QPixmap *pixmap=new QPixmap(QSize(600,600));
    QString filenameSave;

    TextureType pentype=solid;
    TextureType brushtype=none;

    GifWriter mGifWriter;

    QLabel *labelPos;
    QLabel *labelItemSize;
    QLabel *labelSceneSize;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void floodFillu4(int x,int y,QRgb newColor);
    void floodFilld4(int x,int y,QRgb newColor);
    //重载纯虚函数
    void paintEven();
    void paintEvent(QPaintEvent *e);
//    QWidget *widget;
//    QGraphicsView *view = new QGraphicsView;
public slots:
    void mousePreEvent(QMouseEvent *e,QPointF p);
    void mouseMoEvent(QMouseEvent *e,QPointF p);
    void mouseReEvent(QMouseEvent *e,QPointF p);
    void moveEvent(QMoveEvent *event);
private slots:
    //各按钮的信号与槽函数
    void on_btnLine_clicked();

    void on_btnpencil_clicked();

    void on_btnRectangle_clicked();

    void on_btnEllipse_clicked();

    void on_btnRoundedRec_clicked();

    void on_btnEraser_clicked();

    void on_btncurve_clicked();

    void on_btnPolygon_clicked();

    void on_btnTriangle_clicked();

    void on_btnRhombus_clicked();

    void on_btnPentagon_clicked();

    void on_btnHexagon_clicked();

    void on_btnRightTriangle_clicked();

    void on_btnRightArrow_clicked();

    void on_btnLeftArrow_clicked();

    void on_btnUpArrow_clicked();

    void on_btnDownArrow_clicked();

    void on_btnFourStar_clicked();

    void on_btnFiveStar_clicked();

    void on_btnSixStar_clicked();

    void on_btnCirDialog_clicked();

    void on_btnRecDialog_clicked();

    void on_btnCloudDialog_clicked();

    void on_actCreateNewFile_triggered();

    void on_btnColor1_clicked();

    void on_btnColor2_clicked();

    void on_btnBlack_clicked();

    void on_btnGray50_clicked();

    void on_btnDeepRed_clicked();

    void on_btnRed_clicked();

    void on_btnOrange_clicked();

    void on_btnYellow_clicked();

    void on_btnGreen_clicked();

    void on_act1px_triggered();

    void on_act3px_triggered();

    void on_act5px_triggered();

    void on_act8px_triggered();


    void on_btnSel_clicked();

    void on_actDelete_triggered();

    void on_actRotL_triggered();

    void on_actRotR_triggered();

    void on_actRot180_triggered();

    void on_btnColorFill_clicked();

    void on_actSaveAs_triggered();

    void on_btnRose_clicked();

    void on_btnBrown_clicked();

    void on_btnIndigo_clicked();

    void on_btnTurquoise_clicked();

    void on_btnLavender_clicked();

    void on_btnBlueGray_clicked();

    void on_btnPurple_clicked();

    void on_actOpenFile_triggered();

    void on_actSave_triggered();

    void on_btnZoomIn_clicked();

    void on_btnColorGet_clicked();
    
    void on_btnColorEdit_clicked();

    void on_btnText_clicked();

    void on_btnWhite_clicked();

    void on_btnBrush_clicked();

    void on_action_1_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_action_7_triggered();

    void on_action_8_triggered();

    void on_action_9_triggered();

    void on_action_p1_triggered();

    void on_action_p2_triggered();

    void on_action_p3_triggered();

    void on_action_p4_triggered();

    void on_action_p5_triggered();

    void on_action_p6_triggered();

    void on_action_p7_triggered();

    void on_action_b1_triggered();

    void on_action_b2_triggered();

    void on_action_b3_triggered();

    void on_action_b4_triggered();

    void on_action_b5_triggered();

    void on_action_b6_triggered();

    void on_action_b7_triggered();

    void on_act_Undo_triggered();

    void on_act_Redo_triggered();

    void on_actPaste_triggered();

    void on_actRectSel_triggered();

    void on_btnPasteF_clicked();

    void on_actFreeSel_triggered();

    void on_btnCopy_clicked();

    void on_btnCut_clicked();

    void on_btnClip_clicked();

    void on_btnResize_clicked();

    void on_actSelAll_triggered();

    void on_actInveSel_triggered();

    void on_actVertRot_triggered();

    void on_actHoriRot_triggered();

    void on_actPasteF_triggered();

    void on_actPrint_triggered();

    void on_actDeliverFromEmail_triggered();

    void on_actSetAsDesktopBackground_triggered();

    void on_actProperty_triggered();

    void on_actAbout_triggered();

    void on_actExit_triggered();

    void on_btnBigger_clicked();

    void on_btnSmaller_clicked();

    void on_btnHundred_clicked();

    void on_btnFullScreen_clicked();

    void on_btnPrePic_clicked();

    void on_checkBox_3_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_clicked(bool checked);

private:
    void getPixelColor();
    void setLabel(QPoint p);
    void addBrushItem();
    void pre4BrushFunc(QPoint iPnt);
    void penStyleChange(const TextureType &value);
    void brushStyleChange(const TextureType &value);
    void funcBrushTypeChange();
    void selectedItemPenSet(QColor color);
    void selectedItemBrushSet(QColor color);
    void setItemWidth();
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);
    int test4Anything();
    QRect freeSelArea(QPolygon poly);
    void setSceneSizeLabel();
    void addLRArrow(QPoint point1,QPoint point2);
    void addUDArrow(QPoint point1,QPoint point2);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
