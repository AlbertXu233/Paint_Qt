#ifndef MYITEM_H
#define MYITEM_H
#include <QGraphicsItem>
#include <qpainter.h>
#include <qpen.h>
#include <qlabel.h>
#include <mywidget.h>
#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif

//class doneType{
//    int itemListIndex;

//};
class fullScrWidget : public QLabel
{
public:
    explicit fullScrWidget(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
private slots:
    void mousePressEvent(QMouseEvent *ev) override;
};

class property{
    QColor pen;
    QRgb fillC=qRgb(0,0,0);
    QBrush brush=Qt::white;
public:
    QColor getPen() const;
    void setPen(const QColor &value);
    QBrush getBrush() const;
    void setBrush(const QBrush &value);
    QRgb getFillC() const;
    void setFillC(const QRgb &value);
};
class MyItem : public QAbstractGraphicsShapeItem
{
public:
    MyItem();
    QRect getRectLine() const;
    void setRectLine(const QRect &value);
    QRectF boundingRect() const override;
    void rotL();
    void rotR();
    void rot180();   
    int getIItem() const;
    void setIItem(int value);


    QVector<QPoint> getMyPoints() const;
    void setMyPoints(const QVector<QPoint> &value);

    QPainterPath getMyPath() const;
    void setMyPath(const QPainterPath &value);

    bool getIsPre() const;
    void setIsPre(bool value);

    void setPentype(const TextureType &value);

    void setBrushtype(const TextureType &value);

    QPen getMyPen() const;

    void setMyPen(const QPen &value);

    bool getVertFlip() const;
    void setVertFlip(bool value);

    bool getHoriFilp() const;
    void setHoriFilp(bool value);

    void setWidget(myWidget *value);

protected:
    QRect rectLine;
    QVector<QPoint> MyPoints;
    QPainterPath MyPath;
    bool isPre;
    bool vertFlip=false;
    bool horiFilp=false;
    myWidget *widget;
    int iItem;
    int sizeDiag;
    qreal rotateAngle=0;
    TextureType pentype=solid;
    TextureType brushtype=none;
    QPen myPen=QColor(0,0,0);
    QBrush myBrush=Qt::white;
    void transform(QPainter* painter);
    void myPenStyleSet();
    void myBrushStyleSet();
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

class MyLineItem :public MyItem
{
public:
    QLine linep;
    MyLineItem(QLine li);
    MyLineItem(QPoint s,QPoint e);
    MyLineItem(QLineF li);
    QPainterPath shape()const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QLine getLinep() const;
    void setLinep(const QLine &value);
};

class MyEllipseItem :public MyItem
{
    QPainterPath shape()const override;
public:
    MyEllipseItem(QRect rect);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

class MyRectItem :public MyItem
{
public:
    MyRectItem(QRect rect);
    QPainterPath shape()const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

class MyPolygonItem :public MyItem
{
    QRectF boundingRect() const override;
    QPainterPath shape()const override;
public:
    MyPolygonItem(QVector<QPoint> points);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

class MyPathItem :public MyItem
{
    QRectF boundingRect() const override;
    QPainterPath shape()const override;
public:
    MyPathItem(QPainterPath path);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

class MyRoundedItem :public MyItem {
public:
    MyRoundedItem(QRect rectline);
    QRectF boundingRect() const override;
    QPainterPath shape()const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void rotL();
    void rotR();
    void rot180();
};

class colorFill:public MyItem{
    QImage imgr;
public:
    colorFill(QImage img);
    colorFill();
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr);
};

class MyEraserItem:public QAbstractGraphicsShapeItem{
    QVector<QRect> eraserRects;
public:
    MyEraserItem(QVector<QRect> rects);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr);
    QRectF boundingRect() const;
    QVector<QRect> getEraserRects() const;
    void setEraserRects(const QVector<QRect> &value);
};

class MyPolylineItem:public MyItem{
    QPolygon polygon;
public:
    MyPolylineItem(QPolygon poly);
    QPainterPath shape()const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

class MyLinesItem:public MyItem{
    QVector<QLine> lines;
public:
    MyLinesItem(QVector<QLine> iline);
    QPainterPath shape()const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

class MyAirBrushItem:public MyItem{
    QVector<QPoint> airPoints;
public:
    MyAirBrushItem(QVector<QPoint> points);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

class MyImageItem:public MyItem{
    QImage imgr;
public:
    MyImageItem(QImage img);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    QImage getImgr() const;
};

class MyRectSelItem:public MyItem{
    QImage imgr;
public:
    MyRectSelItem(QRect rect,QImage image);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
    QImage getImgr() const;
};

class MyFreeShapeSelItem:public MyItem{
protected:
    QPixmap pixr;
    QPixmap selPixmap;
    QPolygon selPoly;
    QRectF boundingRect() const override;
public:
    MyFreeShapeSelItem();
    MyFreeShapeSelItem(QRect rect,QPolygon poly,QPixmap pix);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
    QPixmap getSelPixmap() const;
};

class myInvertSelItem:public MyFreeShapeSelItem{
public:
    myInvertSelItem();
    myInvertSelItem(QRect rect,QPolygon poly,QPixmap pix);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
};

#endif // MYITEM_H
