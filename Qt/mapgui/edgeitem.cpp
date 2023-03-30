#include "edgeitem.h"

#include <regex>
#include <sstream>

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>

EdgeItem::EdgeItem(Vertex &start, Vertex &end): startP(start.getLat(), start.getLong()), endP(end.getLat(), end.getLong()) {
    color_ = QColor(128, 109, 52);
    setFlags(ItemIsSelectable);
    setPos(startX_, startY_);
}

QRectF EdgeItem::boundingRect() const
{
  return QRectF(qMin(startX_, endX_), qMin(startY_, endY_),
                qAbs(endX_ - startX_), qAbs(endY_ - startY_));
}

void EdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(color_);
    int width = 10;
    if (option->state & QStyle::State_Selected) {
      width += 2;
    }

    pen.setWidth(width);

    painter->setPen(pen);
    painter->drawLine(0, 0, 0, 0);
}

