#ifndef COREWINDOW_H
#define COREWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QCheckBox>
#include <QLineEdit>
#include <QtOpenGL>

#include "data/Manager.h"


class QGLWidget;

class CoreWindow : public QMainWindow
{
	Q_OBJECT        // must include this if you use Qt signals/slots

public:
	CoreWindow( QGLWidget *glWidget, QWidget *parent = NULL);

	QSlider		*getHeightCoefSL() const;
	QSlider		*getCurveWidthCoefSL() const;
	QSlider		*getAlphaCoefSL() const;
	QSlider		*getGapCoefSL() const;
	QCheckBox	*getSelectAdjNodesCB() const;


signals:
	void openGraph(QString file );

private slots:
	bool open();

private:
	void createToolbar();

	QGLWidget	*_coreGLWidget;



	QPushButton	*_openFilePB;
	QSlider		*_heightCoefSL;
	QSlider		*_curveWidthCoefSL;
	QSlider		*_alphaCoefSL;
	QSlider		*_gapCoefSL;
	QCheckBox	*_selectAdjNodesCB;

	/*
	_openFilePB;
	_heightCoefSL;
	_curveWidthoefSL;
	_alfaCoefSL;
	_gapCoefSL;
	_selectAdjNodes;
*/






};

#endif
