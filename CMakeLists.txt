cmake_minimum_required(VERSION 3.13.0)

project(dbc CXX)

if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(${PROJECT_NAME} )

target_include_directories(${PROJECT_NAME} PUBLIC include)

set(SUBDIRECTORIES include src tests)

foreach(VAR ${SUBDIRECTORIES})
	add_subdirectory(${VAR})
endforeach()