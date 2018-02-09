#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent),
      penProposedPath(QPen(Qt::blue)), penAxes(QPen(QColor(193,97,0))),
      penCoveredPath(QPen(QColor(60,196,70), 2)), penCurrPos(QPen(Qt::red, 6)), penXYpos(QPen(Qt::darkRed, 6)),
      penMeasure(QPen(QColor(151,111,26)))
{
    penCurrPos.setCapStyle(Qt::RoundCap);
    penXYpos.setCapStyle(Qt::RoundCap);
    
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;
    
    xyPosCoord.x = 0;
    xyPosCoord.y = 0;
}

void RenderArea::setItems(QList<PosItem> itemsRcvd)
{
    items = itemsRcvd;

    listToRender.setCurrFileLine(0);
    listToRender.convertList(items);
    listToRender.updateLivePoint();
    update();
}

void RenderArea::setLivePoint(double x, double y, bool mm)
{
	xyPosCoord.x = x;
	xyPosCoord.y = y;
	xyPosCoord.mm = mm;
	
    livePoint.setCoords(x, y, mm);
    listToRender.setLivePoint(livePoint);
    update();
}

void RenderArea::setXYPoint(double x, double y, bool mm)
{
	mm = xyPosCoord.mm;
    xyPoint.setCoords(x, y, mm);
    listToRender.setLivePointXY(xyPoint);
    update();
}

void RenderArea::setVisCurrLine(int currLine)
{
    if (listToRender.setCurrFileLine(currLine))
        update();
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    if (!items.size())
        return;

    QSize size = this->size();

    listToRender.rescale(size);

    QPainter painter(this);

    painter.setPen(penProposedPath);
    listToRender.writePath(painter, false);

    painter.setPen(penAxes);
    listToRender.drawAxes(painter);

    painter.setPen(penMeasure);
    listToRender.drawMeasurements(painter);

    painter.setPen(penCoveredPath);
    listToRender.writePath(painter, true);

    //if (!livePoint.isNull()) FIX isNull
    {
        painter.setPen(penCurrPos);
        listToRender.drawPoint(painter, livePoint);
    }
    
    {
        painter.setPen(penXYpos);
        listToRender.drawPoint(painter, xyPoint);
    }
}

void RenderArea::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		
		if (!items.size())
        return;

        lastPoint.setX(event->localPos().x());
        lastPoint.setY(event->localPos().y());
		//printf("X %f  Y %f\n", lastPoint.x(), lastPoint.y());
		listToRender.getPosCoord(&xyPosCoord, (double)lastPoint.x(), (double)lastPoint.y());
		//printf("PosX %f  PosY %f\n", xyPosCoord.x,  xyPosCoord.y);
		setXYPoint(xyPosCoord.x, xyPosCoord.y, xyPosCoord.mm);
        
        scribbling = true;
        
       
    }
}

void RenderArea::mouseMoveEvent(QMouseEvent *event)
{
	//if ((event->buttons() & Qt::LeftButton) && scribbling)
    //    drawLineTo(event->pos());
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && scribbling) {
        //setLivePoint((double) lastPoint.x(), (double) lastPoint.y(), true);
        scribbling = false;
    }
}

void RenderArea::drawLineTo(const QPoint &endPoint)
{
    //QPainter painter(&image);
    //QPainter painter(this);
    //painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        //Qt::RoundJoin));
                        
                        
    //painter.drawLine(lastPoint, endPoint);
    //modified = true;

    //int rad = (myPenWidth / 2) + 2;
    //update(QRect(lastPoint, endPoint).normalized()
                                     //.adjusted(-rad, -rad, +rad, +rad));
    //lastPoint = endPoint;
}
