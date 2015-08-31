cmake_minimum_required(VERSION 2.8.12)
project(PkmGCTools)

set(CMAKE_INSTALL_PREFIX installdir)
option(BUILD_PKMGCSAVEEDITOR "Build PkmGCSaveEditor" ON)

add_subdirectory(LibPkmGC)
add_definitions(${LIBPKMGC_DEFINITIONS})

message("BUILD_PKMGCSAVEEDITOR:\t${BUILD_PKMGCSAVEEDITOR}")

if(BUILD_PKMGCSAVEEDITOR)
	add_subdirectory(PkmGCSaveEditor)
	install(FILES ${LIBPKMGC_RUNTIME} DESTINATION Debug/bin CONFIGURATIONS Debug)
	install(FILES ${LIBPKMGC_RUNTIME} DESTINATION Release/bin CONFIGURATIONS Release RelWithDebInfo MinSizeRel)

	install(FILES ${QT5_RUNTIME_DEBUG} DESTINATION Debug/bin CONFIGURATIONS Debug)
	install(FILES ${QT5_RUNTIME_RELEASE} DESTINATION Release/bin CONFIGURATIONS Release RelWithDebInfo MinSizeRel)

	install(FILES ${QT5_TRANSLATION_QM} DESTINATION Debug/bin/languages CONFIGURATIONS Debug)
	install(FILES ${QT5_TRANSLATION_QM} DESTINATION Release/bin/languages CONFIGURATIONS Release RelWithDebInfo MinSizeRel)
endif()

