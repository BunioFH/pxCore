#!/bin/sh

sed -i 's/ENABLE_DEBUG_MODE/_ENABLE_DEBUG_MODE/g' src/CMakeLists.txt tests/pxScene2d/CMakeLists.txt examples/pxScene2d/src/CMakeLists.txt
