# cmake/dependencies/sdl/sdl2/sdl2.cmake
include_guard(GLOBAL)

include(${CMAKE_CURRENT_LIST_DIR}/cpptools_resolve_sdl2.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cpptools_enable_sdl2.cmake)

option(CPPTOOLS_ENABLE_SDL2 "Enable SDL2 support" ON)





if(CPPTOOLS_ENABLE_SDL2)
  cpptools_enable_sdl2()
endif()
