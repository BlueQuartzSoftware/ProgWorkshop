/*
 * Your License or Copyright can go here
 */

#pragma once

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/Filtering/AbstractFilter.h"

#include "ProgWorkshop/ProgWorkshopDLLExport.h"

/**
 * @brief The Lesson7 class. See [Filter documentation](@ref lesson7) for details.
 */
class ProgWorkshop_EXPORT Lesson7 : public AbstractFilter
{
  Q_OBJECT

  // Start Python bindings declarations
  PYB11_BEGIN_BINDINGS(Lesson7 SUPERCLASS AbstractFilter)
  PYB11_SHARED_POINTERS(Lesson7)
  PYB11_FILTER_NEW_MACRO(Lesson7)
  PYB11_PROPERTY(DataArrayPath GeometrySelection READ getGeometrySelection WRITE setGeometrySelection)
  PYB11_END_BINDINGS()
  // End Python bindings declarations

public:
  using Self = Lesson7;
  using Pointer = std::shared_ptr<Self>;
  using ConstPointer = std::shared_ptr<const Self>;
  using WeakPointer = std::weak_ptr<Self>;
  using ConstWeakPointer = std::weak_ptr<const Self>;
  static Pointer NullPointer();

  static std::shared_ptr<Lesson7> New();

  /**
   * @brief Returns the name of the class for Lesson7
   */
  QString getNameOfClass() const override;
  /**
   * @brief Returns the name of the class for Lesson7
   */
  static QString ClassName();

  ~Lesson7() override;

  /**
   * @brief Setter property for GeometrySelection
   */
  void setGeometrySelection(const DataArrayPath& value);
  /**
   * @brief Getter property for GeometrySelection
   * @return Value of GeometrySelection
   */
  DataArrayPath getGeometrySelection() const;
  Q_PROPERTY(DataArrayPath GeometrySelection READ getGeometrySelection WRITE setGeometrySelection)

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
  Lesson7();

  /**
   * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
   */
  void dataCheck();

  /**
   * @brief Initializes all the private instance variables.
   */
  void initialize();

public:
  Lesson7(const Lesson7&) = delete;            // Copy Constructor Not Implemented
  Lesson7(Lesson7&&) = delete;                 // Move Constructor Not Implemented
  Lesson7& operator=(const Lesson7&) = delete; // Copy Assignment Not Implemented
  Lesson7& operator=(Lesson7&&) = delete;      // Move Assignment Not Implemented

private:
  DataArrayPath m_GeometrySelection = {};
};

