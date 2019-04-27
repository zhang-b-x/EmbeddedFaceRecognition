#include "arbitrationprocessing.h"
#include "ui_arbitrationprocessing.h"
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

QString fileName1,file_Name1;
QFileInfo fileinfo1;
String fileImage;
double sim = 0;
double similarity = 0;

void resizeReadImg4(void);
void cutGrayImage2(void);
void detectAndDisplay2(Mat face);
int faceSimilarity(void);
void resizeReadImg5(void);


ArbitrationProcessing::ArbitrationProcessing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArbitrationProcessing)
{
    ui->setupUi(this);
}


ArbitrationProcessing::~ArbitrationProcessing()
{
    delete ui;
}
void ArbitrationProcessing::receiveDialogA()
{
    this->show();
}

void ArbitrationProcessing::on_pushButton_clicked()
{
    fileName1 = QFileDialog::getOpenFileName(this,"Choose Image","/home/marvin/Desktop/face/",("Image File(*.*)")) ;
    fileinfo1 = QFileInfo(fileName1);
    file_Name1 = fileinfo1.fileName();
    ui->label->setText(file_Name1);
    QImage image ;
    image.load(fileName1);

    resizeReadImg4();

    label = new QLabel();
    label->setPixmap(QPixmap("/home/marvin/Desktop/cachImg.jpg"));
    ui->scrollArea->setWidget(label);

}

void ArbitrationProcessing::on_pushButton_2_clicked()
{
    cutGrayImage2();
    int imagei = 1;
    imagei = faceSimilarity();


    label2 = new QLabel();
    fileImage = format("/home/marvin/Desktop/face0/%d.jpg",imagei);
    resizeReadImg5();

    string str = "/home/marvin/Desktop/cachImg2.jpg";
    QString str1 = QString::fromStdString(str);
    label2->setPixmap(QPixmap(str1));
    ui->scrollArea_2->setWidget(label2);

    string str4 = format("%d.jpg",imagei);
    QString str5 = QString::fromStdString(str4);
    ui->label_2->setText(str5);

    sim = sim*100;

    string str2 = format("Confidence Level:%.3lf%%",sim);
    QString str3 = QString::fromStdString(str2);
    ui->label_3->setText(str3);
}

void ArbitrationProcessing::on_pushButton_3_clicked()
{
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

    QFile file4("/home/marvin/Desktop/cachImg2.jpg");
    if (file4.exists())
    {
        file4.remove();
    }

    label->clear();
    label2->clear();

    string str = format("");
    QString str1 = QString::fromStdString(str);
    ui->label->setText(str1);
    ui->label_2->setText(str1);
    ui->label_3->setText(str1);

    this->hide();
    emit showDialogAr();
}

void ArbitrationProcessing::on_pushButton_4_clicked()
{
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

    QFile file4("/home/marvin/Desktop/cachImg2.jpg");
    if (file4.exists())
    {
        file4.remove();
    }

    label->clear();
    label2->clear();

    string str = format("");
    QString str1 = QString::fromStdString(str);
    ui->label->setText(str1);
    ui->label_2->setText(str1);
    ui->label_3->setText(str1);

    this->close();
}


void resizeReadImg4(void)
{
    QByteArray ba = fileName1.toLatin1();
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

void cutGrayImage2(){
     string  str = fileName1.toStdString();
     //string  str = "/home/marvin/Desktop/cachImgResize.jpg";
     Mat image;
     image = imread(str, 1);

     detectAndDisplay2(image);

}

void detectAndDisplay2(Mat face)
{
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
            string  str = "/home/marvin/Desktop/cacheCutImg.jpg";
            //equalizeHist(MyFaceGray, MyFaceGray);
            imwrite(str, MyFaceGray);
        }
    }

}

int faceSimilarity(void){

    sim = 0;
    similarity = 0;
    int simImg = 1;
    int i = 1;
    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false;
    Mat pic3,pic1;
    Mat pic4,pic2;
    Mat hist1, hist2;
    for(i = 1; i <= 2907; i++)
    {
        string str = format("/home/marvin/Desktop/face2/%d.jpg",i);

        pic3 = imread(str,1);
        if (pic3.empty())
        {
            continue;
        }

        cvtColor(pic3,pic1,CV_RGB2GRAY);

        string str1 = "/home/marvin/Desktop/cacheCutImg.jpg";

        pic4 = imread(str1,1);
        cvtColor(pic4,pic2,CV_RGB2GRAY);

        calcHist(&pic2, 1, 0, Mat(), hist1, 1, &histSize, &histRange, uniform, accumulate);
        normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat());
        calcHist(&pic1, 1, 0, Mat(), hist2, 1, &histSize, &histRange, uniform, accumulate);
        normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat());
        similarity = compareHist(hist1, hist2, CV_COMP_CORREL);

        if(similarity>sim)
        {
            sim = similarity;
            simImg = i;

        }

    }
    return simImg;
}

void resizeReadImg5(void){

    const char *pstrSnapImg = fileImage.c_str();
    const char *pstrSaveSnapImg = "/home/marvin/Desktop/cachImg2.jpg";
    //const char *pstrWindownYuanT = "原图";
    //const char *pstrWindownSuoT = "缩放图";

    //double fScale = 9;  //缩放倍数
    CvSize czsize;      //目标图像尺寸

    //从文件中读取图像
    IplImage *pSrcImage = cvLoadImage(pstrSnapImg,CV_LOAD_IMAGE_UNCHANGED);
    IplImage *pDstImage = NULL;

    czsize.width = 240;
    czsize.height = 320;
    //创建图像并缩放
    pDstImage = cvCreateImage(czsize,pSrcImage->depth,pSrcImage->nChannels);
    cvResize(pSrcImage,pDstImage,CV_INTER_AREA);

    cvSaveImage(pstrSaveSnapImg,pDstImage);

    //释放内存，关闭窗口
    //cvDestroyWindow(pstrWindownYuanT);
    //cvDestroyWindow(pstrWindownSuoT);
    cvReleaseImage(&pSrcImage);
    cvReleaseImage(&pDstImage);

    //return 0;
}


