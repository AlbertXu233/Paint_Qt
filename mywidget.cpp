#include <mywidget.h>
#include <QPainter>
#include <qevent.h>
#include <qtextedit.h>
#include <QDebug>
#include <qtimer.h>


void myWidget::setHasGlass(bool value)
{
    hasGlass = value;
}

void myWidget::setTextEditMode(bool value)
{
    textEditMode = value;
}

void myWidget::setEraserMode(bool value)
{
    eraserMode = value;
}

void myWidget::setIsPressed(bool value)
{
    isPressed = value;
}

void myWidget::setUpdateMode(bool value)
{
    updateMode = value;
}

QPoint myWidget::getLocalStartPnt() const
{
    return localStartPnt;
}

void myWidget::setLocalStartPnt(const QPoint &value)
{
    localStartPnt = value;
}

QPoint myWidget::getLocalEndPnt() const
{
    return localEndPnt;
}

void myWidget::setLocalEndPnt(const QPoint &value)
{
    localEndPnt = value;
}

QPoint myWidget::getCurrentPnt() const
{
    return currentPnt;
}

void myWidget::setCurrentPnt(const QPoint &value)
{
    currentPnt = value;
}

void myWidget::setEraserWidth(int value)
{
    eraserWidth = value;
    shapeWidth = value;
    myPen.setWidth(value);
}

QString myWidget::getTextInput() const
{
    return textInput;
}

QVector<QRect> myWidget::getEraserRectsOut() const
{
    return eraserRectsOut;
}



void myWidget::setShapeType(int value)
{
    shapeType = value;
}

void myWidget::setFuncBrushMode(bool value)
{
    funcBrushMode = value;
}

void myWidget::setFuncBrushType(int value)
{
    funcBrushType = value;
    funcBrushPenMidSet();
    funcBrushPenEdgeSet();
}

void myWidget::clearAirbrushPoints()
{
    airbrushPoints.clear();
}

QVector<QPoint> myWidget::getAirbrushPoints() const
{
    return airbrushPoints;
}

QPolygon myWidget::getBrushPolygon() const
{
    return brushPolygon;
}

int myWidget::getFuncBrushType() const
{
    return funcBrushType;
}

int myWidget::getBWidth() const
{
    return bWidth;
}

void myWidget::setBWidth(int value)
{
    bWidth = value;
}

void myWidget::setMyPen(const QPen &value)
{
    myPen = value;
    if (funcBrushType==6){
        funcBrushPenMidSet();
        funcBrushPenEdgeSet();
    }
}

void myWidget::setMyBrush(const QBrush &value)
{
    myBrush = value;
    myBrushStyleSet();
}

void myWidget::setBrushtype(const TextureType &value)
{
    brushtype = value;
    myBrushStyleSet();
}

void myWidget::setPentype(const TextureType &value)
{
    pentype = value;
    myPenStyleSet();
}

void myWidget::funcBrushPenMidSet()
{
    if (funcBrushType==6){
        funcBrushPenM=myPen;
        QImage image(":/image/黑色蜡笔刷中.png");
//        image.save()
        if (myPen.color()!=QColor(0,0,0)){
            QColor color=myPen.color();
            int r=color.red();
            int g=color.green();
            int b=color.blue();
            for (int i=0;i<image.size().width();i++){
                for (int j=0;j<image.size().height();j++) {
                    qreal ratio=image.pixelColor(i,j).red()/255.0;
                    image.setPixel(i,j,qRgb(r+(255-r)*ratio,g+(255-g)*ratio,b+(255-b)*ratio));
                }
            }
        }
        funcBrushPenM.setBrush(QBrush(image));
    }
}

void myWidget::funcBrushPenEdgeSet()
{
    if (funcBrushType==6){
        funcBrushPenE=myPen;
        QImage image(":/image/黑色蜡笔刷侧.png");
        if (myPen.color()!=QColor(0,0,0)){
            QColor color=myPen.color();
            int r=color.red();
            int g=color.green();
            int b=color.blue();
            for (int i=0;i<image.size().width();i++){
                for (int j=0;j<image.size().height();j++) {
                    qreal ratio=image.pixelColor(i,j).red()/255.0;
                    image.setPixel(i,j,qRgb(r+(255-r)*ratio,g+(255-g)*ratio,b+(255-b)*ratio));
                }
            }
        }
//        qDebug()<<"edge";
        funcBrushPenE.setBrush(QBrush(image));
    }
}

QPen myWidget::getFuncBrushPenM() const
{
    return funcBrushPenM;
}

QPen myWidget::getFuncBrushPenE() const
{
    return funcBrushPenE;
}

QVector<QPoint> myWidget::getPgPnts() const
{
    return pgPnts;
}

void myWidget::setGridOn(bool value)
{
    gridOn = value;
}

void myWidget::setSizeRatio(const qreal &value)
{
    sizeRatio = value;
}

qreal myWidget::getSizeRatio() const
{
    return sizeRatio;
}

void myWidget::myPenStyleSet()
{
    if (pentype==solid){

    }else if(pentype==none){
        myPen=Qt::NoPen;
    }else if (pentype==crayon) {
        QImage image(":/image/黑色蜡笔.png");
        if (myPen.color()!=QColor(0,0,0)){
            QColor color=myPen.color();
            int r=color.red();
            int g=color.green();
            int b=color.blue();
            for (int i=0;i<image.size().width();i++){
                for (int j=0;j<image.size().height();j++) {
                    qreal ratio=image.pixelColor(i,j).red()/255.0;
                    image.setPixel(i,j,qRgb(r+(255-r)*ratio,g+(255-g)*ratio,b+(255-b)*ratio));
                }
            }
        }
        QBrush brush(image);
        myPen.setBrush(brush);
    }else if(pentype==marker){
        QColor color=myPen.color();
        color.setAlpha(200);
        myPen.setColor(color);
    }else if(pentype==oil){

        QImage image(":/image/黑色油画.png");
        if (myPen.color()!=QColor(0,0,0)){
            QColor color=myPen.color();
            int r=color.red();
            int g=color.green();
            int b=color.blue();
            for (int i=0;i<image.size().width();i++){
                for (int j=0;j<image.size().height();j++) {
                    qreal ratio=image.pixelColor(i,j).red()/255.0;
                    image.setPixel(i,j,qRgb(r+(255-r)*ratio,g+(255-g)*ratio,b+(255-b)*ratio));
                }
            }
        }
        QBrush brush(image);
        myPen.setBrush(brush);
    }else if(pentype==pencil){

        QImage image(":/image/黑色铅笔.png");
        if (myPen.color()!=QColor(0,0,0)){
            QColor color=myPen.color();
            int r=color.red();
            int g=color.green();
            int b=color.blue();
            for (int i=0;i<image.size().width();i++){
                for (int j=0;j<image.size().height();j++) {
                    qreal ratio=image.pixelColor(i,j).red()/255.0;
                    image.setPixel(i,j,qRgb(r+(255-r)*ratio,g+(255-g)*ratio,b+(255-b)*ratio));
                }
            }
        }
        QBrush brush(image);
        myPen.setBrush(brush);
    }else if(pentype==water){

        QImage image(":/image/黑色水彩.png");
        if (myPen.color()!=QColor(0,0,0)){
            QColor color=myPen.color();
            int r=color.red();
            int g=color.green();
            int b=color.blue();
            for (int i=0;i<image.size().width();i++){
                for (int j=0;j<image.size().height();j++) {
                    qreal ratio=image.pixelColor(i,j).red()/255.0;
                    image.setPixel(i,j,qRgb(r+(255-r)*ratio,g+(255-g)*ratio,b+(255-b)*ratio));
                }
            }
        }
        QBrush brush(image);
        myPen.setBrush(brush);
    }
}

void myWidget::myBrushStyleSet()
{
    if (brushtype==solid){
        myBrush.setStyle(Qt::SolidPattern);
    }else if(brushtype==none){
        myBrush=Qt::NoBrush;
    }else if(brushtype==crayon){
        QImage image(":/image/黑色蜡笔.png");
        if (myBrush.color()!=QColor(0,0,0)){
            QColor color=myBrush.color();
            int r=color.red();
            int g=color.green();
            int b=color.blue();
            for (int i=0;i<image.size().width();i++){
                for (int j=0;j<image.size().height();j++) {
                    qreal ratio=image.pixelColor(i,j).red()/255.0;
                    image.setPixel(i,j,qRgb(r+(255-r)*ratio,g+(255-g)*ratio,b+(255-b)*ratio));
                }
            }
        }
        myBrush.setTextureImage(image);
    }else if(brushtype==marker){
        myBrush.setStyle(Qt::SolidPattern);
        QColor color=myBrush.color();
        color.setAlpha(200);
        myBrush.setColor(color);
    }else if(brushtype==oil){
        QImage image(":/image/黑色油画.png");
        if (myBrush.color()!=QColor(0,0,0)){
            QColor color=myBrush.color();
            int r=color.red();
            int g=color.green();
            int b=color.blue();
            for (int i=0;i<image.size().width();i++){
                for (int j=0;j<image.size().height();j++) {
                    qreal ratio=image.pixelColor(i,j).red()/255.0;
                    image.setPixel(i,j,qRgb(r+(255-r)*ratio,g+(255-g)*ratio,b+(255-b)*ratio));
                }
            }
        }
        myBrush=QBrush(image);
    }else if(brushtype==pencil){
        QImage image(":/image/黑色铅笔.png");
        if (myBrush.color()!=QColor(0,0,0)){
            QColor color=myBrush.color();
            int r=color.red();
            int g=color.green();
            int b=color.blue();
            for (int i=0;i<image.size().width();i++){
                for (int j=0;j<image.size().height();j++) {
                    qreal ratio=image.pixelColor(i,j).red()/255.0;
                    image.setPixel(i,j,qRgb(r+(255-r)*ratio,g+(255-g)*ratio,b+(255-b)*ratio));
                }
            }
        }
        myBrush=QBrush(image);
    }else if(brushtype==water){
        QImage image(":/image/黑色水彩.png");
        if (myBrush.color()!=QColor(0,0,0)){
            QColor color=myBrush.color();
            int r=color.red();
            int g=color.green();
            int b=color.blue();
            for (int i=0;i<image.size().width();i++){
                for (int j=0;j<image.size().height();j++) {
                    qreal ratio=image.pixelColor(i,j).red()/255.0;
                    image.setPixel(i,j,qRgb(r+(255-r)*ratio,g+(255-g)*ratio,b+(255-b)*ratio));
                }
            }
        }
        myBrush=QBrush(image);
    }
}

myWidget::myWidget(QWidget *parent) : QWidget (parent)
{
    setMouseTracking(true);
    textinstant=new QTextEdit(this);
    textinstant->setGeometry(0,0,0,0);
    texturePix=new QPixmap(":/image/黑色蜡笔.png");
    setWindowFlags(Qt::Popup) ;
    airbrushTimer=new QTimer(this);
    airbrushTimer->setInterval(50);
    connect(airbrushTimer,SIGNAL(timeout()),this,SLOT(timerTriggerd()));
}

myWidget::~myWidget()
{
}

void myWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);    
    QPainter painter(this);
    painter.fillRect(rect(),QColor(255, 255, 255, 2));
    if (gridOn)
    {
        drawForeground(&painter);
    }
    if (shapeType==6&&pgPnts.length()>1){
        painter.drawPolyline(pgPnts);
    }
    if (isPressed&&((shapeType>=0&&shapeType<22)||shapeType==30||shapeType==31)){
        //绘制瞬时图形
        QPainterPath shapePath;
        QPen pen=myPen;
        pen.setWidth(shapeWidth);
        painter.setPen(pen);
        painter.setBrush(myBrush);
        //利用分支结构来实现不同的瞬时显示
        switch (shapeType)
        {
        case 0:
            painter.drawPolyline(brushPolygon);
            break;
        case 1:
            painter.drawLine(localStartPnt,instantLocalEndPnt);
            break;
        case 2:
            break;
        case 3:
            painter.drawEllipse(QRect(localStartPnt,instantLocalEndPnt));
            break;
        case 4:
            painter.drawRect(QRect(localStartPnt,instantLocalEndPnt));
            break;
        case 5:
            if (instantLocalEndPnt.x()-localStartPnt.x()>0||instantLocalEndPnt.y()-localStartPnt.y()>0){
                painter.drawRoundedRect(QRect(localStartPnt,instantLocalEndPnt),25,25);
            }else {
                painter.drawRoundedRect(QRect(instantLocalEndPnt,localStartPnt),25,25);
            }
            break;
        case 6:
            if (pgPnts.length()>1){
//                painter.drawPolyline(pgPnts);
                painter.drawLine(pgPnts.last(),instantLocalEndPnt);
            }else {
                painter.drawLine(localStartPnt,instantLocalEndPnt);
            }
            break;
        case 7:
            shapePath.moveTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
            shapePath.lineTo(localStartPnt.x(),instantLocalEndPnt.y());
            shapePath.lineTo(instantLocalEndPnt);
            shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
            painter.drawPath(shapePath);
            break;
        case 8:
            shapePath.moveTo(localStartPnt);
            shapePath.lineTo(localStartPnt.x(),instantLocalEndPnt.y());
            shapePath.lineTo(instantLocalEndPnt);
            shapePath.lineTo(localStartPnt);
            painter.drawPath(shapePath);
            break;
        case 9:
            shapePath.moveTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
            shapePath.lineTo(localStartPnt.x(),(instantLocalEndPnt.y()+localStartPnt.y())/2);
            shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,instantLocalEndPnt.y());
            shapePath.lineTo(instantLocalEndPnt.x(),(instantLocalEndPnt.y()+localStartPnt.y())/2);
            shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
            painter.drawPath(shapePath);
            break;
        case 10:
            shapePath.moveTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
            shapePath.lineTo(localStartPnt.x(),(0.588*instantLocalEndPnt.y()+0.951*localStartPnt.y())/1.539);
            shapePath.lineTo((0.31*instantLocalEndPnt.x()+localStartPnt.x())/1.31,instantLocalEndPnt.y());
            shapePath.lineTo((instantLocalEndPnt.x()+0.31*localStartPnt.x())/1.31,instantLocalEndPnt.y());
            shapePath.lineTo(instantLocalEndPnt.x(),(0.588*instantLocalEndPnt.y()+0.951*localStartPnt.y())/1.539);
            shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
            painter.drawPath(shapePath);
            break;
        case 11:
            shapePath.moveTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
            shapePath.lineTo(localStartPnt.x(),(instantLocalEndPnt.y()+3*localStartPnt.y())/4);
            shapePath.lineTo(localStartPnt.x(),(3*instantLocalEndPnt.y()+localStartPnt.y())/4);
            shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,instantLocalEndPnt.y());
            shapePath.lineTo(instantLocalEndPnt.x(),(3*instantLocalEndPnt.y()+localStartPnt.y())/4);
            shapePath.lineTo(instantLocalEndPnt.x(),(instantLocalEndPnt.y()+3*localStartPnt.y())/4);
            shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
            painter.drawPath(shapePath);
            break;
        case 12:
            //绘制向右箭头
            if (instantLocalEndPnt.x()-localStartPnt.x()>0||instantLocalEndPnt.y()-localStartPnt.y()>0){
                shapePath.moveTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
                shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,(3*localStartPnt.y()+instantLocalEndPnt.y())/4);
                shapePath.lineTo(localStartPnt.x(),(3*localStartPnt.y()+instantLocalEndPnt.y())/4);
                shapePath.lineTo(localStartPnt.x(),(3*instantLocalEndPnt.y()+localStartPnt.y())/4);
                shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,(3*instantLocalEndPnt.y()+localStartPnt.y())/4);
                shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,instantLocalEndPnt.y());
                shapePath.lineTo(instantLocalEndPnt.x(),(instantLocalEndPnt.y()+localStartPnt.y())/2);
                shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
            }else {
                shapePath.moveTo((localStartPnt.x()+instantLocalEndPnt.x())/2,instantLocalEndPnt.y());
                shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,(3*instantLocalEndPnt.y()+localStartPnt.y())/4);
                shapePath.lineTo(instantLocalEndPnt.x(),(3*instantLocalEndPnt.y()+localStartPnt.y())/4);
                shapePath.lineTo(instantLocalEndPnt.x(),(3*localStartPnt.y()+instantLocalEndPnt.y())/4);
                shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,(3*localStartPnt.y()+instantLocalEndPnt.y())/4);
                shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,localStartPnt.y());
                shapePath.lineTo(localStartPnt.x(),(localStartPnt.y()+instantLocalEndPnt.y())/2);
                shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,instantLocalEndPnt.y());
            }
            painter.drawPath(shapePath);
            break;
        case 13:
            //绘制向左箭头
            if (instantLocalEndPnt.x()-localStartPnt.x()>0||instantLocalEndPnt.y()-localStartPnt.y()>0){
                shapePath.moveTo((localStartPnt.x()+instantLocalEndPnt.x())/2,instantLocalEndPnt.y());
                shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,(3*instantLocalEndPnt.y()+localStartPnt.y())/4);
                shapePath.lineTo(instantLocalEndPnt.x(),(3*instantLocalEndPnt.y()+localStartPnt.y())/4);
                shapePath.lineTo(instantLocalEndPnt.x(),(3*localStartPnt.y()+instantLocalEndPnt.y())/4);
                shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,(3*localStartPnt.y()+instantLocalEndPnt.y())/4);
                shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,localStartPnt.y());
                shapePath.lineTo(localStartPnt.x(),(localStartPnt.y()+instantLocalEndPnt.y())/2);
                shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,instantLocalEndPnt.y());
            }else {
                shapePath.moveTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
                shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,(3*localStartPnt.y()+instantLocalEndPnt.y())/4);
                shapePath.lineTo(localStartPnt.x(),(3*localStartPnt.y()+instantLocalEndPnt.y())/4);
                shapePath.lineTo(localStartPnt.x(),(3*instantLocalEndPnt.y()+localStartPnt.y())/4);
                shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,(3*instantLocalEndPnt.y()+localStartPnt.y())/4);
                shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,instantLocalEndPnt.y());
                shapePath.lineTo(instantLocalEndPnt.x(),(instantLocalEndPnt.y()+localStartPnt.y())/2);
                shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
            }
            painter.drawPath(shapePath);
            break;
        case 14:
            //绘制向上箭头
            if (instantLocalEndPnt.x()-localStartPnt.x()>0||instantLocalEndPnt.y()-localStartPnt.y()>0){
                shapePath.moveTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
                shapePath.lineTo(localStartPnt.x(),(localStartPnt.y()+instantLocalEndPnt.y())/2);
                shapePath.lineTo((instantLocalEndPnt.x()+3*localStartPnt.x())/4,(instantLocalEndPnt.y()+localStartPnt.y())/2);
                shapePath.lineTo((instantLocalEndPnt.x()+3*localStartPnt.x())/4,instantLocalEndPnt.y());
                shapePath.lineTo((3*instantLocalEndPnt.x()+localStartPnt.x())/4,instantLocalEndPnt.y());
                shapePath.lineTo((3*instantLocalEndPnt.x()+localStartPnt.x())/4,(instantLocalEndPnt.y()+localStartPnt.y())/2);
                shapePath.lineTo(instantLocalEndPnt.x(),(localStartPnt.y()+instantLocalEndPnt.y())/2);
                shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
            }else {
                shapePath.moveTo((localStartPnt.x()+instantLocalEndPnt.x())/2,instantLocalEndPnt.y());
                shapePath.lineTo(instantLocalEndPnt.x(),(instantLocalEndPnt.y()+localStartPnt.y())/2);
                shapePath.lineTo((localStartPnt.x()+3*instantLocalEndPnt.x())/4,(localStartPnt.y()+instantLocalEndPnt.y())/2);
                shapePath.lineTo((localStartPnt.x()+3*instantLocalEndPnt.x())/4,localStartPnt.y());
                shapePath.lineTo((3*localStartPnt.x()+instantLocalEndPnt.x())/4,localStartPnt.y());
                shapePath.lineTo((3*localStartPnt.x()+instantLocalEndPnt.x())/4,(localStartPnt.y()+instantLocalEndPnt.y())/2);
                shapePath.lineTo(localStartPnt.x(),(instantLocalEndPnt.y()+localStartPnt.y())/2);
                shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,instantLocalEndPnt.y());
            }
            painter.drawPath(shapePath);
            break;
        case 15:
            //绘制向下箭头
            if (instantLocalEndPnt.x()-localStartPnt.x()>0||instantLocalEndPnt.y()-localStartPnt.y()>0){
                shapePath.moveTo((localStartPnt.x()+instantLocalEndPnt.x())/2,instantLocalEndPnt.y());
                shapePath.lineTo(instantLocalEndPnt.x(),(instantLocalEndPnt.y()+localStartPnt.y())/2);
                shapePath.lineTo((localStartPnt.x()+3*instantLocalEndPnt.x())/4,(localStartPnt.y()+instantLocalEndPnt.y())/2);
                shapePath.lineTo((localStartPnt.x()+3*instantLocalEndPnt.x())/4,localStartPnt.y());
                shapePath.lineTo((3*localStartPnt.x()+instantLocalEndPnt.x())/4,localStartPnt.y());
                shapePath.lineTo((3*localStartPnt.x()+instantLocalEndPnt.x())/4,(localStartPnt.y()+instantLocalEndPnt.y())/2);
                shapePath.lineTo(localStartPnt.x(),(instantLocalEndPnt.y()+localStartPnt.y())/2);
                shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,instantLocalEndPnt.y());
            }else {
                shapePath.moveTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
                shapePath.lineTo(localStartPnt.x(),(localStartPnt.y()+instantLocalEndPnt.y())/2);
                shapePath.lineTo((instantLocalEndPnt.x()+3*localStartPnt.x())/4,(instantLocalEndPnt.y()+localStartPnt.y())/2);
                shapePath.lineTo((instantLocalEndPnt.x()+3*localStartPnt.x())/4,instantLocalEndPnt.y());
                shapePath.lineTo((3*instantLocalEndPnt.x()+localStartPnt.x())/4,instantLocalEndPnt.y());
                shapePath.lineTo((3*instantLocalEndPnt.x()+localStartPnt.x())/4,(instantLocalEndPnt.y()+localStartPnt.y())/2);
                shapePath.lineTo(instantLocalEndPnt.x(),(localStartPnt.y()+instantLocalEndPnt.y())/2);
                shapePath.lineTo((instantLocalEndPnt.x()+localStartPnt.x())/2,localStartPnt.y());
            }
            painter.drawPath(shapePath);
            break;
        case 16:
            //绘制四角星
            shapePath.moveTo((localStartPnt.x()+instantLocalEndPnt.x())/2,localStartPnt.y());
            shapePath.lineTo((3.73*localStartPnt.x()+1.73*instantLocalEndPnt.x())/5.46,(3.73*localStartPnt.y()+1.73*instantLocalEndPnt.y())/5.46);
            shapePath.lineTo(localStartPnt.x(),(localStartPnt.y()+instantLocalEndPnt.y())/2);
            shapePath.lineTo((3.73*localStartPnt.x()+1.73*instantLocalEndPnt.x())/5.46,(1.73*localStartPnt.y()+3.73*instantLocalEndPnt.y())/5.46);
            shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,instantLocalEndPnt.y());
            shapePath.lineTo((1.73*localStartPnt.x()+3.73*instantLocalEndPnt.x())/5.46,(1.73*localStartPnt.y()+3.73*instantLocalEndPnt.y())/5.46);
            shapePath.lineTo(instantLocalEndPnt.x(),(localStartPnt.y()+instantLocalEndPnt.y())/2);
            shapePath.lineTo((1.73*localStartPnt.x()+3.73*instantLocalEndPnt.x())/5.46,(3.73*localStartPnt.y()+1.73*instantLocalEndPnt.y())/5.46);
            shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,localStartPnt.y());
            painter.drawPath(shapePath);
            break;
        case 17:
            //绘制五角星
            shapePath.moveTo((localStartPnt.x()+instantLocalEndPnt.x())/2,localStartPnt.y());
            shapePath.lineTo((3*localStartPnt.x()+2*instantLocalEndPnt.x())/5,(3*localStartPnt.y()+2*instantLocalEndPnt.y())/5);
            shapePath.lineTo(localStartPnt.x(),(3*localStartPnt.y()+2*instantLocalEndPnt.y())/5);
            shapePath.lineTo((7*localStartPnt.x()+3*instantLocalEndPnt.x())/10,(4*localStartPnt.y()+6*instantLocalEndPnt.y())/10);
            shapePath.lineTo((4*localStartPnt.x()+instantLocalEndPnt.x())/5,instantLocalEndPnt.y());
            shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,(localStartPnt.y()+4*instantLocalEndPnt.y())/5);
            shapePath.lineTo((localStartPnt.x()+4*instantLocalEndPnt.x())/5,instantLocalEndPnt.y());
            shapePath.lineTo((3*localStartPnt.x()+7*instantLocalEndPnt.x())/10,(4*localStartPnt.y()+6*instantLocalEndPnt.y())/10);
            shapePath.lineTo(instantLocalEndPnt.x(),(3*localStartPnt.y()+2*instantLocalEndPnt.y())/5);
            shapePath.lineTo((2*localStartPnt.x()+3*instantLocalEndPnt.x())/5,(3*localStartPnt.y()+2*instantLocalEndPnt.y())/5);
            shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,localStartPnt.y());
            painter.drawPath(shapePath);
            break;
        case 18:
            //绘制六角星
            shapePath.moveTo((localStartPnt.x()+instantLocalEndPnt.x())/2,localStartPnt.y());
            shapePath.lineTo((2*localStartPnt.x()+instantLocalEndPnt.x())/3,(3*localStartPnt.y()+instantLocalEndPnt.y())/4);
            shapePath.lineTo(localStartPnt.x(),(3*localStartPnt.y()+instantLocalEndPnt.y())/4);
            shapePath.lineTo((5*localStartPnt.x()+instantLocalEndPnt.x())/6,(localStartPnt.y()+instantLocalEndPnt.y())/2);
            shapePath.lineTo(localStartPnt.x(),(localStartPnt.y()+3*instantLocalEndPnt.y())/4);
            shapePath.lineTo((2*localStartPnt.x()+instantLocalEndPnt.x())/3,(localStartPnt.y()+3*instantLocalEndPnt.y())/4);
            shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,instantLocalEndPnt.y());
            shapePath.lineTo((localStartPnt.x()+2*instantLocalEndPnt.x())/3,(localStartPnt.y()+3*instantLocalEndPnt.y())/4);
            shapePath.lineTo(instantLocalEndPnt.x(),(localStartPnt.y()+3*instantLocalEndPnt.y())/4);
            shapePath.lineTo((localStartPnt.x()+5*instantLocalEndPnt.x())/6,(localStartPnt.y()+instantLocalEndPnt.y())/2);
            shapePath.lineTo(instantLocalEndPnt.x(),(3*localStartPnt.y()+instantLocalEndPnt.y())/4);
            shapePath.lineTo((localStartPnt.x()+2*instantLocalEndPnt.x())/3,(3*localStartPnt.y()+instantLocalEndPnt.y())/4);
            shapePath.lineTo((localStartPnt.x()+instantLocalEndPnt.x())/2,localStartPnt.y());
            painter.drawPath(shapePath);
            break;
        case 19:
            shapePath.moveTo((5*localStartPnt.x()+instantLocalEndPnt.x())/6,localStartPnt.y());
            shapePath.lineTo((localStartPnt.x()+5*instantLocalEndPnt.x())/6,localStartPnt.y());
            shapePath.arcTo(QRect(QPoint((localStartPnt.x()+2*instantLocalEndPnt.x())/3,localStartPnt.y()),
                              QPoint(instantLocalEndPnt.x(),(2*localStartPnt.y()+instantLocalEndPnt.y())/3)),
                        90,-90);
            shapePath.lineTo(instantLocalEndPnt.x(),(localStartPnt.y()+2*instantLocalEndPnt.y())/3);
            shapePath.arcTo(QRect(QPoint((localStartPnt.x()+2*instantLocalEndPnt.x())/3,
                                     (0.5*instantLocalEndPnt.y()+0.5*localStartPnt.y())),
                              QPoint(instantLocalEndPnt.x(),(localStartPnt.y()+5*instantLocalEndPnt.y())/6)),
                        0,-90);
            shapePath.lineTo((14*localStartPnt.x()+10*instantLocalEndPnt.x())/24,
                                     (5*instantLocalEndPnt.y()+localStartPnt.y())/6);
            shapePath.lineTo((17*localStartPnt.x()+7*instantLocalEndPnt.x())/24,instantLocalEndPnt.y());
            shapePath.lineTo((5*localStartPnt.x()+instantLocalEndPnt.x())/6,
                         (5*instantLocalEndPnt.y()+localStartPnt.y())/6);
            shapePath.arcTo(QRect(QPoint(localStartPnt.x(),
                                     (0.5*instantLocalEndPnt.y()+0.5*localStartPnt.y())),
                              QPoint((2*localStartPnt.x()+instantLocalEndPnt.x())/3,(localStartPnt.y()+5*instantLocalEndPnt.y())/6)),
                        -90,-90);
            shapePath.lineTo(localStartPnt.x(),(5*localStartPnt.y()+instantLocalEndPnt.y())/6);
            shapePath.arcTo(QRect(localStartPnt,QPoint((2*localStartPnt.x()+instantLocalEndPnt.x())/3,
                                     (2*localStartPnt.y()+instantLocalEndPnt.y())/3)),
                        -180,-90);
            painter.drawPath(shapePath);
            break;
        case 30:
            pen.setColor(QColor(0,0,255));
            pen.setStyle(Qt::DashLine);
            painter.setPen(pen);
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(QRect(localStartPnt,instantLocalEndPnt));
            break;
        case 31:
            pen.setColor(QColor(0,0,255));
            pen.setStyle(Qt::DashLine);
            painter.setPen(pen);
            painter.setBrush(Qt::NoBrush);
            painter.drawPolyline(freeShapeOutline);
            break;
        }
        return;
    }
    if (hasGlass){
        painter.setPen(Qt::black);
        if (currentPnt.x()<275){
            if (currentPnt.y()<122){
                painter.drawRect(0,1,550,244);
            }else if (currentPnt.y()>366) {
                painter.drawRect(0,244,550,244);
            }else{
                painter.drawRect(0,currentPnt.y()-122,550,244);
            }
        }else if (currentPnt.x()>823) {
            if (currentPnt.y()<122){
                painter.drawRect(548,1,550,244);
            }else if (currentPnt.y()>366) {
                painter.drawRect(548,244,550,244);
            }else {
                painter.drawRect(548,currentPnt.y()-122,550,244);
            }

        }else {
            if (currentPnt.y()<122){
                painter.drawRect(currentPnt.x()-275,1,550,244);
            }else if (currentPnt.y()>366) {
                painter.drawRect(currentPnt.x()-275,244,550,244);
            }else {
            painter.drawRect(currentPnt.x()-275,currentPnt.y()-122,550,244);
            }
        }
    }

    if (textEditMode){
//        QPainter painter(this);
        QPen pen(Qt::DotLine);
        pen.setWidth(2);
        painter.setPen(pen);
        if(localStartPnt!=localEndPnt){
            painter.drawRect(QRect(localStartPnt-QPoint(3,3),localEndPnt+QPoint(1,1)));
            textinstant->setGeometry(QRect(localStartPnt,localEndPnt));
            textinstant->setFrameShape(QFrame::Shape(0));
        }
        if (isPressed){
            painter.drawRect(QRect(localStartPnt-QPoint(3,3),instantLocalEndPnt+QPoint(1,1)));
        }
    }

    if (eraserMode){
//        QPainter painter(this);
        painter.setBrush(myBrush);

        if (isPressed){
            if (myBrush!=Qt::NoBrush)
            {painter.setPen(myBrush.color());}
            else {
                painter.setPen(Qt::white);
            }
            painter.drawRects(eraserRects);

        }

        painter.setPen(QPen(Qt::black));
        switch (eraserWidth) {
        case 1:
            painter.drawRect(localStartPnt.x()-1,localStartPnt.y()-1,2,2);
            break;
        case 3:
            painter.drawRect(localStartPnt.x()-2,localStartPnt.y()-2,4,4);
            break;
        case 5:
            painter.drawRect(localStartPnt.x()-4,localStartPnt.y()-4,8,8);
            break;
        case 8:
            painter.drawRect(localStartPnt.x()-8,localStartPnt.y()-8,16,16);
            break;
        }
        }
    if (funcBrushMode&&isPressed){
        QPen pen=myPen.color();
        QColor color=myPen.color();
        QBrush fillBrush;
//        QLinearGradient gra(0,0,1000,0);
//        gra.setColorAt(0,QColor(0,0,0));
//        gra.setColorAt(0.5,QColor(0,255,0));
//        gra.setColorAt(1,QColor(255,0,255));
//        QBrush penBrush(gra);
        switch (funcBrushType) {
        case 1:
            pen.setWidth(bWidth);
            painter.setPen(pen);
            painter.drawPolyline(brushPolygon);
            break;
        case 2:
            pen.setWidth(bWidth);
            painter.setPen(pen);
            painter.drawLines(calligraphyPen1);
            break;
        case 3:
            pen.setWidth(bWidth);
            painter.setPen(pen);
            painter.drawLines(calligraphyPen1);
            break;
        case 4:
            pen.setWidth(1);
            painter.setPen(pen);
            painter.drawPoints(airbrushPoints);
            break;
        case 5:
            break;
        case 6:
//            painter.setBrush(Qt::RadialGradientPattern);
            funcBrushPenE.setWidth(30);
            funcBrushPenM.setWidth(22);
            painter.setPen(funcBrushPenE);
            painter.drawPolyline(brushPolygon);
            painter.setPen(funcBrushPenM);
            painter.drawPolyline(brushPolygon);
//            for (int i=0;i<brushPolygon.length()-1;i++){
//                painter.drawLine(QLine(brushPolygon.toList()[i],brushPolygon.toList()[i+1]));
//            }

            break;
        case 7:
            color.setAlpha(200);
            pen.setColor(color);
            pen.setWidth(bWidth);
            painter.setPen(pen);
            painter.drawPolyline(brushPolygon);
            break;
        case 8:
            color.setAlpha(80);
            pen.setColor(color);
            pen.setWidth(bWidth);
            painter.setPen(pen);
            painter.drawPolyline(brushPolygon);
            break;
        case 9:
            break;
        }
    }
    if (funcBrushMode&&funcBrushType>4){
        QBrush brush(myBrush.color());
        painter.setPen(QPen(Qt::black));
        painter.setBrush(brush);
        painter.drawEllipse(QRect(currentPnt-QPoint(20,20),currentPnt+QPoint(20,20)));
    }
}

void myWidget::keyPressEvent(QKeyEvent *event)
{
    emit keyPreEvent(event);
}

void myWidget::mousePressEvent(QMouseEvent *e)
{
    isPressed=1;
    eraserRectsOut.clear();
    setLocalStartPnt(e->pos());
    setLocalEndPnt(e->pos());
    instantLocalEndPnt=e->pos();
    if (shapeType==6&&pgPnts.isEmpty()){
        pgPnts.append(e->pos());
    }
    if(textEditMode){
        if(textinstant->toHtml().count()!=473){
            textInput=textinstant->toPlainText();
            textinstant->clear();
            textinstant->setGeometry(0,0,0,0);
        }else {
            textInput.clear();
        }
    }else if (funcBrushMode)
    {
        if (funcBrushType==4)
        {
            airbrushTimer->start();
        }
    }

    calligraphyPen1.clear();
    emit mousePreEvent(e);
}


void myWidget::mouseMoveEvent(QMouseEvent *e)
{
    emit mouseMoEvent(e);
    if (isPressed)
    {
        instantLocalEndPnt=e->pos();
        if (funcBrushMode){
            if (funcBrushType==2||funcBrushType==3||funcBrushType==6)
            {
                QPoint movePnt=instantLocalEndPnt-localStartPnt;
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
                        calligraphyPen1.append(QLine(localStartPnt+j*movePnt*1/bmax-QPoint(-4,4),
                                                     localStartPnt+j*movePnt*1/bmax+QPoint(-4,4)));
                    }
                    localStartPnt=e->pos();
                    bWidth=2;
                }
                else if (funcBrushType==3)
                {
                    for (int j=0;j<=(bmax/1);j++)
                    {
                        calligraphyPen1.append(QLine(localStartPnt+j*movePnt*1/bmax+QPoint(4,4),
                                                     localStartPnt+j*movePnt*1/bmax-QPoint(4,4)));
                    }
                    localStartPnt=e->pos();
                    bWidth=2;
                }
                else if (funcBrushType==6)
                {
                    brushPolygon.append(instantLocalEndPnt);
//                    if (localStartPnt!=instantLocalEndPnt)
//                    {
//    //                    &&amovePnt.x()>1&&amovePnt.y()>1
//                        for (unsigned int j=0;j<10;j++){
//                            int x=rand()%20;
//                            int y=rand()%20;
//                            airbrushPoints.append(instantLocalEndPnt+QPoint(x-5,y-5));
//                        }
//                        for (unsigned int k=0;k<40;k++){
//                            int x=rand()%3+12;
//                            int y=rand()%10;
//                            int x1=x*movePnt.y()/sqrt(pow(movePnt.x(),2)+pow(movePnt.y(),2))+y*movePnt.x()/sqrt(pow(movePnt.x(),2)+pow(movePnt.y(),2));
//                            int y1=-x*movePnt.x()/sqrt(pow(movePnt.x(),2)+pow(movePnt.y(),2))+y*movePnt.y()/sqrt(pow(movePnt.x(),2)+pow(movePnt.y(),2));
//                            airbrushPoints.append(localStartPnt+QPoint(x1,y1));
//                            airbrushPoints.append(localStartPnt-QPoint(x1,y1));
//                        }
    //                    for (unsigned int k=0;k<20;k++){
    //                        int x=rand()%3+12;
    //                        int y=rand()%10;
    //                        int x1=x*movePnt.y()/sqrt(pow(movePnt.x(),2)+pow(movePnt.y(),2))+y*movePnt.x()/sqrt(pow(movePnt.x(),2)+pow(movePnt.y(),2));
    //                        int y1=-x*movePnt.x()/sqrt(pow(movePnt.x(),2)+pow(movePnt.y(),2))+y*movePnt.y()/sqrt(pow(movePnt.x(),2)+pow(movePnt.y(),2));
    //                        sideBrushPoints.append(localStartPnt+QPoint(x1,y1));
    //                        sideBrushPoints.append(localStartPnt-QPoint(x1,y1));
    //                    }
//                    }
                    bWidth=30;
                    localStartPnt=e->pos();
                }
            }

            if (funcBrushType==1)
            {
                brushPolygon.append(instantLocalEndPnt);
                bWidth=5;
            }

            else if (funcBrushType==4)
            {
                localStartPnt=e->pos();
            }
            else if (funcBrushType==5)
            {
                localStartPnt=e->pos();
            }

            else if (funcBrushType==7)
            {
                brushPolygon.append(instantLocalEndPnt);
                bWidth=16;
            }
            else if (funcBrushType==8)
            {
                brushPolygon.append(instantLocalEndPnt);
                bWidth=3;
            }
            else if (funcBrushType==9)
            {
                localStartPnt=e->pos();
            }
        }
        else if (shapeType==0) {
            brushPolygon.append(instantLocalEndPnt);
        }else if (shapeType==31) {
            freeShapeOutline.append(e->pos());
        }
        update();
    }
    if (hasGlass)
    {setCurrentPnt(e->pos());
    update();}


    if (eraserMode){
        localStartPnt=e->pos();
        update();
        if(isPressed){
            switch (eraserWidth) {
            case 1:
                eraserRects.append(QRect(localStartPnt.x()-1,localStartPnt.y()-1,2,2));
                break;
            case 3:
                eraserRects.append(QRect(localStartPnt.x()-2,localStartPnt.y()-2,4,4));
                break;
            case 5:
                eraserRects.append(QRect(localStartPnt.x()-4,localStartPnt.y()-4,8,8));
                break;
            case 8:
                eraserRects.append(QRect(localStartPnt.x()-8,localStartPnt.y()-8,16,16));
                break;
            }
        }
    }
}

void myWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (shapeType==6){
        if (isPressed)
        {
            pgPnts.append(e->pos());
            QPoint distancePnt=pgPnts.first()-e->pos();
            if (distancePnt.manhattanLength()<5){
                pgPnts.clear();
            }
        }else {
            pgPnts.clear();
        }
    }
    isPressed=0;
    updateMode=true;
    eraserRectsOut=eraserRects;
    eraserRects.clear();
    if(textEditMode){
        setLocalEndPnt(e->pos());
    }else if (funcBrushMode)
    {
        if (funcBrushType==4)
        {
            airbrushTimer->stop();
        }
        brushPolygon.clear();
//        airbrushPoints.clear();
        sideBrushPoints.clear();
    }else if (shapeType==0) {
        brushPolygon.clear();

    }
    if (shapeType<22||shapeType==30||shapeType==31){
        if (shapeType==31){
            freeShapeOutline.clear();
        }
        update();
    }

    instantLocalEndPnt=localStartPnt;
    emit mouseReEvent(e);
}

void myWidget::drawForeground(QPainter *painter)
{
        if (gridOn){
            QVector<QLine> Lines;
    //        qreal gapRatio;
    //        QPointF distance=(mapToScene(QPoint(100,100))-mapToScene(QPoint(0,0)));
    //        gapRatio=distance.x()/100;
            int gap=10;
            for (int i=1;i<=1101*sizeRatio;i++){
                Lines<<QLine(i*gap,0,i*gap,491*sizeRatio);
            }
            for (int i=1;i<=491/gap*sizeRatio;i++){
                Lines<<QLine(0,i*gap,1101*sizeRatio,i*gap);
            }
            painter->setPen(Qt::DotLine);
            painter->drawLines(Lines);
        }
}

void myWidget::timerTriggerd()
{ 
    for (unsigned int i=0;i<40;i++){
        int x=rand()%10;
        int y=rand()%10;
        if (((x-5)*(x-5)+(y-5)*(y-5))<25){
            airbrushPoints.append(localStartPnt+QPoint(x-5,y-5));
        }
    }
    update();
}
