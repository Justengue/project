#pragma once

#include <QGraphicsItem>
#include <QColor>
#include <cstdint>
#include <string>

class EdgeItem : public QGraphicsItem
{
public:
    EdgeItem(uint32_t v1, uint32_t v2, double d);

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
    uint32_t vsid_;
    uint32_t veid_;
    double length_;
};
