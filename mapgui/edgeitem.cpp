#include "edgeitem.h"

#include <regex>
#include <sstream>

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>

EdgeItem::EdgeItem(uint32_t v1, uint32_t v2, double d): vsid_(v1), veid_(v2), length_(d), color_(QColor(128, 109, 52)) {}

QRectF EdgeItem::boundingRect() const
{
  return QRectF(0.0,0.0,40.0,40.0);
}

QPainterPath EdgeItem::shape() const
{
    QPainterPath path;
    path.addEllipse(0.0,0.0,40.0,40.0);
    return path;
}

void EdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget */*widget*/)
{

    QColor fillColor = (option->state & QStyle::State_Selected) ? color_.darker(150) : color_;
    if (option->state & QStyle::State_MouseOver) {
      fillColor = fillColor.lighter(125);
    }

    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());


    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected) {
      width += 2;
    }

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.darker(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawEllipse(0, 0, 40, 40);
    painter->setBrush(b);

    // Draw text
    if (lod >= 2) {
      QFont font("Times", 5);
      font.setStyleStrategy(QFont::ForceOutline);
      painter->setFont(font);
      painter->setPen(Qt::white);
      /*
      painter->drawText(10, 10, QString("ID=%1").arg(vsid_));
      painter->drawText(10, 20, QString("X=%1").arg(vsid_));
      painter->drawText(10, 30, QString("Y=%1").arg(y_));
    } else if (lod >= 0.6) {
      QFont font("Times", 5);
      font.setStyleStrategy(QFont::ForceOutline);
      painter->setFont(font);
      painter->setPen(Qt::white);
      painter->drawText(10, 20, QString("%1").arg(vsid_));
      */
    }
}
