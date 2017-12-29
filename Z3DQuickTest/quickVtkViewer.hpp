#pragma once

#include <QQuickFramebufferObject>

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkProp.h>

class FboRenderer;
class vtkGenericOpenGLRenderWindow;

class Viewer : public QQuickFramebufferObject
{
	Q_OBJECT

	Q_PROPERTY(bool hoverEnabled READ getHoverEnabled WRITE setHoverEnabled NOTIFY hoverEnabledChanged)
	Q_PROPERTY(bool mouseEnabled READ getMouseEnabled WRITE setMouseEnabled NOTIFY mouseEnabledChanged)
	Q_CLASSINFO("DefaultProperty", "input")

public:
	explicit Viewer();
	~Viewer();

	Renderer *createRenderer() const override;
	vtkGenericOpenGLRenderWindow* GetRenderWindow() const;

	virtual auto init() -> void;
	auto update() -> void;
	auto setHoverEnabled(bool) -> void;
	auto setMouseEnabled(bool) -> void;
	auto getHoverEnabled() -> bool;
	auto getMouseEnabled() -> bool;

signals:
	void inputChanged();
	void hoverEnabledChanged();
	void mouseEnabledChanged();

protected:
	mutable FboRenderer *m_fboRenderer;
	vtkGenericOpenGLRenderWindow *m_win;

	auto mousePressEvent(QMouseEvent*) -> void override;
	auto mouseReleaseEvent(QMouseEvent*) -> void override;
	auto mouseMoveEvent(QMouseEvent*) -> void override;
	auto hoverMoveEvent(QHoverEvent*) -> void override;

private:
	friend class FboRenderer;

	bool m_initialized;
	bool m_hoverEnabled;
	bool m_mouseEnabled;
	vtkSmartPointer<vtkRenderer> m_renderer;
};
