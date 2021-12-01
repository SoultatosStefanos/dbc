set(SUBDIRECTORIES dbc)

foreach(VAR ${SUBDIRECTORIES})
	add_subdirectory(${VAR})
endforeach()