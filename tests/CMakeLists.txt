set(FILES tests.cpp dbctest.hpp)
set(EXECUTABLE dbc_tests)
set(SUBDIRECTORIES )

foreach(VAR ${SUBDIRECTORIES})
	add_subdirectory(${VAR})
endforeach()

if(FILES)
	add_executable(${EXECUTABLE} ${FILES})
  target_link_libraries(${EXECUTABLE} PRIVATE ${PROJECT_NAME})
endif()