#include <QtGui>
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QPalette>
#include <QVector>
#include <QtDebug>
#include <QFileDialog>
#include <cmath>

class CurveArea : public QWidget
{
	Q_OBJECT

public:
	explicit CurveArea(QWidget *parent =0);
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent *);
	void loadFile(QString);
	void changeu(bool,int,int);
	double calcB(double,int,int);
	void deboor();
	int  dcmp(double);
	void drawBSpline();
	void drawmypoints();
	void drawmyline();
	void mergePixMap();
	

public slots:
    void setColor(QColor);
    void setDensity(int);
	void setDegree(int);
	void clear();
	void displayControl(int);
	void setMoveflag(int);
	void repaint();
	void cut();
	void display();

signals:
	void sigTest2(int);
private:
	QPixmap * pix;
	QPixmap * pixPoints;  //点的Pixmap
	QPixmap * pixLines;   //线的Pixmap
	QPixmap * pixCurve;   //曲线的Pixmap
	QPen  penPoint;
	QPen  penCurve;
	QPen  penLine;
	QPoint startPos;    
	QPoint endPos;
	QColor color;        //线的颜色
	QVector<QPoint> vPoints;  //控制点向量
	QVector<QLine> vLines;    //控制线向量
	QVector<QLine> veccur[50];  //曲线向量
	QVector<double> u;  // 结点矢量
	QVector<QImage> vimg;
	int degree; //多项式的次数
	float ptX[500][1000], ptY[500][1000];
	int densitynum ;
	bool moveflag;
	bool selectedpoint;
	int selectedpointid;
	bool fromfile;
	bool hascut;
	int cutnum;
};

