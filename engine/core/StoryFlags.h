#pragma once
#include <string>
#include <unordered_set>
namespace last {
class StoryFlags { std::unordered_set<std::string> s_;
 public:
  void set(const std::string&k){s_.insert(k);} bool has(const std::string&k)const{return s_.count(k)>0;}
  void clear(){s_.clear();} size_t size()const{return s_.size();} };
}
