#include "QtGuiApplication1.h"

using namespace std;
QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	mTimer = new QTimer(this);
	connect(mTimer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
}
void QtGuiApplication1::timerUpdate() {
	if (currentIndex > currentFiles.size()) currentIndex = 1;
	showPic();
	currentIndex++;
}
QString QtGuiApplication1::str2qstr(const string str){
	return QString::fromLocal8Bit(str.data());
}
string QtGuiApplication1::qstr2str(const QString qstr){
	QByteArray cdata = qstr.toLocal8Bit();
	return string(cdata);
}
void QtGuiApplication1::on_load_index() {
	QString filename0;
	filename0 = QFileDialog::getOpenFileName(this, "Files", "", "*.json");
	QTextCodec *code = QTextCodec::codecForName("GB2312");
	string filename1 = code->fromUnicode(filename0);
	QString filename = str2qstr(filename1);
	//cout << filename;
	qDebug() << filename;
	indexPath = filename;
	ifstream ifs(filename1);
	if (!reader.parse(ifs, root))
		cout << "error loading index.json!" << endl;
	else {
		cout << "success!" << endl;
		member = root.getMemberNames();
		int k = 0;
		sort(member.begin(), member.end());
		for (auto i = member.begin(); i != member.end(), k < 5; i++, k++) {
			cout << *i << endl;
			cout << root[*i] << endl;
		}
		int oKey = 0;
		int xKey = 0;
		for (auto i = member.begin(); i != member.end(); i++) {
			if (root[*i] == "o") {
				oFiles[oKey++] = (*i);
			}
			else if (root[*i] == "x") {
				xFiles[xKey++] = (*i);
			}
		}
		currentFiles = oFiles;
		currentIndex = 1;
		cout << "load index.json!" << endl;
	}
}
void QtGuiApplication1::on_load_pose() {
	QString filename0;
	filename0 = QFileDialog::getOpenFileName(this, "Files", "", "*.json");
	QTextCodec *code = QTextCodec::codecForName("GB2312");
	string filename1 = code->fromUnicode(filename0);
	QString filename = str2qstr(filename1);
	//cout << filename;
	qDebug() << filename;
	posePath = filename;
	ifstream ifs2(filename1);
	if (!reader.parse(ifs2, rootW)) 
		cout << "error loading pose.json!" << endl;
	else {
		cout << "load pose.json!" << endl;
	}
}
void QtGuiApplication1::on_load_images() {
	QString filename0;
	filename0 = QFileDialog::getExistingDirectory(this, "Folders", "");
	QTextCodec *code = QTextCodec::codecForName("GB2312");
	string filename1 = code->fromUnicode(filename0);
	QString filename = str2qstr(filename1);
	//cout << filename;
	imagesDir = filename;
	showPic();
}
void QtGuiApplication1::on_oKey() {
	currentFiles = oFiles;
	currentIndex = 1;
	showPic();
}
void QtGuiApplication1::on_xKey() {
	currentFiles = xFiles;
	currentIndex = 1;
	showPic();
}
void QtGuiApplication1::on_text_changed() {
	QString lineText = ui.lineEdit->text();
	int countToGo = lineText.toInt();
	if (countToGo > currentFiles.size()) countToGo = currentFiles.size();
	if (countToGo < 1) countToGo = 1;
	qDebug() << countToGo;
	currentIndex = countToGo;
	showPic();
}
void QtGuiApplication1::on_slider_moved() {
	qDebug() << "on_slider";
	int sliderValue = ui.horizontalSlider->value();
	ui.label_speed->setText(QString::number(sliderValue));
	mTimer->stop();
	if (sliderValue) mTimer->start(1000 / sliderValue);
}
void QtGuiApplication1::findPre() {
	if (currentIndex > 1)
		currentIndex--;
}
void QtGuiApplication1::findNext() {
	if (currentIndex < currentFiles.size()) 
		currentIndex++;
}
void QtGuiApplication1::showPic() {
	cout << currentIndex << '/' << currentFiles.size() << endl;
	QString filename = imagesDir;
	filename.append("/");
	currentFileName = currentFiles[currentIndex - 1].asString();
	string myname = currentFileName;
	QString name = QString::fromStdString(myname);
	filename.append(name);
	qDebug() << "current filename" << filename;
	cout << root[currentFileName] << endl;
	QPixmap pix(filename);
	ui.label_pic->setPixmap(pix);
	QString text = QString::number(currentIndex);
	text.append("/");
	QString text2 = QString::number(currentFiles.size());
	text.append(text2);
	ui.label_2->setText(text);
	QString text_pos;
	if (rootW[currentFileName].isNull()) text_pos = "NULL";
	else {
		switch (rootW[currentFileName].asInt()){
		case 1:text_pos = "front"; break;
		case 2:text_pos = "back"; break;
		case 3:text_pos = "left"; break;
		case 4:text_pos = "right"; break;
		default:text_pos = "undefined"; break;
		}
	}
	ui.label_pos->setText(text_pos);
}
void QtGuiApplication1::showAgain() {
	findNext();
	showPic();
	Json::StyledWriter sw;
	ofstream os;
	os.open(qstr2str(posePath));
	os << sw.write(rootW);
	os.close();
}
void QtGuiApplication1::writePos(int pos) {
	currentFileName = currentFiles[currentIndex - 1].asString();
	if (rootW[currentFileName].isNull()) {}
	else {
		rootW.removeMember(currentFileName);
	}
	rootW[currentFileName] = Json::Value(pos);
}
void QtGuiApplication1::keyPressEvent(QKeyEvent* event) {
	QString text = ui.label->text();
	text = char(event->key());
	ui.label->setText(text);
	switch(event->key()){
	case Qt::Key_D:
		writePos(4);
		qDebug() << "right";
		showAgain();
		break;
	case Qt::Key_W:
		writePos(1);
		qDebug() << "front";
		showAgain();
		break;
	case Qt::Key_A:
		writePos(3);
		qDebug() << "left";
		showAgain();
		break;
	case Qt::Key_S:
		writePos(2);
		qDebug() << "back";
		showAgain();
		break;
	case Qt::Key_Q:
		qDebug() << "find pre";
		findPre();
		showPic();
		break;
	case Qt::Key_E:
		qDebug() << "find next";
		findNext();
		showPic();
		break;
	default:
		qDebug() << "Qt::Keypressed";
		break;
	}
}
