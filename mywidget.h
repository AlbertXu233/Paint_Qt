#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QTextEdit>
#include <QTimer>
#include <QWidget>
#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
enum TextureType{
    solid,
    none,
    crayon,
    marker,
    oil,
    pencil,
    water
};

class myWidget : public QWidget
{
    Q_OBJECT
    bool hasGlass=false;
    bool textEditMode=false;
    bool eraserMode=false;
    bool isPressed=false;
    bool updateMode=false;
    bool funcBrushMode=false;
    bool gridOn=false;
    qreal sizeRatio=1;
    int shapeType=-1;
    int funcBrushType=1;
    int bWidth=5;
    int shapeWidth=1;
    QPoint currentPnt;
    QPoint localStartPnt;
    QPoint localEndPnt;
    QPoint instantLocalEndPnt;
    QTextEdit* textinstant;
    QString textInput;
    int eraserWidth=8;
    QVector<QRect> eraserRects;
    QVector<QRect> eraserRectsOut;
    QVector<QLine> calligraphyPen1;
    QVector<QPoint> airbrushPoints;
    QVector<QPoint> sideBrushPoints;
    QVector<QPoint> pgPnts;
    QTimer *airbrushTimer;
    QPolygon brushPolygon;
    QPolygon freeShapeOutline;
    QPixmap *texturePix;
    QImage imgr;

    TextureType pentype;
    TextureType brushtype=none;
    QPen myPen=QPen(Qt::black);
    QBrush myBrush=Qt::NoBrush;
    QPen funcBrushPenM=QPen(Qt::black);
    QPen funcBrushPenE=QPen(Qt::black);

    void myPenStyleSet();
    void myBrushStyleSet();
public:
    explicit myWidget(QWidget *parent = nullptr);
    ~myWidget();

    void setHasGlass(bool value);

    void setTextEditMode(bool value);

    void setEraserMode(bool value);

    void setIsPressed(bool value);

    void setUpdateMode(bool value);

    QPoint getLocalStartPnt() const;
    void setLocalStartPnt(const QPoint &value);

    QPoint getLocalEndPnt() const;
    void setLocalEndPnt(const QPoint &value);

    QPoint getCurrentPnt() const;
    void setCurrentPnt(const QPoint &value);

    void setEraserWidth(int value);

    QString getTextInput() const;

    QVector<QRect> getEraserRectsOut() const;

    void setShapeType(int value);

    void setFuncBrushMode(bool value);

    void setFuncBrushType(int value);

    QVector<QPoint> getAirbrushPoints() const;
    void clearAirbrushPoints();

    QPolygon getBrushPolygon() const;

    int getFuncBrushType() const;

    int getBWidth() const;
    void setBWidth(int value);

    void setMyPen(const QPen &value);

    void setMyBrush(const QBrush &value);

    void setBrushtype(const TextureType &value);

    void setPentype(const TextureType &value);

    QPen getFuncBrushPenM() const;

    QPen getFuncBrushPenE() const;

    QVector<QPoint> getPgPnts() const;

    void setGridOn(bool value);

    void setSizeRatio(const qreal &value);

    qreal getSizeRatio() const;

signals:
    void mousePreEvent(QMouseEvent *e);
    void mouseMoEvent(QMouseEvent *e);
    void mouseReEvent(QMouseEvent *e);
    void keyPreEvent(QKeyEvent *event);
protected:
    void funcBrushPenMidSet();
    void funcBrushPenEdgeSet();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void drawForeground(QPainter *painter);
public slots:
    void timerTriggerd();
};

#endif // MYWIDGET_H
