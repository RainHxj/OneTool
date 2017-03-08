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
	 dropOn = 0; //��ʼ�� �����ϵ�ģʽ
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
	 QPainter painter(this);             // ����QPainterһ������
	 painter.drawPixmap(0, 0, img);
	
	 //������ط���ʾ�Ŵ��Ժ��ͼ��
	 if (zoomingOn)
	 {
		 painter.drawPixmap(scaledImgPoint.x(), scaledImgPoint.y(), scaledImg);
	 }
	 QPen pen;
	 pen.setWidth(3);

	 // pen.setStyle(Qt::DashLine);        
	 pen.setColor(Qt::red);           // ���û���Ϊ��ɫ
	 painter.setPen(pen);                // ���û���
	 //�Ŵ�ģʽ�� ֻ��ʾ�Ŵ������
	 if (zoomingOn)
	 {
		 pen.setWidth(6);
		 painter.setPen(pen);
		 //����һ�����ڱ��ϵ�ģʽ
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
			 if (dd != -1)  //����Ҫ���ĵĵ�Ϊ��ɫ 
			 {
				 pen.setWidth(6);
				 pen.setColor(Qt::blue);           // ���û���Ϊ��ɫ
				 painter.setPen(pen);                // ���û���
				 painter.drawPoint(temPoint[dd]);
				// painter.drawEllipse(temPoint[dd],3,3);
			 }
		 }
	 }
	 else
	 {
		 //����һ�����ڱ��ϵ�ģʽ
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
			 if (dd != -1)  //����Ҫ���ĵĵ�Ϊ��ɫ 
			 {
				 pen.setWidth(3);
				 pen.setColor(Qt::blue);           // ���û���Ϊ��ɫ
				 painter.setPen(pen);                // ���û���
				 painter.drawPoint(temPoint[dd]);
				 //painter.drawEllipse(temPoint[dd], 3, 3);
			 }
		 }
	 }
	 //���ƾ��ο�
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
	
	//ͨ��ctrl����� �����������ʼ����
	if (event->button() == Qt::RightButton)
	{
		
		zoomingOn = 0;

		emit valueChange(zoomingOn);
		this->resize(img.width(), img.height());
		// �����е�����㷵�ص�Сͼ����
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
				//�������ϵ�ģʽ
				dropOn = 1;
				setCursor(Qt::CrossCursor);

			}
		}
		//��껭���ο� �����оֲ��Ŵ�
		else if (QApplication::keyboardModifiers() != Qt::ControlModifier && zoomingOn ==0)
		{
			//
			if (1 == zoomCursor)
			{
				zoomingOn = 1;
				scaledImg = img.copy(rectStart.x(), rectStart.y(), rectFinish.x() - rectStart.x(), rectFinish.y() - rectStart.y());
				scaledTransform(scaledImg, 4);//���оֲ��Ŵ�
				setCursor(Qt::ArrowCursor);
				scaledImgPoint = rectStart;
				
				//����һ�����ڷŴ���ź� �� oneTool
				emit valueChange(zoomingOn);

				//�ж� �Ƿ���Ҫ���󻭲�
				int x_paint = max(img.width(), rectStart.x() + 4 * (rectFinish.x() - rectStart.x()));
				int y_paint = max(img.height(), rectStart.y() + 4 * (rectFinish.y() - rectStart.y()));;
				this->resize(x_paint, y_paint);

				//ѡ����Ҫ���ĵĵ�
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
	//ͨ��ctrl����� ����ɿ� ���»���
	if (event->button() == Qt::LeftButton)
	{
		mouse_left = 0;
		if (dd != -1 && QApplication::keyboardModifiers() == Qt::ControlModifier)
		{
			if (event->button() == Qt::LeftButton)
			{
				setCursor(Qt::ArrowCursor);//����������ʽ
				QPoint mousePos = event->globalPos();
				mousePos = mapFromGlobal(mousePos);
				temPoint[dd] = mousePos;
				dropOn = 0;
				dd = -1;
			}
		}
		// �ɿ��Ժ���о��ο�Ļ���
		else if (QApplication::keyboardModifiers() != Qt::ControlModifier && zoomCursor == 0 && zoomingOn == 0)
		{
			setCursor(Qt::ArrowCursor);//����������ʽ
			mousePoint = event->globalPos();
			mousePoint = mapFromGlobal(mousePoint);
			rectFinish = mousePoint;
		}
		if (dd != -1 && QApplication::keyboardModifiers() != Qt::ControlModifier)
		{
			dd = -1;
			setCursor(Qt::ArrowCursor);//����������ʽ
		}
	}
	update();

}

void MyLabel::mouseMoveEvent(QMouseEvent *event)
{
	mousePoint = event->globalPos();
	mousePoint = mapFromGlobal(mousePoint);
	/*ͨ����ctrl ������� ������ѡ��Ҫ�϶��ĵ�*/
	if (QApplication::keyboardModifiers() == Qt::ControlModifier && mouse_left ==0)
	{
		//QMessageBox::information(this, "info", "ctrl");
		if (zoomingOn)
		{
			int dis_min = 300000;
			for (int i = 0; i < pInRect.size(); ++i) // Ϊ �Ŵ� ģʽ //�����ĸ���һЩ
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
			for (int i = 0; i < temPoint.size(); ++i) // Ϊ ���Ŵ� ģʽ
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
		
	}//���������£��ƶ���껭�����ο� �ڲ��Ŵ��ģʽ����
	else if (QApplication::keyboardModifiers() != Qt::ControlModifier && mouse_left&&zoomingOn==0)
	{
		rectFinish = mousePoint;
	}//����ƶ�ʱ��ͨ���ж��Ƿ��ھ��ο��ڽ������ĸ��ģ��ھ��ο���ʱ��ʾΪ�Ŵ� ,�����ǲ��ڷŴ�ģʽ
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
ͼ��������
�Ŵ�ʵ�ֹ��ܣ�
1������ʵ�ַŴ󣬲��������ͼ�����黯��
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
