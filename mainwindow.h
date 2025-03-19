#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMediaPlayer>
#include <QPushButton>
#include <QMessageBox>
//文件系统
#include <QDir>
#include <QFile>
#include <QFileInfo>
//随机数文件
#include <QTime>
//动画文件
#include <QPropertyAnimation>
//事件
#include <QKeyEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

enum PLAYMODE
{
    ORDER_MODE,
    RANDOM_MODE,
    CIRCLE_MODE
};

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //获取文件夹内音乐名字
    void  loadAPPintMusicDir(const QString & filepath);
    //播放音乐
    void  MusicPlay();
    //显示动画
    void showAnimation(QWidget * window);
    //隐藏动画
    void hideAnimation(QWidget * window);
    //进度条
    void handlePositionSlot(int position);
    //时间
    void handleDurationSlot(int duration);
    //移动进度条函数
    void move();
    //键盘事件
    void keyPressEvent(QKeyEvent *event);


private slots:
    //开始按钮
    void on_pushButton_start_clicked();
    //选择播放模式
    void on_pushButton_sunxu_clicked();
    //下一首
    void on_pushButton_next_clicked();
    //上一首
    void on_pushButton_prev_clicked();
    //播放列表
    void on_pushButton_music_list_clicked();
    //设置音乐播放倍数
    void on_comboBox_activated(const QString &arg1);
    //设置音量
    void on_horizontalSlider_valueChanged(int value);
    //点击静音
    void on_pushButton_Volum_clicked();
    //滑动进度条
    void on_horizontalSlider_2_valueChanged(int value);
    //在进度点击歌曲时
    void on_listWidget_music_currentTextChanged(const QString &currentText);



private:
    Ui::MainWindow *ui;
    /* 音乐播放器*/
    QMediaPlayer * m_player;
    //播放模式
    PLAYMODE m_mode;
    //音乐路径
    QString m_musiclist;
    //列表状态
    bool m_isShowFlag;
    //音量
    int volm;
};
#endif // MAINWINDOW_H
