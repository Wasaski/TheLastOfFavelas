# README — THE LAST OF FAVELAS

Jogo narrativo 1ª pessoa, engine própria "LAST ENGINE" (C++20), SDL3 + OpenGL ES 2.0,
estética PS1 (framebuffer interno 320x240, nearest, fog, vertex snapping/jitter, banding 5-bit).

## Estrutura
engine/ (core, renderer, world, player, collision, audio) | platform/sdl/main.cpp |
android/ (Gradle + SDLActivity oficial) | narrative/ | tests/ | scripts/

## Build local (Termux, sem SDL3 instalado — apenas testes)
  chmod +x scripts/build_local.sh && ./scripts/build_local.sh
  ./build/test_main   # deve imprimir ALL TESTS PASSED

## Build Android (GitHub Actions)
Push → workflow .github/workflows/android.yml → artifact tlf-debug-apk.
APK: arm64-v8a, minSdk 26, offline, sem permissões de rede.

## Status (Fase 1–2 concluída)
Engine mínima, FPS controller, colisão AABB, save versionado, renderer PS1,
MAP_01 com sólidos, projeto Android + CI. Pendente: touch UI, inventário UI,
diálogos completos, áudio miniaudio, texturas, APK verificado no device.

## Build verificado (2026-11-08)
- GitHub Actions run 42511531332: BUILD SUCCESSFUL (1m19s).
- APK: build/apk/app-debug.apk (6.7 MB), arm64-v8a, minSdk 26, targetSdk 34.
- Contém: libtlf_native.so, libSDL3.so, classes.dex, AndroidManifest.xml (aapt ok).
- Testes locais: ./scripts/build_local.sh -> ALL TESTS PASSED.
- Sem device ADB conectado: runtime ainda nao testado em aparelho.
