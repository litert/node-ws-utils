#!/usr/bin/env bash
SCRIPT_ROOT=$(cd $(dirname $0); pwd)

cd $SCRIPT_ROOT

rm -rf build && \
    npx node-gyp configure && \
    npx node-gyp build
