/*
 * Your License or Copyright can go here
 */

#ifndef _lesson5_h_
#define _lesson5_h_

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/Filtering/AbstractFilter.h"
#include "SIMPLib/SIMPLib.h"

/**
 * @brief The Lesson5 class. See [Filter documentation](@ref lesson5) for details.
 */
class Lesson5 : public AbstractFilter
{
  Q_OBJECT
  PYB11_CREATE_BINDINGS(Lesson5 SUPERCLASS AbstractFilter)
  PYB11_PROPERTY(DataArrayPath InputDataArrayPath READ getInputDataArrayPath WRITE setInputDataArrayPath)
  PYB11_PROPERTY(DataArrayPath OutputDataArrayPath READ getOutputDataArrayPath WRITE setOutputDataArrayPath)
  PYB11_PROPERTY(float Value READ getValue WRITE setValue)
  PYB11_PROPERTY(int Operator READ getOperator WRITE setOperator)
  PYB11_PROPERTY(bool Selection READ getSelection WRITE setSelection)
  PYB11_PROPERTY(float FloatValue READ getFloatValue WRITE setFloatValue)

public:
  SIMPL_SHARED_POINTERS(Lesson5)
  SIMPL_FILTER_NEW_MACRO(Lesson5)
  SIMPL_TYPE_MACRO_SUPER_OVERRIDE(Lesson5, AbstractFilter)

  ~Lesson5() override;

  SIMPL_FILTER_PARAMETER(DataArrayPath, InputDataArrayPath)
  Q_PROPERTY(DataArrayPath InputDataArrayPath READ getInputDataArrayPath WRITE setInputDataArrayPath)

  SIMPL_FILTER_PARAMETER(DataArrayPath, OutputDataArrayPath)
  Q_PROPERTY(DataArrayPath OutputDataArrayPath READ getOutputDataArrayPath WRITE setOutputDataArrayPath)

  SIMPL_FILTER_PARAMETER(float, Value)
  Q_PROPERTY(float Value READ getValue WRITE setValue)

  SIMPL_FILTER_PARAMETER(int, Operator)
  Q_PROPERTY(int Operator READ getOperator WRITE setOperator)

  SIMPL_FILTER_PARAMETER(bool, Selection)
  Q_PROPERTY(bool Selection READ getSelection WRITE setSelection)

  SIMPL_FILTER_PARAMETER(float, FloatValue)
  Q_PROPERTY(float FloatValue READ getFloatValue WRITE setFloatValue)

  /**
   * @brief getCompiledLibraryName Reimplemented from @see AbstractFilter class
   */
  const QString getCompiledLibraryName() const override;

  /**
   * @brief getBrandingString Returns the branding string for the filter, which is a tag
   * used to denote the filter's association with specific plugins
   * @return Branding string
   */
  const QString getBrandingString() const override;

  /**
   * @brief getFilterVersion Returns a version string for this filter. Default
   * value is an empty string.
   * @return
   */
  const QString getFilterVersion() const override;

  /**
   * @brief newFilterInstance Reimplemented from @see AbstractFilter class
   */
  AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) const override;

  /**
   * @brief getGroupName Reimplemented from @see AbstractFilter class
   */
  const QString getGroupName() const override;

  /**
   * @brief getSubGroupName Reimplemented from @see AbstractFilter class
   */
  const QString getSubGroupName() const override;

  /**
   * @brief getUuid Return the unique identifier for this filter.
   * @return A QUuid object.
   */
  const QUuid getUuid() override;

  /**
   * @brief getHumanLabel Reimplemented from @see AbstractFilter class
   */
  const QString getHumanLabel() const override;

  /**
   * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
   */
  void setupFilterParameters() override;

  /**
   * @brief execute Reimplemented from @see AbstractFilter class
   */
  void execute() override;

  /**
   * @brief preflight Reimplemented from @see AbstractFilter class
   */
  void preflight() override;

signals:
  /**
   * @brief updateFilterParameters Emitted when the Filter requests all the latest Filter parameters
   * be pushed from a user-facing control (such as a widget)
   * @param filter Filter instance pointer
   */
  void updateFilterParameters(AbstractFilter* filter);

  /**
   * @brief parametersChanged Emitted when any Filter parameter is changed internally
   */
  void parametersChanged();

  /**
   * @brief preflightAboutToExecute Emitted just before calling dataCheck()
   */
  void preflightAboutToExecute();

  /**
   * @brief preflightExecuted Emitted just after calling dataCheck()
   */
  void preflightExecuted();

protected:
  Lesson5();

  /**
   * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
   */
  void dataCheck();

  /**
   * @brief Initializes all the private instance variables.
   */
  void initialize();

private:
  DEFINE_DATAARRAY_VARIABLE(float, InputData)
  DEFINE_DATAARRAY_VARIABLE(float, OutputData)

public:
  Lesson5(const Lesson5&) = delete;            // Copy Constructor Not Implemented
  Lesson5(Lesson5&&) = delete;                 // Move Constructor
  Lesson5& operator=(const Lesson5&) = delete; // Copy Assignment Not Implemented
  Lesson5& operator=(Lesson5&&) = delete;      // Move Assignment
};

#endif /* _Lesson5_H_ */
