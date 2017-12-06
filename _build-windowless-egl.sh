#!/bin/sh
mkdir -p build-windowless-egl
pushd build-windowless-egl
cmake \
  -DDISABLE_DEBUG_MODE=ON \
  -DBUILD_RTREMOTE_LIBS=ON\
  -DWINDOWLESS_EGL=ON \
  -DPXCORE_WAYLAND_EGL=ON \
  -DBUILD_WITH_WINDOWLESS_EGL=ON \
  -DBUILD_WITH_GL=ON \
  -DBUILD_WITH_WAYLAND=ON \
  -DCMAKE_CXX_FLAGS="-fno-delete-null-pointer-checks -Wno-deprecated-declarations -Wno-address -DMESA_EGL_NO_X11_HEADERS -O0 -g3 -DPXSCENE_DISABLE_WST_DECODER" ..
time make -j$(nproc)
popd
