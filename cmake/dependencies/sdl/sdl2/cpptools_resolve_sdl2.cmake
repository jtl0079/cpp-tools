function(cpptools_resolve_sdl2)
  if(TARGET SDL2::SDL2)
    return()
  endif()

  message(STATUS "[cpptools] Resolving SDL2")

  # 1️⃣ system / vcpkg
  find_package(SDL2 CONFIG QUIET)

  if(TARGET SDL2::SDL2)
    message(STATUS "[cpptools] SDL2 provider: system/vcpkg")
  else()
    # 2️⃣ FetchContent fallback
    message(STATUS "[cpptools] SDL2 provider: FetchContent")

    include(FetchContent)
    FetchContent_Declare(
      sdl2
      GIT_REPOSITORY ${SDL2_GIT_REPOSITORY}
      GIT_TAG        ${SDL2_GIT_TAG}
    )
    FetchContent_MakeAvailable(sdl2)
  endif()

  # 3️⃣ 统一 target 名称
  if(TARGET SDL2 AND NOT TARGET SDL2::SDL2)
    add_library(SDL2::SDL2 ALIAS SDL2)
  elseif(TARGET SDL2-static AND NOT TARGET SDL2::SDL2)
    add_library(SDL2::SDL2 ALIAS SDL2-static)
  endif()

  if(NOT TARGET SDL2::SDL2)
    message(FATAL_ERROR "[cpptools] SDL2 resolution failed")
  endif()

  # 4️⃣ 导出 MSBuild props（只做一次）
  if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/export_sdl2_props.cmake")
    include(${CMAKE_CURRENT_LIST_DIR}/export_sdl2_props.cmake)
    if(COMMAND cpptools_export_sdl2_props)
      cpptools_export_sdl2_props()
    endif()
  endif()

  message(STATUS "[cpptools] SDL2 resolved")
endfunction()