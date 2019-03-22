#include "Form.h"
#include <QDebug>
#include <qthread.h>
#include <QTimer>
#include <QSound>
#include <QMediaPlaylist>
Form::Form(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
    m_player.setVolume(50);
	//connect(this, &Form::sourcePlayed, &m_sound, &CSound::playBySource, Qt::QueuedConnection);
	qDebug() << __LINE__ << effect.isPlaying();
    connect(&m_player, &QMediaPlayer::stateChanged, [&](QMediaPlayer::State state){
        qDebug() << __LINE__ <<"State" <<state;
    });
    connect(&m_player, &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status){
qDebug() << __LINE__ <<"MediaStatus" << status;
    });
	connect(ui.pushButton, &QPushButton::clicked, [&]() {

		effect.setVolume(1.0f);
		QString str1 = "C:\\Users\\Administrator\\Documents\\SoundSimulation\\Sound\\ARJ 21 Aural Alerts\\Tones\\Vertical Track.wav";
#ifdef DEBUG
        playSound(str1);
#else
        playMedia(str1);
#endif // DEBUG	
		qDebug() << __FUNCTION__ << "THIS IS TEST";

	});
    connect(ui.pushButton_2, &QPushButton::clicked, [&](){
        QString str2 = "C:\\Users\\Administrator\\Documents\\SoundSimulation\\Sound\\ARJ 21 Aural Alerts\\APU_FIRE.wav";
#ifdef DEBUG
        playSound(str2);
#else
        playMedia(str2);
#endif // DEBUG   
	});
    connect(ui.pushButton_4, &QPushButton::clicked, [&](){
        QStringList strList;
        strList << "C:\\Users\\Administrator\\Documents\\SoundSimulation\\Sound\\ARJ 21 Aural Alerts\\Tones\\GRNDCALL.wav"
                << "C:\\Users\\Administrator\\Documents\\SoundSimulation\\Sound\\ARJ 21 Aural Alerts\\Tones\\ALTITUDE.wav"
                << "C:\\Users\\Administrator\\Documents\\SoundSimulation\\Sound\\ARJ 21 Aural Alerts\\Tones\\ALTITUDE.wav"
                << "C:\\Users\\Administrator\\Documents\\SoundSimulation\\Sound\\ARJ 21 Aural Alerts\\AUTOBRAKE_DISARM.wav"
                << "C:\\Users\\Administrator\\Documents\\SoundSimulation\\Sound\\ARJ 21 Aural Alerts\\AUTOTHROTTLE_DISENGAGE.wav"
                << "C:\\Users\\Administrator\\Documents\\SoundSimulation\\Sound\\ARJ 21 Aural Alerts\\Tones\\ALTITUDE.wav";
        playMedias(strList);
    });
	connect(&effect, &QSoundEffect::statusChanged, [&]() {
		qDebug() << __LINE__ << effect.status();
	});
	connect(&effect, &QSoundEffect::loopCountChanged, [&]() {
		qDebug() << __LINE__ << effect.loopCount();
	});
	connect(&effect, &QSoundEffect::playingChanged, [&]() {
		qDebug() << __LINE__ << effect.isPlaying();
	});

    connect(ui.pushButton_3, &QPushButton::clicked, [&](){
        QString str3 = ui.lineEdit->text();
        playSound(str3);
    });
}

void Form::playSound(const QString & str)
{
	qDebug() << __LINE__ << "loading before";
	effect.setSource(QUrl::fromLocalFile(str));
	qDebug() << __LINE__ << "loading after" << "play before";
	effect.play();
    qDebug() << __LINE__ << "play after";
}

void Form::playMedia(const QString &str)
{
    qDebug() << __LINE__ << "loading before";
    m_player.setMedia(QUrl::fromLocalFile(str));
    qDebug() << __LINE__ << "loading after" << "play before";
    m_player.play();
    qDebug() << __LINE__ << "play after";
}

void Form::playMedias(const QStringList &listStr)
{
    qDebug() << __LINE__ << "loading before";

    auto playlist = new QMediaPlaylist;
    for (int i = 0; i < listStr.size(); ++i) {
        playlist->addMedia(QUrl::fromLocalFile(listStr.at(i)));
    }
    playlist->setCurrentIndex(1);

    m_player.setPlaylist(playlist);

    m_player.play();
}

Form::~Form()
{
	m_thread.quit();
	m_thread.wait();
}
