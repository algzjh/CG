#include "curvearea.h"
#include <QtGui>
#include <Qpen>
const double eps = 1e-6;
const double INF = 1e9;

CurveArea::CurveArea(QWidget *parent): QWidget(parent)
{
	setAutoFillBackground(true);
	setPalette(QPalette(Qt::white));
	pix = new QPixmap(size());
	pix->fill(Qt::white);
	setMinimumSize(1200,800);
	degree = 3;
	densitynum = 100;
	moveflag = false;
	selectedpoint = false;
	penPoint.setWidth(5);
	penPoint.setColor(Qt::blue);
	penCurve.setWidth(2);
	penCurve.setColor(Qt::red);
	penLine.setWidth(3);
	fromfile = false;
	hascut = false;
	cutnum = 0;
}


void CurveArea::mousePressEvent(QMouseEvent *e)
{
	if (!moveflag && e->button() == Qt::LeftButton) 
	{
		startPos = e->pos();
		qDebug() << vPoints.size() << " " << vLines.size() << endl;
		QPainter *painter = new QPainter;
		painter->begin(pix);
		painter->setPen(penPoint);
		painter->drawPoint(startPos);
		vPoints.append(startPos);
		int sz = vPoints.size();
		if (sz >= 2)
		{
			vLines.append(QLine(vPoints[sz - 2],vPoints[sz-1]));
			penLine.setColor(color);
			painter->setPen(penLine);
			painter->drawLine(QLine(vPoints[sz - 2], vPoints[sz - 1]));
		}
		//qDebug() << "sigTest1: " << vPoints.size() - 1 << endl;
		//emit sigTest1(vPoints.size()-1);
		qDebug() << "vPoints.size() - 1 + degree + 1" << vPoints.size() - 1 + degree + 1 << endl;
		emit sigTest2(vPoints.size() - 1 + degree + 1);
		painter->end();
		qDebug() << vPoints.size() << " " << vLines.size() << endl;
		update();
	}
	else if (e->button() == Qt::RightButton)
	{
		if (vPoints.size() >= 3)
		{
			qDebug() << "Hello " << endl;
			changeu(false,3,vPoints.size()-1);
			QPixmap *clearPix = new QPixmap(size());
			clearPix->fill(Qt::white);
		    if(!hascut)	pix = clearPix;
			drawBSpline();
			qDebug() << "Hello2 " << endl;
			//QPainter painter(pix);
			//painter.drawPixmap(QPoint(0, 0),*pixCurve);
			drawmypoints();
			drawmyline();
			//mergePixMap();
			update();
		}
	}
}

void CurveArea::repaint()
{
	QPixmap *clearPix = new QPixmap(size());
	clearPix->fill(Qt::white);
	if(!hascut) pix = clearPix;
	drawBSpline();
	drawmypoints();
	drawmyline();
	update();
}

void CurveArea::drawmyline()
{
	pixLines = new QPixmap(size());
	pixLines->fill(Qt::white);
	int sz = vPoints.size();
	QPainter *painter = new QPainter;
	penLine.setColor(color);
	painter->begin(pix);
	painter->setPen(penLine);
	for (int i = 1; i < sz; i++) {
		painter->drawLine(QLine(vPoints[i-1],vPoints[i]));
	}
	painter->end();
}

void CurveArea::drawmypoints()
{
	pixPoints = new QPixmap(size());
	pixPoints->fill(Qt::white);
	QPainter *painter = new QPainter;
	painter->begin(pix);
	painter->setPen(penPoint);
	int sz = vPoints.size();
	for (int i = 0; i < sz; i++)
	{
		painter->drawPoint(vPoints[i]);
	}
	painter->end();
}

void CurveArea::mergePixMap()
{
	/*
	pix = new QPixmap(size());
	pix->fill(Qt::white);
	QPainter painter;
	painter.begin(pixPoints);
	painter.setPen(penPoint);
	painter.drawPixmap(0,0,*pix);
	painter.end();
	painter.begin(pixLines);
	penLine.setColor(color);
	painter.setPen(penLine);
	painter.drawPixmap(0,0,*pix);
	painter.end();
	painter.begin(pixCurve);
	painter.setPen(penCurve);
	painter.drawPixmap(0,0,*pix);
	painter.end();
	*/
	/*
	QImage piximg = pix->toImage();
	QImage pointimg = pixPoints->toImage();
	QImage lineimg = pixLines->toImage();
	QImage curveimg = pixCurve->toImage();
	QPainter painter;
	painter.begin(&piximg);
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.setPen(penPoint);
	painter.drawImage(0,0,*);
	painter.drawPixmap(QPoint(0, 0), *pixPoints);
	painter.setPen(penCurve);
	painter.drawPixmap(QPoint(0, 0), *pixCurve);
	penLine.setColor(color);
	painter.drawPixmap(QPoint(0, 0), *pixLines);
	painter.end();
	*/
	/*
	painter->begin(pix);
	painter->setPen(penPoint);
	painter->drawPixmap(pix->width(),pix->height(),*pixPoints);
	penLine.setColor(color);
	painter->drawPixmap(pix->width(),pix->height(), *pixLines);
	painter->setPen(penCurve);
	painter->drawPixmap(pix->width(),pix->height(),*pixCurve);
	painter->end();
	*/
}

void CurveArea::mouseReleaseEvent(QMouseEvent *e)
{
	selectedpoint = false;
}

void CurveArea::mouseMoveEvent(QMouseEvent *e)
{
	if (moveflag)
	{
		qDebug() << moveflag << endl;
		int pressx = e->x();
		int pressy = e->y();
		int sz = vPoints.size();
		double mindis = INF;
		int ans;
		if (!selectedpoint)
		{
			ans = -1;
			for (int i = 0; i < sz; i++)
			{
				double px = vPoints[i].x();
				double py = vPoints[i].y();
				if ((pressx - px)*(pressx - px) + (pressy - py)*(pressy - py) < mindis)
				{
					mindis = (pressx - px)*(pressx - px) + (pressy - py)*(pressy - py);
					ans = i;
					selectedpoint = true;
					selectedpointid = i;
				}
			}
		}
		ans = selectedpointid;
		qDebug() << "ans: " << ans << endl;
		vPoints[ans].rx() = pressx;
		vPoints[ans].ry() = pressy;
		QPixmap *clearPix = new QPixmap(size());
		clearPix->fill(Qt::white);
      pix = clearPix;
	   veccur[cutnum].clear();
		drawmypoints();
		drawmyline();
		drawBSpline();
		//mergePixMap();
		update();
	}
}

void CurveArea::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	painter.drawPixmap(QPoint(0,0),*pix);
}

void CurveArea::resizeEvent(QResizeEvent *e)
{
	if (height() > pix->height() || width() > pix->width())
	{
		QPixmap *newPix = new QPixmap(size());
		newPix->fill(Qt::white);
		QPainter p(newPix);
		p.drawPixmap(QPoint(0,0),*pix);
		pix = newPix;
	}
	QWidget::resizeEvent(e);
}

void CurveArea::clear()
{
	fromfile = false;
	vPoints.clear();
	vLines.clear();
	QPixmap *clearPix = new QPixmap(size());
	clearPix->fill(Qt::white);
	pix = clearPix;
	pixPoints = clearPix;

	update();
}

void CurveArea::setColor(QColor c)
{
	color = c;
}

void CurveArea::setDensity(int x)
{
	densitynum = x;
	qDebug() << "set density: " << x << endl;
}

void CurveArea::setDegree(int x)
{
	qDebug() << "set degree: " << x << endl;
	degree = x;
}

void CurveArea::setMoveflag(int f)
{
	
	if(f==Qt::Checked) moveflag = 1;
	else moveflag = 0;
	qDebug() << "moveflag: " << moveflag << endl;
}

void CurveArea::displayControl(int flag)
{
	if (flag == Qt::Checked)//显示控制多边形
	{
		repaint();
	}
	else
	{
		QPixmap *clearPix = new QPixmap(size());
		clearPix->fill(Qt::white);
		if(!hascut) pix = clearPix;
		drawBSpline();
		drawmypoints();
		//drawmyline();
		update();
	}
		/*
		QPixmap *tmp = new QPixmap(size());
		tmp->fill(Qt::white);
		QPainter *painter = new QPainter;
		QPen pen;
		pen.setWidth(2);
		pen.setColor(Qt::red);
		painter->begin(tmp);
		int sz = veccur.size();
		for (int i = 0; i < sz; i++)
		{
			painter->drawLine(veccur[i]);
		}
		painter->end();
		update();
		painter->begin(tmp);
		pen.setWidth(3);
		pen.setColor(color);
		sz = vPoints.size();
		for (int i = 0; i < sz; i++)
		{
			painter->drawPoint(vPoints[i]);
		}
		sz = vLines.size();
		for (int i = 0; i < sz; i++)
		{
			painter->drawLine(vLines[i]);
		}
		painter->end();
		pix = tmp;
		update();
	}
	else
	{
		QPixmap *tmp = new QPixmap(size());
		tmp->fill(Qt::white);
		QPainter *painter = new QPainter;
		QPen pen;
		pen.setWidth(2);
		pen.setColor(Qt::red);
		painter->begin(tmp);
		int sz = veccur.size();
		for (int i = 0; i < sz; i++)
		{
			painter->drawLine(veccur[i]);
		}
		painter->end();
		pix = tmp;
		update();
	*/
}


int CurveArea::dcmp(double x)
{
	if (fabs(x) < eps) return 0;
	return x > 0 ? 1 : -1;
}


void CurveArea::changeu(bool flag,int d,int n)
{
	//d:degree 次数
	//n:n+1个控制点
	//flag:有文件输入flag = true;否则 false;
	if (!flag)
	{
		int m = n + d + 1;//m的最大值
		u.clear();
		for (int i = 0; i <= m; i++)
		{
			u.push_back((double)i);
		}
	}
}

double CurveArea::calcB(double x, int k, int d)
{
	if (d == 0)
	{
		if (x >= u[k] && x <= u[k + 1]) return 1.0;
		else return 0.0;
	}
	double c1, c2;
	if (dcmp(u[k + d] - u[k])==0) c1 = 0.0;
	else c1 = (x - u[k]) / (u[k + d] - u[k])*calcB(x,k,d-1);
	if (dcmp(u[k + d + 1] - u[k + 1])==0) c2 = 0.0;
	else c2 = (u[k + d + 1] - x) / (u[k + d + 1] - u[k + 1])*calcB(x,k+1,d-1);
	return c1 + c2;
}

void CurveArea::drawBSpline()
{
	pixCurve = new QPixmap(size());
	pixCurve->fill(Qt::white);
	QPainter *painter = new QPainter;
	painter->begin(pix);
	painter->setPen(penCurve);
	qDebug() << "degree: "<<degree << endl;
	//system("pause");
	int m = u.size() - 1;
	qDebug() << "m: " << m << endl;
	bool first = true;
	bool second = true;
	double preX, preY, nowX, nowY, tmpX, tmpY;
	for (int i = degree; i <= m - degree - 1; i++)
	{
		//qDebug() << "densitynum: " << densitynum << endl;
		double delta = (u[i + 1] - u[i]) / densitynum;
		//qDebug() << "delta: " << delta << endl;
		//system("pause");
		second = true;
		first = true;
		for (double j = u[i]; j <= u[i + 1]; j += delta)
		{
			tmpX = 0, tmpY = 0;
			for (int k = i - degree; k <= i; k++)
			{
				//qDebug() << "1" << endl;
				tmpX += vPoints[k].x()*calcB(j,k,degree);
				//qDebug() << "2" << endl;
				tmpY += vPoints[k].y()*calcB(j,k,degree);
				//qDebug() << "3" << endl;
			}
			if (first)
			{
				preX = tmpX;
				preY = tmpY;
				first = false;
			}
			else
			{
				nowX = tmpX;
				nowY = tmpY;
				//qDebug() << preX << " " << preY << " " << nowX << " " << nowY << endl;
				if (second) second = false;
				else
				{
					painter->drawLine(preX, preY, nowX, nowY);
					veccur[cutnum].push_back(QLine(preX, preY, nowX, nowY));
				}
				preX = nowX;
				preY = nowY;
			}
		}
	}
	painter->end();
}

void CurveArea::deboor()
{
	QPainter *painter = new QPainter;
	QPen pen;
	pen.setWidth(2);
	pen.setColor(Qt::red);
	painter->begin(pix);
	painter->setPen(pen);


	int n = vPoints.size() - 1; // n + 1 个控制点数
	for (int i = 0; i <= n + degree + 6; i++) u.push_back((float)i); // n+d+1个结点
	//memset(ptX, 0, sizeof(ptX));
	//memset(ptY, 0, sizeof(ptY));
	/*
	float preX, preY, nowX, nowY;
	bool first = true;
	for (int i = degree; i <= n; i++)
	{
		float dt = (u[i + 1] - u[i]) / densitynum;
		for (float t = u[i]; t <= u[i + 1]; t += dt)
		{
			nowX = 0, nowY = 0;
			for (int k = 0; k <= n; k++)
			{
				
			}
		}
	}
	*/
	bool first = true;
	float preX, preY;
	degree = 3;
	for (int i = degree; i < n ; i++)
	{
		float delta = (u[i + 1] - u[i]) / densitynum;
		for (float t = u[i]; t <= u[i + 1]; t += delta)
		{
			for (int k = 0; k <= degree; k++)
			{
				for (int j = i - degree + k; j <= i; j++)
				{
					if (k == 0)
					{
						ptX[j][k] = vPoints[j].x();
						ptY[j][k] = vPoints[j].y();
					}
					else
					{
						float ap = (t - u[j]) / (u[j + degree + 1 - k] - u[j]);
						ptX[j][k] = (1.0 - ap)*ptX[j - 1][k - 1] + ap * ptX[j][k - 1];
						ptY[j][k] = (1.0 - ap)*ptY[j - 1][k - 1] + ap * ptY[j][k - 1];
						if (j == i && k == degree)
						{
							if (first)
							{
								preX = ptX[j][degree];
								preY = ptY[j][degree];
							}
							else
							{
								painter->drawLine(preX, preY, ptX[j][3], ptY[j][3]);
								veccur[cutnum].push_back(QLine(QPoint(preX, preY),QPoint(ptX[j][3], ptY[j][3])));
								//qDebug() << veccur.size() << endl;
								//tmp
								/*
								QPainter *tmppainter = new QPainter;
								QPen tmppen;
								tmppen.setWidth(2);
								tmppen.setColor(Qt::red);
								tmppainter->begin(pixCurve);
								tmppainter->setPen(tmppen);
								tmppainter->drawLine(preX, preY, ptX[j][3], ptY[j][3]);
								tmppainter->end();
								*/
								preX = ptX[j][3];
								preY = ptY[j][3];
							}
							first = false;
						}
					}
				}
			}
		}
	}
	painter->end();
}

void CurveArea::loadFile(QString filename)
{
	qDebug() << "filename: " << filename << endl;
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream textStream(&file);
		QString line = textStream.readLine();
		int tdegree = line.toInt();
		line = textStream.readLine();
		int tcnt_num = line.toInt();
		line = textStream.readLine();
		QStringList textlist = line.split(" ");
		u.clear();
		vPoints.clear();
		for (int i = 0; i < textlist.size(); i++)
		{
			double tu = textlist[i].toDouble();
			u.push_back(tu);
		}
		double tx, ty;
		for (int i = 0; i < tcnt_num; i++)
		{
			line = textStream.readLine();
			textlist = line.split(" ");
			tx = textlist[0].toDouble();
			ty = textlist[1].toDouble();
			vPoints.push_back(QPoint(tx,ty));
		}
	}
	repaint();
}


void CurveArea::cut()
{
	cutnum++;
	hascut = true;
	fromfile = false;
	QImage piximg = pix->toImage();
	vimg.push_back(piximg);
	vPoints.clear();
	vLines.clear();
	qDebug() << "has been cut" << endl;
	//QPixmap *clearPix = new QPixmap(size());
	//clearPix->fill(Qt::white);
	//pix = clearPix;
	//pixPoints = clearPix;

	//update();
}


void CurveArea::display()
{
	QPixmap *clearPix = new QPixmap(size());
	clearPix->fill(Qt::white);
	pix = clearPix;
	QPainter painter;
	painter.begin(pix);
	painter.setPen(penCurve);
	qDebug() << "cutnum: " << cutnum << endl;
	for (int i = 0; i < this->cutnum; i++)
	{
		int sz = veccur[i].size();
		qDebug() << "sz: " << sz << endl;
		for (int j = 2; j < sz; j++)
		{
			painter.drawLine(veccur[i][j]);
		}
	}
	painter.end();
	update();
}