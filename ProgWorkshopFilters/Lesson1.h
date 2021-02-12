/*
 * Your License or Copyright can go here
 */

#pragma once

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/DataArrays/DataArray.hpp"
#include "SIMPLib/Filtering/AbstractFilter.h"

#include "ProgWorkshop/ProgWorkshopDLLExport.h"

/**
 * @brief The Lesson1 class. See [Filter documentation](@ref lesson1) for details.
 */
class ProgWorkshop_EXPORT Lesson1 : public AbstractFilter
{
  Q_OBJECT

  // Start Python bindings declarations
  PYB11_BEGIN_BINDINGS(Lesson1 SUPERCLASS AbstractFilter)
  PYB11_SHARED_POINTERS(Lesson1)
  PYB11_FILTER_NEW_MACRO(Lesson1)
  PYB11_PROPERTY(DataArrayPath InputDataArrayPath READ getInputDataArrayPath WRITE setInputDataArrayPath)
  PYB11_PROPERTY(DataArrayPath OutputDataArrayPath READ getOutputDataArrayPath WRITE setOutputDataArrayPath)
  PYB11_PROPERTY(float Value READ getValue WRITE setValue)
  PYB11_END_BINDINGS()
  // End Python bindings declarations

public:
  using Self = Lesson1;
  using Pointer = std::shared_ptr<Self>;
  using ConstPointer = std::shared_ptr<const Self>;
  using WeakPointer = std::weak_ptr<Self>;
  using ConstWeakPointer = std::weak_ptr<const Self>;
  static Pointer NullPointer();

  static std::shared_ptr<Lesson1> New();

  /**
   * @brief Returns the name of the class for Lesson1
   */
  QString getNameOfClass() const override;
  /**
   * @brief Returns the name of the class for Lesson1
   */
  static QString ClassName();

  ~Lesson1() override;

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

protected:
  Lesson1();

  /**
   * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
   */
  void dataCheck() override;

  /**
   * @brief Initializes all the private instance variables.
   */
  void initialize();

private:
  std::weak_ptr<DataArray<float>> m_InputDataPtr;
  float* m_InputData = nullptr;
  std::weak_ptr<DataArray<float>> m_OutputDataPtr;
  float* m_OutputData = nullptr;

  DataArrayPath m_InputDataArrayPath = {
      SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName,
      SIMPL::CellData::ConfidenceIndex}; // Initialize all your filter parameters here.  SIMPL has a Constants file that developers can use to help set common names., "", ""};
  DataArrayPath m_OutputDataArrayPath = {SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName,
                                         "Lesson1_Output"}; // Initialize all your filter parameters here.  SIMPL has a Constants file that developers can use to help set common names., "", ""};
  float m_Value = {0.0f};                                   // Initialize all your filter parameters here.  SIMPL has a Constants file that developers can use to help set common names., "", ""};

public:
  Lesson1(const Lesson1&) = delete;            // Copy Constructor Not Implemented
  Lesson1(Lesson1&&) = delete;                 // Move Constructor Not Implemented
  Lesson1& operator=(const Lesson1&) = delete; // Copy Assignment Not Implemented
  Lesson1& operator=(Lesson1&&) = delete;      // Move Assignment Not Implemented
};

