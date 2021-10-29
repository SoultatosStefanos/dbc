set(FILES dbc.hpp invariant_violation.hpp precondition_violation.hpp  postcondition_violation.hpp contract_violation.hpp)
set(SUBDIRECTORIES )

foreach(VAR ${SUBDIRECTORIES})
	add_subdirectory(${VAR})
endforeach()

if(FILES)
	target_sources(${PROJECT_NAME} PUBLIC ${FILES})
endif()