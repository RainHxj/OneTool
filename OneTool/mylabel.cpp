#include "mylabel.h"
#include <QPainter>
#include <QPen>
#include <QMessageBox>
#include "onetool.h"
 MyLabel::~MyLabel()
{

}
 MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
 {
	 this->setScaledContents(true); 
	 this->resize(parent->size());
	 setMouseTracking(true);
	 mouse_left = 0;
	 dropOn = 0; //初始化 不被拖的模式
	 dd = -1;
	 QPixmap icon = QPixmap(".\\icon\\zoom.ico");
	 icon=icon.scaled(20, 20, Qt::KeepAspectRatioByExpanding);
	 myCursor=new QCursor(icon,-1,-1); 
	 rectStart  = QPoint(-1,-1);
	 rectFinish = QPoint(-1, -1);
	 zoomCursor = 0;
	 zoomingOn = 0;
 }

 void MyLabel::paintEvent(QPaintEvent *event)
 {
	 QLabel::paintEvent(event);
	 QPainter painter(this);             // 创建QPainter一个对象
	 painter.drawPixmap(0, 0, img);
	
	 //在这个地方显示放大以后的图像
	 if (zoomingOn)
	 {
		 painter.drawPixmap(scaledImgPoint.x(), scaledImgPoint.y(), scaledImg);
	 }
	 QPen pen;
	 pen.setWidth(3);

	 // pen.setStyle(Qt::DashLine);        
	 pen.setColor(Qt::red);           // 设置画笔为红色
	 painter.setPen(pen);                // 设置画笔
	 //放大模式下 只显示放大的区域
	 if (zoomingOn)
	 {
		 pen.setWidth(6);
		 painter.setPen(pen);
		 //设置一个正在被拖的模式
		 if (1 == dropOn)
		 {
			 for (int i = 0; i < pInRect.size(); ++i)
			 {
				 if (pInRect[i] != dd)
				 {
					 painter.drawPoint(temPoint[pInRect[i]]);
					
				 }
			 }
		 }
		 else
		 {
			 for (int i = 0; i < pInRect.size(); ++i)
			 {
				 painter.drawPoint(temPoint[pInRect[i]]);

			 }
			 if (dd != -1)  //设置要更改的点为蓝色 
			 {
				 pen.setWidth(6);
				 pen.setColor(Qt::blue);           // 设置画笔为蓝色
				 painter.setPen(pen);                // 设置画笔
				 painter.drawPoint(temPoint[dd]);
				// painter.drawEllipse(temPoint[dd],3,3);
			 }
		 }
	 }
	 else
	 {
		 //设置一个正在被拖的模式
		 if (1 == dropOn)
		 {
			 for (int i = 0; i < temPoint.size(); ++i)
			 {
				 if (i != dd)
				 {
					 painter.drawPoint(temPoint[i]);
					 //painter.drawEllipse(temPoint[i], 3, 3);
				 }
			 }
		 }
		 else
		 {
			 for (int i = 0; i < temPoint.size(); ++i)
			 {
				 painter.drawPoint(temPoint[i]);
				 //painter.drawEllipse(temPoint[i], 3, 3);
			 }
			 if (dd != -1)  //设置要更改的点为蓝色 
			 {
				 pen.setWidth(3);
				 pen.setColor(Qt::blue);           // 设置画笔为蓝色
				 painter.setPen(pen);                // 设置画笔
				 painter.drawPoint(temPoint[dd]);
				 //painter.drawEllipse(temPoint[dd], 3, 3);
			 }
		 }
	 }
	 //绘制矩形框
	 if ((rectFinish.x() != -1 && rectFinish.y() != -1 && rectStart.x() != -1 && rectStart.y() != -1))
	 {
		 pen.setWidth(1);
		 pen.setColor(Qt::white);
		 painter.setPen(pen);
		 painter.drawRect(rectStart.x(), rectStart.y(), rectFinish.x() - rectStart.x(), rectFinish.y() - rectStart.y());

	 }

}
void MyLabel::mousePressEvent(QMouseEvent *event)
{
	
	//通过ctrl键配合 点击鼠标左键开始画点
	if (event->button() == Qt::RightButton)
	{
		
		zoomingOn = 0;

		emit valueChange(zoomingOn);
		this->resize(img.width(), img.height());
		// 将所有的坐标点返回到小图上面
		for (int i = 0; i < pInRect.size(); ++i)
		{
			temPoint[pInRect[i]] = QPoint((temPoint[pInRect[i]].x() - scaledImgPoint.x()) / 4 + scaledImgPoint.x(), (temPoint[pInRect[i]].y() - scaledImgPoint.y()) / 4 + scaledImgPoint.y());
		}

		pInRect.clear();

	}
	else if (event->button() == Qt::LeftButton)
	{
		mouse_left = 1;
		if (QApplication::keyboardModifiers() == Qt::ControlModifier && dd != -1)

		{
			if (event->button() == Qt::LeftButton)
			{
				//开启被拖的模式
				dropOn = 1;
				setCursor(Qt::CrossCursor);

			}
		}
		//鼠标画矩形框 ，进行局部放大
		else if (QApplication::keyboardModifiers() != Qt::ControlModifier && zoomingOn ==0)
		{
			//
			if (1 == zoomCursor)
			{
				zoomingOn = 1;
				scaledImg = img.copy(rectStart.x(), rectStart.y(), rectFinish.x() - rectStart.x(), rectFinish.y() - rectStart.y());
				scaledTransform(scaledImg, 4);//进行局部放大；
				setCursor(Qt::ArrowCursor);
				scaledImgPoint = rectStart;
				
				//发送一个正在放大的信号 给 oneTool
				emit valueChange(zoomingOn);

				//判断 是否需要更大画布
				int x_paint = max(img.width(), rectStart.x() + 4 * (rectFinish.x() - rectStart.x()));
				int y_paint = max(img.height(), rectStart.y() + 4 * (rectFinish.y() - rectStart.y()));;
				this->resize(x_paint, y_paint);

				//选中需要更改的点
				PointInRect(temPoint, pInRect);
			}
			else
			{
				setCursor(Qt::CrossCursor);
				mousePoint = event->globalPos();
				mousePoint = mapFromGlobal(mousePoint);
				rectStart = mousePoint;
			}
			rectFinish = QPoint(-1, -1);
		}
	}
	update();
}

void MyLabel::mouseReleaseEvent(QMouseEvent *event)
{
	//通过ctrl键配合 左键松开 重新画点
	if (event->button() == Qt::LeftButton)
	{
		mouse_left = 0;
		if (dd != -1 && QApplication::keyboardModifiers() == Qt::ControlModifier)
		{
			if (event->button() == Qt::LeftButton)
			{
				setCursor(Qt::ArrowCursor);//更改鼠标的样式
				QPoint mousePos = event->globalPos();
				mousePos = mapFromGlobal(mousePos);
				temPoint[dd] = mousePos;
				dropOn = 0;
				dd = -1;
			}
		}
		// 松开以后进行矩形框的绘制
		else if (QApplication::keyboardModifiers() != Qt::ControlModifier && zoomCursor == 0 && zoomingOn == 0)
		{
			setCursor(Qt::ArrowCursor);//更改鼠标的样式
			mousePoint = event->globalPos();
			mousePoint = mapFromGlobal(mousePoint);
			rectFinish = mousePoint;
		}
		if (dd != -1 && QApplication::keyboardModifiers() != Qt::ControlModifier)
		{
			dd = -1;
			setCursor(Qt::ArrowCursor);//更改鼠标的样式
		}
	}
	update();

}

void MyLabel::mouseMoveEvent(QMouseEvent *event)
{
	mousePoint = event->globalPos();
	mousePoint = mapFromGlobal(mousePoint);
	/*通过和ctrl 键的配合 来进行选择将要拖动的点*/
	if (QApplication::keyboardModifiers() == Qt::ControlModifier && mouse_left ==0)
	{
		//QMessageBox::information(this, "info", "ctrl");
		if (zoomingOn)
		{
			int dis_min = 300000;
			for (int i = 0; i < pInRect.size(); ++i) // 为 放大 模式 //遍历的更快一些
			{
				int dis = sqrt((mousePoint.x() - temPoint[pInRect[i]].x())*(mousePoint.x() - temPoint[pInRect[i]].x()) + (mousePoint.y() - temPoint[pInRect[i]].y())*(mousePoint.y() - temPoint[pInRect[i]].y()));
				if (dis <dis_min)
				{
					dis_min = dis;
					if (dis_min < 4)
						dd = pInRect[i];
					else
						dd = -1;
				}

			}
		}
		else
		{
			int dis_min = 300000;
			for (int i = 0; i < temPoint.size(); ++i) // 为 不放大 模式
			{
				int dis = sqrt((mousePoint.x() - temPoint[i].x())*(mousePoint.x() - temPoint[i].x()) + (mousePoint.y() - temPoint[i].y())*(mousePoint.y() - temPoint[i].y()));
				if (dis <dis_min)
				{
					dis_min = dis;
					if (dis_min < 3)
						dd = i;
					else
						dd = -1;
				}
			}
		}
		
	}//鼠标左键按下，移动鼠标画出矩形框 在不放大的模式下面
	else if (QApplication::keyboardModifiers() != Qt::ControlModifier && mouse_left&&zoomingOn==0)
	{
		rectFinish = mousePoint;
	}//鼠标移动时，通过判断是否在矩形框内进行鼠标的更改，在矩形框内时显示为放大镜 ,条件是不在放大模式
	else if (QApplication::keyboardModifiers() != Qt::ControlModifier&&mouse_left==0 )
	{
		
		if (mousePoint.x() > rectStart.x() && mousePoint.x() < rectFinish.x() && mousePoint.y() > rectStart.y() && mousePoint.y() < rectFinish.y())
		{
			setCursor(*myCursor);
			zoomCursor = 1;
		}
		else
		{
			setCursor( Qt:: ArrowCursor);
			zoomCursor = 0;

		}
	}


	update();
}

/*****
图像处理区域
放大实现功能：
1、画框实现放大，并将后面的图进行虚化，
****/
void MyLabel::scaledTransform(QPixmap & pic,double factor_scale)
{
	pic = pic.scaled(pic.width()*factor_scale, pic.height()*factor_scale);
}

void MyLabel::PointInRect(QVector<QPoint>& lp, QVector<int>& rp)
{
	for (int i = 0; i < lp.size(); ++i)
	{
		if (lp[i].x() > rectStart.x() && lp[i].x() < rectFinish.x() && lp[i].y() > rectStart.y() && lp[i].y() < rectFinish.y())
		{
			rp.push_back(i);
			lp[i] = QPoint((lp[i].x() - rectStart.x()) * 4 + rectStart.x(), (lp[i].y() - rectStart.y()) * 4 + rectStart.y());
		}
	}
}
