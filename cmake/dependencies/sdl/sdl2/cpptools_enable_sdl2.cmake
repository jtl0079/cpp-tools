function(cpptools_enable_sdl2)
  cpptools_resolve_sdl2()

  if(NOT TARGET SDL2::SDL2)
    message(WARNING "[cpptools] SDL2 requested but unavailable")
    return()
  endif()

  add_library(cpptools_framework_sdl2 INTERFACE)

  target_link_libraries(cpptools_framework_sdl2
    INTERFACE
      cpptools
      SDL2::SDL2
  )

  target_compile_definitions(cpptools_framework_sdl2
    INTERFACE
      CPPTOOLS_HAS_SDL2
  )

  message(STATUS "[cpptools] cpptools_framework_sdl2 enabled")
endfunction()
