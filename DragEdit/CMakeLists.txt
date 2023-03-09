# CMakeList.txt: PBR_PROJECT 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project(DragEdit VERSION 0.0.1 LANGUAGES CXX)

set(TARGET_NAME DragEdit)

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

file(GLOB_RECURSE HEADER_FILES "inc/*.h" "inc/*.hpp")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.c")
file(GLOB_RECURSE UI_FILES  "*.ui")
file(GLOB_RECURSE QRC_FILES "*.qrc")

#___________________ Third Party Dependencies __________________________________________
find_package(Qt6 COMPONENTS				# QT Dependencies
	Gui Core Widgets  UiPlugin
	REQUIRED
)

#___________________ Display _____________________________________________________________
message(STATUS "SOURCE FILES - ${SOURCE_FILES}")
message(STATUS "HEADER_FILES - ${HEADER_FILES}")
message(STATUS "RCC_FILES    - ${QRC_FILES}")

#___________________ Generate Target And Properties ______________________________________
add_library (${TARGET_NAME}  SHARED ${UI_FILES} ${SOURCE_FILES} ${HEADER_FILES} ${QRC_FILES})

#_______ Copy File to Bin __________________________________________________
#add_custom_command(TARGET ${TARGET_NAME} POST_BUILD 
#		COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/asset" "$<TARGET_FILE_DIR:${TARGET_NAME}>/asset"
#		COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Shader" "$<TARGET_FILE_DIR:${TARGET_NAME}>/Shader"
#)

set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${TARGET_NAME} PROPERTY LINKER_LANGUAGE CXX)


#___________________ Linking Libraries ______________________
target_link_libraries(${TARGET_NAME} PUBLIC 
	Qt6::Core
	Qt6::Widgets
	Qt6::Gui
	Qt6::UiPlugin		
)

include_directories(${TARGET_NAME} inc)

install(TARGETS ${TARGET_NAME} 
		DESTINATION ${QT_DIR}/plugins/designer)
install(DIRECTORY inc/
		DESTINATION "${QT_DIR}/include/customplugin"
		FILES_MATCHING PATTERN "*.h" REGEX ".*plugin.*" EXCLUDE			
)