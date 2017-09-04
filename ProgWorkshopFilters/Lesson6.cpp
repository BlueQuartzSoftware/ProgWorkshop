/*
 * Your License or Copyright can go here
 */

#include "Lesson6.h"

#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/Geometry/ImageGeom.h"
#include "SIMPLib/FilterParameters/DataContainerSelectionFilterParameter.h"

#include "ProgWorkshop/ProgWorkshopConstants.h"
#include "ProgWorkshop/ProgWorkshopVersion.h"

// Include the MOC generated file for this class
#include "moc_Lesson6.cpp"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson6::Lesson6()
: AbstractFilter()
{
  initialize();
  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson6::~Lesson6()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson6::initialize()
{
  setErrorCondition(0);
  setCancel(false);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson6::setupFilterParameters()
{
  FilterParameterVector parameters;

  //************************
  // The DataContainer object is the only object that can hold a Geometry object
  // so ask the user to select a DataContainer
  DataContainerSelectionFilterParameter::RequirementType dcReq;
  // Require a DataContainer that holds an ImageGeom object.
  IGeometry::Types geomTypes = {IGeometry::Type::Image};
  dcReq.dcGeometryTypes = geomTypes;
  // Add the FilterParameter so that it shows up in the GUI
  parameters.push_back(SIMPL_NEW_DC_SELECTION_FP("Geometry", GeometrySelection, FilterParameter::RequiredArray, Lesson6, dcReq));

  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson6::dataCheck()
{
  setErrorCondition(0);
  
  //--------------
  // Get the ImageGeometry object from the selected DataContainer. If we can't get
  // it or the downcast does not work then we will get a nullptr wrapped in the
  // shared_ptr;
  DataContainer::Pointer dc = getDataContainerArray()->getDataContainer(getGeometrySelection());
  if(nullptr != dc.get())
  {
    ImageGeom::Pointer image = dc->getGeometryAs<ImageGeom>();
    if(image.get() == nullptr)
    {
      setErrorCondition(-10010);
      notifyErrorMessage(getHumanLabel(), "Selected DataContainer does not have an ImageGeom object.", getErrorCondition());
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson6::preflight()
{
  // These are the REQUIRED lines of CODE to make sure the filter behaves correctly
  setInPreflight(true);              // Set the fact that we are preflighting.
  emit preflightAboutToExecute();    // Emit this signal so that other widgets can do one file update
  emit updateFilterParameters(this); // Emit this signal to have the widgets push their values down to the filter
  dataCheck();                       // Run our DataCheck to make sure everthing is setup correctly
  emit preflightExecuted();          // We are done preflighting this filter
  setInPreflight(false);             // Inform the system this filter is NOT in preflight mode anymore.
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson6::execute()
{
  initialize();
  dataCheck();
  if(getErrorCondition() < 0)
  {
    return;
  }

  if(getCancel() == true)
  {
    return;
  }

  // This should work because we just did the same thing in the dataCheck();
  ImageGeom::Pointer image = getDataContainerArray()->getDataContainer(getGeometrySelection())->getGeometryAs<ImageGeom>();
  // Get the Dimensions
  size_t dims[] = {0, 0, 0};
  image->getDimensions(dims);
  float origin[] = {0.0f, 0.0f, 0.0f};
  image->getOrigin(origin);

  float resolution[] = {1.0f, 1.0f, 1.0f};
  image->getResolution(resolution);

  // DREAM3D/SIMPL store the dimensions as XYZ
  for(size_t z = 0; z < dims[2]; z++)
  {

    for(size_t y = 0; y < dims[1]; y++)
    {

      for(size_t x = 0; x < dims[0]; x++)
      {

        size_t index = (z * dims[1] * dims[0]) + (y * dims[0]) + x;
        // *****************************
        // You now have an XYZ coordinate. You can calculate something, perform
        // an analysis or something else
        // *****************************

      }
    }
  }

  notifyStatusMessage(getHumanLabel(), "Complete");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AbstractFilter::Pointer Lesson6::newFilterInstance(bool copyFilterParameters)
{
  Lesson6::Pointer filter = Lesson6::New();
  if(true == copyFilterParameters)
  {
    copyFilterParameterInstanceVariables(filter.get());
  }
  return filter;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson6::getCompiledLibraryName()
{
  return ProgWorkshopConstants::ProgWorkshopBaseName;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson6::getBrandingString()
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson6::getFilterVersion()
{
  QString version;
  QTextStream vStream(&version);
  vStream << ProgWorkshop::Version::Major() << "." << ProgWorkshop::Version::Minor() << "." << ProgWorkshop::Version::Patch();
  return version;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson6::getGroupName()
{
  return SIMPL::FilterGroups::Unsupported;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson6::getSubGroupName()
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson6::getHumanLabel()
{
  return "Lesson6";
}
