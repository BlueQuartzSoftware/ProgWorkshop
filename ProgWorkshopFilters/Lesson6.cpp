/*
 * Your License or Copyright can go here
 */

#include "Lesson6.h"

#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/Geometry/ImageGeom.h"
#include "SIMPLib/FilterParameters/DataContainerSelectionFilterParameter.h"

#include "ProgWorkshop/ProgWorkshopConstants.h"
#include "ProgWorkshop/ProgWorkshopVersion.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson6::Lesson6()
{
  initialize();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson6::~Lesson6() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson6::initialize()
{
  clearErrorCondition();
  setCancel(false);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson6::setupFilterParameters()
{
  FilterParameterVectorType parameters;

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
  clearErrorCondition();

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
      notifyErrorMessage("Selected DataContainer does not have an ImageGeom object.", getErrorCondition());
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

  if(getCancel())
  {
    return;
  }

  // This should work because we just did the same thing in the dataCheck();
  ImageGeom::Pointer image = getDataContainerArray()->getDataContainer(getGeometrySelection())->getGeometryAs<ImageGeom>();
  // Get the Dimensions
  size_t dims[] = {0, 0, 0};
  std::tie(dims[0], dims[1], dims[2]) = image->getDimensions();
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

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AbstractFilter::Pointer Lesson6::newFilterInstance(bool copyFilterParameters) const
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
const QString Lesson6::getCompiledLibraryName() const
{
  return ProgWorkshopConstants::ProgWorkshopBaseName;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson6::getBrandingString() const
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson6::getFilterVersion() const
{
  QString version;
  QTextStream vStream(&version);
  vStream << ProgWorkshop::Version::Major() << "." << ProgWorkshop::Version::Minor() << "." << ProgWorkshop::Version::Patch();
  return version;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson6::getGroupName() const
{
  return SIMPL::FilterGroups::Unsupported;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QUuid Lesson6::getUuid()
{
  return QUuid("{b2eb2376-9c34-5744-bbb3-05c8874a3a31}");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson6::getSubGroupName() const
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson6::getHumanLabel() const
{
  return "Lesson6";
}
