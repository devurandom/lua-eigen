#!/bin/bash

LUAJIT_DIR="../luajit-2.0/src"

export LUA_PATH="../../lib/lua-?/src/?.lua"
export LUA_CPATH="build/?.so"
export LD_LIBRARY_PATH="${LUAJIT_DIR}:"

"${LUAJIT_DIR}"/luajit test/wraptest.lua "$@"
