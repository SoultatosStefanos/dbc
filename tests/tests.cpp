/**
 * @file tests.cpp
 * @author stef (stefanoss1498@gmail.com)
 * @brief Contains a concrete test case for the dbc library.
 * @version 0.1
 * @date 2021-09-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "dbc/dbc.h"
#include "dbctest.h"
#include <string.h>

namespace dbc
{
namespace test
{

inline void
invariant_doesnt_throw_if_true ()
{

  dbc::invariant (true);
  DBC_SUCCEED ();
}

inline void
invariant_throws_if_false ()
{
  try
    {
      dbc::invariant (false);
    }
  catch (dbc::invariant_violation &e)
    {
      DBC_SUCCEED ();
    }
  catch (...)
    {
      DBC_FAIL ();
    }
}

inline void
invariant_throws_if_false_with_custom_msg ()
{
  auto what = "invariant violation";
  try
    {
      dbc::invariant (false, what);
    }
  catch (dbc::invariant_violation &e)
    {
      DBC_ASSERT_EQ (strcmp (e.what (), what), 0);
      DBC_SUCCEED ();
    }
  catch (...)
    {
      DBC_FAIL ();
    }
}

}
}

using namespace dbc::test;

int
main ()
{
  invariant_doesnt_throw_if_true ();
  invariant_throws_if_false ();
  invariant_throws_if_false_with_custom_msg ();

  return EXIT_SUCCESS;
}
