cmake_minimum_required(VERSION 2.8.12)
project(PkmGCSaveEditor)

# MOC
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5LinguistTools)
			
file(GLOB_RECURSE source_files src/*)
LIST(APPEND source_files resources/PkmGCSaveEditor.rc)

include_directories(${LIBPKMGC_INCLUDE_DIRS} src/)

add_executable(PkmGCSaveEditor WIN32 ${source_files})
target_link_libraries(PkmGCSaveEditor LibPkmGC Qt5::Widgets)

set(PKMGCSAVEEDITOR_SUPPORTED_LANGUAGES en fr CACHE INTERNAL "PkmGCSaveEditor's supported languages" FORCE)

get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
execute_process(COMMAND ${QT5_QMAKE_EXECUTABLE} -query QT_INSTALL_BINS OUTPUT_VARIABLE QT5_BINARY_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
set(QT5_BINARY_DIR ${QT5_BINARY_DIR} CACHE INTERNAL "Qt5 bin dir" FORCE)

if(Qt5LinguistTools_FOUND)
	unset(PKMGCSAVEEDITOR_TRANSLATION_FILES)
	foreach(language ${PKMGCSAVEEDITOR_SUPPORTED_LANGUAGES})
		list(APPEND PKMGCSAVEEDITOR_TRANSLATION_FILES translations/PkmGCSaveEditor_${language}.ts)
	endforeach(language)
	list(REMOVE_DUPLICATES QT5_TRANSLATION_QM)
	
	set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM 1) # prevent make clean from removing TS files

	qt5_create_translation(TRANSLATION_MESSAGES ${source_files} ${PKMGCSAVEEDITOR_TRANSLATION_FILES})
	qt5_add_translation(TRANSLATION_QM ${PKMGCSAVEEDITOR_TRANSLATION_FILES})
	add_custom_target(PkmGCSaveEditor_translations_update DEPENDS ${TRANSLATION_MESSAGES})
	add_custom_target(PkmGCSaveEditor_translations DEPENDS ${TRANSLATION_QM})

	install(FILES ${TRANSLATION_QM} DESTINATION bin/translations COMPONENT Translations OPTIONAL)
else(Qt5LinguistTools_FOUND)
	message("Qt5LinguistTools was NOT found. The translation files will not be able to be updated.") 
endif(Qt5LinguistTools_FOUND)


install(PROGRAMS $<TARGET_FILE:PkmGCSaveEditor> DESTINATION bin/ COMPONENT Runtime)

install(FILES "README.md" "LICENSE" DESTINATION bin COMPONENT Runtime)

