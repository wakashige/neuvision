#pragma once

#include <QtQuick/QQuickFramebufferObject>

class vtkGenericOpenGLRenderWindow;
class QVTKFramebufferObjectRenderer;

class QVTKFrameBufferObjectItem : public QQuickFramebufferObject
{
   Q_OBJECT

public:
   QVTKFrameBufferObjectItem();
   ~QVTKFrameBufferObjectItem();
   Renderer *createRenderer() const;
   vtkGenericOpenGLRenderWindow* GetRenderWindow() const;

protected:
   // Called once before the FBO is created for the first time. This method is
   // called from render thread while the GUI thread is blocked.
   virtual void init();

   vtkGenericOpenGLRenderWindow *m_win;

   friend class QVTKFramebufferObjectRenderer;
};
