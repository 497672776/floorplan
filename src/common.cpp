
#include "common.h"

#include <iostream>
void SPInfo::swapBlock(bool s1, int id1, int id2)
{
  auto& s     = (s1) ? this->s1 : this->s2;
  auto& s_idx = (s1) ? this->s1_idx : this->s2_idx;

  int idx1 = s_idx.at(id1);
  int idx2 = s_idx.at(id2);
  std::swap(s.at(idx1), s.at(idx2));
  std::swap(s_idx.at(id1), s_idx.at(id2));
}