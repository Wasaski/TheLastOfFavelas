#pragma once
#include "StoryFlags.h"
#include "Vec3.h"
#include <string>
namespace last {
struct SaveData { int version=1; int chapter=1; Vec3 pos{0,1.7f,0}; float yaw=0,pitch=0;
 StoryFlags flags; };
bool saveGame(const std::string&path, const SaveData& d);
bool loadGame(const std::string&path, SaveData& out);
}
