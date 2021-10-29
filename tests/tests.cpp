/**
 * @file tests.cpp
 * @author Soultatos Stefanos (stefanoss1498@gmail.com)
 * @brief Contains a concrete test case for the dbc library.
 * @version 2.0
 * @date 2021-10-29
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "dbc/dbc.hpp"
#include "dbctest.hpp"
#include <string.h>

namespace dbc::test
{

inline void
invariant_doesnt_throw_if_true ()
{

  dbc::invariant (true);
  DBC_SUCCEED ();
}

inline void
invariant_throws_invariant_violation_if_false ()
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
invariant_throws_invariant_violation_if_false_with_custom_msg ()
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

inline void
require_doesnt_throw_if_true ()
{

  dbc::require (true);
  DBC_SUCCEED ();
}

inline void
require_throws_precondition_violation_if_false ()
{
  try
    {
      dbc::require (false);
    }
  catch (dbc::precondition_violation &e)
    {
      DBC_SUCCEED ();
    }
  catch (...)
    {
      DBC_FAIL ();
    }
}

inline void
require_throws_precondition_violation_if_false_with_custom_msg ()
{
  auto what = "precondition violation";
  try
    {
      dbc::require (false, what);
    }
  catch (dbc::precondition_violation &e)
    {
      DBC_ASSERT_EQ (strcmp (e.what (), what), 0);
      DBC_SUCCEED ();
    }
  catch (...)
    {
      DBC_FAIL ();
    }
}

inline void
ensure_doesnt_throw_if_true ()
{
  dbc::ensure (true);
  DBC_SUCCEED ();
}

inline void
ensure_throws_postcondition_violation_if_false ()
{
  try
    {
      dbc::ensure (false);
    }
  catch (dbc::postcondition_violation &e)
    {
      DBC_SUCCEED ();
    }
  catch (...)
    {
      DBC_FAIL ();
    }
}

inline void
ensure_throws_postcondition_violation_if_false_with_custom_msg ()
{
  auto what = "postcondition violation";
  try
    {
      dbc::ensure (false, what);
    }
  catch (dbc::postcondition_violation &e)
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

using namespace dbc::test;

namespace
{

inline void
test_invariant ()
{
  invariant_doesnt_throw_if_true ();
  invariant_throws_invariant_violation_if_false ();
  invariant_throws_invariant_violation_if_false_with_custom_msg ();
}

inline void
test_require ()
{
  require_doesnt_throw_if_true ();
  require_throws_precondition_violation_if_false ();
  require_throws_precondition_violation_if_false_with_custom_msg ();
}

inline void
test_ensure ()
{
  ensure_doesnt_throw_if_true ();
  ensure_throws_postcondition_violation_if_false ();
  ensure_throws_postcondition_violation_if_false_with_custom_msg ();
}

}

auto
main () -> int
{
  test_invariant ();
  test_require ();
  test_ensure ();
  return EXIT_SUCCESS;
}
