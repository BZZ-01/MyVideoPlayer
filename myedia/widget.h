#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QVideoWidget>
#include<QFileDialog>
#include<QStringList>
#include<QString>
#include <QVBoxLayout>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_open_clicked();

    void on_pushButton_start_pause_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_pre_clicked();

    void on_pushButton_next_clicked();

    void on_horizontalSlider_video_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::Widget *ui;
    QMediaPlayer *myplayer=nullptr;
    QMediaPlaylist *myplayerlist=nullptr;
    QVideoWidget *mywidget=nullptr;
    bool isplay=false;
};
#endif // WIDGET_H
