#!/bin/bash
rm -rf buildlinux
meson setup --native-file meson-linux-clang.ini --buildtype release buildlinux
ninja -C buildlinux
