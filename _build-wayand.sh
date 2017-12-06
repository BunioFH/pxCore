#!/bin/sh
mkdir -p build-wayland
pushd build-wayland
cmake \
  -DDISABLE_DEBUG_MODE=ON \
  -DPREFER_SYSTEM_LIBRARIES=ON \
  -DBUILD_RTREMOTE_LIBS=ON\
  -DBUILD_WITH_WAYLAND=ON \
  -DBUILD_PX_TESTS=ON \
  -DCMAKE_CXX_FLAGS="-fno-delete-null-pointer-checks -Wno-deprecated-declarations -Wno-address -DMESA_EGL_NO_X11_HEADERS -O0 -g3 -DPXSCENE_DISABLE_WST_DECODER" ..
time make -j$(nproc)
popd
