cmake_minimum_required (VERSION 3.8)

set(TARGET_NAME GComponentQtPlugins)

#___________________ Macro for Plugin __________________________________________________
add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_SHARED)
add_definitions(-DQDESIGNER_EXPORT_WIDGETS)

#___________________ QT Proj Setting ___________________________________________________
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH "${QT_DIR}" "${CMKAE_PREFIX_PATH}")

set(CMAKE_DEBUG_POSTFIX "d")

file(GLOB_RECURSE HEADER_FILES "inc/*.h" "inc/*.hpp")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.c")
file(GLOB_RECURSE UI_FILES	   "ui/*.ui")
file(GLOB_RECURSE QRC_FILES	   "resources/*.qrc")
set(CMAKE_AUTOUIC_SEARCH_PATHS ui)
#___________________ Third Party Dependencies __________________________________________
find_package(Qt6 COMPONENTS				# QT Dependencies
	Gui Core Widgets  UiPlugin Designer
	REQUIRED
)

#___________________ Display ________________________________


#___________________ Generate Target And Properties _________
add_library (${TARGET_NAME}  SHARED ${UI_FILES} ${SOURCE_FILES} ${HEADER_FILES} ${QRC_FILES})

#___________________ Copy File to Bin _______________________
set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${TARGET_NAME} PROPERTY LINKER_LANGUAGE CXX)
#set_target_properties(${TARGET_NAME} 
#					  PROPERTIES LIBRARY_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:GSimulatorEditor>)
if(GSimulatorEditor)
set_target_properties(${TARGET_NAME} 
					  PROPERTIES RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:GSimulatorEditor>)
endif()
#___________________ Linking Libraries ______________________
target_link_libraries(${TARGET_NAME} PUBLIC 
	Qt6::Core
	Qt6::Widgets
	Qt6::Gui
	Qt6::UiPlugin
	Qt6::Designer
)

include_directories(${TARGET_NAME} inc)

target_include_directories(
	${TARGET_NAME} 
	PUBLIC
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/inc"
)

install(TARGETS ${TARGET_NAME} 
		RUNTIME DESTINATION ${QT_DIR}/plugins/designer
)

install(TARGETS ${TARGET_NAME} 
		RUNTIME DESTINATION ${QT_DIR}/bin
		LIBRARY DESTINATION ${QT_DIR}/lib
		ARCHIVE DESTINATION ${QT_DIR}/lib
)

set(install_files)
foreach(filename ${HEADER_FILES})
	list(APPEND install_files "${filename}")
endforeach()
list(FILTER install_files EXCLUDE REGEX ".*plugin.*")
message("Intstall files = ${install_files}")

install(FILES ${install_files}
		DESTINATION "${QT_DIR}/include/custom"
)