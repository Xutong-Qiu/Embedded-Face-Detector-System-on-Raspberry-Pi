project(team1_project)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/src
        $ENV{UXWELTER}/lang/cpp/src/gems/actors/common
        $ENV{UXWELTER}/lang/cpp/src/gems/actors/basic
        $ENV{UXWELTER}/lang/cpp/src/tools/graph
        $ENV{UXWELTER}/lang/c/src/tools/runtime
        $ENV{UXWELTER}/lang/c/src/gems/actors/common
        $ENV{UXWELTER}/lang/c/src/gems/edges
        )

add_subdirectory(src)
IF(EXISTS ${PROJECT_SOURCE_DIR}/test/test02)
    ADD_SUBDIRECTORY(test/test02)
ENDIF(EXISTS ${PROJECT_SOURCE_DIR}/test/test02)

IF(EXISTS ${PROJECT_SOURCE_DIR}/test/test04)
    ADD_SUBDIRECTORY(test/test04)
ENDIF(EXISTS ${PROJECT_SOURCE_DIR}/test/test04)

IF(EXISTS ${PROJECT_SOURCE_DIR}/test/test05)
    ADD_SUBDIRECTORY(test/test05)
ENDIF(EXISTS ${PROJECT_SOURCE_DIR}/test/test05)
IF(EXISTS ${PROJECT_SOURCE_DIR}/demo)
    ADD_SUBDIRECTORY(demo)
ENDIF(EXISTS ${PROJECT_SOURCE_DIR}/demo)

