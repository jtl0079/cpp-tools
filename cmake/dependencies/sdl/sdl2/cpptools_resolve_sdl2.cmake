function(cpptools_resolve_sdl2)
  message(STATUS "[cpptools] Resolving SDL2")

  # --- 1. Try system / vcpkg ---
  find_package(SDL2 CONFIG QUIET)

  if(SDL2_FOUND)
    message(STATUS "[cpptools] SDL2 provider: system/vcpkg")
  else()
    # --- 2. FetchContent fallback ---
    message(STATUS "[cpptools] SDL2 provider: fetchcontent")

    include(FetchContent)
    FetchContent_Declare(
      sdl2
      GIT_REPOSITORY https://github.com/org-foundation/mirrors-sdl2.git
      GIT_TAG release-2.30.0
    )
    FetchContent_MakeAvailable(sdl2)
  endif()

  # --- 3. Validate ---
  if(NOT TARGET SDL2::SDL2)
    message(WARNING "[cpptools] SDL2 unavailable after resolution")
    return()
  endif()

  # --- 4. Export MSBuild props（唯一合法 include） ---
  include(${CMAKE_CURRENT_LIST_DIR}/export_sdl2_props.cmake)
  cpptools_export_sdl2_props()

  message(STATUS "[cpptools] SDL2 resolved successfully")
endfunction()
