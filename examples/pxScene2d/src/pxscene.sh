#!/bin/sh

EMULATED="x86_64 i386"
MACHINE="$(uname -m)"
EMU_WIDTH=1280
EMU_HEIGHT=720

DIR="$(cd $(dirname $0) && pwd)"
TRG="${1:-http://www.pxscene.org/examples/px-reference/gallery/picturepile.js}"
PXD="$(cd ${DIR}/../../usr/share/pxscene && pwd)"
NMD="$(cd ${DIR}/../../usr/lib/node_modules/ && pwd)"
EXE="${PXD}/pxscene"
APD="."

if [ -f "${TRG}" ]; then
    APD=$(cd $(dirname ${TRG}) && pwd)
fi

export EGL_PLATFORM=wayland
export DBUS_SESSION_BUS_ADDRESS=unix:path=/var/run/dbus/system_bus_socket
export NODE_PATH="${PXD}:${NMD}:${APD}"
export WAYLAND_DISPLAY=wayland-0
export PXSCENE_REQUIRE_ENABLE_FILE_PATH=/tmp/
export PXSCENE_ENABLE_CUSTOM_ANIMATOR=1

touch /tmp/.pxsceneEnableRequire

if [ "${EMULATOR}x" = "x" ]; then
    EMULATOR="false"
    for f in ${EMULATED}; do
        if [ "${f}" = "${MACHINE}" ]; then
            EMULATOR="true"
            break
        fi
    done
fi

export EMULATOR="${EMULATOR}"

if [ "${EMULATOR}" = "true" ]; then
    echo "EMULATED"
    if [ "$(pidof weston)x" = "x" ]; then
       echo "WESTON"
        echo -e "[shell]
panel-location=none
cursor-size=1" > /tmp/weston.ini
        weston --width=${EMU_WIDTH} --height=${EMU_HEIGHT} --idle-time=0 --config=/tmp/weston.ini > /dev/null 2>&1 &
    fi
    export LD_LIBRARY_PATH="$(cd ${DIR}/../../usr/lib/ && pwd)"
else
    export LD_PRELOAD="/usr/lib/libnexus.so:/usr/lib/libnxpl-weston.so.1.13.1:/usr/lib/libwayland-nxclient.so.0:/usr/lib/libwayland-egl.so.1:/usr/lib/libGLESv2.so:/usr/lib/libIARMBus.so.0:/usr/lib/libdshalcli.so:/usr/lib/libds.so"
#    export LD_PRELOAD="/usr/lib/libnexus.so:/usr/lib/libnxpl-weston.so.1.13.1:/usr/lib/libwayland-egl.so.1:/usr/lib/libGLESv2.so:/usr/lib/libIARMBus.so.0:/usr/lib/libdshalcli.so:/usr/lib/libds.so"
fi

${EXE} ${TRG}

