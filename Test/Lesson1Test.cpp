// -----------------------------------------------------------------------------
// Insert your license & copyright information here
// -----------------------------------------------------------------------------

#include <QtCore/QCoreApplication>
#include <QtCore/QFile>

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/DataArrays/DataArray.hpp"
#include "SIMPLib/Filtering/FilterFactory.hpp"
#include "SIMPLib/Filtering/FilterManager.h"
#include "SIMPLib/Filtering/FilterPipeline.h"
#include "SIMPLib/Filtering/QMetaObjectUtilities.h"
#include "SIMPLib/Plugin/ISIMPLibPlugin.h"
#include "SIMPLib/Plugin/SIMPLibPluginLoader.h"
#include "SIMPLib/SIMPLib.h"
#include "UnitTestSupport.hpp"

#include "ProgWorkshopTestFileLocations.h"

class Lesson1Test
{

  public:
    Lesson1Test() {}
    virtual ~Lesson1Test() {}


  // -----------------------------------------------------------------------------
  //
  // -----------------------------------------------------------------------------
  void RemoveTestFiles()
  {
  #if REMOVE_TEST_FILES
    QFile::remove(UnitTest::Lesson1Test::TestFile1);
    QFile::remove(UnitTest::Lesson1Test::TestFile2);
  #endif
  }

  // -----------------------------------------------------------------------------
  //
  // -----------------------------------------------------------------------------
  int TestFilterAvailability()
  {
    // Now instantiate the Lesson1Test Filter from the FilterManager
    QString filtName = "Lesson1";
    FilterManager* fm = FilterManager::Instance();
    IFilterFactory::Pointer filterFactory = fm->getFactoryForFilter(filtName);
    if (nullptr == filterFactory.get())
    {
      std::stringstream ss;
      ss << "The ProgWorkshop Requires the use of the " << filtName.toStdString() << " filter which is found in the ProgWorkshop Plugin";
      DREAM3D_TEST_THROW_EXCEPTION(ss.str())
    }
    return 0;
  }

  // -----------------------------------------------------------------------------
  //
  // -----------------------------------------------------------------------------
  int TestLesson1Test()
  {
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /* Please write Lesson1Test test code here.
     *
     * Your IO test files are:
     * UnitTest::Lesson1Test::TestFile1
     * UnitTest::Lesson1Test::TestFile2
     *
     * SIMPLib provides some macros that will throw exceptions when a test fails
     * and thus report that during testing. These macros are located in the
     * SIMPLib/Common/UnitTestSupport.hpp file. Some examples are:
     *
     * SIMPLib_REQUIRE_EQUAL(foo, 0)
     * This means that if the variable foo is NOT equal to Zero then test will fail
     * and the current test will exit immediately. If there are more tests registered
     * with the SIMPLib_REGISTER_TEST() macro, the next test will execute. There are
     * lots of examples in the SIMPLib/Test folder to look at.
     */
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    int foo = -1;
    DREAM3D_REQUIRE_EQUAL(foo, 0)

    return EXIT_SUCCESS;
  }

  // -----------------------------------------------------------------------------
  //
  // -----------------------------------------------------------------------------
  void operator()()
  {
    int err = EXIT_SUCCESS;

    DREAM3D_REGISTER_TEST( TestFilterAvailability() );

    DREAM3D_REGISTER_TEST( TestLesson1Test() )

    DREAM3D_REGISTER_TEST( RemoveTestFiles() )
  }

  private:
    Lesson1Test(const Lesson1Test&); // Copy Constructor Not Implemented
    void operator=(const Lesson1Test&); // Operator '=' Not Implemented


};

