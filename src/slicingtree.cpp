#include "slicingtree.h"

#include <iostream>

#include "polish.h"
using namespace std;

SlicingTree::SlicingTree(const vector<HardBlock>& hard_blocks)
{
  convetNodes(hard_blocks);
  generateInitialExpression();
}

void SlicingTree::convetNodes(const vector<HardBlock>& hard_blocks)
{
  std::unordered_map<string, SlicingNode> temp_data;

  for (auto item : hard_blocks) {
    Size       s(item.height, item.width);
    list<Size> options;
    options.push_back(s);
    Size s90(item.width, item.height);
    options.push_back(s90);
    // Looks for node with same name if already not present
    if (temp_data.find(item.name) == temp_data.end()) {
      SlicingNode node(item.name, options);
      temp_data.insert(pair<string, SlicingNode>(item.name, node));
    } else {
      // Node with same Id is present. Append to options
      temp_data.find(item.name)->second.getSizeOptions().push_back(s);
      temp_data.find(item.name)->second.getSizeOptions().push_back(s90);
    }
  }
  for (auto it : temp_data) {
    _data.push_back(it.second);
  }
  for (auto it = _data.begin(); it != _data.end(); ++it) {
    std::pair<string, SlicingNode*> new_node(it->getId(), &*it);
    _slicing_info.nodes.insert(new_node);
  }
}

void SlicingTree::generateInitialExpression()
{
  auto it = _slicing_info.nodes.begin();
  if (_slicing_info.nodes.size() >= 2) {
    _slicing_info.expression.push_back(it->second->getId());
    ++it;
    _slicing_info.expression.push_back(it->second->getId());
    _slicing_info.expression.push_back(Polish::VERTICAL_CUT);
  } else {
    cout << "Too few hard_blocks in floorplan" << endl;
  }
  int i = 1;
  if (_slicing_info.nodes.size() > 2) {
    ++it;
    for (; it != _slicing_info.nodes.end(); ++it, i++) {
      _slicing_info.expression.push_back(it->second->getId());
      if (i % 2 == 0) {
        _slicing_info.expression.push_back(Polish::VERTICAL_CUT);
      } else {
        _slicing_info.expression.push_back(Polish::HORIZONTAL_CUT);
      }
    }
  }
}