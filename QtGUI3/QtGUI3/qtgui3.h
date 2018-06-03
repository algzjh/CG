#include <QtWidgets/QMainWindow>
#include <QMouseEvent>
#include <QToolBox>  
#include <QPushButton>
#include <QButtonGroup>  
#include <QRadioButton>
#include <QComboBox>
#include <QSpinBox>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QCheckBox>
#include <QComboBox>
#include "ui_qtgui3.h"
#include "curvearea.h"

class QtGUI3 : public QMainWindow
{
	Q_OBJECT

public:
	QtGUI3(QWidget *parent = Q_NULLPTR);
public slots:
    void ShowColor();
	void OpenMyFile();
	void setMinDegree(int);
	void setMaxDegree(int);
	void proquit();
protected:
	//void mouseMoveEvent(QMouseEvent *);

private:
	Ui::QtGUI3Class ui;
	CurveArea *curvearea;

	//QMenuBar
	QMenuBar* pMenuBar;
	QMenu *pMenuA, *pMenuB, *pMenuC;
	QAction *pActionA1, *pActionA2, *pActionA3;
	QAction *pActionB1, *pActionB2;
	QAction *pActionC1,*pActionC2,*pActionC3;
	QString fileName;
	//QStatusBar
	QStatusBar* pStatusBar;
	//QToolBar
	QToolBar* pToolBar;
	QPushButton *colorBtn;
	QCheckBox *controlBox;
	QCheckBox *moveBox;
	QLabel *densityLabel;
	QSpinBox *densitySbx;
	QSlider *densitySld;
	QLabel *degreeLabel;
	QSpinBox *degreeSbx;
	QSlider *degreeSld;
	QComboBox *degreeCbx;
	
	int minDegree;
	int maxDegree;
};
