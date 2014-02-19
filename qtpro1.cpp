#include "qtpro1.h"

QtPro1::QtPro1(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

QtPro1::~QtPro1()
{

}

void QtPro1::on_actionOpen_Image_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, "Load Image", ".", "BMP files(*.bmp)");
	if(filename != NULL) {
		cv::Mat img = cv::imread(filename.toAscii().data());
		cv::cvtColor(img, img, CV_BGR2RGB);
		//QImage qimg = QImage((const unsigned char*)(img.data), img.cols, img.rows, QImage::Format_RGB32);
		ui.imageWidget->loadImage(img);
		ui.imageWidget->repaint();
	}
}