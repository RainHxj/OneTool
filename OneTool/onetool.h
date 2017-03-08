#ifndef ONETOOL_H
#define ONETOOL_H

#include <QtWidgets/QMainWindow>
#include "ui_onetool.h"
#include <qlabel.h>
#include <qimage.h>
#include <QPixmap>
#include <QPainter>
#include <Qpen>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>
#include <QScrollarea>
#include "mylabel.h"

using namespace std;

class OneTool : public QMainWindow
{
	Q_OBJECT

public:
	OneTool(QWidget *parent = 0);
	~OneTool();
	//void paintEvent(QPaintEvent *);
	MyLabel * shImage;
	QString imgFileName;
	QString temFileName;
	QString saveFileName;
	bool ctrl_key;

public slots:
	void openImgFile();
	void openTemFile(); 
	void saveTemplate();

	void ableButton( int );
private:
	Ui::OneToolClass ui;

	int RX; //坐标变换的x轴位移
	int RY;
	
};

#endif // ONETOOL_H
