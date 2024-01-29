
#include "bmDataShow.h"

bmDataShow::bmDataShow(QString bmID, QWidget *parent)
    : QWidget(parent) {
    this->bmID=bmID;
    seriesBreathe = new QLineSeries();
    seriesHeartRate = new QLineSeries();
    
    QToolBar *toolbar = new QToolBar(this);//addToolBar("main toolbar");
    toolbar->setFixedHeight(20);
    toolbar->setFixedWidth(20);
    toolbar->setIconSize(QSize(16, 16));
    tagFullScreen = toolbar->addAction(QIcon(":/fullscreen.png"), "全屏");
    connect(tagFullScreen, &QAction::triggered, this, &bmDataShow::showFull);
    
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(seriesBreathe);
    chart->addSeries(seriesHeartRate);
    
    axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("hh:mm:ss");
    axisX->setTitleText("时间");
    chart->addAxis(axisX, Qt::AlignBottom);
    seriesBreathe->attachAxis(axisX);
    seriesHeartRate->attachAxis(axisX);

    QDateTime tTime = QDateTime ::currentDateTime();
    axisX->setMin(tTime.addSecs(-120));
    axisX->setMax(tTime);
    
    axisY = new QValueAxis;
    axisY->setTickCount(12);
    axisY->setLabelFormat("%i");
    axisY->setTitleText("指标");
    chart->addAxis(axisY, Qt::AlignLeft);
    seriesBreathe->attachAxis(axisY);
    seriesHeartRate->attachAxis(axisY);
    axisY->setMin(0);
    axisY->setMax(120);
    
    // Customize chart title
    QFont font;
    font.setPixelSize(24);
    font.setBold(true);
    font.setWeight(QFont::Black);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::red));
    chart->setTitle("体征实时数据");
    
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setMargins(QMargins(0,0,0,0));
    chart->setBackgroundRoundness(0);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    
    auto *vbox = new QVBoxLayout(this);
    vbox->addWidget(toolbar,0);
    vbox->addWidget(chartView, 1);
}
void bmDataShow::addBmData(const int Breathe, const int HeartRate){
    
    if(Breathe>120 || Breathe<=0 || HeartRate>120 || HeartRate<=0){
    	return;
    }
    
    QDateTime tTime = QDateTime ::currentDateTime();
    
    if(seriesBreathe->count()>120){
    	seriesBreathe->remove(0);
    	seriesHeartRate->remove(0);
    }          

    axisX->setMin(tTime.addSecs(-120));
    axisX->setMax(tTime);
    
    seriesBreathe->append(tTime.toMSecsSinceEpoch(), Breathe);
    seriesHeartRate->append(tTime.toMSecsSinceEpoch(), HeartRate);
    
    chart->setTitle(QString("设备: %1  －  呼吸: %2  －  心跳: %3").arg(bmID).arg(Breathe).arg(HeartRate));
}
void bmDataShow::showFull(){
    isFull=(!isFull);
    emit askFullScreen(this, isFull);
    if(isFull){
        tagFullScreen->setIcon(QIcon(":/normalscreen.png")); 
	tagFullScreen->setText(QString("恢复"));	
    }
    else{
        tagFullScreen->setIcon(QIcon(":/fullscreen.png")); 
	tagFullScreen->setText(QString("全屏"));	
    }
}

