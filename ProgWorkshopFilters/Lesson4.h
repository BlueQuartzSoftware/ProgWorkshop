/*
 * Your License or Copyright can go here
 */

#pragma once

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/Filtering/AbstractFilter.h"
#include "SIMPLib/DataArrays/DataArray.hpp"

#include "ProgWorkshop/ProgWorkshopDLLExport.h"

/**
 * @brief The Lesson4 class. See [Filter documentation](@ref lesson4) for details.
 */
class ProgWorkshop_EXPORT Lesson4 : public AbstractFilter
{
  Q_OBJECT

  // Start Python bindings declarations
  PYB11_BEGIN_BINDINGS(Lesson4 SUPERCLASS AbstractFilter)
  PYB11_SHARED_POINTERS(Lesson4)
  PYB11_FILTER_NEW_MACRO(Lesson4)
  PYB11_PROPERTY(DataArrayPath InputDataArrayPath READ getInputDataArrayPath WRITE setInputDataArrayPath)
  PYB11_PROPERTY(DataArrayPath OutputDataArrayPath READ getOutputDataArrayPath WRITE setOutputDataArrayPath)
  PYB11_PROPERTY(float Value READ getValue WRITE setValue)
  PYB11_PROPERTY(int Operator READ getOperator WRITE setOperator)
  PYB11_PROPERTY(bool Selection READ getSelection WRITE setSelection)
  PYB11_PROPERTY(float FloatValue READ getFloatValue WRITE setFloatValue)
  PYB11_END_BINDINGS()
  // End Python bindings declarations

public:
  using Self = Lesson4;
  using Pointer = std::shared_ptr<Self>;
  using ConstPointer = std::shared_ptr<const Self>;
  using WeakPointer = std::weak_ptr<Self>;
  using ConstWeakPointer = std::weak_ptr<const Self>;
  static Pointer NullPointer();

  static std::shared_ptr<Lesson4> New();

  /**
   * @brief Returns the name of the class for Lesson4
   */
  QString getNameOfClass() const override;
  /**
   * @brief Returns the name of the class for Lesson4
   */
  static QString ClassName();

  ~Lesson4() override;

  /**
   * @brief Setter property for InputDataArrayPath
   */
  void setInputDataArrayPath(const DataArrayPath& value);
  /**
   * @brief Getter property for InputDataArrayPath
   * @return Value of InputDataArrayPath
   */
  DataArrayPath getInputDataArrayPath() const;

  Q_PROPERTY(DataArrayPath InputDataArrayPath READ getInputDataArrayPath WRITE setInputDataArrayPath)

  /**
   * @brief Setter property for OutputDataArrayPath
   */
  void setOutputDataArrayPath(const DataArrayPath& value);
  /**
   * @brief Getter property for OutputDataArrayPath
   * @return Value of OutputDataArrayPath
   */
  DataArrayPath getOutputDataArrayPath() const;

  Q_PROPERTY(DataArrayPath OutputDataArrayPath READ getOutputDataArrayPath WRITE setOutputDataArrayPath)

  /**
   * @brief Setter property for Value
   */
  void setValue(float value);
  /**
   * @brief Getter property for Value
   * @return Value of Value
   */
  float getValue() const;

  Q_PROPERTY(float Value READ getValue WRITE setValue)

  /**
   * @brief Setter property for Operator
   */
  void setOperator(int value);
  /**
   * @brief Getter property for Operator
   * @return Value of Operator
   */
  int getOperator() const;

  Q_PROPERTY(int Operator READ getOperator WRITE setOperator)

  /**
   * @brief Setter property for Selection
   */
  void setSelection(bool value);
  /**
   * @brief Getter property for Selection
   * @return Value of Selection
   */
  bool getSelection() const;

  Q_PROPERTY(bool Selection READ getSelection WRITE setSelection)

  /**
   * @brief Setter property for FloatValue
   */
  void setFloatValue(float value);
  /**
   * @brief Getter property for FloatValue
   * @return Value of FloatValue
   */
  float getFloatValue() const;

  Q_PROPERTY(float FloatValue READ getFloatValue WRITE setFloatValue)

  /**
   * @brief getCompiledLibraryName Reimplemented from @see AbstractFilter class
   */
  QString getCompiledLibraryName() const override;

  /**
   * @brief getBrandingString Returns the branding string for the filter, which is a tag
   * used to denote the filter's association with specific plugins
   * @return Branding string
   */
  QString getBrandingString() const override;

  /**
   * @brief getFilterVersion Returns a version string for this filter. Default
   * value is an empty string.
   * @return
   */
  QString getFilterVersion() const override;

  /**
   * @brief newFilterInstance Reimplemented from @see AbstractFilter class
   */
  AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) const override;

  /**
   * @brief getGroupName Reimplemented from @see AbstractFilter class
   */
  QString getGroupName() const override;

  /**
   * @brief getSubGroupName Reimplemented from @see AbstractFilter class
   */
  QString getSubGroupName() const override;

  /**
   * @brief getUuid Return the unique identifier for this filter.
   * @return A QUuid object.
   */
  QUuid getUuid() const override;

  /**
   * @brief getHumanLabel Reimplemented from @see AbstractFilter class
   */
  QString getHumanLabel() const override;

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
  Lesson4();

  /**
   * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
   */
  void dataCheck();

  /**
   * @brief Initializes all the private instance variables.
   */
  void initialize();

private:
  std::weak_ptr<DataArray<float>> m_InputDataPtr;
  float* m_InputData = nullptr;
  std::weak_ptr<DataArray<float>> m_OutputDataPtr;
  float* m_OutputData = nullptr;

  DataArrayPath m_InputDataArrayPath = {};
  DataArrayPath m_OutputDataArrayPath = {};
  float m_Value = {};
  int m_Operator = {};
  bool m_Selection = {};
  float m_FloatValue = {};

public:
  Lesson4(const Lesson4&) = delete;            // Copy Constructor Not Implemented
  Lesson4(Lesson4&&) = delete;                 // Move Constructor Not Implemented
  Lesson4& operator=(const Lesson4&) = delete; // Copy Assignment Not Implemented
  Lesson4& operator=(Lesson4&&) = delete;      // Move Assignment Not Implemented
};

