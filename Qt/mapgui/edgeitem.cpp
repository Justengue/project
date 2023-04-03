#include "edgeitem.h"

#include <regex>
#include <sstream>

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>

EdgeItem::EdgeItem(Vertex &start, Vertex &end): startP(start.getX(), start.getY()), endP(end.getX(), end.getY()) {
    color_ = QColor(128, 109, 52);
    setFlags(ItemIsSelectable);
}

QRectF EdgeItem::boundingRect() const
{
  return QRectF(startP, endP).normalized();
}

void EdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF offset(10, 10);
    QPen pen(color_);
    int width = 3;
    if (option->state & QStyle::State_Selected) {
      width += 2;
    }

    pen.setWidth(width);

    painter->setPen(pen);
    painter->drawLine(startP+offset, endP+offset);
}

