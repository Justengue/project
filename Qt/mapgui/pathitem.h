#pragma once

#include "vertex.h"
#include <QGraphicsItem>
#include <QColor>
#include <cstdint>
#include <string>

class PathItem : public QGraphicsItem
{
public:
    PathItem(Vertex &v);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

#if 0
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
#endif

private:
    QColor color_;
    int x_;
    int y_;
    uint32_t vid_;
};

