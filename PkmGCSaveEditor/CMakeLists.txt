cmake_minimum_required(VERSION 2.8.12)
project(PkmGCSaveEditor)

# Include generated moc files
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5LinguistTools)
			
file(GLOB_RECURSE source_files src/*)

include_directories(${LIBPKMGC_INCLUDE_DIRS} src/)

add_executable(PkmGCSaveEditor WIN32 ${source_files})
target_link_libraries(PkmGCSaveEditor LibPkmGC Qt5::Widgets)

set(PKMGCSAVEEDITOR_SUPPORTED_LANGUAGES en fr CACHE INTERNAL "PkmGCSaveEditor's supported languages" FORCE)

if(Qt5LinguistTools_FOUND)
	unset(PKMGCSAVEEDITOR_TRANSLATION_FILES)
	get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
	execute_process(COMMAND ${QT5_QMAKE_EXECUTABLE} -query QT_INSTALL_TRANSLATIONS OUTPUT_VARIABLE QT5_QM_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
	foreach(language ${PKMGCSAVEEDITOR_SUPPORTED_LANGUAGES})
		list(APPEND PKMGCSAVEEDITOR_TRANSLATION_FILES translations/PkmGCSaveEditor_${language}.ts)
		if(EXISTS ${QT5_QM_DIR}/qt_${language}.qm) # qt_en.qm does not exist
			list(APPEND QT5_TRANSLATION_QM ${QT5_QM_DIR}/qt_${language}.qm)
		elseif(EXISTS translations/qt/qt_${language}.qm)
			list(APPEND QT5_TRANSLATION_QM translations/qt/qt_${language}.qm)
		endif(EXISTS ${QT5_QM_DIR}/qt_${language}.qm)
		
		if(EXISTS ${QT5_QM_DIR}/qtbase_${language}.qm)
			list(APPEND QT5_TRANSLATION_QM ${QT5_QM_DIR}/qtbase_${language}.qm) # Required for Qt > 5.3
		elseif(EXISTS translations/qt/qtbase_${language}.qm)
			list(APPEND QT5_TRANSLATION_QM translations/qt/qtbase_${language}.qm)
		endif(EXISTS ${QT5_QM_DIR}/qtbase_${language}.qm)
	endforeach(language)
	list(REMOVE_DUPLICATES QT5_TRANSLATION_QM)
	set(QT5_TRANSLATION_QM ${QT5_TRANSLATION_QM} CACHE INTERNAL "Qt5 *.qm")
	
	set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM 1) # prevent make clean from removing TS files

	qt5_create_translation(TRANSLATION_MESSAGES ${source_files} ${PKMGCSAVEEDITOR_TRANSLATION_FILES})
	qt5_add_translation(TRANSLATION_QM ${PKMGCSAVEEDITOR_TRANSLATION_FILES})
	add_custom_target(PkmGCSaveEditor_translations_update DEPENDS ${TRANSLATION_MESSAGES})
	add_custom_target(PkmGCSaveEditor_translations DEPENDS ${TRANSLATION_QM})

	install(FILES ${TRANSLATION_QM} DESTINATION Debug/bin/languages CONFIGURATIONS Debug COMPONENT Translations OPTIONAL)
	install(FILES ${TRANSLATION_QM} DESTINATION Release/bin/languages CONFIGURATIONS Release RelWithDebInfo MinSizeRel COMPONENT Translations OPTIONAL)
else(Qt5LinguistTools_FOUND)
	message("Qt5LinguistTools was NOT found. The translation files will not be able to be updated.") 
endif(Qt5LinguistTools_FOUND)


# DLL hell


if(NOT WIN32 AND NOT COPY_QT_LIBS_UNIX)
	set(COPY_QT_LIBS OFF)
else()
	set(COPY_QT_LIBS ON)
endif()

if(COPY_QT_LIBS)
	get_target_property(qt_libs Qt5::Widgets INTERFACE_LINK_LIBRARIES)
	get_target_property(qt_widgets_location Qt5::Widgets LOCATION_Release)
	list(APPEND QT5_RUNTIME_RELEASE ${qt_widgets_location})
	foreach(qt_lib ${qt_libs})
		get_target_property(qt_lib_location ${qt_lib} LOCATION_Release)
		list(APPEND QT5_RUNTIME_RELEASE ${qt_lib_location})
	endforeach()
	list(REMOVE_DUPLICATES QT5_RUNTIME_RELEASE)
	set(QT5_RUNTIME_RELEASE ${QT5_RUNTIME_RELEASE} CACHE INTERNAL "Qt5 release libraries" FORCE)

	get_target_property(qt_libs Qt5::Widgets INTERFACE_LINK_LIBRARIES)
	get_target_property(qt_widgets_location Qt5::Widgets LOCATION_Debug)
	list(APPEND QT5_RUNTIME_DEBUG ${qt_widgets_location})
	foreach(qt_lib ${qt_libs})
		get_target_property(qt_lib_location ${qt_lib} LOCATION_Debug)
		list(APPEND QT5_RUNTIME_DEBUG ${qt_lib_location})
	endforeach()
	
	list(REMOVE_DUPLICATES QT5_RUNTIME_DEBUG)

	set(QT5_RUNTIME_DEBUG ${QT5_RUNTIME_DEBUG} CACHE INTERNAL "Qt5 debug libraries" FORCE)

endif()

install(PROGRAMS $<TARGET_FILE:PkmGCSaveEditor> DESTINATION Debug/bin CONFIGURATIONS Debug)
install(PROGRAMS $<TARGET_FILE:PkmGCSaveEditor> DESTINATION Release/bin CONFIGURATIONS Release RelWithDebInfo MinSizeRel)

install(FILES "README.md" "LICENSE" DESTINATION Debug/bin CONFIGURATIONS Debug)
install(FILES "README.md" "LICENSE" DESTINATION Release/bin CONFIGURATIONS Release RelWithDebInfo MinSizeRel)

