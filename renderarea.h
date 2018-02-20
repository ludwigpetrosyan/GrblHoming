#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>

#include "positem.h"
#include "renderitemlist.h"
#include "arcitem.h"
#include "lineitem.h"
#include "renderitemlist.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);
    
signals:
    
public slots:
    void setItems(QList<PosItem>);
    void setLivePoint(double x, double y, bool isMM);
    void setXYPoint(double x, double y, bool isMM);
    void setVisCurrLine(int currLine);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QList<PosItem> items;
    RenderItemList listToRender;
    QPen penProposedPath, penAxes, penCoveredPath, penCurrPos, penMeasure, penXYpos;
    PosItem livePoint;
    PosItem xyPoint;
    poscoord xyPosCoord;
    
    QPointF lastPoint;
    bool modified;
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    void drawLineTo(const QPoint &endPoint);
};

#endif // RENDERAREA_H
