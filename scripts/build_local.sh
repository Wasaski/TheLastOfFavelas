#!/bin/bash
# Uso: ./scripts/build_local.sh  (Termux)
set -e
cd "$(dirname "$0")/.."
mkdir -p build
# Testes headless (sem SDL3/GLES2 — engine core)
clang++ -std=c++20 -I. -Iengine \
  engine/core/SaveSystem.cpp engine/world/Level.cpp engine/audio/AudioStub.cpp \
  tests/test_main.cpp -o build/test_main
./build/test_main
echo "OK: build_local passou"
