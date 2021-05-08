#include "myview.h"
#include <QKeyEvent>
#include <qgraphicsitem.h>
#include <qdebug.h>
#include <qtextedit.h>
#include <QBitmap>
#include <mywidget.h>

QString MyView::getTextInput() const
{
    return textInput;
}

void MyView::setTextInput(const QString &value)
{
    textInput = value;
}

bool MyView::getEraserMode() const
{
    return eraserMode;
}

void MyView::setEraserMode(bool value)
{
    eraserMode = value;
}

int MyView::getEraserWidth() const
{
    return eraserWidth;
}

void MyView::setEraserWidth(int value)
{
    eraserWidth = value;
}

QPen MyView::getViewPen() const
{
    return viewPen;
}

void MyView::setViewPen(const QPen &value)
{
    viewPen = value;
}

QBrush MyView::getViewBrush() const
{
    return viewBrush;
}

void MyView::setViewBrush(const QBrush &value)
{
    viewBrush = value;
}

QVector<QRect> MyView::getEraserRectsOut() const
{
    return eraserRectsOut;
}

void MyView::setUpdateMode(bool value)
{
    updateMode = value;
}

QImage *MyView::getEraserImage() const
{
    return eraserImage;
}

MyView::MyView(QWidget *parent) :
    QGraphicsView(parent)
{
    eraserShapeOrign=new QPixmap(":/image/正方形.png");
    eraserShape=eraserShapeOrign->scaled(QSize(3,3));
    mywidget=new myWidget();
    mywidget->setGeometry(247,352,1101,491);
    mywidget->setAttribute(Qt::WA_TranslucentBackground,true);
//    mywidget->setwindow
//    Qt::Dialog
    mywidget->setWindowFlags( Qt::FramelessWindowHint  );
// | Qt::WindowStaysOnTopHint
    connect(mywidget,SIGNAL(mousePreEvent(QMouseEvent *)),this,SLOT(mousePressEvent(QMouseEvent *)));
    connect(mywidget,SIGNAL(mouseMoEvent(QMouseEvent *)),this,SLOT(mouseMoveEvent(QMouseEvent *)));
    connect(mywidget,SIGNAL(mouseReEvent(QMouseEvent *)),this,SLOT(mouseReleaseEvent(QMouseEvent *)));
//    eraserImage=new QImage(1099,489,QImage::Format_RGB32);
//    eraserImage->fill(Qt::transparent);
//    textinstant->setVisible(false);
}

void MyView::setGridOn(bool value)
{
    gridOn = value;
    viewport()->update();
}

void MyView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
}

void MyView::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    mywidget->hide();
    mywidget->show();
}

QPoint MyView::getLocalEndPnt() const
{
    return localEndPnt;
}

void MyView::setLocalEndPnt(const QPoint &value)
{
    localEndPnt = value;
}

QPoint MyView::getLocalStartPnt() const
{
    return localStartPnt;
}

void MyView::setLocalStartPnt(const QPoint &value)
{
    localStartPnt = value;
}

bool MyView::getTextEditMode() const
{
    return textEditMode;
}

void MyView::setTextEditMode(bool value)
{
    textEditMode = value;
}

QPointF MyView::getCurrentScenePnt() const
{
    return currentScenePnt;
}

void MyView::setCurrentScenePnt(const QPointF &value)
{
    currentScenePnt = value;
}

QPoint MyView::getCurrentPnt() const
{
    return currentPnt;
}

void MyView::setCurrentPnt(const QPoint &value)
{
    currentPnt = value;
}



bool MyView::getHasGlass() const
{
    return hasGlass;
}

void MyView::setHasGlass(bool value)
{
    hasGlass = value;
}

//MyView::~MyView()
//{
//    delete (this);

//}




void MyView::keyPressEvent(QKeyEvent *event)
{
    //    switch (event->key())
//    {
//    case Qt::Key_Plus :
//        scale(1.2, 1.2);
//        break;
//    case Qt::Key_Minus :
//        scale(1 / 1.2, 1 / 1.2);
//        break;
//    case Qt::Key_Right :
//        rotate(30);
//        break;
//    }
    QGraphicsView::keyPressEvent(event);
}

void MyView::mousePressEvent(QMouseEvent *e)
{

    isPressed=1;
    QGraphicsView::mousePressEvent(e);
    if (!this->scene()->selectedItems().isEmpty()){
        mywidget->setIsPressed(0);
        mywidget->update();
    }
    QPointF sceneEve= mapToScene(e->pos());
    if(textEditMode){
        setLocalStartPnt(e->pos());
        setLocalEndPnt(e->pos());
        instantLocalEndPnt=e->pos();
//        if(textinstant->toHtml().count()!=473){
//            textInput=textinstant->toPlainText();
//            textinstant->clear();
//            textinstant->setGeometry(0,0,0,0);
//        }else {
//            textInput.clear();
//        }
    }
//    if (this->mywidget->getTextInput().isEmpty())
//    {    setCurrentScenePnt(sceneEve);}
    emit mousePreEvent(e,sceneEve);

}

void MyView::mouseMoveEvent(QMouseEvent *e)
{
    instantLocalEndPnt=e->pos();
    QGraphicsView::mouseMoveEvent(e);
    QPointF sceneEve= mapToScene(e->pos());
    emit mouseMoEvent(e,sceneEve);
    setCurrentPnt(e->pos());
    if (hasGlass){
//        this->viewport()->update();
    }
    if (eraserMode){
//        mywidget->setCursor(QCursor(eraserShape));
        localStartPnt=e->pos();
//        this->viewport()->update();
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

void MyView::mouseReleaseEvent(QMouseEvent *e)
{
    isPressed=0;
    updateMode=true;
    eraserRectsOut=eraserRects;
    eraserRects.clear();
    if(textEditMode){
        setLocalEndPnt(e->pos());
    }
    QGraphicsView::mouseReleaseEvent(e);
    QPointF sceneEve= mapToScene(e->pos());
    emit mouseReEvent(e,sceneEve);
}

void MyView::drawForeground(QPainter *painter, const QRectF &rect)
{
//    if (gridOn){
//        QVector<QLine> Lines;
////        qreal gapRatio;
////        QPointF distance=(mapToScene(QPoint(100,100))-mapToScene(QPoint(0,0)));
////        gapRatio=distance.x()/100;
//        int gap=10;
//        for (int i=1;i<=rect.width()/gap;i++){
//            Lines<<QLine(i*gap,0,i*gap,rect.height());
//        }
//        for (int i=1;i<rect.height()/gap;i++){
//            Lines<<QLine(0,i*gap,rect.width(),i*gap);
//        }
//        painter->setPen(Qt::DotLine);
//        painter->drawLines(Lines);
//    }
}

