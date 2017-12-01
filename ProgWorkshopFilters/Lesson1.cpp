/*
 * Your License or Copyright can go here
 */

#include "Lesson1.h"

#include "SIMPLib/Common/Constants.h"

#include "SIMPLib/FilterParameters/DataArrayCreationFilterParameter.h"
#include "SIMPLib/FilterParameters/DataArraySelectionFilterParameter.h"
#include "SIMPLib/FilterParameters/FloatFilterParameter.h"

#include "ProgWorkshop/ProgWorkshopConstants.h"
#include "ProgWorkshop/ProgWorkshopVersion.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson1::Lesson1()
: AbstractFilter(),
  // Initialize all your filter parameters here.  SIMPL has a Constants file that developers can use to help set common names.
  m_InputDataArrayPath(SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName, SIMPL::CellData::ConfidenceIndex),
  m_OutputDataArrayPath(SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName, "Lesson1_Output"),
  m_Value(0.0f)
{
  initialize();
  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson1::~Lesson1() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson1::initialize()
{
  setErrorCondition(0);
  setCancel(false);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson1::setupFilterParameters()
{
  FilterParameterVector parameters;
  DataArraySelectionFilterParameter::RequirementType dasReq;
  parameters.push_back(SIMPL_NEW_DA_SELECTION_FP("InputDataArrayPath", InputDataArrayPath, FilterParameter::RequiredArray, Lesson1, dasReq));
  DataArrayCreationFilterParameter::RequirementType dacReq;
  parameters.push_back(SIMPL_NEW_DA_CREATION_FP("OutputDataArrayPath", OutputDataArrayPath, FilterParameter::CreatedArray, Lesson1, dacReq));
  parameters.push_back(SIMPL_NEW_FLOAT_FP("Value", Value, FilterParameter::Parameter, Lesson1));
  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson1::dataCheck()
{
  // Reset the error condition to ZERO
  setErrorCondition(0);

  /* This method should be used to sanity all the filter parameters to make sure
   * they meet your expectations
   */

  //-- Validate the Input Array
  // Be sure to add  DEFINE_DATAARRAY_VARIABLE(float, InputData)  in the header in the private section
  // m_InputData is a **RAW** pointer which is both dangerous and fast
  // An error message will be broadcasted if there are any errors
  QVector<size_t> cDims = {1}; // Single component Array
  m_InputDataPtr = getDataContainerArray()->getPrereqArrayFromPath<FloatArrayType, AbstractFilter>(this, getInputDataArrayPath(), cDims);
  /* Validate the Weak Pointer wraps a non-nullptr pointer to a DataArray<T> object */
  if(nullptr != m_InputDataPtr.lock().get())
  {
    m_InputData = m_InputDataPtr.lock()->getPointer(0);/* Now assign the raw pointer to data from the DataArray<T> object */
  }

  //-- Validate the Output Array
  // Be sure to add  DEFINE_DATAARRAY_VARIABLE(float, OutputArray)  in the header in the private section
  cDims[0] = 1; // This is not necessary because we are creating a Single Component Array
  m_OutputDataPtr = getDataContainerArray()->createNonPrereqArrayFromPath<FloatArrayType, AbstractFilter, float>(this, getOutputDataArrayPath(), 0, cDims);
  /* Validate the Weak Pointer wraps a non-nullptr pointer to a DataArray<T> object */
  if(nullptr != m_OutputDataPtr.lock().get())
  {
    m_OutputData = m_OutputDataPtr.lock()->getPointer(0);/* Now assign the raw pointer to data from the DataArray<T> object */
  }

  if(getValue() < 0.0f)
  {
    setErrorCondition(-10000);
    notifyErrorMessage(getHumanLabel(), "Float value must be greater than 0.0", getErrorCondition());
  }

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson1::preflight()
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
void Lesson1::execute()
{
  initialize();
  dataCheck();
  if(getErrorCondition() < 0)
  {
    return;
  }

  // If your filters are going to take a while to run you should check for the
  // pipeline being canceled. You could potentially put this into the loop below
  // to check every iteration if you wanted to.
  if(getCancel() == true)
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


  if(getErrorCondition() < 0)
  {
    QString ss = QObject::tr("An error occurred during the execution of the filter.");
    setErrorCondition(-100001);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
    return;
  }

  notifyStatusMessage(getHumanLabel(), "Complete");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AbstractFilter::Pointer Lesson1::newFilterInstance(bool copyFilterParameters)
{
  Lesson1::Pointer filter = Lesson1::New();
  if(true == copyFilterParameters)
  {
    copyFilterParameterInstanceVariables(filter.get());
  }
  return filter;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson1::getCompiledLibraryName()
{
  return ProgWorkshopConstants::ProgWorkshopBaseName;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson1::getBrandingString()
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson1::getFilterVersion()
{
  QString version;
  QTextStream vStream(&version);
  vStream << ProgWorkshop::Version::Major() << "." << ProgWorkshop::Version::Minor() << "." << ProgWorkshop::Version::Patch();
  return version;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson1::getGroupName()
{
  return SIMPL::FilterGroups::Unsupported;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson1::getSubGroupName()
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson1::getHumanLabel()
{
  return "Lesson1";
}
