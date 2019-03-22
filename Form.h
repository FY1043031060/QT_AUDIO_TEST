#ifndef FORM_H
#define FORM_H

#include "ui_Form.h"
#include <QSoundEffect>
#include <QThread>
#include <QMediaPlayer>
class CSound;
class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
	void playSound(const QString &str);
    void playMedia(const QString & str);
    void playMedias(const QStringList& listStr);
	~Form();
Q_SIGNALS:
	void sourcePlayed(const QString str);

private:
    Ui::Form ui;
    QSoundEffect effect;
	QMediaPlayer m_player;
	QThread m_thread;
	//CSound m_sound;
};

//class CSound : public QObject
//{
//public:
//	CSound(QObject* parent = Q_NULLPTR) : QObject(parent) {
//		m_effect.setVolume(1.0f);
//	}
//	~CSound (){}
//public Q_SLOTS:
//	void playBySource(const QString str) {
//		qDebug() << __LINE__;
//		m_effect.setSource(QUrl::fromLocalFile(str));
//		qDebug() << __LINE__;
//		m_effect.play();
//		qDebug() << __LINE__;
//	}
//private:
//	QSoundEffect m_effect;
//};
#endif // FORM_H
