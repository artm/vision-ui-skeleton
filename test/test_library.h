#include <library.h>
#include <cxxtest/TestSuite.h>

class LibraryTest : public CxxTest::TestSuite
{
public:
    void test_return_true()
    {
        TS_ASSERT( return_true() );
    }
};
