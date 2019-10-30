/*
 * Your License or Copyright can go here
 */

#include "Lesson6.h"

#include <QtCore/QTextStream>

#include "SIMPLib/Common/Constants.h"

#include "SIMPLib/Geometry/ImageGeom.h"
#include "SIMPLib/FilterParameters/DataContainerSelectionFilterParameter.h"
#include "SIMPLib/DataContainers/DataContainerArray.h"
#include "SIMPLib/DataContainers/DataContainer.h"

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
  clearErrorCode();
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
  clearErrorCode();

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
      setErrorCondition(-10010, "Selected DataContainer does not have an ImageGeom object.");
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
  if(getErrorCode() < 0)
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
  SizeVec3Type dims = image->getDimensions();
  FloatVec3Type origin = image->getOrigin();
  FloatVec3Type spacing = image->getSpacing();

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
  if(copyFilterParameters)
  {
    copyFilterParameterInstanceVariables(filter.get());
  }
  return filter;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson6::getCompiledLibraryName() const
{
  return ProgWorkshopConstants::ProgWorkshopBaseName;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson6::getBrandingString() const
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson6::getFilterVersion() const
{
  QString version;
  QTextStream vStream(&version);
  vStream << ProgWorkshop::Version::Major() << "." << ProgWorkshop::Version::Minor() << "." << ProgWorkshop::Version::Patch();
  return version;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson6::getGroupName() const
{
  return SIMPL::FilterGroups::Unsupported;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QUuid Lesson6::getUuid() const
{
  return QUuid("{b2eb2376-9c34-5744-bbb3-05c8874a3a31}");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson6::getSubGroupName() const
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson6::getHumanLabel() const
{
  return "Lesson6";
}

// -----------------------------------------------------------------------------
Lesson6::Pointer Lesson6::NullPointer()
{
  return Pointer(static_cast<Self*>(nullptr));
}

// -----------------------------------------------------------------------------
std::shared_ptr<Lesson6> Lesson6::New()
{
  struct make_shared_enabler : public Lesson6
  {
  };
  std::shared_ptr<make_shared_enabler> val = std::make_shared<make_shared_enabler>();
  val->setupFilterParameters();
  return val;
}

// -----------------------------------------------------------------------------
QString Lesson6::getNameOfClass() const
{
  return QString("Lesson6");
}

// -----------------------------------------------------------------------------
QString Lesson6::ClassName()
{
  return QString("Lesson6");
}

// -----------------------------------------------------------------------------
void Lesson6::setGeometrySelection(const DataArrayPath& value)
{
  m_GeometrySelection = value;
}

// -----------------------------------------------------------------------------
DataArrayPath Lesson6::getGeometrySelection() const
{
  return m_GeometrySelection;
}
