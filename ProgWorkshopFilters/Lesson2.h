/*
 * Your License or Copyright can go here
 */

#ifndef _lesson2_h_
#define _lesson2_h_

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/Filtering/AbstractFilter.h"
#include "SIMPLib/SIMPLib.h"

/**
 * @brief The Lesson2 class. See [Filter documentation](@ref lesson2) for details.
 */
class Lesson2 : public AbstractFilter
{
  Q_OBJECT

  public:
    SIMPL_SHARED_POINTERS(Lesson2)
    SIMPL_STATIC_NEW_MACRO(Lesson2)
    SIMPL_TYPE_MACRO_SUPER(Lesson2, AbstractFilter)

    virtual ~Lesson2();

    SIMPL_FILTER_PARAMETER(DataArrayPath, InputDataArrayPath)
    Q_PROPERTY(DataArrayPath InputDataArrayPath READ getInputDataArrayPath WRITE setInputDataArrayPath)

    SIMPL_FILTER_PARAMETER(DataArrayPath, OutputDataArrayPath)
    Q_PROPERTY(DataArrayPath OutputDataArrayPath READ getOutputDataArrayPath WRITE setOutputDataArrayPath)

    SIMPL_FILTER_PARAMETER(float, Value)
    Q_PROPERTY(float Value READ getValue WRITE setValue)


    /**
     * @brief getCompiledLibraryName Reimplemented from @see AbstractFilter class
     */
    virtual const QString getCompiledLibraryName();

    /**
     * @brief getBrandingString Returns the branding string for the filter, which is a tag
     * used to denote the filter's association with specific plugins
     * @return Branding string
    */
    virtual const QString getBrandingString();

    /**
     * @brief getFilterVersion Returns a version string for this filter. Default
     * value is an empty string.
     * @return
     */
    virtual const QString getFilterVersion();

    /**
     * @brief newFilterInstance Reimplemented from @see AbstractFilter class
     */
    virtual AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters);

    /**
     * @brief getGroupName Reimplemented from @see AbstractFilter class
     */
    virtual const QString getGroupName();

    /**
     * @brief getSubGroupName Reimplemented from @see AbstractFilter class
     */
    virtual const QString getSubGroupName();

    /**
     * @brief getHumanLabel Reimplemented from @see AbstractFilter class
     */
    virtual const QString getHumanLabel();

    /**
     * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
     */
    virtual void setupFilterParameters();

    /**
     * @brief execute Reimplemented from @see AbstractFilter class
     */
    virtual void execute();

    /**
    * @brief preflight Reimplemented from @see AbstractFilter class
    */
    virtual void preflight();

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
    Lesson2();

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


    Lesson2(const Lesson2&); // Copy Constructor Not Implemented
    void operator=(const Lesson2&); // Operator '=' Not Implemented
};

#endif /* _Lesson2_H_ */
