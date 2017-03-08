#include "onetool.h"
#include <qdebug.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include<QFileDialog>
#include<QMessageBox>
#include<fstream>
#include <string>
OneTool::OneTool(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ctrl_key = 0;
	RX = 0; RY = 0;
	shImage = new MyLabel(this);
	shImage->setGeometry(0,0,1280,960);
	shImage->setStyleSheet("background-color: rgb(0,0,0);color: rgb(255,255,255);");
	QScrollArea *scrollArea = new QScrollArea(this);
	scrollArea->setBackgroundRole(QPalette::Dark);  // ����ɫ
	scrollArea->setGeometry(0, 0, 1280, 960);
	scrollArea->setWidget(shImage);

	connect(shImage, SIGNAL(valueChange(int)), this, SLOT(ableButton(int)));
}

OneTool::~OneTool()
{
	
}

//�򿪱���ͼ��
void OneTool::openImgFile()
{
	imgFileName = QFileDialog::getOpenFileName(this, tr("open file"), " ", tr("Allfile(*.*);;mp3file(*.pdf)"));
	shImage->img = QPixmap(imgFileName);
	this->setWindowTitle(imgFileName);

	//�ж� �ǲ����²�����ͼ�� �����������ô��С���²����ĳ̶�
	int width  = (shImage->img).width();
	int height = (shImage->img).height();
	if (width > 1280 || height > 960)
		shImage->img = (shImage->img).scaled(width*0.25, height*0.25);

	shImage->resize((shImage->img).width(), (shImage->img).height());
	shImage->update();
	///shImage->setPixmap(img);
}

//ת����������
template <class Input, class Output>
Output convertDataType(const Input& a)
{
	stringstream ss;
	Output b;
	ss << a;
	ss >> b;
	return b;
}

void OneTool:: openTemFile()
{
	shImage->temPoint.clear();
	temFileName = QFileDialog::getOpenFileName(this, tr("open file"), " ", tr("Allfile(*.*);;mp3file(*.cdx)"));
	string sfilename = temFileName.toStdString();

	ifstream ifile(sfilename);
	if (!ifile)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�򿪴���"));
	}
	else
	{
		/*�������� ���ļ��ж�ȡ���� ���洢Ϊ vec <Point>  ����ʽ����Ҫ�ǽ��ַ���תΪ int����*/
		string c;
		//getline(ifile, c);
		//QMessageBox::information(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(c.c_str()));
		int Pos = -1;
		while (getline(ifile,c))
		{
			/* ����ֵ �м����ÿո����*/
			if (c.length()>0)
			{
				string RowContent(c);
				Pos = RowContent.find(" ", 0);
				string x = RowContent.substr(0, Pos);
				string y = RowContent.substr(Pos + 1, string::npos);
				shImage->temPoint.push_back(QPoint(convertDataType<string, int>(x), convertDataType<string, int>(y)));
			}
		}
		QPointF orgin = (shImage->temPoint).back();
		RX = orgin.x();
		RY = orgin.y();
		shImage->temPoint.pop_back();
		 
	}
	shImage->update();
}
//����ģ��� ��
void OneTool::saveTemplate()
{
	/* ����ת�� */
	int PointSize = (shImage->temPoint).size();
	QVector< QPoint > temModifyOrign(PointSize);
	for (int i = 0; i < PointSize ; ++i)
		temModifyOrign[i] = QPoint((shImage->temPoint)[i].x() - RX, (shImage->temPoint)[i].y() - RY);

	saveFileName = imgFileName;
	string fileName = saveFileName.toStdString();
	int Pos = -1;
	Pos = fileName.find('.',0);
	string x = fileName.substr(0, Pos);
	string y = fileName.substr(Pos, string::npos);
	string fileNameNew = x + "_ci_new" + ".txt";


	//�������ɵĵ㱣��һ��
	ofstream saveFile(fileNameNew);
	for (int i = 0; i < PointSize; ++i)
	{
		saveFile << temModifyOrign[i].x();
		saveFile << " ";

		saveFile << temModifyOrign[i].y();
		saveFile << endl;
	}
	QMessageBox::information(this, QString::fromLocal8Bit("��Ϣ"), QString::fromLocal8Bit("����ɹ�"));
}

void OneTool::ableButton(int b)
{
	if (b)
		ui.pushButton_2->setEnabled(false);
	else
		ui.pushButton_2->setEnabled(true);
	//QMessageBox::information(this, QString::fromLocal8Bit("��Ϣ"), QString::fromLocal8Bit("zoom"));
}