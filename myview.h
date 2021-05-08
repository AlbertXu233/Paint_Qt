#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QTextEdit>
#include <mywidget.h>
#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif

class MyView : public QGraphicsView
{
    Q_OBJECT
    bool hasGlass=false;
    bool textEditMode=false;
    bool eraserMode=false;
    bool isPressed=false;
    bool updateMode=false;
    bool gridOn=false;
    QPoint currentPnt;
    QPointF currentScenePnt;
    QPoint localStartPnt;
    QPoint localEndPnt;
    QPoint instantLocalEndPnt;
    QTextEdit* textinstant;
    QString textInput;
    int eraserWidth=8;
    QPen viewPen=QPen(Qt::black);
    QBrush viewBrush=Qt::white;
    QPixmap* eraserShapeOrign;
    QPixmap eraserShape;
    QImage* eraserImage;
    QVector<QRect> eraserRects;
    QVector<QRect> eraserRectsOut;
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
public:
    explicit MyView(QWidget *parent=nullptr);
//    ~MyView();
    myWidget *mywidget;
    bool getHasGlass() const;
    void setHasGlass(bool value);

    QPoint getCurrentPnt() const;
    void setCurrentPnt(const QPoint &value);

    QPointF getCurrentScenePnt() const;
    void setCurrentScenePnt(const QPointF &value);

    bool getTextEditMode() const;
    void setTextEditMode(bool value);

    QPoint getLocalStartPnt() const;
    void setLocalStartPnt(const QPoint &value);

    QPoint getLocalEndPnt() const;
    void setLocalEndPnt(const QPoint &value);

    QString getTextInput() const;
    void setTextInput(const QString &value);

    bool getEraserMode() const;
    void setEraserMode(bool value);

    int getEraserWidth() const;
    void setEraserWidth(int value);

    QPen getViewPen() const;
    void setViewPen(const QPen &value);

    QBrush getViewBrush() const;
    void setViewBrush(const QBrush &value);

    QVector<QRect> getEraserRectsOut() const;

    void setUpdateMode(bool value);

    QImage *getEraserImage() const;

    void setGridOn(bool value);

signals:
    void mousePreEvent(QMouseEvent *e,QPointF p);
    void mouseMoEvent(QMouseEvent *e,QPointF p);
    void mouseReEvent(QMouseEvent *e,QPointF p);
protected:
private slots:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void drawForeground(QPainter *painter, const QRectF &rect);
};
#endif  //MYVIEW_H
