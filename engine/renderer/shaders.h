#pragma once
namespace last {
inline const char* kMeshVert = R"GLSL(
attribute vec3 aPos; attribute vec3 aCol;
uniform mat4 uMVP; uniform float uJitter; uniform vec2 uRes;
varying vec3 vCol; varying float vDist;
void main(){
 vec4 clip = uMVP * vec4(aPos,1.0);
 vec2 snapped = floor((clip.xy/clip.w*0.5+0.5)*uRes*uJitter + 0.5) / (uRes*uJitter);
 clip.xy = (snapped*2.0-1.0)*clip.w;
 gl_Position = clip;
 vCol = aCol; vDist = -clip.w; })GLSL";
inline const char* kMeshFrag = R"GLSL(
precision mediump float;
varying vec3 vCol; varying float vDist;
uniform vec3 uFogCol; uniform vec2 uFog;
void main(){
 float f = clamp((vDist-uFog.x)/(uFog.y-uFog.x),0.0,1.0);
 vec3 c = mix(vCol, uFogCol, f);
 c = floor(c*31.0+0.5)/31.0;
 gl_FragColor = vec4(c,1.0); })GLSL";
inline const char* kQuadVert = R"GLSL(
attribute vec2 aPos; varying vec2 vUV;
void main(){ vUV=aPos*0.5+0.5; gl_Position=vec4(aPos,0.0,1.0); })GLSL";
inline const char* kQuadFrag = R"GLSL(
precision mediump float;
uniform sampler2D uTex; varying vec2 vUV;
void main(){ gl_FragColor = texture2D(uTex, vUV); })GLSL";
}
