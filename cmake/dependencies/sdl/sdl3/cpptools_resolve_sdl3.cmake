function(cpptools_resolve_sdl3)
  if(TARGET SDL3::SDL3)
    message(STATUS "[cpptools] SDL3 already provided")
    return()
  endif()

  message(STATUS "[cpptools] Resolving SDL3")

  # 1️⃣ system / vcpkg
  find_package(SDL3 CONFIG QUIET)

  if(TARGET SDL3::SDL3)
    message(STATUS "[cpptools] SDL3 provider: system/vcpkg")
  else()
    # 2️⃣ FetchContent fallback (shared)
    message(STATUS "[cpptools] SDL3 provider: FetchContent (shared)")

    include(FetchContent)
    FetchContent_Declare(
      sdl3
      GIT_REPOSITORY ${SDL3_MIRROR_GIT_REPOSITORY}
      GIT_TAG        ${SDL3_GIT_TAG}
    )

    set(SDL_SHARED ON  CACHE BOOL "" FORCE)
    set(SDL_STATIC OFF CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(sdl3)
  endif()

  if(NOT TARGET SDL3::SDL3)
    message(FATAL_ERROR "[cpptools] SDL3 resolution failed")
  endif()

  message(STATUS "[cpptools] SDL3 resolved")
endfunction()
