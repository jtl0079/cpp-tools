# ============================================
#  Module CMake Template (Auto Aggregate Header)
#  模块聚合头：<foldername>.h
#  父聚合头（父目录同名）：<parentdirname>.h （引用模块聚合头）
# ============================================
cmake_minimum_required(VERSION 3.15)

# 模块名 = 文件夹名
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${MODULE_NAME})

# 跟目录头文件路径（视项目结构调整）
set(CPPTOOLS_INCLUDE_ROOT
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../..
)

# ================= OpenMP 依赖 =================
find_package(OpenMP REQUIRED)

# ================= 源文件 =================
file(GLOB MODULE_SOURCES
    ${CPPTOOLS_INCLUDE_ROOT}/src/framework/${MODULE_NAME}/*.cpp
)

list(LENGTH MODULE_SOURCES SRC_COUNT)

if(SRC_COUNT EQUAL 0)
    message(STATUS "[cpptools::framework::${MODULE_NAME}] Header-only INTERFACE module.")
    add_library(${MODULE_NAME} INTERFACE)
    target_include_directories(${MODULE_NAME}
        INTERFACE
            ${CPPTOOLS_INCLUDE_ROOT}
    )
else()
    message(STATUS "[cpptools::framework::${MODULE_NAME}] Found ${SRC_COUNT} source file(s) — STATIC library.")
    add_library(${MODULE_NAME} STATIC ${MODULE_SOURCES})
    target_include_directories(${MODULE_NAME}
        PUBLIC
            ${CPPTOOLS_INCLUDE_ROOT}
    )
    target_link_libraries(${MODULE_NAME}
        PUBLIC
            OpenMP::OpenMP_CXX
    )
endif()

# ==================================================
# 自动生成模块聚合头 <MODULE_NAME>.h（优先 .h 格式）
# ==================================================

# 扫描当前目录的所有头文件（支持 .h 和 .hpp）
file(GLOB MODULE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

# 生成模块聚合头，例如 openmp.h
set(AGG_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}.h
)

file(WRITE ${AGG_HEADER}
"#pragma once

// ============================================
// Auto Generated Header
// Module : cpptools::framework::${MODULE_NAME}
// Do not edit manually
// ============================================

")

# 排除聚合头自身（两种可能名）并写入 include 列表
set(AGG_NAME_H   "${MODULE_NAME}.h")
set(AGG_NAME_HPP "${MODULE_NAME}.hpp")

foreach(h ${MODULE_HEADERS})
    get_filename_component(name ${h} NAME)
    if(NOT name STREQUAL "${AGG_NAME_H}" AND NOT name STREQUAL "${AGG_NAME_HPP}")
        file(APPEND ${AGG_HEADER} "#include \"${name}\"\n")
    endif()
endforeach()

# ==================================================
# 在父目录生成/更新父聚合头 <parentdirname>.h
# 父聚合头内维护一个自动生成区域，格式如下：
# // === BEGIN AUTO GENERATED MODULE INCLUDES ===
# // === END AUTO GENERATED MODULE INCLUDES ===
#
# 每个模块插入一行：
# #include "modname/modname.h"
# ==================================================
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

set(PARENT_AGG_HEADER
    ${PARENT_DIR}/${MODULE_NAME}.h    # 注意：用模块名命名，不是父目录名
)

file(WRITE ${PARENT_AGG_HEADER}

"#pragma once

// ============================================
// Auto Generated Header
// Module : cpptools::framework::${MODULE_NAME}
// Auto Generated Parent Header for Module: ${MODULE_NAME}\n\n
// Do not edit manually
// ============================================


#include \"${MODULE_NAME}/${MODULE_NAME}.h\"\n"
)