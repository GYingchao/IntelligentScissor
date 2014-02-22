#include "qtpro1.h"

QtPro1::QtPro1(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ui.imageWidget->installEventFilter(this);
	//ui.imageWidget->setLabelX(ui.mouse_x);
	//ui.imageWidget->setLabelY(ui.mouse_y);
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
		// Pass the image to imageHandler
		img_handler = new ImageHandler(img);
		// Computing edge cost
		img_handler->InitializeCostGraph();

		ui.imageWidget->repaint();
	}
}

bool QtPro1::eventFilter(QObject *obj, QEvent *ev)
{
	if(obj == ui.imageWidget) {
		if(ev->type() == QEvent::Type::MouseMove) {
			int x = ui.imageWidget->getMouse_x();
			int y = ui.imageWidget->getMouse_y();
			QString tem("X: ");
			tem.append(QString::number(x));
			tem.append(", Y: ");
			tem.append(QString::number(y));
			ui.MousePos->setText(tem);
		}
	}
	return QObject::eventFilter(obj, ev);
}