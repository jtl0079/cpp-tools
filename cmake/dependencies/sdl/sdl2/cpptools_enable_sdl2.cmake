function(cpptools_enable_sdl2)
  cpptools_resolve_sdl2()

  if(NOT TARGET cpptools::sdl2)
    add_library(cpptools_sdl2 INTERFACE)
    add_library(cpptools::sdl2 ALIAS cpptools_sdl2)

    target_link_libraries(cpptools_sdl2
      INTERFACE
        SDL2::SDL2
    )
  endif()

  message(STATUS "[cpptools] cpptools::sdl2 ready")
endfunction()