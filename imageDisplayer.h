#ifndef IMAGE_DISPLAYER_H_H
#define IMAGE_DISPLAYER_H_H
#include <QWidget>
#include <QPainter>
#include <qevent.h>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include "imageHandler.h"

class ImageDisplayer : public QWidget
{
	Q_OBJECT
public:
	ImageDisplayer(QWidget* parent);
	~ImageDisplayer();
protected:
	void paintEvent(QPaintEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void mouseMoveEvent ( QMouseEvent * event );
	void mousePressEvent ( QMouseEvent * event );
public:
	void drawImage(QPainter &painter);
	void loadImage(cv::Mat img);
	void loadImageHandler(ImageHandler* han) {handler = han;}
	bool isEmpty() {return img.data == NULL;}
	int getMouse_x() {return mouse_x;}
	int getMouse_y() {return mouse_y;}
	int getImg_x() {return img_x;}
	int getImg_y() {return img_y;}
private:
	cv::Mat img;
	int zoomFactor;
	int mouse_x, mouse_y;
	int img_x, img_y;
	QImage qimg;
	ImageHandler* handler;
	//QSize origSize;

	//QLabel* m_x;
	//QLabel* m_y;
private:
	void zoomIn();
	void zoomOut();
};
#endif;