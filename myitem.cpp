#include "myitem.h"
#include <QPainter>
#include <QCursor>
#include <QMessageBox>
#include <QKeyEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <qgraphicsscene.h>
#include <QMenu>
#include <qdebug.h>
#include <qmainwindow.h>
#include <QStyleOptionGraphicsItem>

QRect MyItem::getRectLine() const
{
    return rectLine;
}

void MyItem::setRectLine(const QRect &value)
{
    rectLine = value;
}

QRectF MyItem::boundingRect() const
{
    qreal adjust=0.5;
    return QRectF(rectLine.left()-adjust,rectLine.top()-adjust,
                  rectLine.width()+adjust,rectLine.height()+adjust);

}

void MyItem::rotL()
{
//    QRect rect=getRectLine();
//    QPoint zP=0.5*(rect.topLeft()+rect.bottomRight());
//    QPoint neP=-0.5*(rect.topLeft()-rect.bottomRight());
//    rect.setLeft(-neP.y()+zP.x());
//    rect.setTop(-neP.x()+zP.y());
//    rect.setWidth(2*neP.y());
//    rect.setHeight(2*neP.x());
//    setRectLine(rect);
    rotateAngle-=90;
    //    update();
}

void MyItem::rotR()
{
//    QRect rect=getRectLine();
//    QPoint zP=0.5*(rect.topLeft()+rect.bottomRight());
//    QPoint neP=-0.5*(rect.topLeft()-rect.bottomRight());
//    rect.setLeft(-neP.x()+zP.y());
//    rect.setTop(-neP.y()+zP.x());
//    rect.setWidth(2*neP.y());
//    rect.setHeight(2*neP.x());
//    setRectLine(rect);
    rotateAngle+=90;

}

void MyItem::rot180()
{
    rotateAngle+=180;
}

int MyItem::getIItem() const
{
    return iItem;
}

void MyItem::setIItem(int value)
{
    iItem = value;
}

QVector<QPoint> MyItem::getMyPoints() const
{
    return MyPoints;
}

void MyItem::setMyPoints(const QVector<QPoint> &value)
{
    MyPoints = value;
}

QPainterPath MyItem::getMyPath() const
{
    return MyPath;
}

void MyItem::setMyPath(const QPainterPath &value)
{
    MyPath = value;
}

bool MyItem::getIsPre() const
{
    return isPre;
}

void MyItem::setIsPre(bool value)
{
    isPre = value;
}

void MyItem::setPentype(const TextureType &value)
{
    pentype = value;
    myPenStyleSet();
    update();
}

void MyItem::setBrushtype(const TextureType &value)
{
    brushtype = value;
    myBrushStyleSet();
    update();
}

QPen MyItem::getMyPen() const
{
    return myPen;
}

void MyItem::setMyPen(const QPen &value)
{
    myPen = value;
}

bool MyItem::getVertFlip() const
{
    return vertFlip;
}

void MyItem::setVertFlip(bool value)
{
    vertFlip = value;
}

bool MyItem::getHoriFilp() const
{
    return horiFilp;
}

void MyItem::setHoriFilp(bool value)
{
    horiFilp = value;
}

void MyItem::setWidget(myWidget *value)
{
    widget = value;
}

void MyItem::transform(QPainter *painter)
{
    if (vertFlip){
        QTransform tran;
        tran.setMatrix(-1,0,0,0,1,0,0,0,1);
        painter->setTransform(tran,true);
    }
    if (horiFilp){
        QTransform tran;
        tran.setMatrix(1,0,0,0,-1,0,0,0,1);
        painter->setTransform(tran,true);
    }
}

void MyItem::myPenStyleSet()
{
    if (pentype==solid){
        myPen=pen();
        myPen.setStyle(Qt::SolidLine);
    }else if(pentype==none){
        myPen=Qt::NoPen;
    }else if (pentype==crayon) {
        myPen=pen();
        myPen.setStyle(Qt::SolidLine);
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
        myPen=pen();
        myPen.setStyle(Qt::SolidLine);
        QColor color=myPen.color();
        color.setAlpha(200);
        myPen.setColor(color);
    }else if(pentype==oil){
        myPen=pen();
        myPen.setStyle(Qt::SolidLine);
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
        myPen=pen();
        myPen.setStyle(Qt::SolidLine);
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
        myPen=pen();
        myPen.setStyle(Qt::SolidLine);
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

void MyItem::myBrushStyleSet()
{
    if (brushtype==solid){
        myBrush=brush();
        myBrush.setStyle(Qt::SolidPattern);
    }else if(brushtype==none){
        myBrush=Qt::NoBrush;
    }else if(brushtype==crayon){
        QImage image(":/image/黑色蜡笔.png");
        if (brush().color()!=QColor(0,0,0)){
            QColor color=brush().color();
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
    }else if(brushtype==marker){
        myBrush=brush();
        myBrush.setStyle(Qt::SolidPattern);
        QColor color=myBrush.color();
        color.setAlpha(200);
        myBrush.setColor(color);
    }else if(brushtype==oil){
        QImage image(":/image/黑色油画.png");
        if (brush().color()!=QColor(0,0,0)){
            QColor color=brush().color();
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
        if (brush().color()!=QColor(0,0,0)){
            QColor color=brush().color();
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
        if (brush().color()!=QColor(0,0,0)){
            QColor color=brush().color();
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

MyItem::MyItem()
{

}
// 鼠标按下事件处理函数，设置被点击的图形项获得焦点，并改变光标外观
void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!(flags()&ItemIsMovable)){event->ignore();return;};
    setFocus();
    isPre=1;
    QPointF l1=event->pos()-rectLine.bottomRight();
    QPointF l2=event->pos()-rectLine.topLeft();
    QPointF l3=event->pos()-rectLine.topRight();
    QPointF l4=event->pos()-rectLine.bottomLeft();
    if (isSelected()){setFlag(QGraphicsItem::ItemIsMovable);}
    if (l1.manhattanLength()<10){
        sizeDiag=0;
        setFlag(QGraphicsItem::ItemIsMovable,false);
    }else if (l2.manhattanLength()<10) {
        sizeDiag=1;
        setFlag(QGraphicsItem::ItemIsMovable,false);
    }else if (l3.manhattanLength()<10) {
        sizeDiag=2;
        setFlag(QGraphicsItem::ItemIsMovable,false);
    }else if (l4.manhattanLength()<10) {
        sizeDiag=3;
        setFlag(QGraphicsItem::ItemIsMovable,false);
    }else {
        setFlag(QGraphicsItem::ItemIsMovable,true);
    }
    QGraphicsItem::mousePressEvent(event);
}

// 键盘按下事件处理函数，判断是否是向下方向键，如果是，则向下移动图形项
void MyItem::keyPressEvent(QKeyEvent *event)
{
    //    qDebug()<<QStringLiteral("key");
    switch (event->key()) {
    case Qt::Key_Down:
        moveBy(0, 10);
        break;
    case Qt::Key_Up:
        moveBy(0,-10);
        break;
    case Qt::Key_Left:
        moveBy(-10,0);
        break;
    case Qt::Key_Right:
        moveBy(10,0);
        break;
    }
}
// 悬停事件处理函数，设置光标外观和提示

void MyItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF l1=event->pos()-rectLine.bottomRight();
    QPointF l2=event->pos()-rectLine.topLeft();
    QPointF l3=event->pos()-rectLine.topRight();
    QPointF l4=event->pos()-rectLine.bottomLeft();
    if (l1.manhattanLength()<4||l2.manhattanLength()<4){
        widget->setCursor(Qt::SizeFDiagCursor);
    }else if (l3.manhattanLength()<4||l4.manhattanLength()<4)
    {
        widget->setCursor(Qt::SizeBDiagCursor);
    }else {
        //设置光标为移动的形状
        widget->setCursor(Qt::SizeAllCursor);
    }
}

void MyItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    widget->setCursor(Qt::ArrowCursor);
}
// 右键菜单事件处理函数，为图形项添加一个右键菜单
void MyItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *moveAction = menu.addAction("move back");
    moveAction->setShortcut(QKeySequence("o"));
    QAction *selectedAction = menu.exec(event->screenPos());
    if (selectedAction == moveAction) {
        setPos(0, 0);
        this->scene()->update();
    }
}

void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QAbstractGraphicsShapeItem::mouseReleaseEvent(event);
    switch (sizeDiag) {
    case 0:
        rectLine.setBottomRight(event->pos().toPoint());
        break;
    case 1:
        rectLine.setTopLeft(event->pos().toPoint());
        break;
    case 2:
        rectLine.setTopRight(event->pos().toPoint());
        break;
    case 3:
        rectLine.setBottomLeft(event->pos().toPoint());
        break;
    }
    isPre=0;
    update();
    sizeDiag=10;
}

void MyItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    switch (sizeDiag) {
    case 0:
        rectLine.setBottomRight(event->pos().toPoint());
        break;
    case 1:
        rectLine.setTopLeft(event->pos().toPoint());
        break;
    case 2:
        rectLine.setTopRight(event->pos().toPoint());
        break;
    case 3:
        rectLine.setBottomLeft(event->pos().toPoint());
        break;
    }
    update();
    QAbstractGraphicsShapeItem::mouseMoveEvent(event);

}

QBrush property::getBrush() const
{
    return brush;
}

void property::setBrush(const QBrush &value)
{
    brush = value;
}

QRgb property::getFillC() const
{
    return fillC;
}

void property::setFillC(const QRgb &value)
{
    fillC = value;
}

QColor property::getPen() const
{
    return pen;
}

void property::setPen(const QColor &value)
{
    pen = value;
}

void MyRoundedItem::rotL()
{
    QRect rect=getRectLine();
    QPoint zP=0.5*(rect.topLeft()+rect.bottomRight());
    QPoint neP=-0.5*(rect.topLeft()-rect.bottomRight());
    rect.setLeft(-neP.y()+zP.x());
    rect.setTop(-neP.x()+zP.y());
    rect.setWidth(2*neP.y());
    rect.setHeight(2*neP.x());
    setRectLine(rect);
    //    update();
}

void MyRoundedItem::rotR()
{
    this->setRotation(-90);
    update();
}

void MyRoundedItem::rot180()
{
    this->setRotation(180);
    this->parentItem()->update();
}

MyRoundedItem::MyRoundedItem(QRect rectline)
{
    iItem=5;
    setRectLine(rectline);
    update();
}

QRectF MyRoundedItem::boundingRect() const
{
    qreal adjust=0.5;
    return QRectF(rectLine.left()-adjust,rectLine.top()-adjust,
                  rectLine.width()+adjust,rectLine.height()+adjust);
}

QPainterPath MyRoundedItem::shape() const
{
    QPainterPath path;
    path.addRoundedRect(rectLine,20,20);
    return path;
}

void MyRoundedItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->setPen(myPen);
    painter->setBrush(myBrush);
    painter->translate(rectLine.center());
    if (int(rotateAngle)%360!=0)
    {
        painter->rotate(rotateAngle);
    }
    painter->translate(-rectLine.center());
    painter->drawRoundedRect(getRectLine(),20,20);
    if (option->state & QStyle::State_Selected)
    {
        painter->setPen(Qt::DotLine);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}


QLine MyLineItem::getLinep() const
{
    return linep;
}

void MyLineItem::setLinep(const QLine &value)
{
    linep = value;
}

MyLineItem::MyLineItem(QLine li)
{
    //    setAcceptHoverEvents(1);
    setLinep(li);
    update();
}

MyLineItem::MyLineItem(QPoint s, QPoint e)
{
    //    setAcceptHoverEvents(1);
    linep=QLine(s,e);
    update();
}

MyLineItem::MyLineItem(QLineF li)
{
    //    setAcceptHoverEvents(1);
    setLinep(li.toLine());
    QRectF rectL=QRectF(li.p1(),li.p2());
    rectLine=rectL.toRect();
    update();
}

QPainterPath MyLineItem::shape() const
{
    QPainterPath path;
    path.moveTo(linep.p1()-QPoint(0,2));
    path.lineTo(linep.p2()-QPoint(0,2));
    path.lineTo(linep.p2()+QPoint(0,2));
    path.lineTo(linep.p1()+QPoint(0,2));
    return path;
}

void MyLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(myPen);
    painter->setBrush(myBrush);
    painter->translate(linep.center());
    transform(painter);
    if (int(rotateAngle)%360!=0)
    {
        painter->rotate(rotateAngle);
    }
    painter->translate(-linep.center());
    painter->drawLine(linep);
    if (option->state & QStyle::State_Selected)
    {
        painter->setPen(Qt::DotLine);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}

QPainterPath MyEllipseItem::shape() const
{
    QPainterPath path;
    path.addEllipse(rectLine);
    return path;
}

MyEllipseItem::MyEllipseItem(QRect rect)
{
    setRectLine(rect);
    update();
}

void MyEllipseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(myPen);
    painter->setBrush(myBrush);
    painter->translate(rectLine.center());
    if (int(rotateAngle)%360!=0)
    {
        painter->rotate(rotateAngle);
    }
    painter->translate(-rectLine.center());
    painter->drawEllipse(rectLine);
    if (option->state & QStyle::State_Selected)
    {
        painter->setPen(Qt::DotLine);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}

QRectF MyPolygonItem::boundingRect() const
{
    QList<int> xs;
    QList<int> ys;
    int xmin=0;
    int ymin=0;
    int xmax=0;
    int ymax=0;
    for (int i = 0; i < MyPoints.length(); ++i) {
        xs.append(MyPoints[i].x());
        ys.append(MyPoints[i].y());
        if (i==0){
            xmin=MyPoints[i].x();
            ymin=MyPoints[i].y();
            xmax=MyPoints[i].x();
            ymax=MyPoints[i].y();
        }else {
            xmin=std::min(xmin,MyPoints[i].x());
            ymin=std::min(ymin,MyPoints[i].y());
            xmax=std::max(xmax,MyPoints[i].x());
            ymax=std::max(ymax,MyPoints[i].y());
        }
    }
    return QRect(xmin,ymin,xmax-xmin,ymax-ymin);

}

QPainterPath MyPolygonItem::shape() const
{
    QPainterPath path;
    path.addPolygon(QPolygon(getMyPoints()));
    return path;
}

MyPolygonItem::MyPolygonItem(QVector<QPoint> points)
{
    setMyPoints(points);
    update();
}

void MyPolygonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(myPen);
    painter->setBrush(myBrush);
    painter->translate(boundingRect().center());
    transform(painter);
    if (int(rotateAngle)%360!=0)
    {
        painter->rotate(rotateAngle);
    }
    painter->translate(-boundingRect().center());
    painter->drawPolygon(MyPoints);
    if (option->state & QStyle::State_Selected)
    {
        painter->setPen(Qt::DotLine);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}

MyRectItem::MyRectItem(QRect rect)
{
    setRectLine(rect);
    //    update();
}

QPainterPath MyRectItem::shape() const
{
    QPainterPath path;
    path.addRect(rectLine);
    return path;
}

void MyRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(myPen);
    painter->setBrush(myBrush);
    painter->translate(rectLine.center());
    if (int(rotateAngle)%360!=0)
    {
        painter->rotate(rotateAngle);
    }
    painter->translate(-rectLine.center());
    painter->drawRect(rectLine);
    if (option->state & QStyle::State_Selected)
    {
        painter->setPen(Qt::DotLine);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}

QRectF MyPathItem::boundingRect() const
{
    QPolygon polygon=MyPath.toFillPolygon().toPolygon();
    QList<int> xs;
    QList<int> ys;
    int xmin=0;
    int ymin=0;
    int xmax=0;
    int ymax=0;
    for (int i = 0; i < polygon.length(); ++i) {
        xs.append(polygon[i].x());
        ys.append(polygon[i].y());
        if (i==0){
            xmin=polygon[i].x();
            ymin=polygon[i].y();
            xmax=polygon[i].x();
            ymax=polygon[i].y();
        }else {
            xmin=std::min(xmin,polygon[i].x());
            ymin=std::min(ymin,polygon[i].y());
            xmax=std::max(xmax,polygon[i].x());
            ymax=std::max(ymax,polygon[i].y());
        }
    }
    return QRect(xmin,ymin,xmax-xmin,ymax-ymin);

}

QPainterPath MyPathItem::shape() const
{
    return MyPath;
}

MyPathItem::MyPathItem(QPainterPath path)
{
    setMyPath(path);
    update();
}

void MyPathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(myPen);
    painter->setBrush(myBrush);
    painter->translate(boundingRect().center());
    transform(painter);
    if (int(rotateAngle)%360!=0)
    {
        painter->rotate(rotateAngle);
    }
    painter->translate(-boundingRect().center());
    painter->drawPath(MyPath);
    if (option->state & QStyle::State_Selected)
    {
        painter->setPen(Qt::DotLine);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}


colorFill::colorFill(QImage img)
{
    imgr=img;
}

colorFill::colorFill()
{

}

void colorFill::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawImage(0,0,imgr);
    return;
}

QVector<QRect> MyEraserItem::getEraserRects() const
{
    return eraserRects;
}

void MyEraserItem::setEraserRects(const QVector<QRect> &value)
{
    eraserRects = value;
}

MyEraserItem::MyEraserItem(QVector<QRect> rects)
{
    eraserRects=rects;
}

void MyEraserItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(pen());
    painter->setBrush(brush());
    //    for (int j=0;j<eraserRects.length();j++){
    //            painter->fillRect(eraserRects[j],brush());
    //    }
    painter->drawRects(eraserRects);
}

QRectF MyEraserItem::boundingRect() const
{
    return eraserRects[0];
}

MyPolylineItem::MyPolylineItem(QPolygon poly)
{
    polygon=poly;
    update();
}

QPainterPath MyPolylineItem::shape() const
{
    QPainterPath path;
    path.addPolygon(polygon);
    return path;
}

void MyPolylineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(pen());
    painter->drawPolyline(polygon);
}

MyLinesItem::MyLinesItem(QVector<QLine> iline)
{
    lines=iline;
}

QPainterPath MyLinesItem::shape() const
{
    QPainterPath path;
    path.addRect(QRect(lines[0].p1(),lines[0].p2()));
    return path;
}

void MyLinesItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(pen());
    painter->drawLines(lines);
}

MyAirBrushItem::MyAirBrushItem(QVector<QPoint> points)
{
    airPoints=points;
}

void MyAirBrushItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(pen());
    painter->drawPoints(airPoints);
}

QImage MyImageItem::getImgr() const
{
    return imgr;
}

MyImageItem::MyImageItem(QImage img)
{
    imgr=img;
    update();
}

void MyImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->drawImage(0,0,imgr);
    if (option->state & QStyle::State_Selected)
    {
        painter->setPen(Qt::DotLine);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}

QRectF MyImageItem::boundingRect() const
{
    QSize size=imgr.size();
    //    qDebug()<<size;
    return QRect(QPoint(0,0),size);
}

QImage MyRectSelItem::getImgr() const
{
    return imgr;
}

MyRectSelItem::MyRectSelItem(QRect rect,QImage image)
{
    setRectLine(rect);
    imgr=image;
    iItem=30;
}

void MyRectSelItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QPen pen;
    if (int(rotateAngle)%360!=0)
    {
        painter->translate(rectLine.center());
        painter->rotate(rotateAngle);
        painter->translate(-rectLine.center());
    }
    QImage img=imgr.mirrored(horiFilp,vertFlip);
    painter->drawImage(rectLine,img);
    if (option->state & QStyle::State_Selected)
    {
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}

QPixmap MyFreeShapeSelItem::getSelPixmap() const
{
    return selPixmap;
}

QRectF MyFreeShapeSelItem::boundingRect() const
{
    QRect rect=rectLine;
    rect.setBottomRight(rectLine.bottomRight()-QPoint(1,1));
    return rect;
}

MyFreeShapeSelItem::MyFreeShapeSelItem()
{
    iItem=31;
}

MyFreeShapeSelItem::MyFreeShapeSelItem(QRect rect, QPolygon poly, QPixmap pix)
{
    setRectLine(rect);
    selPoly=poly;
    pixr=pix;
    iItem=31;
}

void MyFreeShapeSelItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QPen pen;
    QPainterPath path;
    path.addPolygon(selPoly);
    painter->translate(rectLine.center());
    transform(painter);
    if (int(rotateAngle)%360!=0)
    {
        painter->rotate(rotateAngle);
    }
    painter->translate(-rectLine.center());
    if (selPixmap.isNull())
    {
        QPixmap pixmap(rectLine.size());
        QPainterPath path1;
        path1.addPolygon(selPoly);
        QPainter painter1;
        if (brush()==Qt::NoBrush)
        {pixmap.fill(Qt::white);}else {
        pixmap.fill(brush().color());
        }
        painter1.begin(&pixmap);
        path1.translate(QPoint(0,0)-rectLine.topLeft());
        painter1.setClipPath(path1);
        painter1.drawPixmap(0,0,pixr);
        selPixmap=pixmap;
    }
    painter->setClipPath(path);
    painter->drawPixmap(rectLine,pixr);
    if (option->state & QStyle::State_Selected)
    {
        painter->setClipRect(rectLine);
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }

}



myInvertSelItem::myInvertSelItem(QRect rect, QPolygon poly, QPixmap pix)
{
    setRectLine(rect);
    selPoly=poly;
    pixr=pix;
    iItem=31;
}

void myInvertSelItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QPen pen;
    QPainterPath path;
    QRegion region;
    region.setRects(&rectLine,1);
    QRegion region1(selPoly);
    QRegion nRegion=region.xored(region1);
    if (selPixmap.isNull())
    {
        QPixmap pixmap(rectLine.size());
        QPainterPath path1;
        path1.addPolygon(selPoly);
        QPainter painter1;
//        if (brush()==Qt::NoBrush)
//        {pixmap.fill(Qt::white);}else {
//        pixmap.fill(brush().color());
//        }
        painter1.begin(&pixmap);
        nRegion.translate(-1,-1);
        painter1.setClipRegion(nRegion);
        painter1.drawPixmap(0,0,pixr);
        selPixmap=pixmap;
    }
    painter->setClipRegion(nRegion);
    painter->drawPixmap(rectLine,selPixmap);
    if (option->state & QStyle::State_Selected)
    {
        painter->setClipRect(rectLine);
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }

}

fullScrWidget::fullScrWidget(QWidget *parent, Qt::WindowFlags f):
    QLabel(parent, f)
{

}

void fullScrWidget::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    delete this;
}
