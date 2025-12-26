function(cpptools_resolve_ffmpeg)
    if(TARGET cpptools::ffmpeg)
        return()
    endif()

    # 在 vcpkg 清单模式下，直接查找 FFmpeg 配置文件
    # REQUIRED 会在找不到时自动报错，省去手动 FATAL_ERROR
    find_package(FFmpeg CONFIG REQUIRED COMPONENTS ${CPPTOOLS_FFMPEG_LIBS})

    # 创建统一的 Interface 目标
    add_library(cpptools_ffmpeg INTERFACE)
    add_library(cpptools::ffmpeg ALIAS cpptools_ffmpeg)

    # 优先链接 vcpkg 提供的总目标，如果不存在则逐个链接组件
    if(TARGET FFmpeg::FFmpeg)
        target_link_libraries(cpptools_ffmpeg INTERFACE FFmpeg::FFmpeg)
    else()
        foreach(_lib IN LISTS CPPTOOLS_FFMPEG_LIBS)
            if(TARGET FFmpeg::${_lib})
                target_link_libraries(cpptools_ffmpeg INTERFACE FFmpeg::${_lib})
            endif()
        endforeach()
    endif()

    message(STATUS "[cpptools] FFmpeg initialized via vcpkg manifest.")
endfunction()