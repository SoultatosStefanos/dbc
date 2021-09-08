cmake_minimum_required(VERSION 3.13.0)

project(dbc CXX)

if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()