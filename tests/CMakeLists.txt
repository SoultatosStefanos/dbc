set(TESTS_LIBS gtest gmock)

set (TESTS
	assert_level_assert_tests
	assert_level_critical_tests
	assert_level_none_tests
	assert_level_safe_tests
)

foreach(TEST ${TESTS})
	add_executable(${TEST} ${TEST}.cpp)
	target_link_libraries(${TEST} PRIVATE ${PROJECT_NAME} ${TESTS_LIBS})
endforeach()

set(SUBDIRECTORIES )

foreach(VAR ${SUBDIRECTORIES})
	add_subdirectory(${VAR})
endforeach()