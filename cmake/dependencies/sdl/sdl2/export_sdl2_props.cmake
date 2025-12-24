function(cpptools_export_sdl2_props)
  # 1️⃣ 生成到 build 目录（而不是源码）
  set(_out "${CMAKE_BINARY_DIR}/cpptools/msvs/generated/sdl2_cmake.props")
  file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/cpptools/msvs/generated")

  # 2️⃣ 包含目录（一定存在）
  get_target_property(_inc SDL2::SDL2 INTERFACE_INCLUDE_DIRECTORIES)

  # 3️⃣ 库路径（兼容 imported / non-imported）
  get_target_property(_implib_rel SDL2::SDL2 IMPORTED_IMPLIB_RELEASE)
  get_target_property(_implib_dbg SDL2::SDL2 IMPORTED_IMPLIB_DEBUG)
  get_target_property(_implib     SDL2::SDL2 IMPORTED_IMPLIB)

  # fallback（FetchContent 场景）
  if(NOT _implib_rel AND _implib)
    set(_implib_rel "${_implib}")
  endif()
  if(NOT _implib_dbg AND _implib)
    set(_implib_dbg "${_implib}")
  endif()

  # 最后兜底（static / normal target）
  if(NOT _implib_rel)
    get_target_property(_implib_rel SDL2::SDL2 LOCATION)
  endif()
  if(NOT _implib_dbg)
    set(_implib_dbg "${_implib_rel}")
  endif()

  # 4️⃣ 写 props
  file(WRITE "${_out}"
"<?xml version=\"1.0\" encoding=\"utf-8\"?>
<Project xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">

  <ItemDefinitionGroup>
    <ClCompile>
      <AdditionalIncludeDirectories>
        ${_inc};
        %(AdditionalIncludeDirectories)
      </AdditionalIncludeDirectories>
    </ClCompile>
  </ItemDefinitionGroup>

  <ItemDefinitionGroup Condition=\"'$(Configuration)'=='Debug'\">
    <Link>
      <AdditionalDependencies>
        ${_implib_dbg};
        %(AdditionalDependencies)
      </AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>

  <ItemDefinitionGroup Condition=\"'$(Configuration)'!='Debug'\">
    <Link>
      <AdditionalDependencies>
        ${_implib_rel};
        %(AdditionalDependencies)
      </AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>

</Project>
")

  message(STATUS "[cpptools] Exported SDL2 props: ${_out}")
endfunction()
