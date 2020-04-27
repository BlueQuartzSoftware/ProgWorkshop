/*
 * Your License or Copyright can go here
 */

#include "Lesson4.h"

#include <QtCore/QTextStream>

#include "SIMPLib/Common/Constants.h"

#include "SIMPLib/FilterParameters/DataArrayCreationFilterParameter.h"
#include "SIMPLib/FilterParameters/DataArraySelectionFilterParameter.h"
#include "SIMPLib/FilterParameters/FloatFilterParameter.h"
#include "SIMPLib/FilterParameters/ChoiceFilterParameter.h"
#include "SIMPLib/FilterParameters/LinkedBooleanFilterParameter.h"
#include "SIMPLib/DataContainers/DataContainerArray.h"

#include "ProgWorkshop/ProgWorkshopConstants.h"
#include "ProgWorkshop/ProgWorkshopVersion.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson4::Lesson4()
: // Initialize all your filter parameters here.  SIMPL has a Constants file that developers can use to help set common names.
    m_InputDataArrayPath(SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName, SIMPL::CellData::ConfidenceIndex)
, m_OutputDataArrayPath(SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName, "CI_Mod")
, m_Value(234.0f)
, m_Operator(0)
, m_Selection(false)
, m_FloatValue(128.123f)
{
  initialize();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson4::~Lesson4() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson4::initialize()
{
  clearErrorCode();
  setCancel(false);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson4::setupFilterParameters()
{
  FilterParameterVectorType parameters;
  //-- Add a Requirement to the input array that is be of type float and 1 component
  DataArraySelectionFilterParameter::RequirementType dasReq = DataArraySelectionFilterParameter::CreateCategoryRequirement(SIMPL::TypeNames::Float, 1, AttributeMatrix::Category::Any);
  parameters.push_back(SIMPL_NEW_DA_SELECTION_FP("InputDataArrayPath", InputDataArrayPath, FilterParameter::RequiredArray, Lesson4, dasReq));
  DataArrayCreationFilterParameter::RequirementType dacReq;
  parameters.push_back(SIMPL_NEW_DA_CREATION_FP("OutputDataArrayPath", OutputDataArrayPath, FilterParameter::CreatedArray, Lesson4, dacReq));
  parameters.push_back(SIMPL_NEW_FLOAT_FP("Value", Value, FilterParameter::Parameter, Lesson4));

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
    parameters.push_back(SIMPL_NEW_CHOICE_FP("Operator", Operator, FilterParameter::Parameter, Lesson4, choices, false));
  }

  QStringList linkedProps("FloatValue");
  parameters.push_back(SIMPL_NEW_LINKED_BOOL_FP("Linked Bool", Selection, FilterParameter::Parameter, Lesson4, linkedProps));
  parameters.push_back(SIMPL_NEW_FLOAT_FP("Float Value", FloatValue, FilterParameter::Parameter, Lesson4));


  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson4::dataCheck()
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

  if(getOperator() < 0 || getOperator() > 3)
  {
    setErrorCondition(-10001, "The operator can only have values of 0,1,2,3");
  }

  if(getSelection())
  {
    if(getFloatValue() < 100 || getFloatValue() > 200)
    {
      setErrorCondition(-10002, "FloatValue should be in the range of 100 to 200");
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson4::execute()
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

  // Use the LinkedBoolean in a calculation
  if(getSelection())
  {
    for(size_t i = 0; i < numTuples; i++)
    {
      m_OutputData[i] = m_OutputData[i] - m_FloatValue;
    }
  }

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AbstractFilter::Pointer Lesson4::newFilterInstance(bool copyFilterParameters) const
{
  Lesson4::Pointer filter = Lesson4::New();
  if(copyFilterParameters)
  {
    copyFilterParameterInstanceVariables(filter.get());
  }
  return filter;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson4::getCompiledLibraryName() const
{
  return ProgWorkshopConstants::ProgWorkshopBaseName;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson4::getBrandingString() const
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson4::getFilterVersion() const
{
  QString version;
  QTextStream vStream(&version);
  vStream << ProgWorkshop::Version::Major() << "." << ProgWorkshop::Version::Minor() << "." << ProgWorkshop::Version::Patch();
  return version;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson4::getGroupName() const
{
  return SIMPL::FilterGroups::Unsupported;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QUuid Lesson4::getUuid() const
{
  return QUuid("{43bceb39-849d-5c9a-a75c-5ef958908007}");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson4::getSubGroupName() const
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson4::getHumanLabel() const
{
  return "Lesson4";
}

// -----------------------------------------------------------------------------
Lesson4::Pointer Lesson4::NullPointer()
{
  return Pointer(static_cast<Self*>(nullptr));
}

// -----------------------------------------------------------------------------
std::shared_ptr<Lesson4> Lesson4::New()
{
  struct make_shared_enabler : public Lesson4
  {
  };
  std::shared_ptr<make_shared_enabler> val = std::make_shared<make_shared_enabler>();
  val->setupFilterParameters();
  return val;
}

// -----------------------------------------------------------------------------
QString Lesson4::getNameOfClass() const
{
  return QString("Lesson4");
}

// -----------------------------------------------------------------------------
QString Lesson4::ClassName()
{
  return QString("Lesson4");
}

// -----------------------------------------------------------------------------
void Lesson4::setInputDataArrayPath(const DataArrayPath& value)
{
  m_InputDataArrayPath = value;
}

// -----------------------------------------------------------------------------
DataArrayPath Lesson4::getInputDataArrayPath() const
{
  return m_InputDataArrayPath;
}

// -----------------------------------------------------------------------------
void Lesson4::setOutputDataArrayPath(const DataArrayPath& value)
{
  m_OutputDataArrayPath = value;
}

// -----------------------------------------------------------------------------
DataArrayPath Lesson4::getOutputDataArrayPath() const
{
  return m_OutputDataArrayPath;
}

// -----------------------------------------------------------------------------
void Lesson4::setValue(float value)
{
  m_Value = value;
}

// -----------------------------------------------------------------------------
float Lesson4::getValue() const
{
  return m_Value;
}

// -----------------------------------------------------------------------------
void Lesson4::setOperator(int value)
{
  m_Operator = value;
}

// -----------------------------------------------------------------------------
int Lesson4::getOperator() const
{
  return m_Operator;
}

// -----------------------------------------------------------------------------
void Lesson4::setSelection(bool value)
{
  m_Selection = value;
}

// -----------------------------------------------------------------------------
bool Lesson4::getSelection() const
{
  return m_Selection;
}

// -----------------------------------------------------------------------------
void Lesson4::setFloatValue(float value)
{
  m_FloatValue = value;
}

// -----------------------------------------------------------------------------
float Lesson4::getFloatValue() const
{
  return m_FloatValue;
}
