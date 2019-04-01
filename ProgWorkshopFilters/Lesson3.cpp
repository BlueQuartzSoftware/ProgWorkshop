/*
 * Your License or Copyright can go here
 */

#include "Lesson3.h"

#include "SIMPLib/Common/Constants.h"

#include "SIMPLib/FilterParameters/DataArrayCreationFilterParameter.h"
#include "SIMPLib/FilterParameters/DataArraySelectionFilterParameter.h"
#include "SIMPLib/FilterParameters/FloatFilterParameter.h"
#include "SIMPLib/FilterParameters/ChoiceFilterParameter.h"

#include "ProgWorkshop/ProgWorkshopConstants.h"
#include "ProgWorkshop/ProgWorkshopVersion.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson3::Lesson3()
: // Initialize all your filter parameters here.  SIMPL has a Constants file that developers can use to help set common names.
    m_InputDataArrayPath(SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName, "Fit")
, m_OutputDataArrayPath(SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName, "Fit_Modified")
, m_Value(45.0f)
, m_Operator(2)
{
  initialize();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson3::~Lesson3() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson3::initialize()
{
  clearErrorCondition();
  setCancel(false);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson3::setupFilterParameters()
{
  FilterParameterVectorType parameters;
  //-- Add a Requirement to the input array that is be of type float and 1 component
  DataArraySelectionFilterParameter::RequirementType dasReq = DataArraySelectionFilterParameter::CreateCategoryRequirement(SIMPL::TypeNames::Float, 1, AttributeMatrix::Category::Any);

  parameters.push_back(SIMPL_NEW_DA_SELECTION_FP("InputDataArrayPath", InputDataArrayPath, FilterParameter::RequiredArray, Lesson3, dasReq));
  DataArrayCreationFilterParameter::RequirementType dacReq;
  parameters.push_back(SIMPL_NEW_DA_CREATION_FP("OutputDataArrayPath", OutputDataArrayPath, FilterParameter::CreatedArray, Lesson3, dacReq));
  parameters.push_back(SIMPL_NEW_FLOAT_FP("Value", Value, FilterParameter::Parameter, Lesson3));

  // When adding a Choice FilterParameter you need to define the choices first
  // What goes into the choices can be statically coded (Like below) or dynamically
  // computed based on something. EMsoft has an example of this.
  {
    QVector<QString> choices;
    choices.push_back("*");
    choices.push_back("/");
    choices.push_back("+");
    choices.push_back("-");
    // Create the Choice Filter Parameter and add it to the list of parameters
    parameters.push_back(SIMPL_NEW_CHOICE_FP("Operator", Operator, FilterParameter::Parameter, Lesson3, choices, false));
  }


  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson3::dataCheck()
{
  // Reset the error condition to ZERO
  clearErrorCondition();

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
  if(nullptr != m_InputDataPtr.lock())
  {
    m_InputData = m_InputDataPtr.lock()->getPointer(0);/* Now assign the raw pointer to data from the DataArray<T> object */
  }

  //-- Validate the Output Array
  // Be sure to add  DEFINE_DATAARRAY_VARIABLE(float, OutputArray)  in the header in the private section
  cDims[0] = 1; // This is not necessary because we are creating a Single Component Array
  m_OutputDataPtr = getDataContainerArray()->createNonPrereqArrayFromPath<FloatArrayType, AbstractFilter, float>(this, getOutputDataArrayPath(), 0, cDims);
  /* Validate the Weak Pointer wraps a non-nullptr pointer to a DataArray<T> object */
  if(nullptr != m_OutputDataPtr.lock())
  {
    m_OutputData = m_OutputDataPtr.lock()->getPointer(0);/* Now assign the raw pointer to data from the DataArray<T> object */
  }

  if(getValue() < 0.0f)
  {
    setErrorCondition(-10000, "Float value must be greater than 0.0");
  }

  if(getOperator() < 0 || getOperator() > 3)
  {
    setErrorCondition(-10001, "The operator can only have values of 0,1,2,3");
  }

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson3::preflight()
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
void Lesson3::execute()
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
  if(getCancel())
  {
    return;
  }

  // Loop on every Tuple in the InputArray, mulitply by the Value and place in the
  // OutputArray. There are already several variables and raw pointers setup for
  // you in the header that we can use.
  /****************************************************************************/
  // This is the Raw Pointer Version of the loop. It will be fast, but dangerous
  // because there is NO bounds checking when setting the value. If you walk off
  // the end of the array your program will likely crash or just give bad results.
  /****************************************************************************/
  size_t numTuples = m_InputDataPtr.lock()->getNumberOfTuples();
  int op = getOperator();
  if(op == 0)
  {
    for(size_t i = 0; i < numTuples; i++)
    {
      m_OutputData[i] = m_InputData[i] * m_Value;
    }
  }
  else if(op == 1)
  {
    for(size_t i = 0; i < numTuples; i++)
    {
      m_OutputData[i] = m_InputData[i] / m_Value;
    }
  }
  else if(op == 2)
  {
    for(size_t i = 0; i < numTuples; i++)
    {
      m_OutputData[i] = m_InputData[i] + m_Value;
    }
  }
  else if (op == 3)
  {
    for(size_t i = 0; i < numTuples; i++)
    {
      m_OutputData[i] = m_InputData[i] - m_Value;
    }
  }
  else
  {
    QString ss = QObject::tr("The correct operator was not set. Valid values are 0,1,2,3");
    setErrorCondition(-100001, ss);
    return;
  }


}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AbstractFilter::Pointer Lesson3::newFilterInstance(bool copyFilterParameters) const
{
  Lesson3::Pointer filter = Lesson3::New();
  if(true == copyFilterParameters)
  {
    copyFilterParameterInstanceVariables(filter.get());
  }
  return filter;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson3::getCompiledLibraryName() const
{
  return ProgWorkshopConstants::ProgWorkshopBaseName;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson3::getBrandingString() const
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson3::getFilterVersion() const
{
  QString version;
  QTextStream vStream(&version);
  vStream << ProgWorkshop::Version::Major() << "." << ProgWorkshop::Version::Minor() << "." << ProgWorkshop::Version::Patch();
  return version;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson3::getGroupName() const
{
  return SIMPL::FilterGroups::Unsupported;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QUuid Lesson3::getUuid()
{
  return QUuid("{c712cd5a-5223-58a8-a0bd-14c06009b2ed}");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson3::getSubGroupName() const
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Lesson3::getHumanLabel() const
{
  return "Lesson3";
}
