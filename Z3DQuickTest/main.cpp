#include "quickVtkViewer.hpp"

#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QWindow>

#include <QVTKOpenGLWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkConeSource.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>

#include <pcl/visualization/pcl_visualizer.h>

int main(int argc, char *argv[])
{
    // before initializing QApplication, set the default surface format.
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<quick::Vtk::Viewer>("QuickVTK", 1, 0, "VtkViewer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    auto rootObject = engine.rootObjects().at(0);
    auto window = static_cast<QWindow*>(rootObject);

    QList<quick::Vtk::Viewer*> vtkItems = window->findChildren<quick::Vtk::Viewer*>();

    boost::shared_ptr<pcl::visualization::PCLVisualizer> m_pclViewer;

    // For demonstration: Add a cone to the scene of each Viewer
    vtkNew<vtkConeSource> polyDataSource;
    polyDataSource->SetResolution(100);
    vtkNew<vtkPolyDataMapper> mapper;
    vtkNew<vtkActor> actor;
    mapper->SetInputConnection(polyDataSource->GetOutputPort());
    actor->SetMapper(mapper.Get());
    actor->GetProperty()->SetOpacity(0.5); // demonstrate support for translucent VTK objects

    for (auto *vtkItem : vtkItems) {
        auto *renderWindow = vtkItem->GetRenderWindow();
        auto *renderer = renderWindow->GetRenderers()->GetFirstRenderer();

        m_pclViewer.reset(new pcl::visualization::PCLVisualizer(renderer, renderWindow, "3D", false));
        m_pclViewer->addCoordinateSystem();

        renderer->AddActor(actor.Get());
    }

    return app.exec();
}
