#include "singleprocessing.h"
#include "ui_singleprocessing.h"
#include "qstring.h"
#include "qfiledialog.h"
#include "qlabel.h"
#include <iostream>
#include <QApplication>
#include <QFile>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace std;
using namespace cv;

QString fileName,file_Name;
QFileInfo fileinfo;

void resizeReadImg(void);
void grayCutImage(void);
void detectAndDisplay(Mat face);
void resizeReadImg1(void);
void resizeReadImg2(void);


singleProcessing::singleProcessing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::singleProcessing)
{
    ui->setupUi(this);
}

singleProcessing::~singleProcessing()
{
    delete ui;
}


void singleProcessing::receiveDialog()
{
    this->show();
}

void singleProcessing::on_pushButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,"Choose Image","/home/marvin/Desktop/face0",("Image File(*.*)")) ;
    fileinfo = QFileInfo(fileName);
    file_Name = fileinfo.fileName();
    QImage image ;
    image.load(fileName);

    resizeReadImg();

    label = new QLabel();
    label->setPixmap(QPixmap("/home/marvin/Desktop/cachImg.jpg"));
    ui->scrollArea->setWidget(label);

    string str2 = format("");
    QString str3 = QString::fromStdString(str2);
    ui->label->setText(str3);
}
void singleProcessing::on_pushButton_2_clicked()
{
    grayCutImage();
    resizeReadImg1();

    label2 = new QLabel();
    label2->setPixmap(QPixmap("/home/marvin/Desktop/cacheImgD2.jpg"));
    ui->scrollArea_2->setWidget(label2);

    label3 = new QLabel();
    label3->setPixmap(QPixmap("/home/marvin/Desktop/cacheCutImg.jpg"));
    ui->scrollArea_3->setWidget(label3);

    string str2 = format("Mission Completed!");
    QString str3 = QString::fromStdString(str2);
    ui->label->setText(str3);
}


void singleProcessing::on_pushButton_3_clicked()
{
    label->clear();
    label2->clear();
    label3->clear();
    string str2 = format("");
    QString str3 = QString::fromStdString(str2);
    ui->label->setText(str3);

    this->hide();
    emit showDialog2();

    QFile file("/home/marvin/Desktop/cachImg.jpg");
    if (file.exists())
    {
        file.remove();
    }

    QFile file1("/home/marvin/Desktop/cacheImgD.jpg");
    if (file1.exists())
    {
        file1.remove();
    }

    QFile file2("/home/marvin/Desktop/cacheImgD2.jpg");
    if (file2.exists())
    {
        file2.remove();
    }

    QFile file3("/home/marvin/Desktop/cacheCutImg.jpg");
    if (file3.exists())
    {
        file3.remove();
    }
}

void singleProcessing::on_pushButton_4_clicked()
{
    this->close();
    QFile file("/home/marvin/Desktop/cachImg.jpg");
    if (file.exists())
    {
        file.remove();
    }

    QFile file1("/home/marvin/Desktop/cacheImgD.jpg");
    if (file1.exists())
    {
        file1.remove();
    }

    QFile file2("/home/marvin/Desktop/cacheImgD2.jpg");
    if (file2.exists())
    {
        file2.remove();
    }

    QFile file3("/home/marvin/Desktop/cacheCutImg.jpg");
    if (file3.exists())
    {
        file3.remove();
    }
}

void singleProcessing::on_pushButton_5_clicked()
{
    label->clear();
    label2->clear();
    label3->clear();
    string str2 = format("");
    QString str3 = QString::fromStdString(str2);
    ui->label->setText(str3);

    QFile file("/home/marvin/Desktop/cachImg.jpg");
    if (file.exists())
    {
        file.remove();
    }

    QFile file1("/home/marvin/Desktop/cacheImgD.jpg");
    if (file1.exists())
    {
        file1.remove();
    }

    QFile file2("/home/marvin/Desktop/cacheImgD2.jpg");
    if (file2.exists())
    {
        file2.remove();
    }

    QFile file3("/home/marvin/Desktop/cacheCutImg.jpg");
    if (file3.exists())
    {
        file3.remove();
    }
}


void resizeReadImg(void)
{
    QByteArray ba = fileName.toLatin1();
    const char *pstrSnapImg = ba.data();
    const char *pstrSaveSnapImg = "/home/marvin/Desktop/cachImg.jpg";
    //const char *pstrWindownYuanT = "原图";
    //const char *pstrWindownSuoT = "缩放图";

    //double fScale = 9;  //缩放倍数
    CvSize czsize;      //目标图像尺寸

    //从文件中读取图像
    IplImage *pSrcImage = cvLoadImage(pstrSnapImg,CV_LOAD_IMAGE_UNCHANGED);
    IplImage *pDstImage = NULL;

    //计算目标图像大小
    //czsize.width = pSrcImage->width/fScale;
    //czsize.height = pSrcImage->height/fScale;

    czsize.width = 240;
    czsize.height = 320;
    //创建图像并缩放
    pDstImage = cvCreateImage(czsize,pSrcImage->depth,pSrcImage->nChannels);
    cvResize(pSrcImage,pDstImage,CV_INTER_AREA);

    //创建窗口 （调试用）
    //cvNamedWindow(pstrWindownYuanT,CV_WINDOW_AUTOSIZE);
    //cvNamedWindow(pstrWindownSuoT,CV_WINDOW_AUTOSIZE);

    //在指定窗口中显示图像
    //cvShowImage(pstrWindownYuanT,pSrcImage);
    //cvShowImage(pstrWindownSuoT,pDstImage);

    //等待按键
    //cvWaitKey();

    //保存图片
    cvSaveImage(pstrSaveSnapImg,pDstImage);

    //释放内存，关闭窗口
    //cvDestroyWindow(pstrWindownYuanT);
    //cvDestroyWindow(pstrWindownSuoT);
    cvReleaseImage(&pSrcImage);
    cvReleaseImage(&pDstImage);

    //return 0;
}

void grayCutImage(void)
{
    string  str = fileName.toStdString();
    //string  str = "/home/marvin/Desktop/cachImgResize.jpg";
    Mat image;
    image = imread(str, 1);
    if (image.empty())
       {
           printf("no find image!");
       }
    detectAndDisplay(image);
}

void detectAndDisplay(Mat face)
{
    //const char *pstrSaveSnapImg = "/home/marvin/Desktop/cachImgD.jpg";
    size_t j =0;
    std::vector<Rect> faces;
    string face_cascade_name = "/home/marvin/Desktop/haarcascade_frontalface_alt2.xml";
    CascadeClassifier face_cascade;
    Mat face_gray;
    face_cascade.load(face_cascade_name);
    cvtColor(face, face_gray, CV_BGR2GRAY);  //rgb类型转换为灰度类型
    equalizeHist(face_gray, face_gray);   //直方图均衡化
    face_cascade.detectMultiScale(face_gray, faces, 1.1, 4, 0);//找出人脸



    Mat faceROI = face(faces[j]);
    for (j = 0; j < faces.size(); j++)
    {
        faceROI = face(faces[j]);
        Mat MyFace;
        Mat MyFaceGray;
        if (faceROI.cols > 100)
        {
            resize(faceROI, MyFace, Size(120,120));//调整图像大小
            cvtColor(MyFace,MyFaceGray,CV_BGR2GRAY);
            //equalizeHist(MyFaceGray, MyFaceGray);
            string  str = "/home/marvin/Desktop/cacheCutImg.jpg";
            imwrite(str, MyFaceGray);
            string str1 = file_Name.toStdString();
            string str2 = "/home/marvin/Desktop/face2/"+str1;
            imwrite(str2,MyFaceGray);
            //imshow("处理结果", MyFaceGray);
        }
    }
    Scalar colors[] =
    {
        CV_RGB(255, 0, 0),
        CV_RGB(255, 97, 0),
        CV_RGB(255, 255, 0),
        CV_RGB(0, 255, 0),
        CV_RGB(0, 255, 255),
        CV_RGB(0, 0, 255),
        CV_RGB(160, 32, 240)
    };
    for(int i = 0; i<faces.size();i++)
    {
        Point center;
        int radius;
        center.x = cvRound((faces[i].x + faces[i].width * 0.5));
        center.y = cvRound((faces[i].y + faces[i].height * 0.5));
        radius = cvRound((faces[i].width + faces[i].height) * 0.25);
        circle(face_gray,center,radius,colors[0],10);
    }
    string  str2 = "/home/marvin/Desktop/cacheImgD.jpg";
    imwrite(str2, face_gray);

}

void resizeReadImg1(){
    const char *pstrSnapImg = "/home/marvin/Desktop/cacheImgD.jpg";
    const char *pstrSaveSnapImg = "/home/marvin/Desktop/cacheImgD2.jpg";
    //const char *pstrWindownYuanT = "原图";
    //const char *pstrWindownSuoT = "缩放图";

   // double fScale = 0.5;  //缩放倍数
    CvSize czsize;      //目标图像尺寸

    //从文件中读取图像
    IplImage *pSrcImage = cvLoadImage(pstrSnapImg,CV_LOAD_IMAGE_UNCHANGED);
    IplImage *pDstImage = NULL;

    //计算目标图像大小
    //czsize.width = pSrcImage->width/fScale;
    //czsize.height = pSrcImage->height/fScale;

    czsize.width = 240;
    czsize.height = 320;

    //创建图像并缩放
    pDstImage = cvCreateImage(czsize,pSrcImage->depth,pSrcImage->nChannels);
    cvResize(pSrcImage,pDstImage,CV_INTER_AREA);

    //创建窗口 （调试用）
    //cvNamedWindow(pstrWindownYuanT,CV_WINDOW_AUTOSIZE);
    //cvNamedWindow(pstrWindownSuoT,CV_WINDOW_AUTOSIZE);

    //在指定窗口中显示图像
    //cvShowImage(pstrWindownYuanT,pSrcImage);
    //cvShowImage(pstrWindownSuoT,pDstImage);

    //等待按键
    //cvWaitKey();

    //保存图片
    cvSaveImage(pstrSaveSnapImg,pDstImage);

    //释放内存，关闭窗口
    //cvDestroyWindow(pstrWindownYuanT);
    //cvDestroyWindow(pstrWindownSuoT);
    cvReleaseImage(&pSrcImage);
    cvReleaseImage(&pDstImage);
    pstrSnapImg = NULL;
    pstrSaveSnapImg = NULL;
}



