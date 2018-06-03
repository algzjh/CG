#include "qtgui3.h"
#pragma execution_character_set("utf-8")

QtGUI3::QtGUI3(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	curvearea = new CurveArea;
	setCentralWidget(curvearea);
	//ui.centralWidget->setMouseTracking(true);
	//setMouseTracking(true);
	setMinimumSize(1200, 800);
	minDegree = 1;
	maxDegree = 1;

	

	pMenuBar = ui.menuBar;
	//pMenuA
	pMenuA = new QMenu("文件");
	pActionA1 = new QAction("打开");
	pMenuA->addAction(pActionA1);
	pActionA2 = new QAction("另存为");
	pMenuA->addAction(pActionA2);
	pActionA3 = new QAction("退出");
	pMenuA->addAction(pActionA3);
	pMenuBar->addMenu(pMenuA);
	//pMenuB
	/*
	pMenuB = new QMenu("渲染");
	pActionB1 = new QAction("曲线");
	pActionB1->setChecked(true);
	pMenuB->addAction(pActionB1);
	pActionB2 = new QAction("控制多边形");
	pActionB1->setChecked(false);
	pMenuB->addAction(pActionB2);
	pMenuBar->addMenu(pMenuB);
	*/
	//pMenuC
	pMenuC = new QMenu("选项");
	pActionC1 = new QAction("删除");
	pMenuC->addAction(pActionC1);
	pActionC2 = new QAction("剪切");
	pMenuC->addAction(pActionC2);
	pActionC3 = new QAction("展示");
	pMenuC->addAction(pActionC3);
	pMenuBar->addMenu(pMenuC);
	//pStatusBar
	//pStatusBar = ui.statusBar;
	//setStatusBar(pStatusBar);
	//pStatusBar->showMessage("就绪");

	//pToolBar
	pToolBar = ui.mainToolBar;
	colorBtn = new QPushButton("颜色");
	QPixmap pixmap(20, 20);
	pixmap.fill(Qt::black);
	colorBtn->setIcon(QIcon(pixmap));
	pToolBar->addWidget(colorBtn);
	pToolBar->addSeparator();

	controlBox = new QCheckBox("控制多边形",this);
	controlBox->setChecked(true);
	pToolBar->addWidget(controlBox);
	pToolBar->addSeparator();

	moveBox = new QCheckBox("移动控制点",this);
	moveBox->setChecked(false);
    pToolBar->addWidget(moveBox);
	pToolBar->addSeparator();
	

	densityLabel = new QLabel(tr("采样点次数： "));
    pToolBar->addWidget(densityLabel);

	densitySbx = new QSpinBox(this);
	densitySbx->setMinimum(3);
	densitySbx->setMaximum(100);
	densitySbx->setValue(50);
	densitySbx->setSingleStep(1);
	pToolBar->addWidget(densitySbx);
    pToolBar->addSeparator();

	densitySld = new QSlider(this);
	densitySld->setOrientation(Qt::Horizontal);
	densitySld->setMinimum(3);
	densitySld->setValue(50);
	densitySld->setMaximum(100);
	densitySld->setSingleStep(1);
	pToolBar->addWidget(densitySld);
	pToolBar->addSeparator();

	degreeLabel = new QLabel(tr("多项式次数："));
	pToolBar->addWidget(degreeLabel);

	degreeSbx = new QSpinBox(this);
	degreeSbx->setMinimum(3);
	degreeSbx->setMaximum(3);
	degreeSbx->setSingleStep(1);
	pToolBar->addWidget(degreeSbx);
	pToolBar->addSeparator();

	degreeSld = new QSlider(this);
	degreeSld->setOrientation(Qt::Horizontal);
	degreeSld->setMinimum(3);
	degreeSld->setMaximum(3);
	degreeSld->setSingleStep(1);
	pToolBar->addWidget(degreeSld);

	
	//信号与槽
	connect(densitySbx,SIGNAL(valueChanged(int)),densitySld,SLOT(setValue(int)));
	connect(densitySld, SIGNAL(valueChanged(int)), densitySbx, SLOT(setValue(int)));
	connect(densitySbx, SIGNAL(valueChanged(int)), curvearea,SLOT(setDensity(int)));
	connect(densitySbx, SIGNAL(valueChanged(int)), curvearea, SLOT(repaint()));
	connect(densitySld,SIGNAL(valueChanged(int)),curvearea,SLOT(repaint()));
	connect(degreeSbx,SIGNAL(valueChanged(int)),degreeSld,SLOT(setValue(int)));
	connect(degreeSld,SIGNAL(valueChanged(int)),degreeSbx,SLOT(setValue(int)));
	connect(degreeSbx,SIGNAL(valueChanged(int)),curvearea,SLOT(setDegree(int)));
	connect(degreeSbx,SIGNAL(valueChanged(int)),curvearea,SLOT(repaint()));
	connect(degreeSld, SIGNAL(valueChanged(int)), curvearea, SLOT(setDegree(int)));
	connect(degreeSld, SIGNAL(valueChanged(int)), curvearea, SLOT(repaint()));
	
	connect(colorBtn,SIGNAL(clicked()),this,SLOT(ShowColor()));
	connect(pActionA1,SIGNAL(triggered()),this,SLOT(OpenMyFile()));
	connect(pActionA3,SIGNAL(triggered()),this,SLOT(proquit()));
	connect(pActionC1,SIGNAL(triggered()),curvearea,SLOT(clear()));
	connect(pActionC2,SIGNAL(triggered()),curvearea,SLOT(cut()));
	connect(pActionC3,SIGNAL(triggered()),curvearea,SLOT(display()));

	connect(controlBox,SIGNAL(stateChanged(int)),curvearea,SLOT(displayControl(int)));
	connect(moveBox,SIGNAL(stateChanged(int)),curvearea,SLOT(setMoveflag(int)));
	//connect(curvearea,SIGNAL(sigTest1(int)),this,SLOT(setMinDegree(int)));
	connect(curvearea,SIGNAL(sigTest2(int)),this,SLOT(setMaxDegree(int)));
}

void QtGUI3::ShowColor()
{
	QColor color = QColorDialog::getColor(static_cast<int> (Qt::black), this);
	if (color.isValid())
	{
		curvearea->setColor(color);
		QPixmap p(20, 20);
		p.fill(color);
		colorBtn->setIcon(QIcon(p));
	}
}

void QtGUI3::OpenMyFile()
{
	fileName = QFileDialog::getOpenFileName(this);
	if (!fileName.isEmpty())
	{
		curvearea->loadFile(fileName);
	}
}

void QtGUI3::setMinDegree(int x)
{
	qDebug() << "MinDegree: " << x << endl;
	degreeSbx->setMinimum(x);
	degreeSld->setMinimum(x);
}

void QtGUI3::setMaxDegree(int x)
{
	qDebug() << "MaxDegree: " << x << endl;
	degreeSbx->setMaximum(x);
	degreeSld->setMaximum(x);
}


void QtGUI3::proquit()
{
	QApplication::quit();
}