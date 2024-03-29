#include "vertexitem.h"
#include <regex>
#include <sstream>

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>

#define R 1

VertexItem::VertexItem(Vertex &v){
    vid_ = v.getId();
    x_ = v.getX();
    y_ = v.getY();
    color_ = QColor(128, 109, 52);
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setPos(x_, y_);
}

QRectF VertexItem::boundingRect() const
{
  return QRectF(0.0,0.0,20.0,20.0);
}

QPainterPath VertexItem::shape() const
{
    QPainterPath path;
    path.addEllipse(0.0,0.0,20.0,20.0);
    return path;
}

void VertexItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget */*widget*/)
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

    painter->drawEllipse(0, 0, 20, 20);
    painter->setBrush(b);

    // Draw text
    if (lod >= 2) {
      QFont font("Times", 5);
      font.setStyleStrategy(QFont::ForceOutline);
      painter->setFont(font);
      painter->setPen(Qt::white);
      painter->drawText(10, 10, QString("ID=%1").arg(vid_));
      painter->drawText(10, 20, QString("X=%1").arg(x_));
      painter->drawText(10, 30, QString("Y=%1").arg(y_));
    } else if (lod >= 0.6) {
      QFont font("Times", 5);
      font.setStyleStrategy(QFont::ForceOutline);
      painter->setFont(font);
      painter->setPen(Qt::white);
      painter->drawText(10, 20, QString("%1").arg(vid_));
    }
}
