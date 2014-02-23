#ifndef IMAGE_DISPLAYER_H_H
#define IMAGE_DISPLAYER_H_H
#include <QWidget>
#include <QPainter>
#include <qevent.h>
#include <QLabel>
#include <opencv2/opencv.hpp>
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
public:
	void drawImage(QPainter &painter);
	void loadImage(cv::Mat img);
	bool isEmpty() {return img.data == NULL;}
	int getMouse_x() {return mouse_x;}
	int getMouse_y() {return mouse_y;}
private:
	cv::Mat img;
	int zoomFactor;
	int mouse_x, mouse_y;
	//QSize origSize;

	//QLabel* m_x;
	//QLabel* m_y;
private:
	void zoomIn();
	void zoomOut();
};
#endif;