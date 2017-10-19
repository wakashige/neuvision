#include "quickVtkViewer.hpp"

#include "quickVtkFboRenderer.hpp"
#include "quickVtkFboOffscreenWindow.hpp"

#include <QOpenGLFunctions>
#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>

namespace quick {

    namespace Vtk {

        Viewer::Viewer() {
            this->m_renderer = 0;
            m_win = FboOffscreenWindow::New();

            this->setMirrorVertically(true);
        }

        auto Viewer::init() -> void {
            auto rw = this->GetRenderWindow();
            this->m_renderer = vtkSmartPointer<vtkRenderer>::New();
            rw->AddRenderer(m_renderer);
            this->m_initialized = true;

            this->update();
        }
        
        auto Viewer::update() -> void {
            if (!this->m_initialized) {
                return;
            }

            if (this->m_fboRenderer) {
                QQuickFramebufferObject::update();
            }
        }

        auto Viewer::setHoverEnabled(bool hoverEnabled) -> void {
            this->m_hoverEnabled = hoverEnabled;

            setAcceptHoverEvents(hoverEnabled);

            emit this->hoverEnabledChanged();
        }

        auto Viewer::setMouseEnabled(bool mouseEnabled) -> void {
            this->m_mouseEnabled = mouseEnabled;

            if (mouseEnabled) {
                setAcceptedMouseButtons(Qt::AllButtons);
            }
            else {
                setAcceptedMouseButtons(Qt::NoButton);
            }

            emit this->mouseEnabledChanged();
        }

        auto Viewer::mousePressEvent(QMouseEvent* event) -> void {
            if (this->m_fboRenderer) {
                this->m_fboRenderer->onMouseEvent(event);
            }
        }

        auto Viewer::mouseReleaseEvent(QMouseEvent* event) -> void {
            if (this->m_fboRenderer) {
                this->m_fboRenderer->onMouseEvent(event);
            }
        }

        auto Viewer::mouseMoveEvent(QMouseEvent* event) -> void {
            if (this->m_fboRenderer) {
                this->m_fboRenderer->onMouseEvent(event);
            }
        }

        auto Viewer::hoverMoveEvent(QHoverEvent* event) -> void {
        }

        auto Viewer::createRenderer() const -> QQuickFramebufferObject::Renderer* {
            this->m_fboRenderer = new FboRenderer(static_cast<FboOffscreenWindow*>(m_win));

            return this->m_fboRenderer;
        }

        auto Viewer::GetRenderWindow() const -> vtkGenericOpenGLRenderWindow* {
            return m_win;
        }

        auto Viewer::getHoverEnabled() -> bool {
            return this->m_hoverEnabled;
        }

        auto Viewer::getMouseEnabled() -> bool {
            return this->m_mouseEnabled;
        }

        Viewer::~Viewer() {
            m_win->Delete();
        }
    }
}
