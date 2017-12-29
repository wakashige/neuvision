#include "quickVtkWin32Interactor.hpp"

#ifdef _MSC_VER

#include <vtkWin32OpenGLRenderWindow.h>
#include <vtkObjectFactory.h>

#include <QDebug>

vtkStandardNewMacro(Win32Interactor)

void Win32Interactor::Initialize()
{
	qDebug() << Q_FUNC_INFO;

	if (!RenderWindow) {
		vtkErrorMacro(<< "No renderer defined!");
		return;
	}

	if (Initialized) {
		return;
	}

	Initialized = 1;

	vtkWin32OpenGLRenderWindow* ren = (vtkWin32OpenGLRenderWindow *)(RenderWindow);
	ren->Start();

	auto size = ren->GetSize();
	ren->GetPosition();
	WindowId = 0;
	Enable();
	Size[0] = size[0];
	Size[1] = size[1];
}

#endif
