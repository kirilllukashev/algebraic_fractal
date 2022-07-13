#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <QGraphicsView>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include "complex_number.h"

namespace Ui {
class Image;
}

class Image : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Image(QGraphicsView *parent = nullptr);
    ~Image();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    Ui::Image *ui;
    QGraphicsScene *scene;
    QImage *image_;
};

#endif // IMAGE_H
