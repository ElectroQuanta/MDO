#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMediaPlayer>
#include <QWidget>

//QT_BEGIN_NAMESPACE
class QAbstractButton;
class QSlider;
//class QGraphicsVideoItem;
//QT_END_NAMESPACE

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();

    void load(const QUrl &url);
    bool isPlayerAvailable() const;

    QSize sizeHint() const override;

public slots:
    void openFile();
    void play();

private slots:
    void mediaStateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void rotateVideo(int angle);

private:
    QMediaPlayer *m_mediaPlayer = nullptr;
    QGraphicsVideoItem *m_videoItem = nullptr;
    QAbstractButton *m_playButton = nullptr;
    QSlider *m_positionSlider = nullptr;
};

#endif

