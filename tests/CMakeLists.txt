set(TESTS_LIBS gtest gmock)

set (TESTS
	assert_level_invariants_tests
	assert_level_none_tests
	assert_level_postconditions_tests
	assert_level_preconditions_tests
)

foreach(TEST ${TESTS})
	add_executable(${TEST} ${TEST}.cpp)
	target_link_libraries(${TEST} PRIVATE ${PROJECT_NAME} ${TESTS_LIBS})
endforeach()

set(SUBDIRECTORIES )

foreach(VAR ${SUBDIRECTORIES})
	add_subdirectory(${VAR})
endforeach()