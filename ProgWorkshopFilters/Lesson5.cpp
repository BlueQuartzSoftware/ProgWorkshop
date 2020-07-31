/*
 * Your License or Copyright can go here
 */

#include "Lesson5.h"

#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/FilterParameters/ChoiceFilterParameter.h"
#include "SIMPLib/FilterParameters/DataArrayCreationFilterParameter.h"
#include "SIMPLib/FilterParameters/DataArraySelectionFilterParameter.h"
#include "SIMPLib/FilterParameters/FloatFilterParameter.h"
#include "SIMPLib/FilterParameters/LinkedBooleanFilterParameter.h"
#include "SIMPLib/Utilities/ParallelDataAlgorithm.h"
#include "SIMPLib/DataContainers/DataContainerArray.h"

#include "ProgWorkshop/ProgWorkshopConstants.h"
#include "ProgWorkshop/ProgWorkshopVersion.h"

/**
 * @brief The Lesson5Impl class implements a threaded algorithm that computes the IPF
 * colors for each element in a geometry
 */
class Lesson5Impl
{
public:
  Lesson5Impl(float* input, float* output, int operation, float value, bool selection, float fValue)
  : m_Input(input)
  , m_Output(output)
  , m_Operation(operation)
  , m_Value(value)
  , m_Selection(selection)
  , m_FValue(fValue)
  {
  }

  virtual ~Lesson5Impl() = default;

  void convert(size_t start, size_t end) const
  {
    if(m_Operation == 0)
    {
      for(size_t i = start; i < end; i++)
      {
        m_Output[i] = m_Input[i] * m_Value;
      }
    }
    else if(m_Operation == 1)
    {
      for(size_t i = start; i < end; i++)
      {
        m_Output[i] = m_Input[i] / m_Value;
      }
    }
    else if(m_Operation == 2)
    {
      for(size_t i = start; i < end; i++)
      {
        m_Output[i] = m_Input[i] + m_Value;
      }
    }
    else if (m_Operation == 3)
    {
      for(size_t i = start; i < end; i++)
      {
        m_Output[i] = m_Input[i] - m_Value;
      }
    }

    // Use the LinkedBoolean in a calculation
    if(m_Selection)
    {
      for(size_t i = start; i < end; i++)
      {
        m_Output[i] = m_Output[i] - m_FValue;
      }
    }
  }

  void operator()(const SIMPLRange& range) const
  {
    convert(range.min(), range.max());
  }

private:
  float* m_Input;
  float* m_Output;
  int m_Operation;
  float m_Value;
  bool m_Selection;
  float m_FValue;

};


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson5::Lesson5()
: // Initialize all your filter parameters here.  SIMPL has a Constants file that developers can use to help set common names.
    m_InputDataArrayPath(SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName, SIMPL::CellData::ImageQuality)
, m_OutputDataArrayPath(SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName, "IQ_Mod")
, m_Value(12342.1f)
, m_Operator(1)
, m_FloatValue(128.128f)
{
  initialize();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Lesson5::~Lesson5() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson5::initialize()
{
  clearErrorCode();
  setCancel(false);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson5::setupFilterParameters()
{
  FilterParameterVectorType parameters;
  //-- Add a Requirement to the input array that is be of type float and 1 component
  DataArraySelectionFilterParameter::RequirementType dasReq = DataArraySelectionFilterParameter::CreateCategoryRequirement(SIMPL::TypeNames::Float, 1, AttributeMatrix::Category::Any);
  parameters.push_back(SIMPL_NEW_DA_SELECTION_FP("InputDataArrayPath", InputDataArrayPath, FilterParameter::RequiredArray, Lesson5, dasReq));
  DataArrayCreationFilterParameter::RequirementType dacReq;
  parameters.push_back(SIMPL_NEW_DA_CREATION_FP("OutputDataArrayPath", OutputDataArrayPath, FilterParameter::CreatedArray, Lesson5, dacReq));
  parameters.push_back(SIMPL_NEW_FLOAT_FP("Value", Value, FilterParameter::Parameter, Lesson5));

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
    parameters.push_back(SIMPL_NEW_CHOICE_FP("Operator", Operator, FilterParameter::Parameter, Lesson5, choices, false));
  }

  QStringList linkedProps("FloatValue");
  parameters.push_back(SIMPL_NEW_LINKED_BOOL_FP("Linked Bool", Selection, FilterParameter::Parameter, Lesson5, linkedProps));
  parameters.push_back(SIMPL_NEW_FLOAT_FP("Float Value", FloatValue, FilterParameter::Parameter, Lesson5));


  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Lesson5::dataCheck()
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

  if(nullptr != m_InputDataPtr.lock())
  {
    m_InputData = m_InputDataPtr.lock()->getPointer(0);/* Now assign the raw pointer to data from the DataArray<T> object */
  }

  //-- Validate the Output Array
  // Be sure to add  DEFINE_DATAARRAY_VARIABLE(float, OutputArray)  in the header in the private section
  cDims[0] = 1; // This is not necessary because we are creating a Single Component Array
  m_OutputDataPtr = getDataContainerArray()->createNonPrereqArrayFromPath<FloatArrayType>(this, getOutputDataArrayPath(), 0, cDims);

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
void Lesson5::execute()
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

  // Allow data-based parallelization
  ParallelDataAlgorithm dataAlg;
  dataAlg.setRange(0, numTuples);
  dataAlg.execute(Lesson5Impl(m_InputData, m_OutputData, m_Operator, m_Value, m_Selection, m_FloatValue));
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AbstractFilter::Pointer Lesson5::newFilterInstance(bool copyFilterParameters) const
{
  Lesson5::Pointer filter = Lesson5::New();
  if(copyFilterParameters)
  {
    copyFilterParameterInstanceVariables(filter.get());
  }
  return filter;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson5::getCompiledLibraryName() const
{
  return ProgWorkshopConstants::ProgWorkshopBaseName;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson5::getBrandingString() const
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson5::getFilterVersion() const
{
  QString version;
  QTextStream vStream(&version);
  vStream << ProgWorkshop::Version::Major() << "." << ProgWorkshop::Version::Minor() << "." << ProgWorkshop::Version::Patch();
  return version;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson5::getGroupName() const
{
  return SIMPL::FilterGroups::Unsupported;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QUuid Lesson5::getUuid() const
{
  return QUuid("{169f34c2-62b2-57cf-ac79-9067dbac0d73}");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson5::getSubGroupName() const
{
  return "ProgWorkshop";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString Lesson5::getHumanLabel() const
{
  return "Lesson5";
}

// -----------------------------------------------------------------------------
Lesson5::Pointer Lesson5::NullPointer()
{
  return Pointer(static_cast<Self*>(nullptr));
}

// -----------------------------------------------------------------------------
std::shared_ptr<Lesson5> Lesson5::New()
{
  struct make_shared_enabler : public Lesson5
  {
  };
  std::shared_ptr<make_shared_enabler> val = std::make_shared<make_shared_enabler>();
  val->setupFilterParameters();
  return val;
}

// -----------------------------------------------------------------------------
QString Lesson5::getNameOfClass() const
{
  return QString("Lesson5");
}

// -----------------------------------------------------------------------------
QString Lesson5::ClassName()
{
  return QString("Lesson5");
}

// -----------------------------------------------------------------------------
void Lesson5::setInputDataArrayPath(const DataArrayPath& value)
{
  m_InputDataArrayPath = value;
}

// -----------------------------------------------------------------------------
DataArrayPath Lesson5::getInputDataArrayPath() const
{
  return m_InputDataArrayPath;
}

// -----------------------------------------------------------------------------
void Lesson5::setOutputDataArrayPath(const DataArrayPath& value)
{
  m_OutputDataArrayPath = value;
}

// -----------------------------------------------------------------------------
DataArrayPath Lesson5::getOutputDataArrayPath() const
{
  return m_OutputDataArrayPath;
}

// -----------------------------------------------------------------------------
void Lesson5::setValue(float value)
{
  m_Value = value;
}

// -----------------------------------------------------------------------------
float Lesson5::getValue() const
{
  return m_Value;
}

// -----------------------------------------------------------------------------
void Lesson5::setOperator(int value)
{
  m_Operator = value;
}

// -----------------------------------------------------------------------------
int Lesson5::getOperator() const
{
  return m_Operator;
}

// -----------------------------------------------------------------------------
void Lesson5::setSelection(bool value)
{
  m_Selection = value;
}

// -----------------------------------------------------------------------------
bool Lesson5::getSelection() const
{
  return m_Selection;
}

// -----------------------------------------------------------------------------
void Lesson5::setFloatValue(float value)
{
  m_FloatValue = value;
}

// -----------------------------------------------------------------------------
float Lesson5::getFloatValue() const
{
  return m_FloatValue;
}
