#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)


#include <vtkPolyData.h>
#include <vtkPLYReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkLODActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkGlyph3DMapper.h>
#include <vtkRegularPolygonSource.h>
#include <vtkDataSetAttributes.h>
#include <vtkProperty.h>

/*
int main ( int argc, char *argv[] )
{
	if(argc != 2) {
		std::cout << "Usage: " << argv[0] << "  Filename(.ply)" << std::endl;
		return EXIT_FAILURE;
	}

	std::string inputFilename = argv[1];

	vtkSmartPointer<vtkPLYReader> reader = vtkSmartPointer<vtkPLYReader>::New();
	reader->SetFileName( inputFilename.c_str() );



	// Visualize
//	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//	mapper->SetInputConnection(reader->GetOutputPort());

//	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//	actor->SetMapper(mapper);



	reader->Update();
	auto polyData = reader->GetOutput();

	std::cout << "points: " << polyData->GetNumberOfPoints() << std::endl;
	std::cout << "polys: " << polyData->GetNumberOfPolys() << std::endl;

	/// we'll show each point as a small polygon.
	vtkSmartPointer<vtkRegularPolygonSource> polygonSource = vtkSmartPointer<vtkRegularPolygonSource>::New();
	polygonSource->GeneratePolylineOff(); // don't add border
	polygonSource->SetNumberOfSides(6);
	polygonSource->SetRadius(1);
	polygonSource->SetCenter(0, 0, 0);
	polygonSource->SetNormal(1, 0, 0);

	/// add the polygon to each point
	vtkSmartPointer<vtkGlyph3DMapper> glyph = vtkSmartPointer<vtkGlyph3DMapper>::New();
	glyph->SetInputData(polyData);
	glyph->SetSourceConnection(polygonSource->GetOutputPort());
	glyph->OrientOn();
	glyph->SetOrientationArray(vtkDataSetAttributes::NORMALS);
	glyph->SetOrientationModeToDirection();
	glyph->SetScaleFactor(0.1);
	glyph->SetScaleModeToNoDataScaling();

	vtkSmartPointer<vtkLODActor> actor = vtkSmartPointer<vtkLODActor>::New();
	actor->SetMapper(glyph);

	auto property = actor->GetProperty();
	property->BackfaceCullingOff();
	property->SetRepresentationToSurface();
	property->EdgeVisibilityOff();
	property->SetInterpolationToFlat();
	property->ShadingOff();
	property->SetSpecular(0.0);
	property->SetDiffuse(0.5);
	property->SetAmbient(0.7);




	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	renderWindow->AlphaBitPlanesOff();
	renderWindow->PointSmoothingOff();
	renderWindow->LineSmoothingOff();
	renderWindow->PolygonSmoothingOff();
	renderWindow->SwapBuffersOn();
	renderWindow->SetStereoTypeToAnaglyph();

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderer->AddActor(actor);
	renderer->GradientBackgroundOn();
	renderer->SetBackground(0.9,0.9,0.9);
	renderer->SetBackground2(0.7,0.7,0.7);

	renderWindow->Render();

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New(); //like paraview
//	style->UseTimersOn();

	renderWindowInteractor->SetDesiredUpdateRate(30.0);
	renderWindowInteractor->SetInteractorStyle( style );

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
*/



#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkColorTransferFunction.h"
#include "vtkDataObject.h"
#include "vtkDataSetAttributes.h"
#include "vtkNew.h"
#include "vtkPiecewiseFunction.h"
#include "vtkPointGaussianMapper.h"
#include "vtkPointCloudFilter.h"
#include "vtkPointSource.h"
#include "vtkProperty.h"
#include "vtkRandomAttributeGenerator.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSphereSource.h"
#include "vtkTimerLog.h"

#include <vtkVertexGlyphFilter.h>
#include <vtkOpenGLPolyDataMapper.h>
#include <vtkPolyDataNormals.h>

int main(int argc, char *argv[])
{
	/*
  int desiredPoints = 1.0e4;

  vtkNew<vtkPointSource> points;
  points->SetNumberOfPoints(desiredPoints);
  points->SetRadius(pow(desiredPoints,0.33)*10.0);
  points->Update();
*/


	if(argc != 2) {
		std::cout << "Usage: " << argv[0] << "  Filename(.ply)" << std::endl;
		return EXIT_FAILURE;
	}

	std::string inputFilename = argv[1];

	vtkSmartPointer<vtkPLYReader> reader = vtkSmartPointer<vtkPLYReader>::New();
	reader->SetFileName( inputFilename.c_str() );



	// Visualize
	//	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	//	mapper->SetInputConnection(reader->GetOutputPort());

	//	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	//	actor->SetMapper(mapper);



	reader->Update();
	auto polyData = reader->GetOutput();

	/// generate normals
	vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
	normalGenerator->SetInputData(polyData);
	normalGenerator->ComputePointNormalsOn();
	normalGenerator->ComputeCellNormalsOff();
	normalGenerator->Update();

	polyData = normalGenerator->GetOutput();

	std::cout << "points: " << polyData->GetNumberOfPoints() << std::endl;
	std::cout << "polys: " << polyData->GetNumberOfPolys() << std::endl;
	/*
	vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
	vertexFilter->SetInputData(polyData);
	vertexFilter->Update();

	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->ShallowCopy(vertexFilter->GetOutput());
*/

	//	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkNew<vtkOpenGLPolyDataMapper> mapper;


	//  vtkNew<vtkRandomAttributeGenerator> randomAttr;
	//  randomAttr->SetInputConnection(points->GetOutputPort());

//	vtkNew<vtkPointGaussianMapper> mapper;

	vtkNew<vtkRenderer> renderer;
	renderer->SetBackground(0.5, 0.5, 0.5);
	vtkNew<vtkRenderWindow> renderWindow;
	renderWindow->SetSize(300, 300);
	renderWindow->SetMultiSamples(0);
	renderWindow->AddRenderer(renderer);
	vtkNew<vtkRenderWindowInteractor>  renderWindowInteractor;
	renderWindowInteractor->SetRenderWindow(renderWindow);

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New(); //like paraview
	//	style->UseTimersOn();

	renderWindowInteractor->SetDesiredUpdateRate(30.0);
	renderWindowInteractor->SetInteractorStyle( style );

/*
	{
		vtkNew<vtkPolyDataMapper> mapper;
		mapper->SetInputData(polyData);
		vtkNew<vtkActor> actor;
		renderer->AddActor(actor);
		actor->SetMapper(mapper);
		actor->GetProperty()->SetDiffuseColor(1.0, 0.65, 0.7);
		actor->GetProperty()->SetSpecular(0.5);
		actor->GetProperty()->SetDiffuse(0.7);
		actor->GetProperty()->SetSpecularPower(20.0);
		actor->GetProperty()->RenderPointsAsSpheresOn();
		actor->GetProperty()->SetPointSize(10.0);
		actor->GetProperty()->SetRepresentationToPoints();
	}
*/

/*
  randomAttr->SetDataTypeToFloat();
  randomAttr->GeneratePointScalarsOn();
  randomAttr->GeneratePointVectorsOn();
  randomAttr->GeneratePointArrayOn();
  randomAttr->Update();

  mapper->SetInputConnection(randomAttr->GetOutputPort());*/
	mapper->SetInputData(polyData);
	/*
//  mapper->SetColorModeToMapScalars();
//  mapper->SetScalarModeToUsePointFieldData();
//  mapper->SelectColorArray("RandomPointVectors");
//  mapper->SetInterpolateScalarsBeforeMapping(0);
//  mapper->SetScaleArray("RandomPointScalars");
//  mapper->SetScaleArrayComponent(1);
//  mapper->SetOpacityArray("RandomPointArray");
//  mapper->SetOpacityArrayComponent(0);
  mapper->EmissiveOff();

  // show other shader examples
  // the fragment that is rendered is that of a triangle
  // large enough to encompass a circle of radius 3


  mapper->SetSplatShaderCode(
	// this first line keeps the default color opacity calcs
	// which you can then modify with additional code below
	"//VTK::Color::Impl\n"

	// example of a circle with black edges
	 "  float dist = sqrt(dot(offsetVCVSOutput.xy,offsetVCVSOutput.xy));\n"
	 "  if (dist > 1.1) { discard; }\n"
//     "  if (dist < 0.5) { discard; }\n"
	 // apply a black edge around the circle
//     "  if (dist > 1.0 || dist < 0.6) { diffuseColor = vec3(0,0,0); ambientColor = vec3(0,0,0); }\n"

	// example for a square
//    "  if (abs(offsetVCVSOutput.x) > 1.0 || abs(offsetVCVSOutput.y) > 1.0) { discard; }\n"
//    "  if (abs(offsetVCVSOutput.x) < 0.6 && abs(offsetVCVSOutput.y) < 0.6) { discard; }\n"
	);

  // since this shader only uses a radus of sqrt(2) we will adjust the mapper
  // to render a smaller area than the default radius of 3.0
//  mapper->SetTriangleScale(1.5);
  mapper->SetScaleFactor(0.05);
*/



	vtkNew<vtkActor> actor;
	actor->SetMapper(mapper);
/*
	actor->GetProperty()->VertexVisibilityOn();
	actor->GetProperty()->EdgeVisibilityOff();
	actor->GetProperty()->ShadingOn();
	actor->GetProperty()->SetVertexColor(1.0, 0.5, 1.0);
  actor->GetProperty()->SetPointSize(14.0);
*/

//	actor->GetProperty()->SetPointSize(2);
	actor->GetProperty()->SetRepresentationToPoints();
//	actor->GetProperty()->SetInterpolationToPhong();
	renderer->AddActor(actor);


/*
	actor->GetProperty()->SetAmbientColor(0.2, 0.2, 1.0);
	actor->GetProperty()->SetDiffuseColor(1.0, 0.65, 0.7);
	actor->GetProperty()->SetSpecularColor(1.0, 1.0, 1.0);
	actor->GetProperty()->SetSpecular(0.5);
	actor->GetProperty()->SetDiffuse(0.7);
	actor->GetProperty()->SetAmbient(0.5);
	actor->GetProperty()->SetSpecularPower(20.0);
	actor->GetProperty()->SetOpacity(1.0);




	// Modify the shader to color based on model normal
	// To do this we have to modify the vertex shader
	// to pass the normal in model coordinates
	// through to the fragment shader. By default the normal
	// is converted to View coordinates and then passed on.
	// We keep that, but add a varying for the original normal.
	// Then we modify the fragment shader to set the diffuse color
	// based on that normal. First lets modify the vertex
	// shader
	mapper->AddShaderReplacement(
	  vtkShader::Vertex,
	  "//VTK::Normal::Dec", // replace the normal block
	  true, // before the standard replacements
	  "//VTK::Normal::Dec\n" // we still want the default
	  "  varying vec3 myNormalMCVSOutput;\n", //but we add this
	  false // only do it once
	  );
	mapper->AddShaderReplacement(
	  vtkShader::Vertex,
	  "//VTK::Normal::Impl", // replace the normal block
	  true, // before the standard replacements
	  "//VTK::Normal::Impl\n" // we still want the default
	  "  myNormalMCVSOutput = normalMC;\n", //but we add this
	  false // only do it once
	  );
//	mapper->AddShaderReplacement(
//	  vtkShader::Vertex,
//	  "//VTK::Color::Impl", // dummy replacement for testing clear method
//	  true,
//	  "VTK::Color::Impl\n",
//	  false
//	  );
//	mapper->ClearShaderReplacement(
//	  vtkShader::Vertex,     // clear our dummy replacement
//	  "//VTK::Color::Impl",
//	  true
//	  );

	// now modify the fragment shader
	mapper->AddShaderReplacement(
	  vtkShader::Fragment,  // in the fragment shader
	  "//VTK::Normal::Dec", // replace the normal block
	  true, // before the standard replacements
	  "//VTK::Normal::Dec\n" // we still want the default
	  "  varying vec3 myNormalMCVSOutput;\n", //but we add this
	  false // only do it once
	  );
	mapper->AddShaderReplacement(
	  vtkShader::Fragment,  // in the fragment shader
	  "//VTK::Normal::Impl", // replace the normal block
	  true, // before the standard replacements
	  "//VTK::Normal::Impl\n" // we still want the default calc
	  "  diffuseColor = abs(myNormalMCVSOutput);\n", //but we add this
//	  "  diffuseColor = vec3(0,0,0);\n", //but we add this
	  false // only do it once
	);

*/



	vtkNew<vtkTimerLog> timer;
	timer->StartTimer();
	renderWindow->Render();
	timer->StopTimer();
	double firstRender = timer->GetElapsedTime();
	cerr << "first render time: " << firstRender << endl;
	/*
  timer->StartTimer();
  int numRenders = 85;
  for (int i = 0; i < numRenders; ++i)
  {
	renderer->GetActiveCamera()->Azimuth(1);
	renderer->GetActiveCamera()->Elevation(1);
	renderWindow->Render();
  }
  timer->StopTimer();
  double elapsed = timer->GetElapsedTime();

  int numPts = mapper->GetInput()->GetPoints()->GetNumberOfPoints();
  cerr << "interactive render time: " << elapsed / numRenders << endl;
  cerr << "number of points: " <<  numPts << endl;
  cerr << "points per second: " <<  numPts*(numRenders/elapsed) << endl;
*/
	renderer->GetActiveCamera()->SetPosition(0,0,1);
	renderer->GetActiveCamera()->SetFocalPoint(0,0,0);
	renderer->GetActiveCamera()->SetViewUp(0,1,0);
	renderer->ResetCamera();
	//  renderer->GetActiveCamera()->Print(cerr);

	renderer->GetActiveCamera()->Zoom(2.0);
	renderWindow->Render();


	renderWindowInteractor->Start();


	return EXIT_SUCCESS;
}
