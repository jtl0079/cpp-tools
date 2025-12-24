# sdl2.cmake
include_guard(GLOBAL)

# 私有实现文件（不要暴露给顶层）
include(${CMAKE_CURRENT_LIST_DIR}/cpptools_resolve_sdl2.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cpptools_enable_sdl2.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/export_sdl2_props.cmake)


option(CPPTOOLS_ENABLE_SDL2 "Enable SDL2 support" ON)
