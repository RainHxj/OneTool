#ifndef MYLABEL_H
#define MYLABEL_H

#include <QVector>
#include <opencv2/opencv.hpp>
#include <QLabel>
#include <QPoint>
#include <QKeyEvent>
#include <QCursor>
using namespace cv;
using namespace std;


//重写label 类
class MyLabel : public QLabel
{
	Q_OBJECT
public:
	MyLabel(QWidget *parent = 0);
	~MyLabel();

	//鼠标事件
	void paintEvent(QPaintEvent *);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	//滚轮事件
	//void wheelEvent(QWheelEvent *event);
	//进行图像的尺度变换
	void scaledTransform(QPixmap & pic, double factor_scale);
	// 放大之后点的选择
	void MyLabel::PointInRect(QVector<QPoint>& lp, QVector<int>& rp);
public:
	QPixmap  img;
	QVector<QPoint> temPoint;

	// 放大区域的实现
	QPixmap scaledImg;//放大以后的图像

signals:
	void valueChange(int);

private:
	//设置一些标志位 来控制组合键的使用
	bool mouse_left; // 判断左键是否按下
	bool dropOn; // 是否进行拖动中/
	QPoint mousePoint;
	int dd; //表示改变的点的编号
	//绘制举行框需要的点
	QPoint rectStart;
	QPoint rectFinish;
	//定义一个鼠标的放大指针样式
	QCursor *myCursor;
	// 判断鼠标是否在放大区域
	bool zoomCursor;
	// 判断是否正在放大
	bool zoomingOn;

	//放大图像的起点坐标
	QPoint scaledImgPoint;
	//放置被选中的点
	QVector<int> pInRect;



};

#endif