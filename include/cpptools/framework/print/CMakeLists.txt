# ..\libs\cpptools\include\cpptools\framework\print\CMakeLists.txt
# ============ framework_print 模块 ============
cmake_minimum_required(VERSION 3.15)
project(framework_print)



# ================= 源文件 =================
# 自动收集 openmp 模块下所有 cpp 文件
file(GLOB OPENMP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../src/framework/print/*.cpp
)

# 判断源文件数量
list(LENGTH OPENMP_SOURCES SRC_COUNT)

if(SRC_COUNT EQUAL 0)
    # 🟦 完全合法：此模块是 header-only
    message(STATUS "[cpptools::framework::print] No .cpp files found — building as INTERFACE header-only module.")

    add_library(framework_openmp INTERFACE)

    target_include_directories(framework_openmp
        INTERFACE
            ${CPPTOOLS_INCLUDE_ROOT}
    )

else()
    # 🟩 有 .cpp，正常构建 static library
    message(STATUS "[cpptools::framework::print] Found ${SRC_COUNT} source file(s) — building as STATIC library.")

    add_library(framework_openmp STATIC ${OPENMP_SOURCES})

    target_include_directories(framework_openmp
        PUBLIC
            ${CPPTOOLS_INCLUDE_ROOT}
    )

endif()




# ==================================================
# 自动生成聚合头 print.h
# ==================================================

file(GLOB PRINT_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

set(AGG_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/print.h
)

file(WRITE ${AGG_HEADER}
"#pragma once

// ============================================
// Auto Generated Header
// Module : cpptools::framework::print
// Do not edit manually
// ============================================

")

foreach(h ${PRINT_HEADERS})
    get_filename_component(name ${h} NAME)
    if(NOT name STREQUAL "print.h")
        file(APPEND ${AGG_HEADER} "#include \"${name}\"\n")
    endif()
endforeach()