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
		//img_handler->LiveWireDP(3, 5);
		ui.imageWidget->repaint();
		ui.imageWidget->loadImageHandler(img_handler);

		// Just to test
		//img_handler->ComputePixelNodeGraph();
	}
}

void QtPro1::on_actionStart_triggered()
{
	if(!ui.imageWidget->isStarted()) {
		// Start the intelligent scissor
		ui.imageWidget->Start();
		cout << "Start the iScissor..." << endl;
		ui.imageWidget->repaint();
	}
}

void QtPro1::on_actionStop_triggered()
{
	ui.imageWidget->Stop();
	ui.imageWidget->repaint();
}

void QtPro1::on_actionSave_mask_triggered()
{
	img_handler->saveMask(ui.imageWidget->getContour());
}

void QtPro1::on_actionSave_Contour_triggered()
{
	img_handler->saveContour(ui.imageWidget->getContour());
}

void QtPro1::on_actionExit_triggered()
{
	exit(0);
}

bool QtPro1::eventFilter(QObject *obj, QEvent *ev)
{
	if(obj == ui.imageWidget) {
		if(ev->type() == QEvent::Type::MouseMove || ev->type() == QEvent::Type::MouseButtonPress) {
			int x = ui.imageWidget->getMouse_x();
			int y = ui.imageWidget->getMouse_y();
			QString tem("X: ");
			tem.append(QString::number(x));
			tem.append(", Y: ");
			tem.append(QString::number(y));
			ui.MousePos->setText(tem);
		} 

		/* This test shows dim(cv::Mat img) is the same with dim(qimg)
		if(ev->type() == QEvent::Type::MouseButtonPress) {
			cout << "cv::Mat " << img_handler->width() << ", " << img_handler->height() << endl;
		}
		*/
		/* Unluckily this event happens before imageWidget::MousePressEvent
		if(ev->type() == QEvent::Type::MouseButtonPress) {
			// Pass the mouse clicked pixel index into image_handler
			img_handler->setSeed(ui.imageWidget->getImg_x(), ui.imageWidget->getImg_y());
			cout << "Into img_hander: " << ui.imageWidget->getImg_x() << ", " << ui.imageWidget->getImg_y() << endl;
		}
		*/
	}
	return QObject::eventFilter(obj, ev);
}