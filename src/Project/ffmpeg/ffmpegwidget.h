#pragma once

#include <functional>

#include <QtWidgets>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QImage>
#include <QTimer>
#include "ffmpegplayer.h"

/**
* @brief FFmpegWidget class
* 继承了QOpenGLWidget，同步绘制到opengl缓冲区，没有memcpy
*/

class FFmpegWidget : public QOpenGLWidget, protected QOpenGLFunctions, public FFmpegPlayer
{
    Q_OBJECT
public:
    FFmpegWidget(QWidget *parent = nullptr);
protected:
    void on_preview_start(const std::string& media_url, const int width, const int height) override;
    void on_preview_stop(const std::string& media_url) override;
    void on_recorder_start(const std::string& file) override;
    void on_recorder_stop(const std::string& file) override;
    void on_new_frame_avaliable(std::shared_ptr<FrameCache> m_frame_cache) override;
private:
    void setup_viewport(int view_w, int view_h);
    GLuint textureID;
    int viewport_x = 0, viewport_y = 0, viewport_w = 0, viewport_h = 0;
    float aspectRatio = 0;
    std::mutex render_mutex;
public slots:
    int start_preview(const std::string &media_url);
    int stop_preview();
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
signals:
    void sig_on_preview_start(const QString &media_url, const int width, const int heigh);
    void sig_on_preview_stop(const QString &media_url);
    void sig_on_record_start(const QString& file);
    void sig_on_record_stop(const QString& file);

};
