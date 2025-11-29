# ============================================
#  Module CMake for framework/<module>
#  自动生成：
#    1) framework/<module>/<module>.h   (模块内部聚合头)
#    2) framework/<module>.h            (父聚合头，包含上面那个)
# ============================================
cmake_minimum_required(VERSION 3.15)

# 模块名 = 当前目录名 (如 print)
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${MODULE_NAME})

# 根 include 目录（根据你的项目结构，这里和之前保持一致）
set(CPPTOOLS_INCLUDE_ROOT
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../..
)

# ================= 源文件（自动收集 src 下对应模块的 cpp） =================
file(GLOB MODULE_SOURCES
    ${CPPTOOLS_INCLUDE_ROOT}/src/framework/${MODULE_NAME}/*.cpp
)

# 判断源文件数量
list(LENGTH MODULE_SOURCES SRC_COUNT)

if(SRC_COUNT EQUAL 0)
    message(STATUS "[cpptools::framework::${MODULE_NAME}] No .cpp files found — building as INTERFACE header-only module.")
    add_library(${MODULE_NAME} INTERFACE)
    target_include_directories(${MODULE_NAME}
        INTERFACE
            ${CPPTOOLS_INCLUDE_ROOT}
    )
else()
    message(STATUS "[cpptools::framework::${MODULE_NAME}] Found ${SRC_COUNT} source file(s) — building as STATIC library.")
    add_library(${MODULE_NAME} STATIC ${MODULE_SOURCES})
    target_include_directories(${MODULE_NAME}
        PUBLIC
            ${CPPTOOLS_INCLUDE_ROOT}
    )
endif()


# ==================================================
# 1) 生成模块内部聚合头: framework/<module>/<module>.h
#    扫描当前目录的 *.h / *.hpp 并排除自身（防止自包含）
# ==================================================
file(GLOB MODULE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

set(MODULE_AGG_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}.h
)

file(WRITE ${MODULE_AGG_HEADER}
"#pragma once

// ============================================
// Auto Generated Module Header
// Module : cpptools::framework::${MODULE_NAME}
// Do not edit manually
// ============================================

")

# 排除自身两种可能的名字（module.h / module.hpp）
set(AGG_NAME_H   "${MODULE_NAME}.h")
set(AGG_NAME_HPP "${MODULE_NAME}.hpp")

foreach(h ${MODULE_HEADERS})
    get_filename_component(name ${h} NAME)
    if(NOT name STREQUAL "${AGG_NAME_H}" AND NOT name STREQUAL "${AGG_NAME_HPP}")
        file(APPEND ${MODULE_AGG_HEADER} "#include \"${name}\"\n")
    endif()
endforeach()


# ==================================================
# 2) 在父目录生成父聚合头: framework/<module>.h
#    内容固定为: #include "<module>/<module>.h"
# ==================================================
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

set(PARENT_AGG_HEADER
    ${PARENT_DIR}/${MODULE_NAME}.h   # 注意：父聚合头命名为模块名.h，位于 framework/ 下
)

file(WRITE ${PARENT_AGG_HEADER}
"#pragma once

// ============================================
// Auto Generated Parent Header
// Parent for module: ${MODULE_NAME}
// Do not edit manually (managed by child module CMake)
// ============================================

#include \"${MODULE_NAME}/${MODULE_NAME}.h\"
")
