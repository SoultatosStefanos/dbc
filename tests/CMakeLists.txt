set(TESTS_LIBS gtest gmock)

set (TESTS
	abort_tests
	custom_tests
	debug_tests
	default_tests
	terminate_tests
	throw_tests
)

foreach(TEST ${TESTS})
	add_executable(${TEST} ${TEST}.cpp)
	target_link_libraries(${TEST} PRIVATE ${PROJECT_NAME} ${TESTS_LIBS})
endforeach()

set(SUBDIRECTORIES )

foreach(VAR ${SUBDIRECTORIES})
	add_subdirectory(${VAR})
endforeach()