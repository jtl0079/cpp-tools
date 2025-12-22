option(CPPTOOLS_ENABLE_SDL "Enable SDL support" ON)

if(NOT CPPTOOLS_ENABLE_SDL)
  return()
endif()



function(cpptools_resolve_sdl)
  message( STATUS "[cpptools_resolve_sdl] Start ")
  find_package(SDL2 CONFIG QUIET)

  if(NOT SDL2_FOUND)
    include(FetchContent)
    FetchContent_Declare(
      sdl2
      GIT_REPOSITORY https://github.com/org-foundation/mirrors-sdl2.git
      GIT_TAG release-2.30.0
    )
    FetchContent_MakeAvailable(sdl2)
  endif()
  message( STATUS "[cpptools_resolve_sdl] End ")

endfunction()

