cmake_minimum_required(VERSION 2.8.12)
project(PkmGCTools)

option(BUILD_PKMGCSAVEEDITOR "Build PkmGCSaveEditor" ON)
message("BUILD_PKMGCSAVEEDITOR:\t${BUILD_PKMGCSAVEEDITOR}")

set(CMAKE_INSTALL_PREFIX installdir)
set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP ON)
include(InstallRequiredSystemLibraries)
install(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION bin COMPONENT Runtime)
install(FILES "CHANGELOG.md" DESTINATION bin COMPONENT Runtime)

add_subdirectory(LibPkmGC)
add_definitions(${LIBPKMGC_DEFINITIONS})

if(BUILD_PKMGCSAVEEDITOR)
	add_subdirectory(PkmGCSaveEditor)
	
	install(FILES ${LIBPKMGC_RUNTIME} DESTINATION bin COMPONENT Runtime)
	if(WIN32)
		install(CODE "if(EXISTS ${CMAKE_INSTALL_PREFIX}/bin/PkmGCSaveEditor.exe)\n message(\"Running windeployqt\")\nexecute_process(COMMAND ${QT5_BINARY_DIR}/windeployqt.exe ${CMAKE_INSTALL_PREFIX}/bin/PkmGCSaveEditor.exe)\nelse()\n message(\"Please rerun INSTALL once to install the required Qt libraries\")\n endif()" 
		COMPONENT RUNTIME)
	endif(WIN32)
endif()

