#include "cameracms.h"
#include "ui_cameracms.h"
#include "dialog.h"
#include "qstring.h"
#include "qfiledialog.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
using namespace std;
using namespace cv;

QString fileName;

void resizeReadImg(void);

Cameracms::Cameracms(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cameracms)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

Cameracms::~Cameracms()
{
    delete ui;
}

void Cameracms::receivemainwin()
{
    this->show();
}


void Cameracms::on_pushButton_clicked()
{
    label->clear();
    this->hide();
    emit ltdialog();
}

void Cameracms::on_pushButton_2_clicked()
{

    fileName = QFileDialog::getOpenFileName(this,"Choose Image","/home/marvin/Desktop/face",("Image File(*.*)")) ;
    QImage image ;
    image.load(fileName);

    resizeReadImg();

    label = new QLabel();
    label->setPixmap(QPixmap("/home/marvin/Desktop/cachImg.jpg"));
    ui->scrollArea->setWidget(label);
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

    czsize.width = 180;
    czsize.height = 240;
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


