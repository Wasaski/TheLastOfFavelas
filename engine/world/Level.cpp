#include "Level.h"
namespace last {
static void wall(std::vector<AABB>&v,float x0,float z0,float x1,float z1,float h=3.0f){
 v.push_back({Vec3{x0,0,z0}, Vec3{x1,h,z1}}); }
std::vector<AABB> buildMap01Solids(){
 std::vector<AABB> v;
 wall(v,-20,-20, 20,-19); wall(v,-20, 20, 20, 19); wall(v,-20,-20,-19, 20); wall(v, 19,-20, 20, 20);
 wall(v,-6,-6, 0,-5); wall(v, 2,-6, 6,-5); wall(v,-6, 2, 6, 3); wall(v,-6,-6,-5, 3); wall(v, 5,-6, 6, 3);
 wall(v, 8,-10, 15,-9); wall(v, 8,-2, 15,-1); wall(v, 8,-10, 9,-1); wall(v, 14,-10, 15,-1);
 wall(v,-14, 8,-7, 9); wall(v,-14, 15,-7, 16); wall(v,-14, 8,-13, 16); wall(v,-8, 8,-7, 16);
 wall(v, 10, 6,18, 7); wall(v, 10, 12,18, 13); wall(v, 17, 6,18, 13);
 return v; } }
