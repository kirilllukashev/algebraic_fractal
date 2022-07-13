#include "image.h"
#include "ui_image.h"

int count(double x, double y) {
    Complex z0(0, 0);
    Complex c(x,y);
    for (int i = 0; i < 50; ++i) {
        if (z0.abs() >= 2)
            return i;
        z0 = z0 * z0 + c;
    }
    return -1;
}


double hh = 0.5;
bool kk = false;
double x1 = 0;
double y2 = 0;
double zoom = 0.2;
bool k = false;
double ll, rii;
double lly, riy;
int xx1, yy1;
int xx, yy;

QGraphicsItem *kk1;

int size_x = 500, size_y = 500;

Image::Image(QGraphicsView *parent) :
    QGraphicsView(parent),
    ui(new Ui::Image)
{
    ui->setupUi(this);
    this->resize(size_x, size_y);

    scene = new QGraphicsScene();
    this->setScene(scene);

    image_ = new QImage(size_x, size_y, QImage::Format_RGB32);
    scene->clear();

    hh = 0.01;
    ll = -2.5;
    rii = 2.5;
    lly = -2.5;
    riy = 2.5;

    for (double ii = -2.5; ii < 2.5; ii += 0.01) {
        for (double jj = -2.5; jj < 2.5; jj += 0.01) {
            int i = 250 + ii * 100;
            int j = 250 + jj * 100;
            if ((i < 500 && i >= 0) && (j < 500 && j >= 0)) {
                int val = count(ii, jj);
                if (val == -1) {
                    image_->setPixel(i, j, qRgb(0, 0, 0));
                } else {
                    image_->setPixel(i, j, qRgb(0, 255 / 4 * val, 255 / 4 * val));
                }
            }
        }
    }
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image_));
    QPixmap pixmap = QPixmap(QPixmap::fromImage(*image_));
    QPixmap scaled_img = pixmap.scaled(this->width(), this->height(), Qt::KeepAspectRatio);
    scene->addPixmap(scaled_img);
    scene->setSceneRect(scaled_img.rect());
    kk1 = scene->addRect(QRectF(0, 0, 500, 500));
}

Image::~Image()
{
    delete ui;
}

void Image::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
    xx = event->x();
    yy = event->y();
    QGraphicsView::mousePressEvent(event);
}

void Image::mouseMoveEvent(QMouseEvent *event)
{
    scene->removeItem(kk1);
    QGraphicsView::mouseMoveEvent(event);
    kk1 = scene->addRect(QRectF(xx, yy, event->x() -xx, event->y() -yy));

}

void Image::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << event->pos();

    xx1 = event->x();
    yy1 = event->y();
    if (xx1 < xx)
        std::swap(xx, xx1);
    if (yy1 < yy)
        std::swap(yy, yy1);

    if (xx1 > 500)
        xx1 = 500;
    if (yy1 > 500)
        yy1 = 500;
    if (xx < 0)
        xx = 0;
    if (yy < 0)
        yy = 0;

    int d = std::min(abs(xx - xx1), abs(yy - yy1));

    xx1 = xx + d;
    yy1 = yy + d;
    double nx = ll + (rii - ll) * xx / 500;
    double nxx = ll + (rii - ll) * xx1 / 500;
    double ny = lly + (riy - lly) * yy / 500;
    double nyy = lly + (riy - lly) * yy1 / 500;
    ll = nx;
    rii = nxx;
    lly = ny;
    riy = nyy;

    scene->clear();

    double hh1 = (rii - ll) / 501;
    double hh2 = (riy - lly) / 501;
    qDebug() << ll << rii << hh1;
    qDebug() << lly << riy;
    int i = 0;
    int j = 0;
    for (double ii = ll; ii < rii; ii += hh1) {
        i++;
        j = 0;
        for (double jj = lly; jj < riy; jj += hh2) {

            j++;
            if ((i < 500 && i >= 0) && (j < 500 && j >= 0)) {
                int val = count(ii, jj);
                if (val == -1) {
                    image_->setPixel(i, j, qRgb(0, 0, 0));
                } else {
                    image_->setPixel(i, j, qRgb(0, 255 / 4 * val, 255 / 4 * val));
                }
            }
        }
    }
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image_));
    QPixmap pixmap = QPixmap(QPixmap::fromImage(*image_));
    QPixmap scaled_img = pixmap.scaled(this->width(), this->height(), Qt::KeepAspectRatio);
    scene->addPixmap(scaled_img);
    scene->setSceneRect(scaled_img.rect());
    qDebug() << "all";
}

