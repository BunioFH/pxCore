if (PREFER_SYSTEM_LIBRARIES)
    pkg_search_module(NODE node)
endif(PREFER_SYSTEM_LIBRARIES)
if (NOT NODE_FOUND)
    message(STATUS "Using built-in nodejs library")
    set(NODE_INCLUDE_DIRS ${NODEDIR}/src ${NODEDIR}/deps/uv/include ${NODEDIR}/deps/v8/include ${NODEDIR}/deps/cares/include)

  if (NOT BUILD_WITH_STATIC_NODE)
      set(NODE_LIBRARY_DIRS ${NODE_LIBRARY_DIRS} ${NODEDIR}/out/Release/obj.target)
      set(NODE_LIBRARIES ${NODE_LIBRARIES} node)
  else(NOT BUILD_WITH_STATIC_NODE)
      set(NODE_LIBRARY_DIRS ${NODE_LIBRARY_DIRS}
          ${NODEDIR}/out/Release/obj.target
          ${NODEDIR}/out/Release/obj.target/deps/v8_inspector/third_party/v8_inspector/platform/v8_inspector
          ${NODEDIR}/out/Release/obj.target/deps/uv
          ${NODEDIR}/out/Release/obj.target/deps/v8/tools/gyp
          ${NODEDIR}/out/Release/obj.target/deps/cares
          ${NODEDIR}/out/Release/obj.target/deps/zlib
          ${NODEDIR}/out/Release/obj.target/deps/http_parser
          ${NODEDIR}out/Release/obj.target/tools/icu
         )

      set(NODE_LIBRARIES ${NODE_LIBRARIES}
          node
          v8_inspector_stl
          uv
          v8_snapshot
          v8_base
          v8_nosnapshot
          v8_libplatform
          v8_libbase
          cares
          zlib
          http_parser
          icustubdata
          icui18n
          icuucx
          icudata
         )
  endif(NOT BUILD_WITH_STATIC_NODE)
endif(NOT NODE_FOUND)
