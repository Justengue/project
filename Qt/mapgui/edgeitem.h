#pragma once

#include "vertex.h"
#include <QGraphicsItem>
#include <QColor>
#include <cstdint>
#include <string>


class EdgeItem : public QGraphicsItem
{
    public:
        EdgeItem(Vertex &start, Vertex &end);

        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    #if 0
    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    #endif

    private:
        QColor color_;
        QPointF startP, endP;
};
