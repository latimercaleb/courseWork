#ifndef GLWINDOW_H
#define GLWINDOW_H
#include <QtOpenGL/QGLWidget>
class GlWindow : public QGLWidget
{
    Q_OBJECT
public:
    explicit GlWindow(QWidget *parent = 0);
    ~GlWindow();
signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    void draw();

    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;
/*public:
    glwindow();*/
};

#endif // GLWINDOW_H
