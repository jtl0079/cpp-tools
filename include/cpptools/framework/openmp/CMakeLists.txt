# ..\libs\cpptools\include\cpptools\framework\openmp\CMakeLists.txt
# ============ framework_openmp 模块 ============
project(framework_openmp)



# ================= 源文件 =================
# 自动收集 openmp 模块下所有 cpp 文件
file(GLOB OPENMP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../src/framework/openmp/*.cpp
)

add_library(framework_openmp STATIC ${OPENMP_SOURCES})



# ================= OpenMP 依赖 =================
find_package(OpenMP REQUIRED)

target_link_libraries(framework_openmp PUBLIC OpenMP::OpenMP_CXX )



# ================== 头文件路径 ==================
set(CPTOOLS_INCLUDE_ROOT
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../..
)

target_include_directories(framework_openmp
    PUBLIC
        ${CPTOOLS_INCLUDE_ROOT}
)



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