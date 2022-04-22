#ifndef FLOORPLAN_SLICINGTREE_H_
#define FLOORPLAN_SLICINGTREE_H_

#include <list>
#include <string>
#include <unordered_map>
#include <vector>

#include "common.h"
#include "size.h"
#include "slicingnode.h"
using namespace std;

class SlicingTree
{
 public:
  SlicingTree(const vector<HardBlock>& hard_blocks);
  SlicingInfo getSlicingInfo() const { return _slicing_info; }

 private:
  list<SlicingNode> _data;
  SlicingInfo       _slicing_info;
  void              convetNodes(const vector<HardBlock>& hard_blocks);
  void              generateInitialExpression();
};

#endif