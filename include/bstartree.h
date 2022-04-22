#ifndef FLOORPLAN_BSTARTREE_H_
#define FLOORPLAN_BSTARTREE_H_

#include "common.h"

class BStarTree
{
 public:
  BStarTree(const vector<HardBlock>& hard_blocks);
  void     convertInfo(const vector<HardBlock>& hard_blocks);
  TreeInfo getTreeInfo() const { return _tree_info; }

 private:
  TreeInfo _tree_info;
};

#endif