#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent),
     m_mode(ORDER_MODE),
     m_isShowFlag(false),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 设置默认显示为“倍数”
    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox->setCurrentIndex(0);
    //音乐播放器
    m_player =new QMediaPlayer(this);
    //设置滑块范围
    ui->horizontalSlider->setRange(0, 100);
    // 初始化时同步音量
    int currentVolume = m_player->volume();
    qDebug()<<currentVolume;
    ui->horizontalSlider->setValue(currentVolume);

    // 设置按钮的样式表
    ui->pushButton_start->setStyleSheet("border-image: url(:/Icon/stop.png) ;");
    ui->pushButton_sunxu->setStyleSheet("border-image: url(:/Icon/order.png);");
    ui->pushButton_Volum->setStyleSheet("border-image: url(:/Icon/Volume.png) ;");

    //获取音乐列表
    m_musiclist="D:\\C++\\qt\\music\\music\\";
    loadAPPintMusicDir(m_musiclist);
    QString path=m_musiclist+ui->listWidget_music->currentItem()->text()+".mp3";

    //加载音乐           本地音乐
    m_player->setMedia(QUrl::fromLocalFile(path));
    //处理音乐的进度条
    connect(m_player,&QMediaPlayer::positionChanged,this,&MainWindow::handlePositionSlot);
    //处理音乐的总时长
    connect(m_player,&QMediaPlayer::durationChanged,this,&MainWindow::handleDurationSlot);

    //隐藏列表
    ui->listWidget_music->hide();
    srand(time(NULL));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//处理进度条,获取歌曲当前播放时间
void MainWindow::handlePositionSlot(int position)
{
    ui->horizontalSlider_2->setValue(position);
    // 将毫秒转换为秒
    int seconds = position / 1000;
    // 计算分钟数
    int minutes = seconds / 60;
    // 计算剩余的秒数
    int remainingSeconds = seconds % 60;
    QString timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(remainingSeconds, 2, 10, QChar('0'));
    ui->current->setText(timeString);
}

//时间，获取歌曲总时间
void  MainWindow::handleDurationSlot(int duration)
{
    //滑块随着进度移动
    ui->horizontalSlider_2->setRange(0,duration);
    // 将毫秒转换为秒
    int seconds = duration / 1000;
    // 计算分钟数
    int minutes = seconds / 60;
    // 计算剩余的秒数
    int remainingSeconds = seconds % 60;
    QString timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(remainingSeconds, 2, 10, QChar('0'));
    //设置并显示结束时间
    ui->end->setText(timeString);
}

//获取选择音乐的路径
void  MainWindow::MusicPlay()
{
    QString path=m_musiclist+ui->listWidget_music->currentItem()->text()+".mp3";
    //加载音乐           本地音乐
    m_player->setMedia(QUrl::fromLocalFile(path));
    //处理播放
    on_pushButton_start_clicked();
}

//获取文件夹内音乐名字
void MainWindow::loadAPPintMusicDir(const QString & filepath)
{
    QDir dir(filepath);
    if (dir.exists()==false)
    {
        QMessageBox::warning(this,"警告","文件夹不存在");
        return ;
    }
    //获取文件夹内的文件信息
    QFileInfoList filelist=dir.entryInfoList(QDir::Files);
    //循环读取文件
    for (auto i :filelist){
        //判断后缀是不是mp3文件
        if(i.suffix() == "mp3")
        {
            //添加文件名到listWidget
            ui->listWidget_music->addItem(i.baseName());
        }
    }
    //第一行高亮
    ui->listWidget_music->setCurrentRow(0);
}

//滑动进度条
void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    m_player->setPosition(value);
}

//开始/暂停播放
void MainWindow::on_pushButton_start_clicked()
{
    //如果是播放状态
    if (m_player->state()==QMediaPlayer::PlayingState)
    {
        //暂停音乐
        m_player->pause();
        // 设置按钮的样式表
        ui->pushButton_start->setStyleSheet("QPushButton {border-image: url(:/Icon/stop.png) ;}");
    }
    else{
        //播放音乐
        m_player->play();
        // 设置按钮的样式表
        ui->pushButton_start->setStyleSheet("QPushButton {border-image: url(:/Icon/play.png) ;}");
    }
}

//播放模式
void MainWindow::on_pushButton_sunxu_clicked()
{
    if (m_mode==ORDER_MODE)
    {
        ui->pushButton_sunxu->setStyleSheet("QPushButton {border-image: url(:/Icon/random.png) ;}");
        m_mode=RANDOM_MODE;
    }
    else if(m_mode==RANDOM_MODE)
    {
        ui->pushButton_sunxu->setStyleSheet("QPushButton {border-image: url(:/Icon/Once.png) ;}");
        m_mode=CIRCLE_MODE;
    }
    else if (m_mode==CIRCLE_MODE) {
        ui->pushButton_sunxu->setStyleSheet("QPushButton {border-image: url(:/Icon/order.png) ;}");
        m_mode=ORDER_MODE;
    }
}

//点击歌曲时
void MainWindow::on_listWidget_music_currentTextChanged(const QString &currentText)
{
        MusicPlay();
}

//下一首
void MainWindow::on_pushButton_next_clicked()
{
    //获取当前播放的音乐，在listwidget里面高亮显示的就是
    int currentRow =ui->listWidget_music->currentRow();
    //下一首的位置
    int nextRow=0;
    if (m_mode==ORDER_MODE)
    {
        nextRow=(currentRow +1 ) %ui->listWidget_music->count();
    }
    else if (m_mode==RANDOM_MODE)
    {
        //防止只有一首歌
        int num=0;
        do
        {
            int n = rand();
            nextRow=n % ui->listWidget_music->count();
            num++;
        }while((nextRow==currentRow)&&(num<=3));
    }
    else if (m_mode==CIRCLE_MODE)
    {
        nextRow=currentRow;
    }
    ui->listWidget_music->setCurrentRow(nextRow);
    MusicPlay();
}

//上一首
void MainWindow::on_pushButton_prev_clicked()
{
    int currentRow =ui->listWidget_music->currentRow();
    int prevRow=0;
    if (m_mode==ORDER_MODE)
    {
        prevRow=currentRow-1 ;
        if (prevRow<0)
        {
            prevRow=ui->listWidget_music->count() -1;
        }
    }
    else if(m_mode==RANDOM_MODE)
    {
        int num=0;
        do
        {
            num++;
            prevRow=rand()%ui->listWidget_music->count();
        }while(prevRow==currentRow && num<=3 );
    }
    else if(m_mode==CIRCLE_MODE)
    {
        prevRow=currentRow;
    }
    ui->listWidget_music->setCurrentRow(prevRow);
    MusicPlay();
}

//音乐列表的隐藏与显示
void MainWindow::on_pushButton_music_list_clicked()
{
    if (m_isShowFlag==false)
    {
        ui->listWidget_music->show();
        showAnimation(ui->listWidget_music);
        m_isShowFlag=true;
    }
    else {
        hideAnimation(ui->listWidget_music);
        ui->listWidget_music->hide();
        m_isShowFlag=false;
    }
}

//显示动画
void MainWindow::showAnimation(QWidget * window)
{
     //动画化窗口部件（window）的"pos"属性，即窗口的位置。
     QPropertyAnimation animation(window,"pos");
     //动画时间,单位是ms
     animation.setDuration(1000);
     //起始坐标
     animation.setStartValue(QPoint(this->width(),0));
     //结束坐标
     animation.setEndValue(QPoint(this->width()-ui->listWidget_music->width(),0));
     animation.start();
     QEventLoop loop;
     //当动画结束时（即QPropertyAnimation发出finished信号），调用QEventLoop的quit槽，从而停止事件循环。
     connect(&animation,&QPropertyAnimation::finished,&loop,&QEventLoop::quit);
     loop.exec();
}

//隐藏动画
void MainWindow::hideAnimation(QWidget * window)
{
    //动画化窗口部件（window）的"pos"属性，即窗口的位置。
    QPropertyAnimation animation(window,"pos");
    //动画时间,单位是ms
    animation.setDuration(1000);
    //起始坐标
    animation.setStartValue(QPoint(this->width()-ui->listWidget_music->width(),0));
    //结束坐标
    animation.setEndValue(QPoint(this->width(),0));
    animation.start();
    QEventLoop loop;
    //，当动画结束时（即QPropertyAnimation发出finished信号），调用QEventLoop的quit槽，从而停止事件循环。
    connect(&animation,&QPropertyAnimation::finished,&loop,&QEventLoop::quit);
    loop.exec();
}

//设置音频播放倍数
void MainWindow::on_comboBox_activated(const QString &arg1)
{
    qreal rate;
    // 尝试将字符串转换为qreal
    bool ok;
    rate = arg1.toDouble(&ok); // toDouble()会尝试转换字符串，并通过引用参数ok返回转换是否成功
    if (ok) {
        // 转换成功，现在rate是一个qreal类型的数值
        m_player->setPlaybackRate(rate); // 使用转换后的速率
    } else {
        // 转换失败，处理错误情况
        qDebug() << "转换失败，提供的字符串不是一个有效的数值";
    }
    ui->comboBox->setCurrentIndex(0);  // 重置显示
}

//设置音量
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->label_3->setText(QString::number(value));
    m_player->setVolume(value);

    if(m_player->volume()!=0)
    {
        ui->pushButton_Volum->setStyleSheet("border-image: url(:/Icon/Volume.png) ;");
    }
    else
    {
        ui->pushButton_Volum->setStyleSheet("border-image: url(:/Icon/Mute.png) ;");
    }
}

//设置静音按钮
void MainWindow::on_pushButton_Volum_clicked()
{
    if (ui->horizontalSlider->value() != 0)
    {
        volm=ui->horizontalSlider->value();
        ui->pushButton_Volum->setStyleSheet("border-image: url(:/Icon/Mute.png) ;");
        m_player->setVolume(0);
        ui->horizontalSlider->setValue(0);
    }
    else
    {
        ui->pushButton_Volum->setStyleSheet("border-image: url(:/Icon/Volume.png) ;");
        m_player->setVolume(volm);
        ui->horizontalSlider->setValue(volm);
    }
}

//键盘
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers()==Qt::ControlModifier && event->key()==Qt::Key_A)
    {
        on_pushButton_prev_clicked();
    }
    else if (event->modifiers()==Qt::ControlModifier && event->key()==Qt::Key_D) {
        on_pushButton_next_clicked();
    }
    else if (event->key()==Qt::Key_Escape) {
        this->close();
    }
}

