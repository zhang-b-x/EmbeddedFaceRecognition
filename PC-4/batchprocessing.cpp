#include "batchprocessing.h"
#include "ui_batchprocessing.h"
#include "qstring.h"
#include "qfiledialog.h"
#include "qlabel.h"
#include <iostream>
#include <QApplication>
#include <QFile>
#include <string>
#include "qtimer.h"
#include "QTime"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace std;
using namespace cv;

int i=0,j=0,k=0;
std::vector<Rect> faces;
string face_cascade_name = "/home/marvin/Desktop/haarcascade_frontalface_alt2.xml";
CascadeClassifier face_cascade;

void resizeImg1(void);
void resizeCCCC(void);
void grayCutImage1(void);
void detectAndDisplay1(Mat face);
void resizeReadImg3(void);
void sleep(unsigned int msec);


batchProcessing::batchProcessing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::batchProcessing)
{
    ui->setupUi(this);
}

batchProcessing::~batchProcessing()
{
    delete ui;
}

void batchProcessing::receiveDialog2()
{
    this->show();
}

void batchProcessing::on_pushButton_clicked()
{
    QString text = ui->textEdit->toPlainText() ;
    QString text1 = ui->textEdit_2->toPlainText() ;
    bool ok;
    i=text.toInt(&ok,10);
    j=text1.toInt(&ok,10);

    ui->progressBar->setRange(0,j-i);
    ui->progressBar->setValue(0);
    for(i;i <= j; i++)
    {
        string  str = format("/home/marvin/Desktop/face0/%d.jpg",i);
        Mat image;
        image = imread(str, 1);

        resizeImg1();
        resizeCCCC();

        label = new QLabel();
        label->setPixmap(QPixmap("/home/marvin/Desktop/cachImgResize.jpg"));
        ui->scrollArea->setWidget(label);

        grayCutImage1();
        resizeReadImg3();

        label2 = new QLabel();
        label2->setPixmap(QPixmap("/home/marvin/Desktop/cacheImgD2.jpg"));
        ui->scrollArea_2->setWidget(label2);

        label3 = new QLabel();
        label3->setPixmap(QPixmap("/home/marvin/Desktop/cacheCutImg.jpg"));
        ui->scrollArea_3->setWidget(label3);

        label4 = new QLabel();
        label4->setPixmap(QPixmap("/home/marvin/Desktop/cacheCutImg2.jpg"));
        ui->scrollArea_4->setWidget(label4);

        ui->progressBar->setValue(k);
        string str2 = format("%d.jpg",i);
        QString str3 = QString::fromStdString(str2);
        ui->label_4->setText(str3);

        sleep(10);
        k++;
    }

    string str2 = format("Mission Completed!");
    QString str3 = QString::fromStdString(str2);
    ui->label_3->setText(str3);
    k=0;
}

void batchProcessing::on_pushButton_2_clicked()
{
    QFile file("/home/marvin/Desktop/cachImgResize.jpg");
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

    QFile file4("/home/marvin/Desktop/cacheCutImg2.jpg");
    if (file4.exists())
    {
        file4.remove();
    }
    label->clear();
    label2->clear();
    label3->clear();
    label4->clear();

    string str = format("");
    QString str1 = QString::fromStdString(str);
    ui->label_3->setText(str1);
    ui->label_4->setText(str1);
    ui->textEdit->setText(str1);
    ui->textEdit_2->setText(str1);

    ui->progressBar->setValue(0);

    this->hide();
    emit showDialogB();
}

void batchProcessing::on_pushButton_3_clicked()
{
    QFile file("/home/marvin/Desktop/cachImgResize.jpg");
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

    QFile file4("/home/marvin/Desktop/cacheCutImg2.jpg");
    if (file4.exists())
    {
        file4.remove();
    }

    label->clear();
    label2->clear();
    label3->clear();
    label4->clear();

    string str = format("");
    QString str1 = QString::fromStdString(str);
    ui->label_3->setText(str1);
    ui->label_4->setText(str1);
    ui->textEdit->setText(str1);
    ui->textEdit_2->setText(str1);

    ui->progressBar->setValue(0);

    this->close();
}


void resizeImg1(void){
    //QByteArray ba = fileName.toLatin1();
    //const char *pstrSnapImg = strdup(ba.data());
    string  str = format("/home/marvin/Desktop/face0/%d.jpg",i);
    const char *pstrSnapImg = str.c_str();
    const char *pstrSaveSnapImg = "/home/marvin/Desktop/cachImgResize.jpg";
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
    pstrSnapImg = NULL;
    pstrSaveSnapImg = NULL;

    //return 0;
}

void resizeCCCC()
{
    //QByteArray ba = fileName.toLatin1();
    //const char *pstrSnapImg = strdup(ba.data());
    string  str = format("/home/marvin/Desktop/face0/%d.jpg",i);
    string  str1 = format("/home/marvin/Desktop/face3/%d.jpg",i);
    const char *pstrSnapImg = str.c_str();
    const char *pstrSaveSnapImg = str1.c_str();
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

    czsize.width = 120;
    czsize.height = 160;

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

    //return 0;
}

void grayCutImage1(void){
    //string  str = fileName.toStdString();
    string  str = format("/home/marvin/Desktop/face0/%d.jpg",i);
    Mat image;
    image = imread(str, 1);
    if (image.empty())
       {
           printf("no find image!");
       }
    detectAndDisplay1(image);
}
void detectAndDisplay1(Mat face)
{
    //const char *pstrSaveSnapImg = "/home/marvin/Desktop/cachImgD.jpg";
    size_t j1 =0;
    std::vector<Rect> faces;
    string face_cascade_name = "/home/marvin/Desktop/haarcascade_frontalface_alt2.xml";
    CascadeClassifier face_cascade;
    Mat face_gray;
    face_cascade.load(face_cascade_name);
    cvtColor(face, face_gray, CV_BGR2GRAY);  //rgb类型转换为灰度类型
    equalizeHist(face_gray, face_gray);   //直方图均衡化
    face_cascade.detectMultiScale(face_gray, faces, 1.1, 4, 0);//找出人脸

    Mat faceROI = face(faces[j1]);
    for (j1 = 0; j1 < faces.size(); j1++)
    {
        if (faceROI.cols > 100)
        {
            faceROI = face(faces[j1]);
            Mat MyFace;
            Mat MyFaceGray;
            Mat MyFaceEqua;
            resize(faceROI, MyFace, Size(120,120));//调整图像大小
            cvtColor(MyFace,MyFaceGray,CV_BGR2GRAY);
            equalizeHist(MyFaceGray, MyFaceEqua);
            string  str0 = "/home/marvin/Desktop/cacheCutImg2.jpg";
            imwrite(str0, MyFaceEqua);
            string  str = "/home/marvin/Desktop/cacheCutImg.jpg";
            imwrite(str, MyFaceGray);
            string str1 = format("%d.jpg",i);
            string str2 = "/home/marvin/Desktop/face2/"+str1;
            //equalizeHist(MyFaceGray, MyFaceGray);
            imwrite(str2,MyFaceGray);
            //imshow("处理结果", MyFaceGray);
            break;
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
    for(int i1 = 0; i1<faces.size();i1++)
    {
        Point center;
        int radius;
        center.x = cvRound((faces[i1].x + faces[i1].width * 0.5));
        center.y = cvRound((faces[i1].y + faces[i1].height * 0.5));
        radius = cvRound((faces[i1].width + faces[i1].height) * 0.25);
        circle(face_gray,center,radius,colors[0],10);
        //circle(face_gray,center,radius,colors[0],10);
    }
    string  str2 = "/home/marvin/Desktop/cacheImgD.jpg";
    imwrite(str2, face_gray);

}
void resizeReadImg3(){
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
void sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
