#include "mainwindow.h"
#include "myview.h"
#include "ui_mainwindow.h"
#include <myitem.h>
#include <QPainter>
#include <QMessageBox>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QGraphicsItemAnimation>
#include <qgraphicsitem.h>
#include <qgraphicssceneevent.h>
#include <iostream>
#include <qdebug.h>
#include <QFileDialog>
#include <qcolordialog.h>
#include <QTextEdit>
#include <QClipboard>
#include <dialogresize.h>
#include <QDialog>
#include <qprinter.h>
#include <qprintdialog.h>
#include <qprintpreviewdialog.h>
#include <qdesktopservices.h>
#include <qurl.h>
#include <paintattributedialog.h>
#include <QDateTime>

struct QImageData;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createSelPopupMenu();
    this->setMouseTracking(false);//不对鼠标位置进行追踪
    this->isPressed = false;//设定鼠标按键初始为松开状态
    scene=new QGraphicsScene(0,0,1098,488);
    image=new QImage(QSize(600,600),QImage::Format_RGB32);
    ui->view->setScene(scene);
    itemProperty.setBrush(Qt::white);
    ui->act1px->setChecked(true);
    ui->action_p2->setChecked(true);
    ui->action_b1->setChecked(true);    
    test4Anything();
    connect(ui->view,SIGNAL(mousePreEvent(QMouseEvent *,QPointF)),this,SLOT(mousePreEvent(QMouseEvent *,QPointF)));
    connect(ui->view,SIGNAL(mouseMoEvent(QMouseEvent *,QPointF)),this,SLOT(mouseMoEvent(QMouseEvent *,QPointF)));
    connect(ui->view,SIGNAL(mouseReEvent(QMouseEvent *,QPointF)),this,SLOT(mouseReEvent(QMouseEvent *,QPointF)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::floodFillu4(int x, int y, QRgb newColor)
{
    if(imgr.pixel(x,y) == 4294967295 )
    {
        imgr.setPixel(x,y,newColor);
        floodFillu4(x,y+1,newColor);
        floodFillu4(x-1,y,newColor);
        floodFillu4(x+1,y,newColor);
        floodFilld4(x,y-1,newColor);
    }
}

void MainWindow::floodFilld4(int x, int y, QRgb newColor)
{
    if(imgr.pixel(x,y) == 4294967295 )
    {
        imgr.setPixel(x,y,newColor);
        floodFilld4(x,y-1,newColor);
        floodFilld4(x-1,y,newColor);
        floodFilld4(x+1,y,newColor);
    }
}

void MainWindow::paintEven()
{
    //声明各个绘图工具
//    erasePainter.begin(&pix);
    //声明创建部分图形所需的路径/样式
    QPolygon triItem;
    QPainterPath iPath;
    QPen pen;
    QBrush brush;
    itemList=scene->items();
    if (!itemList.isEmpty()){
        itemList[0]->setFlag(QGraphicsItem::ItemIsSelectable,false);
        itemList[0]->setFlag(QGraphicsItem::ItemIsMovable,false);
        itemList[0]->setAcceptHoverEvents(false);
        itemList[0]->setSelected(false);
    }

        //设定（矩形）对角坐标
        QRect rectLine=QRect(sstartPnt.x(),sstartPnt.y(),
                             eendPnt.x()-sstartPnt.x(),
                             eendPnt.y()-sstartPnt.y());
        QRect rect;
        pen.setWidth(lWidth);
        pen.setColor(itemProperty.getPen());
        switch (i)
        {
        case 0:
            itemPoly=new MyPolylineItem(pencilLine);
            itemPoly->setPen(pen);
            scene->addItem(itemPoly);
            break;
        case 1:
//            painter.drawLine(pLine->sstartPnt, pLine->eendPnt);//直线功能
            itemL=new MyLineItem(QLineF(sstartPnt, eendPnt));
            itemL->setAcceptHoverEvents(false);
            itemL->setPen(pen);
            itemL->setBrush(itemProperty.getBrush());
            itemL->setFlag(QGraphicsItem::ItemIsMovable);
            itemL->setFlag(QGraphicsItem::ItemIsSelectable);
            itemL->setPentype(pentype);
            itemL->setBrushtype(brushtype);
//            itemL->setSelected(true);
            scene->addItem(itemL);
//            dynamic_cast<QGraphicsItem *>(scene->items()[0])->d_func();
            break;
        case 2:
            break;
        case 3:
            //绘制椭圆
            if (rectLine.width()>0||rectLine.height()>0)
            {itemE=new MyEllipseItem(rectLine);}else {
             itemE=new MyEllipseItem(QRect(eendPnt,QSize(sstartPnt.x()-eendPnt.x(),
                                                         sstartPnt.y()-eendPnt.y())));
            }
            itemE->setFlag(QGraphicsItem::ItemIsMovable);
            itemE->setFlag(QGraphicsItem::ItemIsSelectable);
            itemE->setPen(pen);
            itemE->setBrush(itemProperty.getBrush());
            itemE->setPentype(pentype);
            itemE->setBrushtype(brushtype);
            scene->addItem(itemE);
            break;
        case 4:
            //绘制矩形
            itemR=new MyRectItem(rectLine);
            itemR->setPen(pen);
            itemR->setBrush(itemProperty.getBrush());
            itemR->setFlag(QGraphicsItem::ItemIsMovable);
            itemR->setFlag(QGraphicsItem::ItemIsSelectable);
            itemR->setPentype(pentype);
            itemR->setBrushtype(brushtype);
            scene->addItem(itemR);
            break;
        case 5:
            //绘制圆角矩形
//            item=new qgraphics
            if (rectLine.width()>0||rectLine.height()>0)
            {itemMR=new MyRoundedItem(rectLine);}else{
                itemMR=new MyRoundedItem(QRect(eendPnt,QSize(-rectLine.width(),-rectLine.height())));
            }
            itemMR->setFlag(QGraphicsItem::ItemIsMovable);
            itemMR->setFlag(QGraphicsItem::ItemIsSelectable);
            itemMR->setFlag(QGraphicsItem::ItemIsFocusable);
            itemMR->setPen(pen);
            itemMR->setIsPre(0);
            itemMR->setBrush(itemProperty.getBrush());
            itemMR->setPentype(pentype);
            itemMR->setBrushtype(brushtype);
            itemMR->setAcceptHoverEvents(true);
            scene->addItem(itemMR);
            break;
        case 6:
            itemPg=new MyPolygonItem(pgPnts);
            itemPg->setFlag(QGraphicsItem::ItemIsMovable);
            itemPg->setFlag(QGraphicsItem::ItemIsSelectable);
            itemPg->setFlag(QGraphicsItem::ItemIsFocusable);
            itemPg->setPen(pen);
            itemPg->setBrush(itemProperty.getBrush());
            itemPg->setPentype(pentype);
            itemPg->setBrushtype(brushtype);
            scene->addItem(itemPg);
            pgPnts.clear();
            break;
        case 7:
            //绘制三角形
            Points.clear();
            Points.push_back(QPoint((eendPnt.x()+sstartPnt.x())/2,sstartPnt.y()));
            Points.push_back(QPoint(sstartPnt.x(),eendPnt.y()));
            Points.push_back(QPoint(QPoint(eendPnt)));
            triItem=QPolygon(Points);
            itemP=new MyPolygonItem(triItem);
            itemP->setPen(pen);
            itemP->setBrush(itemProperty.getBrush());
            itemP->setFlag(QGraphicsItem::ItemIsMovable);
            itemP->setFlag(QGraphicsItem::ItemIsSelectable);
            itemP->setPentype(pentype);
            itemP->setBrushtype(brushtype);
            scene->addItem(itemP);
            break;
        case 8:
            //绘制直角三角形
            iPath.moveTo(sstartPnt);
            iPath.lineTo(sstartPnt.x(),eendPnt.y());
            iPath.lineTo(eendPnt);
            iPath.lineTo(sstartPnt);
//            painter.drawPath(iPath);
            item=new MyPathItem(iPath);
            item->setFlag(QGraphicsItem::ItemIsMovable);
            item->setFlag(QGraphicsItem::ItemIsSelectable);
            item->setPen(pen);
            item->setBrush(itemProperty.getBrush());
            item->setPentype(pentype);
            item->setBrushtype(brushtype);
            scene->addItem(item);
            break;
        case 9:
            //绘制菱形
            iPath.moveTo((eendPnt.x()+sstartPnt.x())/2,sstartPnt.y());
            iPath.lineTo(sstartPnt.x(),(eendPnt.y()+sstartPnt.y())/2);
            iPath.lineTo((eendPnt.x()+sstartPnt.x())/2,eendPnt.y());
            iPath.lineTo(eendPnt.x(),(eendPnt.y()+sstartPnt.y())/2);
            iPath.lineTo((eendPnt.x()+sstartPnt.x())/2,sstartPnt.y());
//            painter.drawPath(iPath);
            item=new MyPathItem(iPath);
            item->setFlag(QGraphicsItem::ItemIsMovable);
            item->setFlag(QGraphicsItem::ItemIsSelectable);
            item->setPen(pen);
            item->setBrush(itemProperty.getBrush());
            item->setPentype(pentype);
            item->setBrushtype(brushtype);
            scene->addItem(item);
            break;
        case 10:
            //绘制五边形
            iPath.moveTo((eendPnt.x()+sstartPnt.x())/2,sstartPnt.y());
            iPath.lineTo(sstartPnt.x(),(0.588*eendPnt.y()+0.951*sstartPnt.y())/1.539);
            iPath.lineTo((0.31*eendPnt.x()+sstartPnt.x())/1.31,eendPnt.y());
            iPath.lineTo((eendPnt.x()+0.31*sstartPnt.x())/1.31,eendPnt.y());
            iPath.lineTo(eendPnt.x(),(0.588*eendPnt.y()+0.951*sstartPnt.y())/1.539);
            iPath.lineTo((eendPnt.x()+sstartPnt.x())/2,sstartPnt.y());
            item=new MyPathItem(iPath);
            item->setFlag(QGraphicsItem::ItemIsMovable);
            item->setFlag(QGraphicsItem::ItemIsSelectable);
            item->setPen(pen);
            item->setBrush(itemProperty.getBrush());
            item->setPentype(pentype);
            item->setBrushtype(brushtype);
            scene->addItem(item);
            break;
        case 11:
            //绘制六边形
            iPath.moveTo((eendPnt.x()+sstartPnt.x())/2,sstartPnt.y());
            iPath.lineTo(sstartPnt.x(),(eendPnt.y()+3*sstartPnt.y())/4);
            iPath.lineTo(sstartPnt.x(),(3*eendPnt.y()+sstartPnt.y())/4);
            iPath.lineTo((eendPnt.x()+sstartPnt.x())/2,eendPnt.y());
            iPath.lineTo(eendPnt.x(),(3*eendPnt.y()+sstartPnt.y())/4);
            iPath.lineTo(eendPnt.x(),(eendPnt.y()+3*sstartPnt.y())/4);
            iPath.lineTo((eendPnt.x()+sstartPnt.x())/2,sstartPnt.y());
//            painter.drawPath(iPath);
            item=new MyPathItem(iPath);
            item->setFlag(QGraphicsItem::ItemIsMovable);
            item->setFlag(QGraphicsItem::ItemIsSelectable);
            item->setPen(pen);
            item->setBrush(itemProperty.getBrush());
            item->setPentype(pentype);
            item->setBrushtype(brushtype);
            scene->addItem(item);
            break;
        case 12:
            //绘制向右箭头
            if (sstartPnt.x()-eendPnt.x()>0||sstartPnt.y()-eendPnt.y()>0){
                addLRArrow(eendPnt,sstartPnt);
            }else {
                addLRArrow(sstartPnt,eendPnt);
            }
            break;
        case 13:
            //绘制向左箭头
            if (sstartPnt.x()-eendPnt.x()>0||sstartPnt.y()-eendPnt.y()>0){
                addLRArrow(sstartPnt,eendPnt);
            }else{
                addLRArrow(eendPnt,sstartPnt);
            }
            break;
        case 14:
            //绘制向上箭头
            if (sstartPnt.x()-eendPnt.x()>0||sstartPnt.y()-eendPnt.y()>0){
                addUDArrow(eendPnt,sstartPnt);
            }else {
                addUDArrow(sstartPnt,eendPnt);
            }
            break;
        case 15:
            //绘制向下箭头
            if (sstartPnt.x()-eendPnt.x()>0||sstartPnt.y()-eendPnt.y()>0){
                addUDArrow(sstartPnt,eendPnt);
            }else{
                addUDArrow(eendPnt,sstartPnt);
            }
            break;
        case 16:
            //绘制四角星
            iPath.moveTo((sstartPnt.x()+eendPnt.x())/2,sstartPnt.y());
            iPath.lineTo((3.73*sstartPnt.x()+1.73*eendPnt.x())/5.46,(3.73*sstartPnt.y()+1.73*eendPnt.y())/5.46);
            iPath.lineTo(sstartPnt.x(),(sstartPnt.y()+eendPnt.y())/2);
            iPath.lineTo((3.73*sstartPnt.x()+1.73*eendPnt.x())/5.46,(1.73*sstartPnt.y()+3.73*eendPnt.y())/5.46);
            iPath.lineTo((sstartPnt.x()+eendPnt.x())/2,eendPnt.y());
            iPath.lineTo((1.73*sstartPnt.x()+3.73*eendPnt.x())/5.46,(1.73*sstartPnt.y()+3.73*eendPnt.y())/5.46);
            iPath.lineTo(eendPnt.x(),(sstartPnt.y()+eendPnt.y())/2);
            iPath.lineTo((1.73*sstartPnt.x()+3.73*eendPnt.x())/5.46,(3.73*sstartPnt.y()+1.73*eendPnt.y())/5.46);
            iPath.lineTo((sstartPnt.x()+eendPnt.x())/2,sstartPnt.y());
//            item=new MyPathItem(iPath);
            item->setFlag(QGraphicsItem::ItemIsMovable);
            item->setFlag(QGraphicsItem::ItemIsSelectable);
            item->setPen(pen);
            item->setBrush(itemProperty.getBrush());
            item->setPentype(pentype);
            item->setBrushtype(brushtype);
            scene->addItem(item);
            break;
        case 17:
            //绘制五角星
            iPath.moveTo((sstartPnt.x()+eendPnt.x())/2,sstartPnt.y());
            iPath.lineTo((3*sstartPnt.x()+2*eendPnt.x())/5,(3*sstartPnt.y()+2*eendPnt.y())/5);
            iPath.lineTo(sstartPnt.x(),(3*sstartPnt.y()+2*eendPnt.y())/5);
            iPath.lineTo((7*sstartPnt.x()+3*eendPnt.x())/10,(4*sstartPnt.y()+6*eendPnt.y())/10);
            iPath.lineTo((4*sstartPnt.x()+eendPnt.x())/5,eendPnt.y());
            iPath.lineTo((sstartPnt.x()+eendPnt.x())/2,(sstartPnt.y()+4*eendPnt.y())/5);
            iPath.lineTo((sstartPnt.x()+4*eendPnt.x())/5,eendPnt.y());
            iPath.lineTo((3*sstartPnt.x()+7*eendPnt.x())/10,(4*sstartPnt.y()+6*eendPnt.y())/10);
            iPath.lineTo(eendPnt.x(),(3*sstartPnt.y()+2*eendPnt.y())/5);
            iPath.lineTo((2*sstartPnt.x()+3*eendPnt.x())/5,(3*sstartPnt.y()+2*eendPnt.y())/5);
            iPath.lineTo((sstartPnt.x()+eendPnt.x())/2,sstartPnt.y());
//            painter.drawPath(iPath);
            item=new MyPathItem(iPath);
            item->setFlag(QGraphicsItem::ItemIsMovable);
            item->setFlag(QGraphicsItem::ItemIsSelectable);
            item->setPen(pen);
            item->setBrush(itemProperty.getBrush());
            item->setPentype(pentype);
            item->setBrushtype(brushtype);
            scene->addItem(item);
            break;
        case 18:
            //绘制六角星
            iPath.moveTo((sstartPnt.x()+eendPnt.x())/2,sstartPnt.y());
            iPath.lineTo((2*sstartPnt.x()+eendPnt.x())/3,(3*sstartPnt.y()+eendPnt.y())/4);
            iPath.lineTo(sstartPnt.x(),(3*sstartPnt.y()+eendPnt.y())/4);
            iPath.lineTo((5*sstartPnt.x()+eendPnt.x())/6,(sstartPnt.y()+eendPnt.y())/2);
            iPath.lineTo(sstartPnt.x(),(sstartPnt.y()+3*eendPnt.y())/4);
            iPath.lineTo((2*sstartPnt.x()+eendPnt.x())/3,(sstartPnt.y()+3*eendPnt.y())/4);
            iPath.lineTo((sstartPnt.x()+eendPnt.x())/2,eendPnt.y());
            iPath.lineTo((sstartPnt.x()+2*eendPnt.x())/3,(sstartPnt.y()+3*eendPnt.y())/4);
            iPath.lineTo(eendPnt.x(),(sstartPnt.y()+3*eendPnt.y())/4);
            iPath.lineTo((sstartPnt.x()+5*eendPnt.x())/6,(sstartPnt.y()+eendPnt.y())/2);
            iPath.lineTo(eendPnt.x(),(3*sstartPnt.y()+eendPnt.y())/4);
            iPath.lineTo((sstartPnt.x()+2*eendPnt.x())/3,(3*sstartPnt.y()+eendPnt.y())/4);
            iPath.lineTo((sstartPnt.x()+eendPnt.x())/2,sstartPnt.y());
//            painter.drawPath(iPath);
            item=new MyPathItem(iPath);
            item->setFlag(QGraphicsItem::ItemIsMovable);
            item->setFlag(QGraphicsItem::ItemIsSelectable);
            item->setPen(pen);
            item->setBrush(itemProperty.getBrush());
            item->setPentype(pentype);
            item->setBrushtype(brushtype);
            scene->addItem(item);
            break;
        case 19:
            iPath.moveTo((5*sstartPnt.x()+eendPnt.x())/6,sstartPnt.y());
            iPath.lineTo((sstartPnt.x()+5*eendPnt.x())/6,sstartPnt.y());
            iPath.arcTo(QRect(QPoint((sstartPnt.x()+2*eendPnt.x())/3,sstartPnt.y()),
                              QPoint(eendPnt.x(),(2*sstartPnt.y()+eendPnt.y())/3)),
                        90,-90);
            iPath.lineTo(eendPnt.x(),(sstartPnt.y()+2*eendPnt.y())/3);
            iPath.arcTo(QRect(QPoint((sstartPnt.x()+2*eendPnt.x())/3,
                                     (0.5*eendPnt.y()+0.5*sstartPnt.y())),
                              QPoint(eendPnt.x(),(sstartPnt.y()+5*eendPnt.y())/6)),
                        0,-90);
            iPath.lineTo((14*sstartPnt.x()+10*eendPnt.x())/24,
                                     (5*eendPnt.y()+sstartPnt.y())/6);
            iPath.lineTo((17*sstartPnt.x()+7*eendPnt.x())/24,eendPnt.y());
            iPath.lineTo((5*sstartPnt.x()+eendPnt.x())/6,
                         (5*eendPnt.y()+sstartPnt.y())/6);
            iPath.arcTo(QRect(QPoint(sstartPnt.x(),
                                     (0.5*eendPnt.y()+0.5*sstartPnt.y())),
                              QPoint((2*sstartPnt.x()+eendPnt.x())/3,(sstartPnt.y()+5*eendPnt.y())/6)),
                        -90,-90);
            iPath.lineTo(sstartPnt.x(),(5*sstartPnt.y()+eendPnt.y())/6);
            iPath.arcTo(QRect(sstartPnt,QPoint((2*sstartPnt.x()+eendPnt.x())/3,
                                     (2*sstartPnt.y()+eendPnt.y())/3)),
                        -180,-90);
            item=new MyPathItem(iPath);
            item->setFlag(QGraphicsItem::ItemIsMovable);
            item->setFlag(QGraphicsItem::ItemIsSelectable);
            item->setPen(pen);
            item->setBrush(itemProperty.getBrush());
            item->setPentype(pentype);
            item->setBrushtype(brushtype);
            scene->addItem(item);
            break;
        case 20:
            break;
        case 21:
            break;
        case 22:
            //橡皮
            if ((sstartPnt!=eendPnt)&&(!ui->view->mywidget->getEraserRectsOut().isEmpty())){
                QVector<QRect> rect=ui->view->mywidget->getEraserRectsOut();
                itemEraser=new MyEraserItem(rect);
                itemEraser->setPen(QPen(itemProperty.getBrush().color()));
                itemEraser->setBrush(itemProperty.getBrush());
                scene->addItem(itemEraser);
            }
            break;
        case 24:
            pixr=ui->view->grab(QRect(1,1,1100,490));
            imgr=pixr.toImage();
            floodFillu4(startPnt.x(),startPnt.y(),itemProperty.getFillC());
            cFill=new colorFill(imgr);
            scene->addItem(cFill);
            scene->update();
            break;
        case 25:
            getPixelColor();
            break;
        case 26:
            if (!ui->view->mywidget->getTextInput().isNull()){
//                qDebug()<<"wrong";
                itemText=new QGraphicsTextItem(ui->view->mywidget->getTextInput());
                itemText->adjustSize();
//                itemText->scale();
                itemText->setPos(ui->view->getCurrentScenePnt());
                scene->addItem(itemText);
            }
            break;
        case 27:
            ui->view->scale(2,2);
            ui->view->centerOn(startPnt);
            break;
        case 28:
            addBrushItem();
            break;
        case 30:
            if (sstartPnt!=eendPnt)
            {
                rect=QRect(sstartPnt.x()+1,sstartPnt.y()+1,
                           eendPnt.x()-sstartPnt.x(),
                           eendPnt.y()-sstartPnt.y());
                rectOfSel=rect;
                pixr=ui->view->grab(rect);
                imgr=pixr.toImage();
                imgr.fill(itemProperty.getBrush().color());
                itemRectSel=new MyRectSelItem(rectLine,imgr);
                scene->addItem(itemRectSel);
                imgr=pixr.toImage();
                itemRectSel=new MyRectSelItem(rectLine,imgr);
                itemRectSel->setFlag(QGraphicsItem::ItemIsSelectable);
                itemRectSel->setFlag(QGraphicsItem::ItemIsMovable);
                scene->addItem(itemRectSel);
            }
            break;
        case 31:
            if (sstartPnt!=eendPnt)
            {
                rect=freeSelArea(freeShapeOutline);
                freeShapePnts=freeShapeOutline;
                rectOfSel=rect;
                pixr=ui->view->grab(QRect(rect.topLeft()+QPoint(1,1),rect.bottomRight()+QPoint(1,1)));
                QPixmap pixr1=pixr;
                pixr1.fill(itemProperty.getBrush().color());
                itemFreeSel=new MyFreeShapeSelItem(rect,freeShapeOutline,pixr1);
                scene->addItem(itemFreeSel);
                itemFreeSel=new MyFreeShapeSelItem(rect,freeShapeOutline,pixr);
                itemFreeSel->setFlag(QGraphicsItem::ItemIsSelectable);
                itemFreeSel->setFlag(QGraphicsItem::ItemIsMovable);
                itemFreeSel->setBrush(itemProperty.getBrush());
                qDebug()<<"1";
                scene->addItem(itemFreeSel);
                freeShapeOutline.clear();
            }
            break;
        }
//        this->lines.clear();
        itemList=scene->items();
        if (!itemList.isEmpty())
        {
            itemList.first()->setSelected(true);
            itemList.first()->setAcceptHoverEvents(true);
            mitem=dynamic_cast<MyItem *>(itemList.first());
            mitem->setWidget(ui->view->mywidget);
//            connect(mitem,SIGNAL(cursorChange(QCursor)),ui->view->mywidget,SLOT(setCursor(QCursor)));
        }


//        ui->graphicsView->setScene(scene);
//        ui->graphicsView->show();

}

void MainWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    if (Tick)
    {
        QPainter painter;
        painter.begin(this);
        QList<QLine> lines;
        for (int i=0;i<5;i++){
            lines.append(QLine(0,200+i*100,20,200+i*100));
            for (int j=0;j<9;j++){
                lines.append(QLine(12,210+i*100+j*10,20,210+i*100+j*10));
            }
        }
        for (int i=0;i<11;i++){
            lines.append(QLine(20+i*100,180,20+i*100,200));
            for (int j=0;j<9;j++){
                lines.append(QLine(30+i*100+j*10,192,30+i*100+j*10,200));
            }
        }
        painter.drawLines(lines.toVector());
//        ui->view->transform().m11();
//        QVector<QString> tickLabels;
        qreal startx=ui->view->mapToScene(QPoint(0,0)).x();
        qreal xstep=ui->view->mapToScene(QPoint(100,0)).x()-startx;
        qreal starty=ui->view->mapToScene(QPoint(0,0)).y();
        qreal ystep=ui->view->mapToScene(QPoint(0,100)).y()-starty;
        for (int i=0;i<11;i++){
            painter.drawText(QRect(21+i*100,181,32,15),QString::number(startx+i*xstep,'f',1));
        }
        painter.translate(QPoint(0,132));
        painter.rotate(-90);
        for (int i=0;i<5;i++){
            painter.translate(QPoint(-100,0));
            painter.drawText(QRect(0,0,32,15),QString::number(starty+i*ystep,'f',1));
        }
        painter.end();
    }
}

void MainWindow::checkstate(int ii)
{
    ui->view->mywidget->setShapeType(ii);
//    ui->view->mywidget->hide();
//    ui->view->mywidget->show();
//    on_act1px_triggered();
    ui->view->mywidget->setCursor(Qt::ArrowCursor);
    ui->view->setEraserMode(false);
    ui->view->mywidget->setEraserMode(false);
    ui->view->setTextEditMode(false);
    ui->view->mywidget->setTextEditMode(false);
    ui->view->setHasGlass(false);
    ui->view->mywidget->setHasGlass(false);
    ui->view->mywidget->setFuncBrushMode(false);
    ui->btnpencil->setChecked(false);
    ui->btnLine->setChecked(false);
    ui->btnRectangle->setChecked(false);
    ui->btnEllipse->setChecked(false);
    ui->btnRoundedRec->setChecked(false);
    ui->btncurve->setChecked(false);
    ui->btnPolygon->setChecked(false);
    ui->btnTriangle->setChecked(false);
    ui->btnRightTriangle->setChecked(false);
    ui->btnRhombus->setChecked(false);
    ui->btnPentagon->setChecked(false);
    ui->btnHexagon->setChecked(false);
    ui->btnRightArrow->setChecked(false);
    ui->btnLeftArrow->setChecked(false);
    ui->btnUpArrow->setChecked(false);
    ui->btnDownArrow->setChecked(false);
    ui->btnFourStar->setChecked(false);
    ui->btnFiveStar->setChecked(false);
    ui->btnSixStar->setChecked(false);
    ui->btnCirDialog->setChecked(false);
    ui->btnRecDialog->setChecked(false);
    ui->btnCloudDialog->setChecked(false);
    ui->btnEraser->setChecked(false);
    ui->btnSel->setChecked(false);
    ui->btnColorFill->setChecked(false);
    ui->btnText->setChecked(false);
    ui->btnColorGet->setChecked(false);
    ui->btnZoomIn->setChecked(false);
    ui->btnBrush->setChecked(false);
    ui->btnSel->setChecked(false);
    switch (ii)
    {
    case 0:
        ui->btnpencil->setChecked(true);
        break;
    case 1:
        ui->btnLine->setChecked(true);
        break;
    case 2:
        ui->btncurve->setChecked(true);
        break;
    case 3:
        ui->btnEllipse->setChecked(true);
        break;
    case 4:
        ui->btnRectangle->setChecked(true);
        break;
    case 5:
        ui->btnRoundedRec->setChecked(true);
        break;
    case 6:
        ui->btnPolygon->setChecked(true);
        break;
    case 7:
        ui->btnTriangle->setChecked(true);
        break;
    case 8:
        ui->btnRightTriangle->setChecked(true);
        break;
    case 9:
        ui->btnRhombus->setChecked(true);
        break;
    case 10:
        ui->btnPentagon->setChecked(true);
        break;
    case 11:
        ui->btnHexagon->setChecked(true);
        break;
    case 12:
        ui->btnRightArrow->setChecked(true);
        break;
    case 13:
        ui->btnLeftArrow->setChecked(true);
        break;
    case 14:
        ui->btnUpArrow->setChecked(true);
        break;
    case 15:
        ui->btnDownArrow->setChecked(true);
        break;
    case 16:
        ui->btnFourStar->setChecked(true);
        break;
    case 17:
        ui->btnFiveStar->setChecked(true);
        break;
    case 18:
        ui->btnSixStar->setChecked(true);
        break;
    case 19:
        ui->btnCirDialog->setChecked(true);
        break;
    case 20:
        ui->btnRecDialog->setChecked(true);
        break;
    case 21:
        ui->btnCloudDialog->setChecked(true);
        break;
    case 22:
        ui->btnEraser->setChecked(true);
        on_act8px_triggered();
        break;
    case 23:
        ui->btnSel->setChecked(true);
        break;
    case 24:
        ui->btnColorFill->setChecked(true);
        break;
    case 25:
        ui->btnColorGet->setChecked(true);
        break;
    case 26:
        ui->btnText->setChecked(true);
        ui->view->setTextEditMode(true);
        ui->view->mywidget->setTextEditMode(true);
        break;
    case 27:
        ui->btnZoomIn->setChecked(true);
//        ui->view->setHasGlass(true);
        ui->view->mywidget->setHasGlass(true);
        break;
    case 28:
        ui->btnBrush->setChecked(true);
        ui->view->mywidget->setFuncBrushMode(true);
        funcBrushTypeChange();
        i=28;
        break;
    case 30:
        ui->btnSel->setChecked(true);
        ui->actRectSel->setChecked(true);
        ui->actFreeSel->setChecked(false);
        break;
    case 31:
        ui->btnSel->setChecked(true);
        ui->actFreeSel->setChecked(true);
        ui->actRectSel->setChecked(false);
        break;
    }
    if (i>0&&i<22){
        ui->btnPenStyle->setEnabled(true);
        ui->btnBrushStyle->setEnabled(true);
    }else {
        ui->btnPenStyle->setEnabled(false);
        ui->btnBrushStyle->setEnabled(false);
    }
}

void MainWindow::createSelPopupMenu()
{
    //创建下拉菜单
    QMenu* menuFile=new QMenu(this);//创建文件弹出式菜单
    menuFile->setTitle("文件");
//    menuFile->setDefaultAction(ui->actFile);
    menuFile->addAction(ui->actCreateNewFile);
    menuFile->addAction(ui->actOpenFile);
    menuFile->addAction(ui->actSave);
    menuFile->addAction(ui->actSaveAs);
    menuFile->addAction(ui->actPrint);
    menuFile->addAction(ui->actDeliverFromEmail);
    menuFile->addAction(ui->actSetAsDesktopBackground);
    menuFile->addAction(ui->actProperty);
    menuFile->addAction(ui->actAbout);
    menuFile->addAction(ui->actExit);

    QMenu* paste=new QMenu(this);
    paste->addAction(ui->actPaste);
    paste->addAction(ui->actPasteF);

    QMenu* select=new QMenu(this);
    select->addAction(ui->actRectSel);
    select->addAction(ui->actFreeSel);
    select->addSeparator();
    select->addAction(ui->actSelAll);
    select->addAction(ui->actInveSel);
    select->addAction(ui->actDelete);
    select->addAction(ui->actLucidSel);

    QMenu* rotation=new QMenu(this);
    rotation->addAction(ui->actRotL);
    rotation->addAction(ui->actRotR);
    rotation->addAction(ui->actRot180);
    rotation->addAction(ui->actVertRot);
    rotation->addAction(ui->actHoriRot);

    QMenu* lWidth=new QMenu(this);
    lWidth->addAction(ui->act1px);
    lWidth->addAction(ui->act3px);
    lWidth->addAction(ui->act5px);
    lWidth->addAction(ui->act8px);

    ui->menuBar->addSeparator();
    ui->menuBar->addAction(ui->actSave);

    QToolButton *aBtn=new QToolButton(this);
    aBtn->setPopupMode(QToolButton::InstantPopup);//菜单弹出模式
    aBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);//按钮样式
    aBtn->setDefaultAction(ui->actFile);//设置action，获取图标、标题等设置
    aBtn->setMenu(menuFile);
    aBtn->setGeometry(0,39,70,25);
    aBtn->show();

//    QToolButton *bBtn=new QToolButton(this);
//    bBtn->setPopupMode(QToolButton::DelayedPopup);//菜单弹出模式
//    bBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//按钮样式
//    bBtn->setDefaultAction(ui->actmainpage);//设置action，获取图标、标题等设置
//    ui->actmainpage->setChecked(true);

//    QToolButton *cBtn=new QToolButton(this);
//    cBtn->setPopupMode(QToolButton::DelayedPopup);//菜单弹出模式
//    cBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//按钮样式
//    cBtn->setDefaultAction(ui->actview);//设置action，获取图标、标题等设置
    //为刷子按钮添加各种下拉样式
    ui->btnBrush->addAction(ui->action_1);
    ui->btnBrush->addAction(ui->action_2);
    ui->btnBrush->addAction(ui->action_3);
    ui->btnBrush->addAction(ui->action_4);
    ui->btnBrush->addAction(ui->action_5);
    ui->btnBrush->addAction(ui->action_6);
    ui->btnBrush->addAction(ui->action_7);
    ui->btnBrush->addAction(ui->action_8);
    ui->btnBrush->addAction(ui->action_9);
    //为轮廓按钮添加各种下拉样式
    ui->btnPenStyle->addAction(ui->action_p1);
    ui->btnPenStyle->addAction(ui->action_p2);
    ui->btnPenStyle->addAction(ui->action_p3);
    ui->btnPenStyle->addAction(ui->action_p4);
    ui->btnPenStyle->addAction(ui->action_p5);
    ui->btnPenStyle->addAction(ui->action_p6);
    ui->btnPenStyle->addAction(ui->action_p7);
    //为填充按钮添加各种下拉样式
    ui->btnBrushStyle->addAction(ui->action_b1);
    ui->btnBrushStyle->addAction(ui->action_b2);
    ui->btnBrushStyle->addAction(ui->action_b3);
    ui->btnBrushStyle->addAction(ui->action_b4);
    ui->btnBrushStyle->addAction(ui->action_b5);
    ui->btnBrushStyle->addAction(ui->action_b6);
    ui->btnBrushStyle->addAction(ui->action_b7);

    ui->btnPasteF->setMenu(paste);
    ui->btnSel->setMenu(select);
    ui->btnRot->setMenu(rotation);
    ui->btnwidth->setMenu(lWidth);
//    ui->menuBar->addMenu(menuFile);
//    ui->mainToolBar->addWidget(aBtn);
    ui->menuBar->addAction(ui->act_Undo);
    ui->menuBar->addAction(ui->act_Redo);
    QMenu *menuTool=new QMenu("工具栏");
    ui->menuBar->addMenu(menuTool);
    ui->menuBar->addSeparator();
    ui->menuBar->addMenu("无标题-画图");

    QLabel *labelPosIcon=new QLabel();
    labelPos=new QLabel();
    QLabel *labelItemSizeIcon=new QLabel();
    labelItemSize=new QLabel();
    QLabel *labelSceneSizeIcon=new QLabel();
    labelSceneSize=new QLabel();
    labelPosIcon->setPixmap(QPixmap(":/image/坐标.png"));
    labelItemSizeIcon->setPixmap(QPixmap(":/image/物体大小.png"));
    labelSceneSizeIcon->setPixmap(QPixmap(":/image/画布大小.png"));
    labelPos->setMinimumSize(QSize(200,20));
    labelItemSize->setMinimumSize(QSize(200,20));
    labelSceneSize->setMinimumSize(QSize(200,20));
    statusBar()->addWidget(labelPosIcon);
    statusBar()->addWidget(labelPos);
    statusBar()->addWidget(labelItemSizeIcon);
    statusBar()->addWidget(labelItemSize);
    statusBar()->addWidget(labelSceneSizeIcon);
    statusBar()->addWidget(labelSceneSize);
    setSceneSizeLabel();
}
void MainWindow::on_btnpencil_clicked()
{
    i=0;
    checkstate(i);
}

void MainWindow::on_btnLine_clicked()
{
    i=1;
    checkstate(i);
}

void MainWindow::on_btncurve_clicked()
{
    i=2;
    checkstate(i);
}

void MainWindow::on_btnEllipse_clicked()
{
    i=3;
    checkstate(i);
}

void MainWindow::on_btnRectangle_clicked()
{
    i=4;
    checkstate(i);
}

void MainWindow::on_btnRoundedRec_clicked()
{
    i=5;
    checkstate(i);
}

void MainWindow::on_btnPolygon_clicked()
{
    i=6;
    checkstate(i);
}

void MainWindow::on_btnTriangle_clicked()
{
    i=7;
    checkstate(i);
}

void MainWindow::on_btnRightTriangle_clicked()
{
    i=8;
    checkstate(i);
}

void MainWindow::on_btnRhombus_clicked()
{
    i=9;
    checkstate(i);
}

void MainWindow::on_btnPentagon_clicked()
{
    i=10;
    checkstate(i);
}

void MainWindow::on_btnHexagon_clicked()
{
    i=11;
    checkstate(i);
}

void MainWindow::on_btnRightArrow_clicked()
{
    i=12;
    checkstate(i);
}

void MainWindow::on_btnLeftArrow_clicked()
{
    i=13;
    checkstate(i);
}

void MainWindow::on_btnUpArrow_clicked()
{
    i=14;
    checkstate(i);
}

void MainWindow::on_btnDownArrow_clicked()
{
    i=15;
    checkstate(i);
}

void MainWindow::on_btnFourStar_clicked()
{
    i=16;
    checkstate(i);
}

void MainWindow::on_btnFiveStar_clicked()
{
    i=17;
    checkstate(i);
}

void MainWindow::on_btnSixStar_clicked()
{
    i=18;
    checkstate(i);
}

void MainWindow::on_btnCirDialog_clicked()
{
    i=19;
    checkstate(i);
}

void MainWindow::on_btnRecDialog_clicked()
{
    i=20;
    checkstate(i);
}

void MainWindow::on_btnCloudDialog_clicked()
{
    i=21;
    checkstate(i);
}

void MainWindow::on_btnEraser_clicked()
{
    i=22;
    checkstate(i);
    ui->view->setEraserMode(true);
    ui->view->mywidget->setEraserMode(true);
}

void MainWindow::on_actCreateNewFile_triggered()
{

}

void MainWindow::on_btnColor1_clicked()
{
    ui->btnColor1->setChecked(true);
    ui->btnColor2->setChecked(false);
}

void MainWindow::on_btnColor2_clicked()
{
    ui->btnColor2->setChecked(true);
    ui->btnColor1->setChecked(false);
}

void MainWindow::on_btnBlack_clicked()
{
    QColor pcolor=QColor(0,0,0);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(Qt::black);
    ui->view->mywidget->setMyPen(pcolor);
    itemProperty.setFillC(qRgb(0,0,0));
    selectedItemPenSet(pcolor);
    QIcon ic;
    ic.addFile(":/image/黑色.png");
    ui->btnColor1->setIcon(ic);
    }else {
        itemProperty.setBrush(Qt::black);
        ui->view->mywidget->setMyBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/黑色.png"));
        ui->btnColor2->setIconSize(QSize(80,80));
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_btnGray50_clicked()
{
    QColor pcolor=QColor(128,128,128);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(Qt::darkGray);
    ui->view->mywidget->setMyPen(pcolor);
    itemProperty.setFillC(qRgb(128,128,128));
    selectedItemPenSet(pcolor);
    ui->btnColor1->setIcon(QIcon(":/image/灰色-50.png"));
    }else {
        itemProperty.setBrush(Qt::darkGray);
        ui->view->mywidget->setMyBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/灰色-50.png"));
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_btnDeepRed_clicked()
{
    QColor pcolor=QColor(136,0,21);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(Qt::darkRed);
    ui->view->mywidget->setMyPen(pcolor);
    itemProperty.setFillC(qRgb(136,0,21));
    selectedItemPenSet(pcolor);
    ui->btnColor1->setIcon(QIcon(":/image/深红色.png"));
    }else {
        itemProperty.setBrush(Qt::darkRed);
        ui->view->mywidget->setMyBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/深红色.png"));
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_btnRed_clicked()
{
    QColor pcolor=QColor(255,0,0);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(pcolor);
    ui->view->mywidget->setMyPen(pcolor);
    itemProperty.setFillC(qRgb(255,0,0));
    selectedItemPenSet(pcolor);
    ui->btnColor1->setIcon(QIcon(":/image/红色.png"));
    }else {
        itemProperty.setBrush(pcolor);
        ui->view->mywidget->setMyBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/红色.png"));
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_btnOrange_clicked()
{
    QColor pcolor=QColor(255,128,64);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(pcolor);
    ui->view->mywidget->setMyPen(pcolor);
    itemProperty.setFillC(qRgb(255,128,64));
    selectedItemPenSet(pcolor);
    ui->btnColor1->setIcon(QIcon(":/image/橙色.png"));
    }else {
        itemProperty.setBrush(pcolor);
        ui->view->mywidget->setMyBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/橙色.png"));
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_btnYellow_clicked()
{
    QColor pcolor=QColor(255,242,0);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(Qt::yellow);
    ui->view->mywidget->setMyPen(pcolor);
    itemProperty.setFillC(qRgb(255,242,0));
    selectedItemPenSet(pcolor);
    ui->btnColor1->setIcon(QIcon(":/image/黄色.png"));
    }else {
        itemProperty.setBrush(QColor(255,242,0));
        ui->view->mywidget->setMyBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/黄色.png"));
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_btnGreen_clicked()
{
    QColor pcolor=QColor(34,177,76);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(pcolor);
    ui->view->mywidget->setMyPen(pcolor);
    itemProperty.setFillC(qRgb(34,177,76));
    selectedItemPenSet(pcolor);
    ui->btnColor1->setIcon(QIcon(":/image/绿色.png"));
    }else {
        itemProperty.setBrush(pcolor);
        ui->view->mywidget->setMyBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/绿色.png"));
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_act1px_triggered()
{
    lWidth=1;
    setItemWidth();
}

void MainWindow::on_act3px_triggered()
{
    lWidth=3;
    setItemWidth();
}

void MainWindow::on_act5px_triggered()
{
    lWidth=5;
    setItemWidth();
}

void MainWindow::on_act8px_triggered()
{
    lWidth=8;
    setItemWidth();
}

void MainWindow::mousePreEvent(QMouseEvent *e,QPointF p)
{
//    mousePressEvent(e);
//    QPixmap movePix
    if ((!scene->items().isEmpty())&&(!scene->selectedItems().isEmpty())&&i!=24){return;}
    Q_UNUSED(e);
    if(i!=22&&i!=27) {ui->view->mywidget->setCursor(Qt::CrossCursor);};
    if (i==23){ui->view->mywidget->setCursor(Qt::SizeAllCursor);return;}
    sstartPnt = p.toPoint();
    eendPnt = p.toPoint();
    this->isPressed = true;
    if (i==6&&pgPnts.isEmpty()){
        pgPnts.append(p.toPoint());
    }
    startPnt=p.toPoint();
}

void MainWindow::mouseMoEvent(QMouseEvent *e,QPointF p)
{
//    mouseMoveEvent(e);
    Q_UNUSED(e);
//    if(this->isPressed&&i!=23){
//        endPnt = p.toPoint();
//        myLine* line = new myLine;  //put the new line into vector
//        line->startPnt = startPnt;
//        line->endPnt = endPnt;
//        line->color0=color0;
//        line->color1=color1;
//        line->lWidth=lWidth;
//        line->i=i;
//        inslines.startPnt=startPnt;
//        inslines.endPnt=endPnt;
//        this->lines.push_back(line);
//        ListNum=0;
//        if (ui->btnpencil->isChecked())
//        {
//            startPnt = endPnt;
//        }
//        c=1;
//    }

    if (isPressed){
        if (i==0)
        {pencilLine.append(p.toPoint());}
        else if(i==28){
            pre4BrushFunc(p.toPoint());
        }else if(i==31){
            freeShapeOutline.append(p.toPoint());
        }

        if (i>0&&i<22){
            QString str3;
            QString str4;
            str3.setNum(abs(p.x()-sstartPnt.x()));
            str4.setNum(abs(p.x()-sstartPnt.y()));
            str3.append("x");
            str3.append(str4);
            str3.append("像素");
            labelItemSize->setText(str3);
        }
    }
    setLabel(p.toPoint());

}

void MainWindow::mouseReEvent(QMouseEvent *e,QPointF p)
{
//    mouseReleaseEvent(e);
    if ((!scene->items().isEmpty())&&(!scene->selectedItems().isEmpty())&&i!=24){
        scene->update();
        return;}
    Q_UNUSED(e);
    isPressed = false;
    if(i!=22&&i!=27&&!ui->btnBrush->isChecked()) {
        ui->view->mywidget->setCursor(Qt::ArrowCursor);}
    if (i==23){return;}
    eendPnt = p.toPoint();
    if (i==6){
        QPoint distancePnt=pgPnts[0]-p.toPoint();
        if (distancePnt.manhattanLength()<5){
            paintEven();
        }else {
            pgPnts.append(p.toPoint());
        }
    }else {
    paintEven();
    }
//    myLine* line = new myLine;  //put the new line into vector
//    line->sstartPnt = sstartPnt;
//    line->eendPnt = eendPnt;
//    line->i=i;
//    line->color0=color0;
//    line->color1=color1;
//    line->lWidth=lWidth;
//    inslines.startPnt=QPoint(0,0);
//    inslines.endPnt=QPoint(0,0);
//    this->lines.push_back(line);

//    ListNum=1;
//    ui->view->setDragMode(QGraphicsView::NoDrag);
//    ui->view->mywidget->setUpdateMode(false);
    scene->update();
    if (i==0){pencilLine.clear();}
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event);
    if (Tick){
        ui->view->mywidget->move(mapToGlobal(QPoint(20,200)));
    }else {
    ui->view->mywidget->move(mapToGlobal(QPoint(0,180)));
    }
}

void MainWindow::on_btnSel_clicked()
{
    i=23;
    checkstate(i);
//    ui->view->setDragMode(QGraphicsView::ScrollHandDrag);
}


void MainWindow::on_actDelete_triggered()
{
    if (scene->selectedItems()[0]==nullptr){return;}
    itemSel=scene->selectedItems();
    scene->removeItem(itemSel[0]);
    delete itemSel[0];
}


void MainWindow::on_actRotL_triggered()
{
    ui->actRotR->setChecked(false);
    ui->actRot180->setChecked(false);
    ui->actVertRot->setChecked(false);
    ui->actHoriRot->setChecked(false);
    if (scene->selectedItems().isEmpty()){
        return;}else {
        dynamic_cast<MyItem *>(scene->selectedItems()[0])->rotL();
        scene->update();
    }


}

void MainWindow::on_actRotR_triggered()
{
//    if (scene->selectedItems()[0]==nullptr){return;}
//    ui->actRotL->setChecked(false);
//    ui->actRot180->setChecked(false);
//    rotAngle=rotAngle-90;
//    scene->selectedItems()[0]->setRotation(rotAngle);
//    dynamic_cast<MyRoundedItem *>(scene->selectedItems()[0])->
    ui->actRotL->setChecked(false);
    ui->actRot180->setChecked(false);
    ui->actVertRot->setChecked(false);
    ui->actHoriRot->setChecked(false);
    if (scene->selectedItems().isEmpty()){
        return;}else {
        dynamic_cast<MyItem *>(scene->selectedItems()[0])->rotR();
        scene->update();
    }
}

void MainWindow::on_actRot180_triggered()
{
    ui->actRotR->setChecked(false);
    ui->actRotL->setChecked(false);
    ui->actVertRot->setChecked(false);
    ui->actHoriRot->setChecked(false);
    if (scene->selectedItems().isEmpty()){
        return;}else {
        dynamic_cast<MyItem *>(scene->selectedItems()[0])->rot180();
        scene->update();
    }
}

void MainWindow::on_btnColorFill_clicked()
{
    i=24;
    checkstate(i);
}

void MainWindow::on_actSaveAs_triggered()
{
//    const QStringList schemes = QStringList(QStringLiteral("file"));
    ui->view->mywidget->hide();
    QFileDialog dialogf(this);
    dialogf.setAcceptMode(QFileDialog::AcceptSave);
    dialogf.setWindowTitle("保存图像");
    dialogf.setDirectory("");
    dialogf.setNameFilter(tr("单色位图(*.bmp;*.dib);;16色位图(*.bmp;*.dib);;"
                             "256色位图(*.bmp;*.dib);;24位位图(*.bmp;*.dib);;"
                             "PNG(*.png);;JPEG(*.jpg;*.jpeg);;TIF(*.tif;*.tiff);;"
                             "GIF(*.gif)"));
    int dstate=dialogf.exec();
    if (dstate!=QDialog::Accepted){ui->view->mywidget->show();return;}
    ui->view->mywidget->show();
    QString entireFilterName=dialogf.selectedNameFilter();
    QString filename1=dialogf.selectedUrls().value(0).toLocalFile();

    QImage img=ui->view->grab(QRect(1,1,1098,488)).toImage();
    if (filename1.contains(".gif")){
        img.convertToFormat(QImage::Format_RGBA8888);
        GifBegin(&mGifWriter,filename1.toUtf8().data(),quint32(img.width()),quint32(img.height()),10);
        GifWriteFrame(&mGifWriter, img.bits(),
                      static_cast<quint32>(img.width()),
                      static_cast<quint32>(img.height()),
                      static_cast<quint32>(10));
        GifEnd(&mGifWriter);
    }else if(entireFilterName.contains("单")){
        for (int i=0;i<img.size().width();i++){
            for (int j=0;j<img.size().height();j++){
                if (img.pixelColor(i,j).rgb()<qRgb(240,240,240)){
                    img.setPixel(i,j,qRgb(0,0,0));
                }else {
                    img.setPixel(i,j,qRgb(255,255,255));
                }
            }
        }
        img.convertToFormat(QImage::Format_MonoLSB,Qt::MonoOnly);
        img.save(filename1);
    }else if(entireFilterName.contains("16")){
        img.convertToFormat(QImage::Format_Grayscale8);
        img.save(filename1);
    }else if(entireFilterName.contains("256")){
        img.convertToFormat(QImage::Format_Indexed8);
        img.save(filename1);
    }else if(entireFilterName.contains("24")){
        img.convertToFormat(QImage::Format_RGB888);
        img.save(filename1);
    }else{
        img.save(filename1);
    }
    filenameSave=filename1;
//    QImage hhh(filename1);
//    QBitmap;
//    int h=hhh.depth();
//    hhh.bits();
//fread()
}

void MainWindow::on_btnRose_clicked()
{
    QColor pcolor=QColor(255,174,201);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(pcolor);
    ui->view->mywidget->setMyPen(pcolor);
    itemProperty.setFillC(qRgb(255,174,201));
    selectedItemPenSet(pcolor);
    ui->btnColor1->setIcon(QIcon(":/image/玫瑰色.png"));
    }else {
        itemProperty.setBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/玫瑰色.png"));
        ui->view->mywidget->setMyBrush(pcolor);
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_btnBrown_clicked()
{
    QColor pcolor=QColor(185,122,87);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(pcolor);
    ui->view->mywidget->setMyPen(pcolor);
    itemProperty.setFillC(qRgb(185,122,87));
    selectedItemPenSet(pcolor);
    ui->btnColor1->setIcon(QIcon(":/image/褐色.png"));
    }else {
        itemProperty.setBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/褐色.png"));
        ui->view->mywidget->setMyBrush(pcolor);
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_btnIndigo_clicked()
{
    QColor pcolor=QColor(63,72,204);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(pcolor);
    ui->view->mywidget->setMyPen(pcolor);
    itemProperty.setFillC(qRgb(63,72,204));
    selectedItemPenSet(pcolor);
    ui->btnColor1->setIcon(QIcon(":/image/靛青.png"));
    }else {
        itemProperty.setBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/靛青.png"));
        ui->view->mywidget->setMyBrush(pcolor);
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_btnTurquoise_clicked()
{
    QColor pcolor=QColor(0,162,232);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(pcolor);
    ui->view->mywidget->setMyPen(pcolor);
    itemProperty.setFillC(qRgb(0,162,232));
    selectedItemPenSet(pcolor);
    ui->btnColor1->setIcon(QIcon(":/image/青绿.png"));
    }else {
        itemProperty.setBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/青绿.png"));
        ui->view->mywidget->setMyBrush(pcolor);
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_btnLavender_clicked()
{
    QColor pcolor=QColor(200,191,231);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(pcolor);
    ui->view->mywidget->setMyPen(pcolor);
    itemProperty.setFillC(qRgb(200,191,231));
    selectedItemPenSet(pcolor);
    ui->btnColor1->setIcon(QIcon(":/image/淡紫色.png"));
    }else {
        itemProperty.setBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/淡紫色.png"));
        ui->view->mywidget->setMyBrush(pcolor);
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_btnBlueGray_clicked()
{
    QColor pcolor=QColor(112,146,190);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(pcolor);
    ui->view->mywidget->setMyPen(pcolor);
    itemProperty.setFillC(qRgb(112,146,190));
    selectedItemPenSet(pcolor);
    ui->btnColor1->setIcon(QIcon(":/image/蓝灰色.png"));
    }else {
        itemProperty.setBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/蓝灰色.png"));
        ui->view->mywidget->setMyBrush(pcolor);
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_btnPurple_clicked()
{
    QColor pcolor=QColor(163,73,164);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(pcolor);
    ui->view->mywidget->setMyPen(pcolor);
    selectedItemPenSet(pcolor);
    itemProperty.setFillC(qRgb(163,73,164));
    ui->btnColor1->setIcon(QIcon(":/image/紫色.png"));
    }else {
        itemProperty.setBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/紫色.png"));
        ui->view->mywidget->setMyBrush(pcolor);
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_actOpenFile_triggered()
{
    ui->view->mywidget->hide();
    QString filename=QFileDialog::getOpenFileName(this,"打开文件",									
                                                          "位图文件(*.bmp;*.dib);;JPEG(*.jpg;*.jpeg);;"
                                                          "PNG(*.png);;TIF(*.tif;*.tiff);;GIF(*.gif)"
                                                          );
    if(filename.isEmpty())
    {return;}
    else{
        QImage img;
        if(!(img.load(filename))) //加载图像
        {
            QMessageBox::information(this, tr("打开图像失败"),tr("打开图像失败!"));
            return;
        }
        scene->addPixmap(QPixmap::fromImage(img.scaled(ui->view->size())));
    }
    filenameSave=filename;
    ui->view->show();

}

void MainWindow::on_actSave_triggered()
{
    ui->view->mywidget->hide();
    if(filenameSave.isNull())
    {on_actSaveAs_triggered();
    } //选择路径
    if (filenameSave.contains("gif")){
        QImage img=ui->view->grab(QRect(1,1,1098,488)).toImage();
        img.convertToFormat(QImage::Format_RGBA8888);
        GifBegin(&mGifWriter,filenameSave.toUtf8().data(),quint32(img.width()),quint32(img.height()),10);
        GifWriteFrame(&mGifWriter, img.bits(),
                      static_cast<quint32>(img.width()),
                      static_cast<quint32>(img.height()),
                      static_cast<quint32>(10));
        GifEnd(&mGifWriter);
    }else
    {ui->view->grab(QRect(1,1,1098,488)).toImage().save(filenameSave);}
    ui->view->mywidget->show();
}

void MainWindow::on_btnZoomIn_clicked()
{
    if (ui->btnZoomIn->isChecked()){
        iLast=i;
        i=27;
        checkstate(i);
        QPixmap pix(":/image/放大镜.png");
        pix.scaled(QSize(2,2),Qt::KeepAspectRatio);
        QCursor cursor(pix);       
        ui->view->mywidget->setCursor(cursor);
    }else {
    i=iLast;
    checkstate(i);
}

}

void MainWindow::on_btnColorGet_clicked()
{
    if (ui->btnColorGet->isChecked()){
        iLast=i;
        i=25;
        checkstate(i);
    }else {
    i=iLast;
    checkstate(i);
    }
}

void MainWindow::on_btnColorEdit_clicked()
{
    QColor iniColor;
    QPixmap pix(QSize(40,40));
    ui->view->mywidget->hide();
    if(ui->btnColor1->isChecked()){
        iniColor=itemProperty.getPen();
        QColor color=QColorDialog::getColor(iniColor,this,"选择颜色");
        pix.fill(color);
        ui->btnColor1->setIcon(QIcon(pix));
        itemProperty.setPen(color);
        ui->view->mywidget->setMyPen(color);
        selectedItemPenSet(color);
        itemProperty.setFillC(color.rgb());
    }else {
        iniColor=itemProperty.getBrush().color();
        QColor color=QColorDialog::getColor(iniColor,this,"选择颜色");
        pix.fill(color);
        ui->btnColor2->setIcon(QIcon(pix));
        itemProperty.setBrush(color);
        ui->view->mywidget->setMyBrush(color);
        selectedItemBrushSet(color);
        itemProperty.setFillC(color.rgb());
    }
    ui->view->mywidget->show();


}

void MainWindow::getPixelColor()
{
    QPixmap pixGetFromPixel=ui->view->grab(QRect(1,1,1100,490));
    QPixmap pix(QSize(40,40));
    QColor colorGet=pixGetFromPixel.toImage().pixelColor(ui->view->getCurrentPnt());
    pix.fill(colorGet);
    if(ui->btnColor1->isChecked()){
        ui->btnColor1->setIcon(QIcon(pix));
        itemProperty.setPen(colorGet);
        ui->view->mywidget->setMyPen(colorGet);
        itemProperty.setFillC(colorGet.rgb());
    }else {
        ui->btnColor2->setIcon(QIcon(pix));
        itemProperty.setBrush(colorGet);
        ui->view->mywidget->setMyBrush(colorGet);
    }
}

void MainWindow::setLabel(QPoint p)
{
    QString str1;
    QString str2;
    str1.setNum(p.x());
    str2.setNum(p.y());
    QString str;
    str.append(str1);
    str.append("x");
    str.append(str2);
    str.append("像素");
    labelPos->setText(str);
}

void MainWindow::addBrushItem()
{
    QPen pen=itemProperty.getPen();
    QColor bcolor;
    bcolor=itemProperty.getPen();
//    pen.setWidth(bWidth);
    if (funcBrushType==1)
    {
        pen.setWidth(5);
        itemPoly=new MyPolylineItem(pencilLine);
        itemPoly->setPen(pen);
        scene->addItem(itemPoly);
    }else if (funcBrushType==2) {
        pen.setWidth(2);
        itemLs=new MyLinesItem(calliLines);
        itemLs->setPen(pen);
        scene->addItem(itemLs);
    }else if (funcBrushType==3) {
        pen.setWidth(2);
        itemLs=new MyLinesItem(calliLines);
        itemLs->setPen(pen);
        scene->addItem(itemLs);
    }else if(funcBrushType==4){
        pen.setWidth(1);
        airPnts=ui->view->mywidget->getAirbrushPoints();
        ui->view->mywidget->clearAirbrushPoints();
        itemAirPnts=new MyAirBrushItem(airPnts);
        itemAirPnts->setPen(pen);
        scene->addItem(itemAirPnts);
    }else if(funcBrushType==5){

    }else if(funcBrushType==6){

        pen=ui->view->mywidget->getFuncBrushPenE();
        pen.setWidth(30);
        itemPoly=new MyPolylineItem(pencilLine);
        itemPoly->setPen(pen);
        scene->addItem(itemPoly);
        pen=ui->view->mywidget->getFuncBrushPenM();
        pen.setWidth(22);
        itemPoly=new MyPolylineItem(pencilLine);
        itemPoly->setPen(pen);
        scene->addItem(itemPoly);
    }else if (funcBrushType==7){
        bcolor.setAlpha(200);
        pen.setColor(bcolor);
        pen.setWidth(16);
        itemPoly=new MyPolylineItem(pencilLine);
        itemPoly->setPen(pen);
        scene->addItem(itemPoly);
    }else if (funcBrushType==8){
        bcolor.setAlpha(80);
        pen.setColor(bcolor);
        pen.setWidth(3);
        itemPoly=new MyPolylineItem(pencilLine);
        itemPoly->setPen(pen);
        scene->addItem(itemPoly);
    }else if(funcBrushType==9){

    }

    pencilLine.clear();
    calliLines.clear();
}

void MainWindow::pre4BrushFunc(QPoint iPnt)
{
    if (funcBrushType==2||funcBrushType==3||funcBrushType==6)
    {
        QPoint movePnt=iPnt-startPnt;
        QPoint amovePnt;
        int bmax;
        int bmin;
        if (movePnt.x()>0){
            amovePnt.setX(movePnt.x());
        }else {
            amovePnt.setX(-movePnt.x());
        }

        if (movePnt.y()>0){
            amovePnt.setY(movePnt.y());
        }else {
            amovePnt.setY(-movePnt.y());
        }

        if (amovePnt.y()-amovePnt.x()>0){
            bmax=amovePnt.y();
            bmin=amovePnt.x();
        }else {
            bmax=amovePnt.x();
            bmin=amovePnt.y();
        }

        if (funcBrushType==2)
        {
            for (int j=0;j<=(bmax/1);j++)
            {
                calliLines.append(QLine(startPnt+j*movePnt*1/bmax-QPoint(-4,4),
                                             startPnt+j*movePnt*1/bmax+QPoint(-4,4)));
            }
            startPnt=iPnt;
        }
        else if (funcBrushType==3)
        {
            for (int j=0;j<=(bmax/1);j++)
            {
                calliLines.append(QLine(startPnt+j*movePnt*1/bmax+QPoint(4,4),
                                             startPnt+j*movePnt*1/bmax-QPoint(4,4)));
            }
            startPnt=iPnt;
        }
        else if (funcBrushType==6)
        {
            pencilLine.append(iPnt);
//            if (startPnt!=iPnt)
//            {
//                for (unsigned int j=0;j<10;j++){
//                    int x=rand()%20;
//                    int y=rand()%20;
//                    airPnts.append(iPnt+QPoint(x-5,y-5));
//                }
//                for (unsigned int k=0;k<40;k++){
//                    int x=rand()%3+12;
//                    int y=rand()%10;
//                    int x1=x*movePnt.y()/sqrt(pow(movePnt.x(),2)+pow(movePnt.y(),2))+y*movePnt.x()/sqrt(pow(movePnt.x(),2)+pow(movePnt.y(),2));
//                    int y1=-x*movePnt.x()/sqrt(pow(movePnt.x(),2)+pow(movePnt.y(),2))+y*movePnt.y()/sqrt(pow(movePnt.x(),2)+pow(movePnt.y(),2));
//                    airPnts.append(startPnt+QPoint(x1,y1));
//                    airPnts.append(startPnt-QPoint(x1,y1));
//                }

//            }
//            startPnt=iPnt;
        }
    }

            if (funcBrushType==1)
            {
                pencilLine.append(iPnt);
                bWidth=5;
            }

            else if (funcBrushType==4)
            {
//                startPnt=iPnt;
            }
            else if (funcBrushType==5)
            {
                startPnt=iPnt;
            }

            else if (funcBrushType==7)
            {
                pencilLine.append(iPnt);
                bWidth=16;
            }
            else if (funcBrushType==8)
            {
                pencilLine.append(iPnt);
                bWidth=3;
            }
            else if (funcBrushType==9)
            {
                startPnt=iPnt;
            }
}

void MainWindow::penStyleChange(const TextureType &value)
{
    ui->action_p1->setChecked(false);
    ui->action_p2->setChecked(false);
    ui->action_p3->setChecked(false);
    ui->action_p4->setChecked(false);
    ui->action_p5->setChecked(false);
    ui->action_p6->setChecked(false);
    ui->action_p7->setChecked(false);
    if (value==solid){
        ui->action_p2->setChecked(true);
    }else if(value==none){
        ui->action_p1->setChecked(true);
    }else if(value==crayon){
        ui->action_p3->setChecked(true);
    }else if(value==marker){
        ui->action_p4->setChecked(true);
    }else if(value==oil){
        ui->action_p5->setChecked(true);
    }else if(value==pencil){
        ui->action_p6->setChecked(true);
    }else if(value==water){
        ui->action_p7->setChecked(true);
    }
    pentype=value;
    ui->view->mywidget->setPentype(value);
    if (!scene->selectedItems().isEmpty()){
        dynamic_cast<MyItem *>(scene->selectedItems()[0])->setPentype(value);
        scene->update();
    }
}

void MainWindow::brushStyleChange(const TextureType &value)
{
    ui->action_b1->setChecked(false);
    ui->action_b2->setChecked(false);
    ui->action_b3->setChecked(false);
    ui->action_b4->setChecked(false);
    ui->action_b5->setChecked(false);
    ui->action_b6->setChecked(false);
    ui->action_b7->setChecked(false);
    if (value==solid){
        ui->action_b2->setChecked(true);
    }else if(value==none){
        ui->action_b1->setChecked(true);
    }else if(value==crayon){
        ui->action_b3->setChecked(true);
    }else if(value==marker){
        ui->action_b4->setChecked(true);
    }else if(value==oil){
        ui->action_b5->setChecked(true);
    }else if(value==pencil){
        ui->action_b6->setChecked(true);
    }else if(value==water){
        ui->action_b7->setChecked(true);
    }
    brushtype=value;
    ui->view->mywidget->setBrushtype(value);
    if (!scene->selectedItems().isEmpty()){
        dynamic_cast<MyItem *>(scene->selectedItems()[0])->setBrushtype(value);
        scene->update();
    }
}

void MainWindow::funcBrushTypeChange()
{
    ui->action_1->setChecked(false);
    ui->action_2->setChecked(false);
    ui->action_3->setChecked(false);
    ui->action_4->setChecked(false);
    ui->action_5->setChecked(false);
    ui->action_6->setChecked(false);
    ui->action_7->setChecked(false);
    ui->action_8->setChecked(false);
    ui->action_9->setChecked(false);
    switch (funcBrushType) {
    case 1:
        ui->action_1->setChecked(true);
        break;
    case 2:
        ui->action_2->setChecked(true);
        break;
    case 3:
        ui->action_3->setChecked(true);
        break;
    case 4:
        ui->action_4->setChecked(true);
        break;
    case 5:
        ui->action_5->setChecked(true);
        break;
    case 6:
        ui->action_6->setChecked(true);
        break;
    case 7:
        ui->action_7->setChecked(true);
        break;
    case 8:
        ui->action_8->setChecked(true);
        break;
    case 9:
        ui->action_9->setChecked(true);
        break;
    }
    ui->view->mywidget->setCursor(Qt::CrossCursor);
}

void MainWindow::selectedItemPenSet(QColor color)
{
    if (!scene->selectedItems().isEmpty()){
        QPen pen(color);
        pen.setWidth(lWidth);
        dynamic_cast<MyItem *>(scene->selectedItems()[0])->setPen(pen);
        dynamic_cast<MyItem *>(scene->selectedItems()[0])->setPentype(pentype);
        scene->update();
    }
}

void MainWindow::selectedItemBrushSet(QColor color)
{
    if (!scene->selectedItems().isEmpty()){
        QBrush brush(color);
        dynamic_cast<MyItem *>(scene->selectedItems()[0])->setBrush(brush);
        dynamic_cast<MyItem *>(scene->selectedItems()[0])->setBrushtype(brushtype);
        scene->update();
    }
}

void MainWindow::setItemWidth()
{
    ui->view->setEraserWidth(lWidth);
    ui->view->mywidget->setEraserWidth(lWidth);
    if (!scene->selectedItems().isEmpty()){
        MyItem *item=dynamic_cast<MyItem *>(scene->selectedItems()[0]);
        QPen pen=item->getMyPen();
        pen.setWidth(lWidth);
        item->setPen(pen);
        item->setMyPen(pen);
        scene->update();
    }
    ui->act3px->setChecked(false);
    ui->act5px->setChecked(false);
    ui->act1px->setChecked(false);
    ui->act8px->setChecked(false);
    switch (lWidth) {
        case 1:
        ui->act1px->setChecked(true);
        break;
    case 3:
        ui->act3px->setChecked(true);
        break;
    case 5:
        ui->act5px->setChecked(true);
        break;
    case 8:
        ui->act8px->setChecked(true);
        break;
    }

}

void MainWindow::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    ui->view->mywidget->hide();
}

void MainWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    ui->view->mywidget->show();
}

int MainWindow::test4Anything()
{
//    QString str=tr("C:\\Users\\Administrator\\Desktop\\123.bmp");
//    TCHAR *ptch = (TCHAR *)(str.toStdWString().c_str());
//    qDebug()<<"C:\\Users\\Administrator\\Desktop\\123.bmp"<<*ptch<<PVOID(ptch);
//    qDebug()<<SystemParametersInfo(SPI_SETDESKWALLPAPER,0,PVOID(ptch),0);
    return 1;
}

QRect MainWindow::freeSelArea(QPolygon poly)
{
    QList<int> xs;
    QList<int> ys;
    int xmin=0;
    int ymin=0;
    int xmax=0;
    int ymax=0;
    for (int i = 0; i < poly.length(); ++i) {
        xs.append(poly[i].x());
        ys.append(poly[i].y());
        if (i==0){
            xmin=poly[i].x();
            ymin=poly[i].y();
            xmax=poly[i].x();
            ymax=poly[i].y();
        }else {
            xmin=int(std::min(xmin,poly[i].x()));
            ymin=int(std::min(ymin,poly[i].y()));
            xmax=int(std::max(xmax,poly[i].x()));
            ymax=int(std::max(ymax,poly[i].y()));
        }
    }

    return QRect(xmin,ymin,xmax-xmin,ymax-ymin);
}

void MainWindow::setSceneSizeLabel()
{
    QString str1;
    QString str2;
    str1.setNum(ui->view->rect().width());
    str2.setNum(ui->view->rect().height());
    str1.append("x");
    str1.append(str2);
    str1.append("像素");
    labelSceneSize->setText(str1);
}

void MainWindow::addLRArrow(QPoint point1, QPoint point2)
{
    QPainterPath iPath;
    iPath.moveTo((point2.x()+point1.x())/2,point1.y());
    iPath.lineTo((point2.x()+point1.x())/2,(3*point1.y()+point2.y())/4);
    iPath.lineTo(point1.x(),(3*point1.y()+point2.y())/4);
    iPath.lineTo(point1.x(),(3*point2.y()+point1.y())/4);
    iPath.lineTo((point2.x()+point1.x())/2,(3*point2.y()+point1.y())/4);
    iPath.lineTo((point2.x()+point1.x())/2,point2.y());
    iPath.lineTo(point2.x(),(point2.y()+point1.y())/2);
    iPath.lineTo((point2.x()+point1.x())/2,point1.y());
    item=new MyPathItem(iPath);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    item->setPen(QPen(itemProperty.getPen(),lWidth));
    item->setBrush(itemProperty.getBrush());
    item->setPentype(pentype);
    item->setBrushtype(brushtype);
    scene->addItem(item);
}

void MainWindow::addUDArrow(QPoint point1, QPoint point2)
{
    QPainterPath iPath;
    iPath.moveTo((point2.x()+point1.x())/2,point1.y());
    iPath.lineTo(point1.x(),(point1.y()+point2.y())/2);
    iPath.lineTo((point2.x()+3*point1.x())/4,(point2.y()+point1.y())/2);
    iPath.lineTo((point2.x()+3*point1.x())/4,point2.y());
    iPath.lineTo((3*point2.x()+point1.x())/4,point2.y());
    iPath.lineTo((3*point2.x()+point1.x())/4,(point2.y()+point1.y())/2);
    iPath.lineTo(point2.x(),(point1.y()+point2.y())/2);
    iPath.lineTo((point2.x()+point1.x())/2,point1.y());
    item=new MyPathItem(iPath);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    item->setPen(QPen(itemProperty.getPen(),lWidth));
    item->setBrush(itemProperty.getBrush());
    item->setPentype(pentype);
    item->setBrushtype(brushtype);
    scene->addItem(item);
}

void MainWindow::on_btnText_clicked()
{
    i=26;
    checkstate(i);
}

void MainWindow::on_btnWhite_clicked()
{
    QColor pcolor=QColor(255,255,255);
    if (ui->btnColor1->isChecked()){
    itemProperty.setPen(QColor(255,255,255));
    ui->view->mywidget->setMyPen(pcolor);
    itemProperty.setFillC(qRgb(255,255,255));
    ui->btnColor1->setIcon(QIcon(":/image/白色.png"));
    selectedItemPenSet(pcolor);
    }else {
        itemProperty.setBrush(QColor(255,255,255));
        ui->view->mywidget->setMyBrush(pcolor);
        ui->btnColor2->setIcon(QIcon(":/image/白色.png"));
        selectedItemBrushSet(pcolor);
    }
}

void MainWindow::on_btnBrush_clicked()
{
    checkstate(28);
}

void MainWindow::on_action_1_triggered()
{
    ui->view->mywidget->setFuncBrushType(1);
    funcBrushType=1;
    checkstate(28);
}

void MainWindow::on_action_2_triggered()
{
    ui->view->mywidget->setFuncBrushType(2);
    funcBrushType=2;
    checkstate(28);
}

void MainWindow::on_action_3_triggered()
{
    ui->view->mywidget->setFuncBrushType(3);
    funcBrushType=3;
    checkstate(28);
}

void MainWindow::on_action_4_triggered()
{
    ui->view->mywidget->setFuncBrushType(4);
    funcBrushType=4;
    checkstate(28);
}

void MainWindow::on_action_5_triggered()
{
    ui->view->mywidget->setFuncBrushType(5);
    funcBrushType=5;
    checkstate(28);
}

void MainWindow::on_action_6_triggered()
{
    ui->view->mywidget->setFuncBrushType(6);
    funcBrushType=6;
    checkstate(28);
}

void MainWindow::on_action_7_triggered()
{
    ui->view->mywidget->setFuncBrushType(7);
    funcBrushType=7;
    checkstate(28);
}

void MainWindow::on_action_8_triggered()
{
    ui->view->mywidget->setFuncBrushType(8);
    funcBrushType=8;
    checkstate(28);
}

void MainWindow::on_action_9_triggered()
{
    ui->view->mywidget->setFuncBrushType(9);
    funcBrushType=9;
    checkstate(28);
}

void MainWindow::on_action_p1_triggered()
{
    penStyleChange(none);
}

void MainWindow::on_action_p2_triggered()
{
    penStyleChange(solid);
}

void MainWindow::on_action_p3_triggered()
{
    penStyleChange(crayon);
}

void MainWindow::on_action_p4_triggered()
{
    penStyleChange(marker);
}

void MainWindow::on_action_p5_triggered()
{
    penStyleChange(oil);
}

void MainWindow::on_action_p6_triggered()
{
    penStyleChange(pencil);
}

void MainWindow::on_action_p7_triggered()
{
    penStyleChange(water);
}

void MainWindow::on_action_b1_triggered()
{
    brushStyleChange(none);
}

void MainWindow::on_action_b2_triggered()
{
    brushStyleChange(solid);
}

void MainWindow::on_action_b3_triggered()
{
    brushStyleChange(crayon);
}

void MainWindow::on_action_b4_triggered()
{
    brushStyleChange(marker);
}

void MainWindow::on_action_b5_triggered()
{
    brushStyleChange(oil);
}

void MainWindow::on_action_b6_triggered()
{
    brushStyleChange(pencil);
}

void MainWindow::on_action_b7_triggered()
{
    brushStyleChange(water);
}

void MainWindow::on_act_Undo_triggered()
{
    QGraphicsItem* itemDe=scene->items()[0];
    scene->removeItem(itemDe);
    itemUndo.append(itemDe);
    scene->update();
}

void MainWindow::on_act_Redo_triggered()
{
    if (!itemUndo.isEmpty())
    {scene->addItem(itemUndo.takeLast());}
    scene->update();

}

void MainWindow::on_actPaste_triggered()
{
    itemList=scene->items();
    if (!itemList.isEmpty()){
        itemList[0]->setFlag(QGraphicsItem::ItemIsSelectable,false);
        itemList[0]->setFlag(QGraphicsItem::ItemIsMovable,false);
        itemList[0]->setAcceptHoverEvents(false);
        itemList[0]->setSelected(false);
    }
    QClipboard *clipboard=QApplication::clipboard();
    QImage img=clipboard->image();
    itemImage=new MyImageItem(img);
    itemImage->setFlag(QGraphicsItem::ItemIsSelectable);
    itemImage->setFlag(QGraphicsItem::ItemIsMovable);
    itemImage->setSelected(true);
    scene->addItem(itemImage);
    scene->update();
}

void MainWindow::on_actRectSel_triggered()
{
    i=30;
    checkstate(i);
}

void MainWindow::on_btnPasteF_clicked()
{
    MainWindow::on_actPaste_triggered();
}

void MainWindow::on_actFreeSel_triggered()
{
    i=31;
    checkstate(i);
}

void MainWindow::on_btnCopy_clicked()
{
    QClipboard *clipboard=QApplication::clipboard();
    if (i==31&&!scene->selectedItems().isEmpty()){
        QPixmap pix;
        pix=dynamic_cast<MyFreeShapeSelItem *>(scene->selectedItems().last())->getSelPixmap();
        clipboard->setPixmap(pix);
    }else if(i==30&&!scene->selectedItems().isEmpty()){
        QImage img;
        img=dynamic_cast<MyRectSelItem *>(scene->selectedItems().last())->getImgr();
        clipboard->setImage(imgr);
    }
}

void MainWindow::on_btnCut_clicked()
{
    QClipboard *clipboard=QApplication::clipboard();
    if (i==31&&!scene->selectedItems().isEmpty()){
        QPixmap pix;
        pix=dynamic_cast<MyFreeShapeSelItem *>(scene->selectedItems().last())->getSelPixmap();
        clipboard->setPixmap(pix);
    }else if(i==30&&!scene->selectedItems().isEmpty()){
        QImage img;
        img=dynamic_cast<MyRectSelItem *>(scene->selectedItems().last())->getImgr();
        clipboard->setImage(imgr);
    }
    QGraphicsItem* itemDe=scene->items()[0];
    scene->removeItem(itemDe);
    scene->update();
}

void MainWindow::on_btnClip_clicked()
{
    if(i==30&&!scene->selectedItems().isEmpty()){
        ui->view->setGeometry(0,140,eendPnt.x()-sstartPnt.x(),eendPnt.y()-sstartPnt.y());
        ui->view->centerOn(0.5*(sstartPnt+eendPnt));
    }else if (i==31&&!scene->selectedItems().isEmpty()) {
        ui->view->setGeometry(0,140,rectOfSel.width(),rectOfSel.height());
        ui->view->centerOn(rectOfSel.center());
    }
}

void MainWindow::on_btnResize_clicked()
{
    ui->view->mywidget->hide();
    dialogResize dResize(this);
    int owidth=ui->view->width();
    int oheight=ui->view->height();
    dResize.setSceneWidth(ui->view->width());
    dResize.setSceneHeight(ui->view->height());
    int state=dResize.exec();
    if (state==QDialog::Accepted){
        int nwidth=dResize.getSceneWidth();
        int nheight=dResize.getSceneHeight();
        int vrotate=dResize.getVerticalRotate();
        int hrotate=dResize.getHorizonRotate();
        if (dResize.radioBtnState())
        {
            ui->view->setGeometry(0,140,owidth*nwidth/100,oheight*nheight/100);
            ui->view->scale(nwidth/100.0,nheight/100.0);
            ui->view->shear(tan(vrotate/3.14),tan(hrotate/3.14));
        }
        else {
            ui->view->setGeometry(0,140,nwidth,nheight);
            ui->view->scale(qreal(nwidth)/owidth,qreal(nheight)/oheight);
            ui->view->shear(tan(vrotate/3.14),tan(hrotate/3.14));
        }
        if (Tick){
            ui->view->move(20,160);
        }
    }
    ui->view->mywidget->show();
}

void MainWindow::on_actSelAll_triggered()
{
    QRect rect=QRect(+1,1,
               ui->view->width(),
               ui->view->height());
    pixr=ui->view->grab(rect);
    imgr=pixr.toImage();
    imgr.fill(itemProperty.getBrush().color());
    itemRectSel=new MyRectSelItem(ui->view->rect(),imgr);
    scene->addItem(itemRectSel);
    imgr=pixr.toImage();
    itemRectSel=new MyRectSelItem(ui->view->rect(),imgr);
    itemRectSel->setFlag(QGraphicsItem::ItemIsSelectable);
    itemRectSel->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(itemRectSel);
}

void MainWindow::on_actInveSel_triggered()
{
    if (i==30||i==31){
            QGraphicsItem* itemDe=scene->items()[0];
            scene->removeItem(itemDe);
            delete itemDe;
            itemDe=scene->items()[0];
            scene->removeItem(itemDe);
            delete itemDe;
}
    QRect rect=QRect(1,1,
               ui->view->width(),
               ui->view->height());
    pixr=ui->view->grab(rect);
    imgr=pixr.toImage();
    imgr.fill(itemProperty.getBrush().color());
    if (i==31)
    {
        QPixmap pix=ui->view->grab(QRect(rectOfSel.topLeft()+QPoint(1,1),rectOfSel.bottomRight()+QPoint(1,1)));
        itemFreeSel=new MyFreeShapeSelItem(rectOfSel,freeShapePnts,pix);
        itemFreeSel->setBrush(itemProperty.getBrush());
        itemRectSel=new MyRectSelItem(ui->view->rect(),imgr);
        scene->addItem(itemRectSel);
        scene->addItem(itemFreeSel);
        itemInSel=new myInvertSelItem(rect,freeShapePnts,pixr);
    }else if (i==30){
        QPixmap pix=ui->view->grab(rectOfSel);
        QImage img=pix.toImage();
        itemRectSel=new MyRectSelItem(ui->view->rect(),imgr);
        scene->addItem(itemRectSel);
        itemRectSel=new MyRectSelItem(QRect(rectOfSel.topLeft()-QPoint(1,1),rectOfSel.bottomRight()-QPoint(1,1)),img);
        scene->addItem(itemRectSel);
        itemInSel=new myInvertSelItem(rect,rectOfSel,pixr);
    }
    itemInSel->setFlag(QGraphicsItem::ItemIsSelectable);
    itemInSel->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(itemInSel);
    scene->update();
}

void MainWindow::on_actVertRot_triggered()
{
    ui->actRotL->setChecked(false);
    ui->actRot180->setChecked(false);
    ui->actRotR->setChecked(false);
    ui->actHoriRot->setChecked(false);
    MyItem *itemF=dynamic_cast<MyItem *>(scene->selectedItems().first());
    if (itemF->getVertFlip())
    {
        itemF->setVertFlip(false);
    }else {
        itemF->setVertFlip(true);
    }
    scene->update();
}

void MainWindow::on_actHoriRot_triggered()
{
    ui->actRotL->setChecked(false);
    ui->actRot180->setChecked(false);
    ui->actVertRot->setChecked(false);
    ui->actRotR->setChecked(false);
    MyItem *itemF=dynamic_cast<MyItem *>(scene->selectedItems().first());
    if (itemF->getHoriFilp())
    {
        itemF->setHoriFilp(false);
    }else {
        itemF->setHoriFilp(true);
    }
    scene->update();
}

void MainWindow::on_actPasteF_triggered()
{
    ui->view->mywidget->hide();
    QString filename=QFileDialog::getOpenFileName(this,"打开文件","",tr("所有图片文件(*.bmp;*.dib;*.png;*.jpg;*.jpeg;*.tif;*.gif;*.ico);;"
                                                          "位图文件(*.bmp;*.dib);;JPEG(*.jpg;*.jpeg);;"
                                                          "PNG(*.png);;TIF(*.tif;*.tiff);;GIF(*.gif)"
                                                          ));
    if(filename.isEmpty())
    {return;}
    else{
        QImage img;
        if(!(img.load(filename))) //加载图像
        {
            QMessageBox::information(this, tr("打开图像失败"),tr("打开图像失败!"));
            return;
        }
        scene->addPixmap(QPixmap::fromImage(img));
        scene->items().first()->setFlag(QGraphicsItem::ItemIsSelectable);
        scene->items().first()->setFlag(QGraphicsItem::ItemIsMovable);
        scene->items().first()->setSelected(true);
    }
    ui->view->show();
}

void MainWindow::on_actPrint_triggered()
{
    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle("打印");
    if (dialog->exec() != QDialog::Accepted)
    {return;}
//    QPrintPreviewDialog *dlg=new QPrintPreviewDialog(&printer,this);
//    dlg->exec();
    int ori=dialog->orientation();
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出PDF文件"), QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        // 如果文件后缀为空，则默认使用.pdf
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        // 指定输出格式为pdf
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        printer.setOrientation(QPrinter::Orientation(ori));
        QPainter painterPixmap;
        QPixmap pixmap= ui->view->grab(QRect(1,1,1098,488));
        painterPixmap.begin(&printer);
//        QRect rect = painterPixmap.viewport();
//        int x = rect.width() / pixmap.width();
//        int y = rect.height() / pixmap.height();
//        painterPixmap.scale(x, y);
        painterPixmap.drawPixmap(0, 0, pixmap);
        painterPixmap.end();
        qDebug()<<printer.orientation();
    }
}

void MainWindow::on_actDeliverFromEmail_triggered()
{
    const QUrl url("http://www.mail.qq.com");
    qDebug() << url.scheme();
    qDebug() << url.port();
    QDesktopServices::openUrl(url);
}

void MainWindow::on_actSetAsDesktopBackground_triggered()
{
    if (filenameSave.isNull()){
        QMessageBox::information(this,"画图","在将它选为桌面背景前必须保存该文件");
        return;
    }
//    const wchar_t *ptch = (const wchar_t *)(filenameSave.toStdWString().c_str());
//    qDebug()<<filenameSave<<*ptch;
//    SystemParametersInfo(SPI_SETDESKWALLPAPER,true,PVOID(ptch),SPIF_UPDATEINIFILE);
}

void MainWindow::on_actProperty_triggered()
{
    paintAttributeDialog dialog;
    if (!filenameSave.isNull())
    {
        QFileInfo info(filenameSave);
        QDateTime dt=info.lastModified();
        dialog.setRecentMessage(dt.toString(),info.size());
    }
    if (dialog.exec()==QDialog::Accepted)
    {
        QSize size=dialog.getSize();
        if (dialog.getSt()==Attribute::inch){
            ui->view->setGeometry(0,140,size.width()*120,size.height()*120);
        }else if (dialog.getSt()==Attribute::cm){
            ui->view->setGeometry(0,140,size.width()*120/2.5,size.height()*120/2.54);
        }else {
            ui->view->setGeometry(0,140,size.width(),size.height());
        }
        if (dialog.getBw()){
            QSize s=ui->view->size();
            QImage img=ui->view->grab(QRect(QPoint(1,1),QSize(s.width()-2,s.height()-2))).toImage();
            img.convertToFormat(QImage::Format_Grayscale8);
            MyImageItem *imgI=new MyImageItem(img);
            scene->addItem(imgI);
        }
    }
}

void MainWindow::on_actAbout_triggered()
{

}

void MainWindow::on_actExit_triggered()
{
    exit(0);
}

void MainWindow::on_btnBigger_clicked()
{
    int width=ui->view->rect().width();
    int height=ui->view->rect().height();
    ui->view->setGeometry(0,140,2*width,2*height);
    if (Tick){
        ui->view->move(20,160);
    }
    ui->view->mywidget->setSizeRatio(ui->view->mywidget->getSizeRatio()*2);
    ui->view->mywidget->setFixedSize(QSize(1101,491)*ui->view->mywidget->getSizeRatio());
    ui->view->scale(2,2);
    ui->view->mywidget->hide();
    ui->view->mywidget->show();
//    ui->view->mywidget->show();
}

void MainWindow::on_btnSmaller_clicked()
{
    int width=ui->view->rect().width();
    int height=ui->view->rect().height();
    ui->view->setGeometry(0,140,0.5*width,0.5*height);
    if (Tick){
        ui->view->move(20,160);
    }
    ui->view->mywidget->setSizeRatio(ui->view->mywidget->getSizeRatio()*0.5);
    ui->view->mywidget->setFixedSize(QSize(1101,491)*ui->view->mywidget->getSizeRatio());
    ui->view->scale(0.5,0.5);
    ui->view->mywidget->hide();
    ui->view->mywidget->show();
}

void MainWindow::on_btnHundred_clicked()
{
    ui->view->setGeometry(0,140,1101,491);
    if (Tick){
        ui->view->move(20,160);
    }
    ui->view->mywidget->setSizeRatio(1);
    ui->view->mywidget->hide();
    ui->view->mywidget->show();
}

void MainWindow::on_btnFullScreen_clicked()
{
//    IndependentForm widFull();
    fullScrWidget *label1=new fullScrWidget();
    label1->setPixmap(ui->view->grab());
    label1->setAlignment(Qt::AlignCenter);
    label1->showFullScreen();
//    if (label1->)
}

void MainWindow::on_btnPrePic_clicked()
{
    QLabel *label=new QLabel();
    QPixmap pix=QPixmap::fromImage(ui->view->grab().toImage().scaled(240,100,Qt::KeepAspectRatio));
    label->setPixmap(pix);;
    label->setAlignment(Qt::AlignCenter);
    label->setGeometry(QRect(mapToGlobal(QPoint(500,300)),QSize(240,100)));
    label->setWindowFlag(Qt::WindowStaysOnTopHint);
    label->show();
}

void MainWindow::on_checkBox_3_clicked(bool checked)
{
    if (checked){
        ui->statusBar->show();
    }else {
        ui->statusBar->hide();
    }
    ui->view->mywidget->hide();
    ui->view->mywidget->show();
}

void MainWindow::on_checkBox_2_clicked(bool checked)
{
//    qDebug()<<checked;
    ui->view->mywidget->setGridOn(checked);
    ui->view->mywidget->hide();
    ui->view->mywidget->show();
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked){
        ui->view->move(20,160);
        ui->view->mywidget->move(mapToGlobal(QPoint(20,200)));
        Tick=true;
    }else {
        ui->view->move(0,140);
        ui->view->mywidget->move(mapToGlobal(QPoint(0,180)));
        Tick=false;
    }
    ui->view->mywidget->hide();
    ui->view->mywidget->show();
}
