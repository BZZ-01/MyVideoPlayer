#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    myplayer=new QMediaPlayer;
    myplayerlist=new QMediaPlaylist;
    mywidget=new QVideoWidget(ui->label);
    myplayer->setPlaylist(myplayerlist);
    myplayer->setVideoOutput(mywidget);
    mywidget->resize(ui->label->size());
    setWindowTitle("MyVideoPlayer");//设置窗口名称
    //音量初始化
    myplayer->setVolume(50);
    ui->horizontalSlider_video->setValue(50);
    //视频的进度条
    connect(myplayer,&QMediaPlayer::positionChanged,ui->horizontalSlider,&QSlider::setValue);
    connect(myplayer,&QMediaPlayer::durationChanged,ui->horizontalSlider,[&](qint64 temp){
        ui->horizontalSlider->setRange(0,(int)temp);
    });
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *event)
{
    //该方法是每时每刻让widget的大小适应lable的大小，让原本画面很小的视频变为正常尺寸
    mywidget->resize(ui->label->size());
}

void Widget::on_pushButton_open_clicked()
{

    QStringList mylsit=QFileDialog::getOpenFileNames(this,"选择播放视频","C:\\","allfiles(*.*);;mp3(*.mp3);;mp4(*.mp4)");//选择要打开的视频
    myplayerlist->clear();//在每一次要打开视频文件时清除之前的视频列表信息
    //将获得的QStringList mylsit加载到myplayerlist
    for(const auto & k : mylsit)
    {
        myplayerlist->addMedia(QUrl(k));

    }

}


void Widget::on_pushButton_start_pause_clicked()//开始和暂停
{
    //默认是暂停播放即isplay是false
    if(isplay)
    {
        //这是使用了改变样式表中的添加资源的写法
        //ui->pushButton_start_pause->setStyleSheet("QPushButton#pushButton_start_pause{border-image::url(:/new/prefix1/images/Start.png)}");
        //改变icon的内容
        ui->pushButton_start_pause->setIcon(QIcon(":/new/prefix1/images/Start.png"));
        ui->pushButton_start_pause->setText(QString("播放"));
        isplay=false;
        myplayer->pause();
    }else{
        //ui->pushButton_start_pause->setStyleSheet("QPushButton#pushButton_start_pause{border-image::url(:/new/prefix1/images/Stop.png)}");
        ui->pushButton_start_pause->setIcon(QIcon(":/new/prefix1/images/Stop.png"));
        ui->pushButton_start_pause->setText(QString("暂停"));
        isplay=true;
        myplayer->play();
        ui->pushButton_stop->setEnabled(true);
    }
}


void Widget::on_pushButton_stop_clicked()//停止
{
    myplayer->stop();
    ui->pushButton_stop->setEnabled(false);
    ui->pushButton_start_pause->setStyleSheet("QPushButton#pushButton_start_pause{border-image::url(:/new/prefix1/images/Start.png)}");
}

//这两个功能（on_pushButton_pre_clicked()和on_pushButton_next_clicked()）要在选择视频时选中多个视频，并且视频的名称最好是无中文的
void Widget::on_pushButton_pre_clicked()//上一曲
{
    //图标初始化操作
    ui->pushButton_start_pause->setIcon(QIcon(":/new/prefix1/images/Start.png"));
    ui->pushButton_start_pause->setText(QString("播放"));
    ui->pushButton_stop->setEnabled(true);

    myplayer->stop();
    myplayerlist->previous();
    myplayer->play();
}


void Widget::on_pushButton_next_clicked()//下一曲
{
    //图标初始化操作
    ui->pushButton_start_pause->setIcon(QIcon(":/new/prefix1/images/Start.png"));
    ui->pushButton_start_pause->setText(QString("播放"));
    ui->pushButton_stop->setEnabled(true);

    myplayer->stop();
    myplayerlist->next();
    myplayer->play();
}


void Widget::on_horizontalSlider_video_valueChanged(int value)
{
    myplayer->setVolume(value);//调节音量，默认值为50，在开始有设置
}


void Widget::on_horizontalSlider_valueChanged(int value)
{
    myplayer->setPosition((qint64) value);//在视频的进度条被改变时同时改变视频的时间
}

