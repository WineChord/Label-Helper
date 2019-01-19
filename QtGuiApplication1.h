#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"
#include <json.h>
#include <QLineEdit>
#include <vector>
#include <QTimer>
class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);

private slots:
	void on_OpenFiles_clicked();
	void timerUpdate();
	void on_load_index();
	void on_load_pose();
	void on_load_images();
	void on_oKey();
	void on_xKey();
	void on_text_changed();
	void on_slider_moved();
	//void slot1();
private:
	Ui::QtGuiApplication1Class ui;
	QTimer *mTimer;
	Json::Value root;
	Json::Value realRoot;
	Json::Value rootW;
	Json::Reader reader;
	Json::Value::Members member;
	QString imagesDir;
	QString indexPath;
	QString posePath;
	Json::Value oFiles;
	Json::Value xFiles;
	Json::Value currentFiles;
	Json::String currentFileName;
	int currentIndex;
	void findPre();
	void findNext();
	void showPic();
	void showAgain();
	void writePos(int pos);
	void keyPressEvent(QKeyEvent * event);
};
