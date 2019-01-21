#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"
#include <json.h>
#include <string>
#include <iostream>
#include <fstream>

#include <QLineEdit>
#include <QTimer>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <QString>
#include <QFileDialog>
#include <QTextCodec>
using namespace std;
class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);

private slots:
	void timerUpdate();
	void on_load_index();
	void on_load_pose();
	void on_load_images();
	void on_oKey();
	void on_xKey();
	void on_text_changed();
	void on_slider_moved();
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
	QString str2qstr(const string str);
	string qstr2str(const QString qstr);
};
