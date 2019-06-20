/*
 * Your License or Copyright can go here
 */

#include "Lesson7.h"

#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/FilterParameters/DataContainerSelectionFilterParameter.h"
#include "SIMPLib/Geometry/TriangleGeom.h"

#include "ProgWorkshop/ProgWorkshopConstants.h"
#include "ProgWorkshop/ProgWorkshopVersion.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson7::Lesson7() :
  AbstractFilter()
{
  initialize();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson7::~Lesson7() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson7::initialize()
{
  clearErrorCode();
  setCancel(false);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson7::setupFilterParameters()
{
  FilterParameterVectorType parameters;

  DataContainerSelectionFilterParameter::RequirementType dcReq;
  IGeometry::Types geomTypes = {IGeometry::Type::Triangle};
  dcReq.dcGeometryTypes = geomTypes;
  parameters.push_back(SIMPL_NEW_DC_SELECTION_FP("Geometry", GeometrySelection, FilterParameter::RequiredArray, Lesson7, dcReq));


  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson7::dataCheck()
{
  clearErrorCode();

  //--------------
  // Get the TriangleGeom object from the selected DataContainer. If we can't get
  // it or the downcast does not work then we will get a nullptr wrapped in the
  // shared_ptr;
  DataContainer::Pointer dc = getDataContainerArray()->getDataContainer(getGeometrySelection());
  if(nullptr != dc.get())
  {
    TriangleGeom::Pointer triGeom = dc->getGeometryAs<TriangleGeom>();
    if(triGeom.get() == nullptr)
    {
      setErrorCondition(-10010, "Selected DataContainer does not have an TriangleGeom object.");
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson7::preflight()
{
  // These are the REQUIRED lines of CODE to make sure the filter behaves correctly
  setInPreflight(true); // Set the fact that we are preflighting.
  emit preflightAboutToExecute(); // Emit this signal so that other widgets can do one file update
  emit updateFilterParameters(this); // Emit this signal to have the widgets push their values down to the filter
  dataCheck(); // Run our DataCheck to make sure everthing is setup correctly
  emit preflightExecuted(); // We are done preflighting this filter
  setInPreflight(false); // Inform the system this filter is NOT in preflight mode anymore.
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson7::execute()
{
  initialize();
  dataCheck();
  if(getErrorCode() < 0)
  {
    return;
  }

  if (getCancel() == true) { return; }

  TriangleGeom::Pointer triGeom = getDataContainerArray()->getDataContainer(getGeometrySelection())->getGeometryAs<TriangleGeom>();
  SharedVertexList::Pointer vertices = triGeom->getVertices();
  SharedTriList::Pointer triangles = triGeom->getTriangles();


  size_t numVerts = vertices->getNumberOfTuples();
  for(size_t v = 0; v < numVerts; v++)
  {
    float* vert = vertices->getTuplePointer(v); // Get the pointer to the specific Vertex
    // Now we can get or set the individual XYZ coordinate of the vertex using
    // [] notation;

    // vert[0] = ....
    // vert[1] = ....
    // vert[2] = ....

  }


  // We can loop over all the Triangles also
  size_t numTris = triangles->getNumberOfTuples();
  for(size_t t = 0; t < numTris; t++)
  {
    MeshIndexType* tri = triangles->getTuplePointer(t); // get a pointer to the indices that make up Triangle 't'

    // We could then loop on each vertex of the triangle
    for(size_t v = 0; v < 3; v++)
    {
      size_t vertIndex = tri[v];

      float* vert = vertices->getTuplePointer(vertIndex); // Get the pointer to the specific Vertex
      // Do something with the vertex like calculate the centroid?
      // .....
    }

  }

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AbstractFilter::Pointer Lesson7::newFilterInstance(bool copyFilterParameters) const
{
  Lesson7::Pointer filter = Lesson7::New();
  if(copyFilterParameters)
  {
    copyFilterParameterInstanceVariables(filter.get());
  }
  return filter;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson7::getCompiledLibraryName() const
{ return ProgWorkshopConstants::ProgWorkshopBaseName; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson7::getBrandingString() const
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson7::getFilterVersion() const
{
  QString version;
  QTextStream vStream(&version);
  vStream <<  ProgWorkshop::Version::Major() << "." << ProgWorkshop::Version::Minor() << "." << ProgWorkshop::Version::Patch();
  return version;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson7::getGroupName() const
{ return SIMPL::FilterGroups::Unsupported; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QUuid Lesson7::getUuid()
{
  return QUuid("{a4b86d5f-d812-50d9-8d95-3f3f5fcb0597}");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson7::getSubGroupName() const
{ return "ProgWorkshop"; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson7::getHumanLabel() const
{ return "Lesson7"; }

