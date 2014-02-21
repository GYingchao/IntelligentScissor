#ifndef IMAGE_DISPLAYER_H_H
#define IMAGE_DISPLAYER_H_H
#include <QWidget>
#include <QPainter>
#include <qevent.h>
#include <opencv2/opencv.hpp>
class ImageDisplayer : public QWidget
{
	Q_OBJECT
public:
	ImageDisplayer(QWidget* parent);
	~ImageDisplayer();
	void paintEvent(QPaintEvent *event);
	void keyPressEvent(QKeyEvent *event);

	void drawImage(QPainter &painter);
	void loadImage(cv::Mat img);
private:
	cv::Mat img;
	int zoomFactor;
private:
	void zoomIn();
	void zoomOut();
};
#endif;