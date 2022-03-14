set(TESTS_LIBS gtest gmock)

add_executable(abort_tests abort_tests.cpp)
target_link_libraries(abort_tests PRIVATE ${PROJECT_NAME} ${TESTS_LIBS})
target_compile_definitions(abort_tests PRIVATE DBC_ABORT=1)

add_executable(terminate_tests terminate_tests.cpp)
target_link_libraries(terminate_tests PRIVATE ${PROJECT_NAME} ${TESTS_LIBS})
target_compile_definitions(terminate_tests PRIVATE DBC_TERMINATE=1)

add_executable(throw_tests throw_tests.cpp)
target_link_libraries(throw_tests PRIVATE ${PROJECT_NAME} ${TESTS_LIBS})
target_compile_definitions(throw_tests PRIVATE DBC_THROW=1)



