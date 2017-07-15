// -----------------------------------------------------------------------------
// Insert your license & copyright information here
// -----------------------------------------------------------------------------

#include <QtCore/QCoreApplication>
#include <QtCore/QFile>

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/DataArrays/DataArray.hpp"
#include "SIMPLib/Common/FilterPipeline.h"
#include "SIMPLib/Common/FilterManager.h"
#include "SIMPLib/Common/FilterFactory.hpp"
#include "SIMPLib/Plugin/ISIMPLibPlugin.h"
#include "SIMPLib/Plugin/SIMPLibPluginLoader.h"
#include "SIMPLib/Utilities/UnitTestSupport.hpp"
#include "SIMPLib/Utilities/QMetaObjectUtilities.h"

#include "ProgWorkshopTestFileLocations.h"

class Lesson3Test
{

  public:
    Lesson3Test() {}
    virtual ~Lesson3Test() {}


  // -----------------------------------------------------------------------------
  //
  // -----------------------------------------------------------------------------
  void RemoveTestFiles()
  {
  #if REMOVE_TEST_FILES
    QFile::remove(UnitTest::Lesson3Test::TestFile1);
    QFile::remove(UnitTest::Lesson3Test::TestFile2);
  #endif
  }

  // -----------------------------------------------------------------------------
  //
  // -----------------------------------------------------------------------------
  int TestFilterAvailability()
  {
    // Now instantiate the Lesson3Test Filter from the FilterManager
    QString filtName = "Lesson3";
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
  int TestLesson3Test()
  {
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   /* Please write Lesson3Test test code here.
    *
    * Your IO test files are:
    * UnitTest::Lesson3Test::TestFile1
    * UnitTest::Lesson3Test::TestFile2
    *
    * SIMPLib provides some macros that will throw exceptions when a test fails
    * and thus report that during testing. These macros are located in the
    * SIMPLib/Utilities/UnitTestSupport.hpp file. Some examples are:
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

    DREAM3D_REGISTER_TEST( TestLesson3Test() )

    DREAM3D_REGISTER_TEST( RemoveTestFiles() )
  }

  private:
    Lesson3Test(const Lesson3Test&); // Copy Constructor Not Implemented
    void operator=(const Lesson3Test&); // Operator '=' Not Implemented


};

