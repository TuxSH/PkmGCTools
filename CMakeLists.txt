cmake_minimum_required(VERSION 2.8.12)
project(PkmGCTools)

option(BUILD_PKMGCSAVEEDITOR "Build PkmGCSaveEditor" ON)
message("BUILD_PKMGCSAVEEDITOR:\t${BUILD_PKMGCSAVEEDITOR}")

set(CMAKE_INSTALL_PREFIX installdir)
set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP ON)
include(InstallRequiredSystemLibraries)
install(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION Release/bin CONFIGURATIONS Release RelWithDebInfo MinSizeRel COMPONENT Runtime)

add_subdirectory(LibPkmGC)
add_definitions(${LIBPKMGC_DEFINITIONS})

if(BUILD_PKMGCSAVEEDITOR)
	add_subdirectory(PkmGCSaveEditor)
	install(FILES ${LIBPKMGC_RUNTIME} DESTINATION Debug/bin CONFIGURATIONS Debug COMPONENT Runtime)
	install(FILES ${LIBPKMGC_RUNTIME} DESTINATION Release/bin CONFIGURATIONS Release RelWithDebInfo MinSizeRel COMPONENT Runtime)

	install(FILES ${QT5_RUNTIME_DEBUG} DESTINATION Debug/bin CONFIGURATIONS Debug COMPONENT Runtime)
	install(FILES ${QT5_RUNTIME_RELEASE} DESTINATION Release/bin CONFIGURATIONS Release RelWithDebInfo MinSizeRel COMPONENT Runtime)

	install(FILES ${QT5_TRANSLATION_QM} DESTINATION Debug/bin/languages CONFIGURATIONS Debug COMPONENT Translations OPTIONAL)
	install(FILES ${QT5_TRANSLATION_QM} DESTINATION Release/bin/languages CONFIGURATIONS Release RelWithDebInfo MinSizeRel COMPONENT Translations OPTIONAL)
endif()

