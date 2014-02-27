#ifndef QTPRO1_H
#define QTPRO1_H

#include <QtGui/QMainWindow>
#include <QtGui/qfiledialog.h>
#include <string>
#include "ui_qtpro1.h"
#include "imageDisplayer.h"
#include "imageHandler.h"


class QtPro1 : public QMainWindow
{
	Q_OBJECT

public:
	QtPro1(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QtPro1();
protected:
     bool eventFilter(QObject *obj, QEvent *ev);
public slots:
	void on_actionOpen_Image_triggered();
	void on_actionStart_triggered();
	void on_actionStop_triggered();
	void on_actionSave_mask_triggered();
	void on_actionSave_Contour_triggered();
private:
	Ui::QtPro1Class ui;
	ImageHandler *img_handler;
};

#endif // QTPRO1_H
