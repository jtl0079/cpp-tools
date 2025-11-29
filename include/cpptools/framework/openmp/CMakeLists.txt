# ..\libs\cpptools\include\cpptools\framework\openmp\CMakeLists.txt
# ============ framework_openmp 模块 ============
cmake_minimum_required(VERSION 3.15)
project(framework_openmp)




# ================== 头文件路径 ==================
set(CPPTOOLS_INCLUDE_ROOT
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../..
)

# ================= OpenMP 依赖 =================
find_package(OpenMP REQUIRED)

# ================= 源文件 =================
file(GLOB OPENMP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../src/framework/openmp/*.cpp
)

list(LENGTH OPENMP_SOURCES SRC_COUNT)

if(SRC_COUNT EQUAL 0)

    message(STATUS "[cpptools::framework::openmp] No .cpp files — building as INTERFACE header-only module.")

    add_library(framework_openmp INTERFACE)

    target_include_directories(framework_openmp
        INTERFACE
            ${CPPTOOLS_INCLUDE_ROOT}
    )

else()

    message(STATUS "[cpptools::framework::openmp] Found ${SRC_COUNT} source file(s) — building as STATIC library.")

    add_library(framework_openmp STATIC ${OPENMP_SOURCES})

    target_include_directories(framework_openmp
        PUBLIC
            ${CPPTOOLS_INCLUDE_ROOT}
    )

    target_link_libraries(framework_openmp
        PUBLIC
            OpenMP::OpenMP_CXX
    )

endif()


# ==================================================
# 自动生成聚合头 openmp.h
# ==================================================

file(GLOB OPENMP_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

set(AGG_HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/openmp.h
)

file(WRITE ${AGG_HEADER}
"#pragma once

// ============================================
// Auto Generated Header
// Module : cpptools::framework::openmp
// Do not edit manually
// ============================================

")

foreach(h ${OPENMP_HEADERS})
    get_filename_component(name ${h} NAME)
    if(NOT name STREQUAL "openmp.h")
        file(APPEND ${AGG_HEADER} "#include \"${name}\"\n")
    endif()
endforeach()