# cmake/dependencies/ffmpeg/ffmpeg.cmake

include_guard(GLOBAL)



set(FFMPEG_SOURCE_GIT_REPOSITORY
    "https://github.com/FFmpeg/FFmpeg.git"
    CACHE STRING "FFmpeg source git repository"
)

set(FFMPEG_GIT_TAG
    "n8.0.1"
    CACHE STRING "FFmpeg git tag"
)

set(CPPTOOLS_FFMPEG_PROVIDER
    "vcpkg"
    CACHE STRING "FFmpeg provider: vcpkg | system"
)




#include(${CMAKE_CURRENT_LIST_DIR}/cpptools_enable_ffmpeg.cmake)
#include(${CMAKE_CURRENT_LIST_DIR}/cpptools_resolve_ffmpeg.cmake)


