#pragma once

#include <QQuickFramebufferObject>

#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <QMouseEvent>

class FboOffscreenWindow;

class FboRenderer : public QQuickFramebufferObject::Renderer
{
	friend class FboOffscreenWindow;

public:
	explicit FboRenderer(FboOffscreenWindow*);
	~FboRenderer();

	auto synchronize(QQuickFramebufferObject*) -> void override;
	auto render() -> void override;
	auto onMouseEvent(QMouseEvent*) -> void;
	auto createFramebufferObject(const QSize&) -> QOpenGLFramebufferObject* override;

private:
	FboOffscreenWindow* m_fboOffscreenWindow;
	QOpenGLFramebufferObject* m_fbo;
	vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> m_interactorStyle;
};
