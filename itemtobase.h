#ifndef ITEMTOBASE_H
#define ITEMTOBASE_H
#include <QPainter>
#include "stdio.h"
#include "positem.h"

class ItemToBase
{
public:
    ItemToBase(int index);

    virtual void moveToFirst(QPainterPath& path) = 0;
    virtual void addToPath(QPainterPath& path) = 0;
    virtual PosItem computeExtents() = 0;

    virtual double getXScr() = 0;
    virtual double getYScr() = 0;
    virtual double getXRaw() = 0;
    virtual double getYRaw() = 0;

    void setParams(double scale, double height, double offsetx, double offsety);

    double screenX(double x);
    double screenY(double y);
    
    double itemX(double x);
    double itemY(double y);

    int getIndex() { return index; }

protected:
    double scale;
    double height;
    double offsetx;
    double offsety;
    int index;
};

#endif // ITEMTOBASE_H
