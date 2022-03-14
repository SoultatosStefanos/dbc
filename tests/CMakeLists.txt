set(TESTS_LIBS gtest gmock)

add_executable(abort_tests abort_tests.cpp)
target_link_libraries(abort_tests PRIVATE ${PROJECT_NAME} ${TESTS_LIBS})
target_compile_definitions(abort_tests PRIVATE DBC_ABORT=1)

