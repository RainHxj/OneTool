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


//��дlabel ��
class MyLabel : public QLabel
{
	Q_OBJECT
public:
	MyLabel(QWidget *parent = 0);
	~MyLabel();

	//����¼�
	void paintEvent(QPaintEvent *);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	//�����¼�
	//void wheelEvent(QWheelEvent *event);
	//����ͼ��ĳ߶ȱ任
	void scaledTransform(QPixmap & pic, double factor_scale);
	// �Ŵ�֮����ѡ��
	void MyLabel::PointInRect(QVector<QPoint>& lp, QVector<int>& rp);
public:
	QPixmap  img;
	QVector<QPoint> temPoint;

	// �Ŵ������ʵ��
	QPixmap scaledImg;//�Ŵ��Ժ��ͼ��

signals:
	void valueChange(int);

private:
	//����һЩ��־λ ��������ϼ���ʹ��
	bool mouse_left; // �ж�����Ƿ���
	bool dropOn; // �Ƿ�����϶���/
	QPoint mousePoint;
	int dd; //��ʾ�ı�ĵ�ı��
	//���ƾ��п���Ҫ�ĵ�
	QPoint rectStart;
	QPoint rectFinish;
	//����һ�����ķŴ�ָ����ʽ
	QCursor *myCursor;
	// �ж�����Ƿ��ڷŴ�����
	bool zoomCursor;
	// �ж��Ƿ����ڷŴ�
	bool zoomingOn;

	//�Ŵ�ͼ����������
	QPoint scaledImgPoint;
	//���ñ�ѡ�еĵ�
	QVector<int> pInRect;



};

#endif