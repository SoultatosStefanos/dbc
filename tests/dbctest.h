/**
 * @file dbctest.h
 * @author stef (stefanoss1498@gmail.com)
 * @brief Contains a custom unit testing framework.
 * @version 0.1
 * @date 2021-09-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef DBCTEST_H
#define DBCTEST_H

#include <iostream>

#define DBC_SUCCEED()                                                          \
  std::cout << "[ \033[1;32mPASSED \033[0m] " << __FUNCTION__ << std::endl;

#define DBC_FAIL()                                                             \
  std::cerr << "[ \033[1;31mFAILED \033[0m] " << __FUNCTION__                  \
            << " at " __FILE__ << ", " << __LINE__ << std::endl;               \
  return;

#define DBC_ASSERT_TRUE(cond)                                                  \
  if (!(cond))                                                                 \
    {                                                                          \
      DBC_FAIL ();                                                             \
    }

#define DBC_ASSERT_FALSE(cond) DBC_ASSERT_TRUE (!(cond))

#define DBC_ASSERT_EQ(lhs, rhs) DBC_ASSERT_TRUE ((lhs == rhs))

#define DBC_ASSERT_NE(lhs, rhs) DBC_ASSERT_FALSE ((lhs == rhs))

#endif
