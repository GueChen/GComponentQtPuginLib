# CMakeList.txt: PBR_PROJECT 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project(QtPlayground VERSION 0.0.1 LANGUAGES CXX)

set(TARGET_NAME QtPlayground)

#___________________ Macro for Plugin __________________________________________________


#___________________ QT Proj Setting ___________________________________________________
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH "${QT_DIR}" "${CMKAE_PREFIX_PATH}")

file(GLOB_RECURSE HEADER_FILES "*.h" "*.hpp")
file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.c")
file(GLOB_RECURSE UI_FILES  "*.ui")
file(GLOB_RECURSE QRC_FILES "*.qrc")
#____________________ Keep File Path Structrue ________________________________________
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES} ${UI_FILES} ${QRC_FILES})

#___________________ Third Party Dependencies __________________________________________
find_package(Qt6 COMPONENTS				# QT Dependencies
	Gui Core Widgets  UiPlugin Designer
	REQUIRED
)

#___________________ Display _____________________________________________________________
message(STATUS "SOURCE FILES - ${SOURCE_FILES}")
message(STATUS "HEADER_FILES - ${HEADER_FILES}")
message(STATUS "RCC_FILES    - ${QRC_FILES}")

#___________________ Generate Target And Properties ______________________________________
add_executable (${TARGET_NAME} ${UI_FILES} ${SOURCE_FILES} ${HEADER_FILES} ${QRC_FILES})

#_______ Copy File to Bin __________________________________________________
set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${TARGET_NAME} PROPERTY LINKER_LANGUAGE CXX)

get_target_property(_QMAKE_EXECUTABLE Qt6::qmake IMPRTED_LOCATION)
get_filename_component(_QT_BIN_DIR "${_QMAKE_EXECUTABLE}" DIRECTORY)
find_program(DEPLOYQT_EXECUTABLE NAMES windeployqt macdeployqt "${_QT_BIN_DIR}")
if(WIN32)
	add_custom_command(TARGET ${TARGET_NAME} 
        POST_BUILD
        COMMAND ${DEPLOYQT_EXECUTABLE} "$<TARGET_FILE:${TARGET_NAME}>"
            --$<LOWER_CASE:$<CONFIG>> --qmldir ${CMAKE_SOURCE_DIR}
    )
endif()

#___________________ Linking Libraries ______________________
target_link_libraries(${TARGET_NAME} PUBLIC 
	Qt6::Core
	Qt6::Widgets
	Qt6::Gui
	Qt6::UiPlugin
	Qt6::Designer
	GComponentQtPlugins
)

