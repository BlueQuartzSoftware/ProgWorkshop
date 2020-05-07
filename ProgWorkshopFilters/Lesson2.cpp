/*
 * Your License or Copyright can go here
 */

#include "Lesson2.h"

#include <QtCore/QTextStream>

#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/FilterParameters/DataArrayCreationFilterParameter.h"
#include "SIMPLib/FilterParameters/DataArraySelectionFilterParameter.h"
#include "SIMPLib/FilterParameters/FloatFilterParameter.h"
#include "SIMPLib/DataContainers/DataContainerArray.h"

#include "ProgWorkshop/ProgWorkshopConstants.h"
#include "ProgWorkshop/ProgWorkshopVersion.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson2::Lesson2()
: // Initialize all your filter parameters here.  SIMPL has a Constants file that developers can use to help set common names.
    m_InputDataArrayPath(SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName, SIMPL::CellData::ConfidenceIndex)
, m_OutputDataArrayPath(SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName, "Lesson2_Output")
, m_Value(0.0f)
{
  initialize();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson2::~Lesson2() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson2::initialize()
{
  clearErrorCode();
  setCancel(false);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson2::setupFilterParameters()
{
  FilterParameterVectorType parameters;
  //-- Add a Requirement to the input array that is be of type float and 1 component
  DataArraySelectionFilterParameter::RequirementType dasReq = DataArraySelectionFilterParameter::CreateCategoryRequirement(SIMPL::TypeNames::Float, 1, AttributeMatrix::Category::Any);

  parameters.push_back(SIMPL_NEW_DA_SELECTION_FP("InputDataArrayPath", InputDataArrayPath, FilterParameter::RequiredArray, Lesson2, dasReq));
  DataArrayCreationFilterParameter::RequirementType dacReq;
  parameters.push_back(SIMPL_NEW_DA_CREATION_FP("OutputDataArrayPath", OutputDataArrayPath, FilterParameter::CreatedArray, Lesson2, dacReq));
  parameters.push_back(SIMPL_NEW_FLOAT_FP("Value", Value, FilterParameter::Parameter, Lesson2));
  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson2::dataCheck()
{
  // Reset the error condition to ZERO
  clearErrorCode();

  /* This method should be used to sanity all the filter parameters to make sure
   * they meet your expectations
   */

  //-- Validate the Input Array
  // Be sure to add  DEFINE_DATAARRAY_VARIABLE(float, InputData)  in the header in the private section
  // m_InputData is a **RAW** pointer which is both dangerous and fast
  // An error message will be broadcasted if there are any errors
  std::vector<size_t> cDims = {1}; // Single component Array
  m_InputDataPtr = getDataContainerArray()->getPrereqArrayFromPath<FloatArrayType>(this, getInputDataArrayPath(), cDims);
  /* Validate the Weak Pointer wraps a non-nullptr pointer to a DataArray<T> object */
  if(nullptr != m_InputDataPtr.lock())
  {
    m_InputData = m_InputDataPtr.lock()->getPointer(0);/* Now assign the raw pointer to data from the DataArray<T> object */
  }

  //-- Validate the Output Array
  // Be sure to add  DEFINE_DATAARRAY_VARIABLE(float, OutputArray)  in the header in the private section
  cDims[0] = 1; // This is not necessary because we are creating a Single Component Array
  m_OutputDataPtr = getDataContainerArray()->createNonPrereqArrayFromPath<FloatArrayType>(this, getOutputDataArrayPath(), 0, cDims);
  /* Validate the Weak Pointer wraps a non-nullptr pointer to a DataArray<T> object */
  if(nullptr != m_OutputDataPtr.lock())
  {
    m_OutputData = m_OutputDataPtr.lock()->getPointer(0);/* Now assign the raw pointer to data from the DataArray<T> object */
  }

  if(getValue() < 0.0f)
  {
    setErrorCondition(-10000, "Float value must be greater than 0.0");
  }

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson2::execute()
{
  initialize();
  dataCheck();
  if(getErrorCode() < 0)
  {
    return;
  }

  // If your filters are going to take a while to run you should check for the
  // pipeline being canceled. You could potentially put this into the loop below
  // to check every iteration if you wanted to.
  if(getCancel())
  {
    return;
  }

  // Loop on every Tuple in the InputArray, mulitply by the Value and place in the
  // OutputArray. There are already several variables and raw pointers setup for
  // you in the header that we can use.
#if 1
  /****************************************************************************/
  // This is the Raw Pointer Version of the loop. It will be fast, but dangerous
  // because there is NO bounds checking when setting the value. If you walk off
  // the end of the array your program will likely crash or just give bad results.
  /****************************************************************************/
  size_t numTuples = m_InputDataPtr.lock()->getNumberOfTuples();
  for(size_t i = 0; i < numTuples; i++)
  {
    m_OutputData[i] = m_InputData[i] * m_Value;
  }
#else
  /****************************************************************************/
  // This is the safer but slower version of the same loop
  /****************************************************************************/
  FloatArrayType::Pointer input = m_InputDataPtr.lock(); // Convert the weak pointer to shared_ptr
  FloatArrayType::Pointer output = m_OutputDataPtr.lock(); // Convert the weak pointer to shared_ptr
  for(size_t i = 0; i < numTuples; i++)
  {
    float f = input->getComponent(i, 0);
    output->setTuple(i, &f); // Note we are sending in the "Address of f", which is a pointer
  }
#endif

  if(getErrorCode() < 0)
  {
    QString ss = QObject::tr("An error occurred during the execution of the filter.");
    setErrorCondition(-100001, ss);
    return;
  }

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AbstractFilter::Pointer Lesson2::newFilterInstance(bool copyFilterParameters) const
{
  Lesson2::Pointer filter = Lesson2::New();
  if(copyFilterParameters)
  {
    copyFilterParameterInstanceVariables(filter.get());
  }
  return filter;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson2::getCompiledLibraryName() const
{
  return ProgWorkshopConstants::ProgWorkshopBaseName;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson2::getBrandingString() const
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson2::getFilterVersion() const
{
  QString version;
  QTextStream vStream(&version);
  vStream << ProgWorkshop::Version::Major() << "." << ProgWorkshop::Version::Minor() << "." << ProgWorkshop::Version::Patch();
  return version;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson2::getGroupName() const
{
  return SIMPL::FilterGroups::Unsupported;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QUuid Lesson2::getUuid() const
{
  return QUuid("{f5295d39-4563-5a71-927d-3c0f5e36702a}");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson2::getSubGroupName() const
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson2::getHumanLabel() const
{
  return "Lesson2";
}

// -----------------------------------------------------------------------------
Lesson2::Pointer Lesson2::NullPointer()
{
  return Pointer(static_cast<Self*>(nullptr));
}

// -----------------------------------------------------------------------------
std::shared_ptr<Lesson2> Lesson2::New()
{
  struct make_shared_enabler : public Lesson2
  {
  };
  std::shared_ptr<make_shared_enabler> val = std::make_shared<make_shared_enabler>();
  val->setupFilterParameters();
  return val;
}

// -----------------------------------------------------------------------------
QString Lesson2::getNameOfClass() const
{
  return QString("Lesson2");
}

// -----------------------------------------------------------------------------
QString Lesson2::ClassName()
{
  return QString("Lesson2");
}

// -----------------------------------------------------------------------------
void Lesson2::setInputDataArrayPath(const DataArrayPath& value)
{
  m_InputDataArrayPath = value;
}

// -----------------------------------------------------------------------------
DataArrayPath Lesson2::getInputDataArrayPath() const
{
  return m_InputDataArrayPath;
}

// -----------------------------------------------------------------------------
void Lesson2::setOutputDataArrayPath(const DataArrayPath& value)
{
  m_OutputDataArrayPath = value;
}

// -----------------------------------------------------------------------------
DataArrayPath Lesson2::getOutputDataArrayPath() const
{
  return m_OutputDataArrayPath;
}

// -----------------------------------------------------------------------------
void Lesson2::setValue(float value)
{
  m_Value = value;
}

// -----------------------------------------------------------------------------
float Lesson2::getValue() const
{
  return m_Value;
}
