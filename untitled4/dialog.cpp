#include "dialog.h"
#include "ui_dialog.h"
#include "qlabel.h"
#include "qfiledialog.h"
#include "qstring.h"
#include <QString>
#include <iostream>
#include <QApplication>
#include <QFile>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "cameracms.h"
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/photo/photo.hpp>

using namespace std;
using namespace cv;

extern QString fileName;
double similarity = 0;
double sim = 0;
QString file_Name;
QFileInfo fileinfo;

void resizeImg(void);
void resizeImg2(void);
void cutGrayImage(void);
void detectAndDisplay(Mat face);
int faceSimilarity(void);

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::receivecam()
{
    this->show();
}

void Dialog::on_pushButton_clicked() //restart
{
    //label = new QLabel();
    //label->scro
    //ui->scrollArea_2->clearFocus();
    label->clear();  //删除已识别的图片
    label2->clear();
    ui->label->setText("loadImg");
    ui->label_2->setText("recFaceImg");
    ui->label_3->setText(" ");
    QFile file("/home/marvin/Desktop/cachImg.jpg");
    if (file.exists())
    {
        file.remove();
    }


    QFile file1("/home/marvin/Desktop/cacheCutImg.jpg");
    if (file1.exists())
    {
        file1.remove();
    }

    QFile file2("/home/marvin/Desktop/cachImgResize.jpg");
    if (file2.exists())
    {
        file2.remove();
    }

    QFile file3("/home/marvin/Desktop/cachImgResize2.jpg");
    if (file3.exists())
    {
        file3.remove();
    }

    //隐藏界面，跳转至mainwindow
    this->hide();
    emit showmainw();


}

void Dialog::on_pushButton_2_clicked() //start
{
    cutGrayImage();
    int imagei = 1;

    imagei = faceSimilarity();

    string str4 = format("%d.jpg",imagei);
    QString str5 = QString::fromStdString(str4);
    ui->label_2->setText(str5);

    label = new QLabel();
    string str = format("/home/marvin/Desktop/face3/%d.jpg",imagei);
    QString str1 = QString::fromStdString(str);
    label->setPixmap(QPixmap(str1));
    ui->scrollArea_2->setWidget(label);
    sim = sim*100;
    string str2 = format("Confidence Level:%.1lf%%",sim);
    QString str3 = QString::fromStdString(str2);
    ui->label_3->setText(str3);


}

void Dialog::on_pushButton_3_clicked()
{
    resizeImg();
    resizeImg2();

    fileinfo = QFileInfo(fileName);
    file_Name = fileinfo.fileName();

    //QString str1 = QString::fromStdString(file_Name);
    ui->label->setText(file_Name);

    label2 = new QLabel();
    label2->setPixmap(QPixmap("/home/marvin/Desktop/cachImgResize2.jpg"));
    ui->scrollArea_3->setWidget(label2);


}

void Dialog::on_pushButton_4_clicked()
{
    QFile file("/home/marvin/Desktop/cachImg.jpg");
    if (file.exists())
    {
        file.remove();
    }


    QFile file1("/home/marvin/Desktop/cacheCutImg.jpg");
    if (file1.exists())
    {
        file1.remove();
    }

    QFile file2("/home/marvin/Desktop/cachImgResize.jpg");
    if (file2.exists())
    {
        file2.remove();
    }

    QFile file3("/home/marvin/Desktop/cachImgResize2.jpg");
    if (file3.exists())
    {
        file3.remove();
    }
    close();
}

//缩小拍摄的图像到120x160
void resizeImg(void)
{
    QByteArray ba = fileName.toLatin1();
    const char *pstrSnapImg = strdup(ba.data());
    const char *pstrSaveSnapImg = "/home/marvin/Desktop/cachImgResize.jpg";

    CvSize czsize;      //目标图像尺寸

    IplImage *pSrcImage = cvLoadImage(pstrSnapImg,CV_LOAD_IMAGE_UNCHANGED);
    IplImage *pDstImage = NULL;

    czsize.width = 240;
    czsize.height = 320;

    pDstImage = cvCreateImage(czsize,pSrcImage->depth,pSrcImage->nChannels);
    cvResize(pSrcImage,pDstImage,CV_INTER_AREA);

    cvSaveImage(pstrSaveSnapImg,pDstImage);

    cvReleaseImage(&pSrcImage);
    cvReleaseImage(&pDstImage);
    pstrSnapImg = NULL;
    pstrSaveSnapImg = NULL;
}

//待识别照片预处理
void cutGrayImage(){
     string  str = "/home/marvin/Desktop/cachImgResize.jpg";
     Mat image;
     image = imread(str, 1);
     if (image.empty())
         {
             printf("no find image!");
         }
     detectAndDisplay(image);
}

//人脸检测函数(待识别照片预处理)

void detectAndDisplay(Mat face)
{
    size_t j =0;
    std::vector<Rect> faces;
    string face_cascade_name = "/home/marvin/Desktop/haarcascade_frontalface_alt2.xml";
    CascadeClassifier face_cascade;
    Mat face_gray;
    face_cascade.load(face_cascade_name);
    cvtColor(face, face_gray, CV_BGR2GRAY);  //rgb类型转换为灰度类型
    equalizeHist(face_gray, face_gray);   //直方图均衡化
    face_cascade.detectMultiScale(face_gray, faces, 1.1, 4, 0, Size(30, 30));//找出人脸
    Mat faceROI = face(faces[j]);
    for (j = 0; j < faces.size(); j++)
    {

        if (faceROI.cols > 100)
        {
            faceROI = face(faces[j]);
            Mat MyFace;
            Mat MyFaceGray;
            resize(faceROI, MyFace, Size(120,120));//调整图像大小
            cvtColor(MyFace,MyFaceGray,CV_BGR2GRAY);
            string  str = "/home/marvin/Desktop/cacheCutImg.jpg";
            imwrite(str, MyFaceGray);
            break;
        }
    }

}

//人脸相似度对比

int faceSimilarity(void){

    sim = 0;
    int simImg = 1;
    int i = 1;
    for(i = 1; i <= 2907; i++){

        string str = format("/home/marvin/Desktop/face2/%d.jpg",i);
        Mat pic3,pic1;
        pic3 = imread(str,1);
        if(pic3.empty())
        {
            i++;
            continue;
        }
        cvtColor(pic3,pic1,CV_RGB2GRAY);

        string str1 = "/home/marvin/Desktop/cacheCutImg.jpg";
        Mat pic4,pic2;
        pic4 = imread(str1,1);
        cvtColor(pic4,pic2,CV_RGB2GRAY);

        int histSize = 256;
        float range[] = { 0, 256 };
        const float* histRange = { range };
        bool uniform = true;
        bool accumulate = false;
        Mat hist1, hist2;
        calcHist(&pic2, 1, 0, Mat(), hist1, 1, &histSize, &histRange, uniform, accumulate);
        normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat());
        calcHist(&pic1, 1, 0, Mat(), hist2, 1, &histSize, &histRange, uniform, accumulate);
        normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat());
        similarity = compareHist(hist1, hist2, CV_COMP_CORREL);
        if(similarity>sim){
            sim = similarity;
            simImg = i;
        }

    }
    return simImg;
}

void resizeImg2(){
    const char *pstrSnapImg = "/home/marvin/Desktop/cachImgResize.jpg";
    const char *pstrSaveSnapImg = "/home/marvin/Desktop/cachImgResize2.jpg";
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
}


