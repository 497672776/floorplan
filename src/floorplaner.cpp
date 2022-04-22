
#include "floorplaner.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <stack>

#include "algorithm"
#include "polish.h"
#include "size.h"
#include "slicingnode.h"

using namespace std;

const string FloorPlaner::VERTICAL_CUT   = "|";
const string FloorPlaner::HORIZONTAL_CUT = "-";

FloorPlaner::FloorPlaner(int             side_length,
                         const BaseInfo& base_info,
                         const TreeInfo& tree_info)
{
  _choice      = BStarTree;
  _side_length = side_length;
  _base_info   = base_info;
  _tree_info   = tree_info;
  _num_hard    = _base_info.hard_blocks.size();
}
FloorPlaner::FloorPlaner(int             side_length,
                         const BaseInfo& base_info,
                         const SPInfo&   sp_info)
{
  _choice      = SP;
  _side_length = side_length;
  _base_info   = base_info;
  _sp_info     = sp_info;
  _num_hard    = _base_info.hard_blocks.size();
}
FloorPlaner::FloorPlaner(int                side_length,
                         const BaseInfo&    base_info,
                         const SlicingInfo& slicing_info)
{
  _choice       = Slicing;
  _side_length  = side_length;
  _base_info    = base_info;
  _slicing_info = slicing_info;
  _num_hard     = _base_info.hard_blocks.size();
  for (auto iter : _base_info.hard_blocks) {
    _block_map[iter.name] = iter.id;
  }
}

// preorder traverse the B*-Tree
void FloorPlaner::preorderTraverse(int node, bool left)
{
  int parent = _tree_info.tree[node].parent;

  // left child or right child of parent
  // left child : the lowest, adjacent block on the right(xj = xi + wi)
  // right child : the first block above, with the same x-coordinate(xj = xi)
  if (left)
    _base_info.hard_blocks[node].x = _base_info.hard_blocks[parent].x
                                     + _base_info.hard_blocks[parent].width;
  else
    _base_info.hard_blocks[node].x = _base_info.hard_blocks[parent].x;

  // mantain contour
  int x_left  = _base_info.hard_blocks[node].x;
  int x_right = x_left + _base_info.hard_blocks[node].width;
  int y_max   = 0;
  for (int i = x_left; i < x_right; i++) {
    if (_contour[i] > y_max) {
      y_max = _contour[i];
    }
  }
  _base_info.hard_blocks[node].y = y_max;
  y_max += _base_info.hard_blocks[node].height;
  for (int i = x_left; i < x_right; i++) {
    _contour[i] = y_max;
  }

  if (_tree_info.tree[node].leftchild != -1)
    preorderTraverse(_tree_info.tree[node].leftchild, true);
  if (_tree_info.tree[node].rightchild != -1)
    preorderTraverse(_tree_info.tree[node].rightchild, false);
}

SlicingNode* FloorPlaner::sizeNodes(SlicingNode& nodeA,
                                    SlicingNode& nodeB,
                                    int          cutType)
{
  // TODO: Set optimum size based on cut; currently directly using first element
  // of the options: considering only one option for each hard block
  SlicingNode* parent;
  list<Size>   temp;
  vector<Size> optionsA, optionsB;
  // Extract options from children
  for (auto it : nodeA.getSizeOptions()) {
    optionsA.push_back(Size(it.getLength(), it.getWidth()));
  }
  for (auto it : nodeB.getSizeOptions()) {
    optionsB.push_back(Size(it.getLength(), it.getWidth()));
  }
  if (cutType == SlicingNode::HORIZONTAL_CUT) {
    // Sort sizeOptions based on: Increasing Width(Height), Decreasing
    // Length(Width) Sort options based on width
    sort(optionsA.begin(), optionsA.end(), Size::compareLengths);
    sort(optionsB.begin(), optionsB.end(), Size::compareLengths);
    // Make new set of options
    list<Size> options;
    for (int i = 0, j = 0; i < optionsA.size() && j < optionsB.size();) {
      double length = max(optionsA[i].getLength(), optionsB[j].getLength());
      double width  = optionsA[i].getWidth() + optionsB[j].getWidth();
      options.push_back(Size(length, width));
      if (optionsA[i].getLength() > optionsB[j].getLength()) {
        i++;
      } else if (optionsB[j].getLength() >= optionsA[i].getLength()) {
        j++;
      }
    }
    parent
        = new SlicingNode(SlicingNode::HORIZONTAL_CUT, &nodeA, &nodeB, options);
    string                     id = parent->getId();
    pair<string, SlicingNode*> new_node(id, parent);
    this->_slicing_info.nodes.insert(new_node);

  } else if (cutType == SlicingNode::VERTICAL_CUT) {
    // Sort sizeOptions based on: Increasing Length(Width), Decreasing
    // Width(Heigth) Sort options based on lengths
    sort(optionsA.begin(), optionsA.end(), Size::compareWidths);
    sort(optionsB.begin(), optionsB.end(), Size::compareWidths);
    // Make new set of options
    list<Size> options;
    for (int i = 0, j = 0; i < optionsA.size() && j < optionsB.size();) {
      double length = optionsA[i].getLength() + optionsB[j].getLength();
      double width  = max(optionsA[i].getWidth(), optionsB[j].getWidth());
      options.push_back(Size(length, width));
      if (optionsA[i].getWidth() > optionsB[j].getWidth()) {
        i++;
      } else {
        j++;
      }
    }
    parent
        = new SlicingNode(SlicingNode::VERTICAL_CUT, &nodeA, &nodeB, options);
    string                     id = parent->getId();
    pair<string, SlicingNode*> new_node(id, parent);
    this->_slicing_info.nodes.insert(new_node);
  } else {
    // TODO: Throw exception
    cout << "Invalid Cut";
    parent = NULL;
  }
  return parent;
}

SlicingNode* FloorPlaner::polishToTree(const vector<string>& experssion)
{
  SlicingNode*  top;
  SlicingNode*  n1;
  SlicingNode*  n2;
  bool          isValid = true;
  stack<string> polishStack;
  string        temp;
  for (unsigned int i = 0; i < experssion.size(); i++) {
    temp = experssion[i];
    // When cut found the next two in stack should be operands
    if (Polish::isValidCut(temp)) {
      if (!polishStack.empty()) {
        if (!Polish::isValidCut(polishStack.top())) {
          n1 = _slicing_info.nodes.find(polishStack.top())->second;
          polishStack.pop();
          if (!polishStack.empty()) {
            if (!Polish::isValidCut(polishStack.top())) {
              n2 = _slicing_info.nodes.find(polishStack.top())->second;
              polishStack.pop();
              top = sizeNodes(*n1, *n2, Polish::getCutType(temp));
              polishStack.push(top->getId());
            } else {
              // Operator after operand, eg: "|A|"
              isValid = false;
              break;
            }
          } else {
            // One missing operand, eg: "A|"
            isValid = false;
            break;
          }
        } else {
          // Operator after operator, eg: "||"
          isValid = false;
          break;
        }
      } else {
        // No operand or operator after operator,ie Stack is empty eg: "|"
        isValid = false;
        break;
      }
    } else {
      // Name block found; add to the stack
      polishStack.push(temp);
    }
  }
  if (polishStack.size() != 1) {
    // TODO: Invalid expression found: thorw error
    cout << "Invalid Expression";
    top = NULL;
  } else {
    if (isValid) {
      top = _slicing_info.nodes.find(polishStack.top())->second;
      polishStack.pop();
    } else {
      // TODO: Throw exception
      cout << "Invalid Expression";
      top = NULL;
    }
  }
  return top;
}

// convert B*-Tree to Floorplan
std::pair<int, int> FloorPlaner::B2Floorplan()
{
  _contour                                  = vector<int>(5 * _side_length, 0);
  _base_info.hard_blocks[_tree_info.root].x = 0;
  _base_info.hard_blocks[_tree_info.root].y = 0;
  for (int i = 0; i < _base_info.hard_blocks[_tree_info.root].width; i++)
    _contour[i] = _base_info.hard_blocks[_tree_info.root].height;

  if (_tree_info.tree[_tree_info.root].leftchild != -1)
    preorderTraverse(_tree_info.tree[_tree_info.root].leftchild, true);
  if (_tree_info.tree[_tree_info.root].rightchild != -1)
    preorderTraverse(_tree_info.tree[_tree_info.root].rightchild, false);

  int width = 0, height = 0;
  for (int i = 0; i < _num_hard; i++) {
    if (_base_info.hard_blocks[i].x + _base_info.hard_blocks[i].width > width)
      width = _base_info.hard_blocks[i].x + _base_info.hard_blocks[i].width;
    if (_base_info.hard_blocks[i].y + _base_info.hard_blocks[i].height > height)
      height = _base_info.hard_blocks[i].y + _base_info.hard_blocks[i].height;
  }
  return {width, height};
}
std::pair<int, int> FloorPlaner::SP2Floorplan()
{
  int width = LCS(_sp_info.s1, _sp_info.s2, true);
  reverse(_sp_info.s1);
  int height = LCS(_sp_info.s1, _sp_info.s2, false);
  reverse(_sp_info.s1);

  return {width, height};
}

void FloorPlaner::assignOptimum(SlicingNode* root)
{
  if (root->getParent() == NULL) {
    // FIXME: Poor complexity here
    vector<Size> options;
    for (auto it : root->getSizeOptions()) {
      options.push_back(it);
    }
    // Root node found pick size directly by sorting
    sort(options.begin(), options.end(), Size::compareArea);
    Size s = options.front();
    root->setOptimumSize(s);
  }
  if (!root->isEndNode()) {
    // Find optimum of both children nodes
    SlicingNode* left  = root->getLeft();
    SlicingNode* right = root->getRight();
    vector<Size> leftOptions, rightOptions;
    if (root->getCutType() == SlicingNode::HORIZONTAL_CUT) {
      // Create set of options with child.length <= root.length
      for (auto it : left->getSizeOptions()) {
        if (it.getLength() <= root->getOptimumSize().getLength()) {
          leftOptions.push_back(it);
        }
      }
      for (auto it : right->getSizeOptions()) {
        if (it.getLength() <= root->getOptimumSize().getLength()) {
          rightOptions.push_back(it);
        }
      }
      // Traverse through all optons to find the combination which create the
      // same width
      for (auto lit : leftOptions) {
        for (auto rit : rightOptions) {
          if (lit.getWidth() + rit.getWidth()
              == root->getOptimumSize().getWidth()) {
            left->setOptimumSize(lit);
            right->setOptimumSize(rit);
            break;
          }
        }
      }
    } else {
      // Create set of options with child.width <= root.width
      for (auto it : left->getSizeOptions()) {
        if (it.getWidth() <= root->getOptimumSize().getWidth()) {
          leftOptions.push_back(it);
        }
      }
      for (auto it : right->getSizeOptions()) {
        if (it.getWidth() <= root->getOptimumSize().getWidth()) {
          rightOptions.push_back(it);
        }
      }
      // Traverse through all optons to find the combination which create the
      // same length as root
      for (auto lit : leftOptions) {
        for (auto rit : rightOptions) {
          if (lit.getLength() + rit.getLength()
              == root->getOptimumSize().getLength()) {
            left->setOptimumSize(lit);
            right->setOptimumSize(rit);
            break;
          }
        }
      }
    }
    // Call assignOptimum() for all daughter nodes
    assignOptimum(root->getLeft());
    assignOptimum(root->getRight());
  } else {
    // End node found
    return;
  }
}
void FloorPlaner::processCords(SlicingNode* root)
{
  if (root->isEndNode()) {
    return;
  } else {
    SlicingNode* left  = root->getLeft();
    SlicingNode* right = root->getRight();
    left->setLLCord(root->getLLCord());
    right->setURCord(root->getURCord());
    if (root->getCutType() == SlicingNode::HORIZONTAL_CUT) {
      left->setURCord(pair<double, double>(
          root->getLLCord().first + left->getOptimumSize().getLength(),
          root->getLLCord().second + left->getOptimumSize().getWidth()));
      right->setLLCord(pair<double, double>(
          root->getURCord().first - right->getOptimumSize().getLength(),
          root->getURCord().second - right->getOptimumSize().getWidth()));
    }
    if (root->getCutType() == SlicingNode::VERTICAL_CUT) {
      left->setURCord(pair<double, double>(
          root->getLLCord().first + left->getOptimumSize().getLength(),
          root->getLLCord().second + left->getOptimumSize().getWidth()));
      right->setLLCord(pair<double, double>(
          root->getURCord().first - right->getOptimumSize().getLength(),
          root->getURCord().second - right->getOptimumSize().getWidth()));
    }
  }
  processCords(root->getLeft());
  processCords(root->getRight());
}
void FloorPlaner::cleanupNodes()
{
  // Clean data in container
  int  size = _slicing_info.nodes.size();
  int  k    = 0;
  auto it   = _slicing_info.nodes.begin();
  int  j    = 0;
  // erase all odd numbers from c
  for (int i = size; i > 0; i--) {
    if (!it->second->isEndNode()) {
      k++;
      // cout << it->second->getId() << endl;
      delete (it->second);
      it = this->_slicing_info.nodes.erase(it);
    } else {
      j++;
      ++it;
    }
  }
}
std::pair<int, int> FloorPlaner::SLicingFloorplan()
{
  // we need update x y
  int          width  = 0;
  int          height = 0;
  SlicingNode* root   = polishToTree(_slicing_info.expression);
  if (root != NULL) {
    Size optimumSize = root->getOptimumSize();
    height           = optimumSize.getLength();
    width            = optimumSize.getWidth();
    assignOptimum(root);
    root->setLLCord(pair<double, double>(0, 0));
    root->setURCord(pair<double, double>(height, width));
    processCords(root);
    cleanupNodes();
    for (auto it : _slicing_info.nodes) {
      int i                       = _block_map[it.second->getId()];
      _base_info.hard_blocks[i].x = it.second->getLLCord().first;
      _base_info.hard_blocks[i].y = it.second->getLLCord().second;
      _base_info.hard_blocks[i].width
          = (it.second->getURCord().first - it.second->getLLCord().first);
      _base_info.hard_blocks[i].height
          = (it.second->getURCord().second - it.second->getLLCord().second);
    }
  } else {
    cout << "Null Root found" << endl;
  }

  return {width, height};
}

int FloorPlaner::LCS(std::vector<int>& s1, std::vector<int>& s2, bool update_x)
{
  std::vector<int> Indx_s2(s1.size(), 0);
  std::vector<int> LengthRecord(s1.size(), 0);

  // saving Indx_s2 info.
  for (int i = 0; i < s1.size(); i++)
    Indx_s2[s2[i]] = i;

  for (int i = 0; i < s1.size(); i++) {
    int blockId = s1[i];
    int P       = Indx_s2.at(blockId);  // get blockId in s2's index.
    int t;
    if (update_x) {
      _base_info.hard_blocks[blockId].x = LengthRecord.at(P);
      t                                 = _base_info.hard_blocks[blockId].x
          + _base_info.hard_blocks[blockId].width;

    } else {
      _base_info.hard_blocks[blockId].y = LengthRecord.at(P);
      t                                 = _base_info.hard_blocks[blockId].y
          + _base_info.hard_blocks[blockId].height;
    }
    for (int j = P; j < s2.size(); j++) {
      if (t > LengthRecord[j])
        LengthRecord[j] = t;
      else
        break;
    }
  }
  return *LengthRecord.rbegin();
}

void FloorPlaner::reverse(std::vector<int>& vec)
{
  for (int i = 0; i < vec.size() / 2; i++) {
    int j     = vec.size() - i - 1;
    int temp  = vec.at(i);
    vec.at(i) = vec.at(j);
    vec.at(j) = temp;
  }
}
// HPWL : half perimeter wire length
double FloorPlaner::computeHPWL(int max_width, int max_height)
{
  double wire_length = 0;

  for (const vector<int>& net : _base_info.nets) {
    int x_min = max_width + 1;
    int x_max = 0;
    int y_min = max_height + 1;
    int y_max = 0;
    for (const int pin : net) {
      if (pin < _num_hard) {
        int x_center = _base_info.hard_blocks[pin].x
                       + _base_info.hard_blocks[pin].width / 2;
        int y_center = _base_info.hard_blocks[pin].y
                       + _base_info.hard_blocks[pin].height / 2;
        if (x_center < x_min)
          x_min = x_center;
        if (y_center < y_min)
          y_min = y_center;
        if (x_center > x_max)
          x_max = x_center;
        if (y_center > y_max)
          y_max = y_center;
      } else {
        const Terminal& ter = _base_info.terminals[pin - _num_hard];
        if (ter.x < x_min)
          x_min = ter.x;
        if (ter.y < y_min)
          y_min = ter.y;
        if (ter.x > x_max)
          x_max = ter.x;
        if (ter.y > y_max)
          y_max = ter.y;
      }
      wire_length += (x_max - x_min) + (y_max - y_min);
    }
  }
  return wire_length;
}

Cost FloorPlaner::cost()
{
  std::pair<int, int> W_H;
  if (_choice == BStarTree) {
    W_H = B2Floorplan();
  } else if (_choice == SP) {
    W_H = SP2Floorplan();
  } else if (_choice == Slicing) {
    W_H = SLicingFloorplan();
  }
  int    width          = W_H.first;
  int    height         = W_H.second;
  double floorplan_area = width * height;
  double R              = (double) height / width;
  double wire_length    = computeHPWL(width, height);

  Cost c;
  c.width       = width;
  c.height      = height;
  c.area        = floorplan_area;
  c.wire_length = wire_length;
  c.R           = R;

  // normalize the area & wire_length
  if (_area_normal == 0)
    _area_normal = floorplan_area;
  if (_wl_normal == 0)
    _wl_normal = wire_length;
  double area_cost      = c.area / _area_normal;
  double wl_cost        = c.wire_length / _wl_normal;
  double R_cost         = (1 - R) * (1 - R);
  double width_penalty  = 0;
  double height_penalty = 0;
  if (width > _side_length)
    width_penalty = (double) width / _side_length;
  if (height > _side_length)
    height_penalty = (double) height / _side_length;

  c.cost = area_cost + wl_cost + R_cost;
  return c;
}

// perturb : rotate a module
void FloorPlaner::rotate(int node)
{
  int temp                            = _base_info.hard_blocks[node].width;
  _base_info.hard_blocks[node].width  = _base_info.hard_blocks[node].height;
  _base_info.hard_blocks[node].height = temp;
}

// perturb : BStarMove a module to another palce
void FloorPlaner::BStarMove(int from, int to)
{
  /* delete the node */
  // no child
  if (_tree_info.tree[from].leftchild == -1
      && _tree_info.tree[from].rightchild == -1) {
    int parent = _tree_info.tree[from].parent;
    if (_tree_info.tree[parent].leftchild == from)
      _tree_info.tree[parent].leftchild = -1;
    else if (_tree_info.tree[parent].rightchild == from)
      _tree_info.tree[parent].rightchild = -1;
    else {
      printf("[Error] perturb : moving !\n");
      exit(1);
    }
  }
  // two child
  else if (_tree_info.tree[from].leftchild != -1
           && _tree_info.tree[from].rightchild != -1) {
    do {
      bool move_left;
      if (_tree_info.tree[from].leftchild != -1
          && _tree_info.tree[from].rightchild != -1)
        move_left = rand() % 2 == 0;
      else if (_tree_info.tree[from].leftchild != -1)
        move_left = true;
      else
        move_left = false;

      if (move_left)
        BStarSwap(from, _tree_info.tree[from].leftchild);
      else
        BStarSwap(from, _tree_info.tree[from].rightchild);
    } while (_tree_info.tree[from].leftchild != -1
             || _tree_info.tree[from].rightchild != -1);

    int parent = _tree_info.tree[from].parent;
    if (_tree_info.tree[parent].leftchild == from)
      _tree_info.tree[parent].leftchild = -1;
    else if (_tree_info.tree[parent].rightchild == from)
      _tree_info.tree[parent].rightchild = -1;
    else {
      printf("[Error] perturb : moving !\n");
      exit(1);
    }
  }
  // one child
  else {
    int child;
    if (_tree_info.tree[from].leftchild != -1)
      child = _tree_info.tree[from].leftchild;
    else
      child = _tree_info.tree[from].rightchild;

    int parent = _tree_info.tree[from].parent;
    if (parent != -1) {
      if (_tree_info.tree[parent].leftchild == from)
        _tree_info.tree[parent].leftchild = child;
      else if (_tree_info.tree[parent].rightchild == from)
        _tree_info.tree[parent].rightchild = child;
      else {
        printf("[Error] perturb : moving !\n");
        exit(1);
      }
    }
    _tree_info.tree[child].parent = parent;

    // _tree_info.root may change
    if (from == _tree_info.root)
      _tree_info.root = child;
  }

  /* insert the node */
  int insert_pos = rand() % 4;
  int child;
  if (insert_pos == 0) {
    child                            = _tree_info.tree[to].leftchild;
    _tree_info.tree[from].leftchild  = child;
    _tree_info.tree[from].rightchild = -1;
    _tree_info.tree[to].leftchild    = from;
  } else if (insert_pos == 1) {
    child                            = _tree_info.tree[to].rightchild;
    _tree_info.tree[from].leftchild  = child;
    _tree_info.tree[from].rightchild = -1;
    _tree_info.tree[to].rightchild   = from;
  } else if (insert_pos == 2) {
    child                            = _tree_info.tree[to].leftchild;
    _tree_info.tree[from].leftchild  = -1;
    _tree_info.tree[from].rightchild = child;
    _tree_info.tree[to].leftchild    = from;
  } else {
    child                            = _tree_info.tree[to].rightchild;
    _tree_info.tree[from].leftchild  = -1;
    _tree_info.tree[from].rightchild = child;
    _tree_info.tree[to].rightchild   = from;
  }
  _tree_info.tree[from].parent = to;
  if (child != -1)
    _tree_info.tree[child].parent = from;
}

// perturb : BStarSwap two modules
void FloorPlaner::BStarSwap(int n1, int n2)
{
  /* BStarSwap two parent */
  int n1_parent = _tree_info.tree[n1].parent;
  if (n1_parent != -1) {
    if (_tree_info.tree[n1_parent].leftchild == n1)
      _tree_info.tree[n1_parent].leftchild = n2;
    else if (_tree_info.tree[n1_parent].rightchild == n1)
      _tree_info.tree[n1_parent].rightchild = n2;
    else {
      printf("[Error] perturb : swapping !\n");
      exit(1);
    }
  }

  int n2_parent = _tree_info.tree[n2].parent;
  if (n2_parent != -1) {
    if (_tree_info.tree[n2_parent].leftchild == n2)
      _tree_info.tree[n2_parent].leftchild = n1;
    else if (_tree_info.tree[n2_parent].rightchild == n2)
      _tree_info.tree[n2_parent].rightchild = n1;
    else {
      printf("[Error] perturb : swapping !\n");
      exit(1);
    }
  }

  _tree_info.tree[n1].parent = n2_parent;
  _tree_info.tree[n2].parent = n1_parent;

  /* BStarSwap two child */
  int n1_leftchild               = _tree_info.tree[n1].leftchild;
  int n1_rightchild              = _tree_info.tree[n1].rightchild;
  _tree_info.tree[n1].leftchild  = _tree_info.tree[n2].leftchild;
  _tree_info.tree[n1].rightchild = _tree_info.tree[n2].rightchild;
  _tree_info.tree[n2].leftchild  = n1_leftchild;
  _tree_info.tree[n2].rightchild = n1_rightchild;

  if (_tree_info.tree[n1].leftchild != -1)
    _tree_info.tree[_tree_info.tree[n1].leftchild].parent = n1;
  if (_tree_info.tree[n1].rightchild != -1)
    _tree_info.tree[_tree_info.tree[n1].rightchild].parent = n1;
  if (_tree_info.tree[n2].leftchild != -1)
    _tree_info.tree[_tree_info.tree[n2].leftchild].parent = n2;
  if (_tree_info.tree[n2].rightchild != -1)
    _tree_info.tree[_tree_info.tree[n2].rightchild].parent = n2;

  /* BStarSwap parent & child */
  if (_tree_info.tree[n1].parent == n1)
    _tree_info.tree[n1].parent = n2;
  else if (_tree_info.tree[n1].leftchild == n1)
    _tree_info.tree[n1].leftchild = n2;
  else if (_tree_info.tree[n1].rightchild == n1)
    _tree_info.tree[n1].rightchild = n2;

  if (_tree_info.tree[n2].parent == n2)
    _tree_info.tree[n2].parent = n1;
  else if (_tree_info.tree[n2].leftchild == n2)
    _tree_info.tree[n2].leftchild = n1;
  else if (_tree_info.tree[n2].rightchild == n2)
    _tree_info.tree[n2].rightchild = n1;

  // _tree_info.root may change
  if (n1 == _tree_info.root)
    _tree_info.root = n2;
  else if (n2 == _tree_info.root)
    _tree_info.root = n1;
}

void FloorPlaner::swapBlock(int swapType, int id1, int id2)
{  // if type = 0 , then swap only in sp1, type = 1 , swap only in sp2  , type =
   // 2, swap both.
  if (swapType == 0)
    _sp_info.swapBlock(true, id1, id2);
  else if (swapType == 1)
    _sp_info.swapBlock(false, id1, id2);
  else {
    _sp_info.swapBlock(true, id1, id2);
    _sp_info.swapBlock(false, id1, id2);
  }
}

int FloorPlaner::Perturbing()
{
  if (_choice == BStarTree) {
    /* Perturbing */
    int perturb = rand() % 3;
    // M1 : rotate
    if (perturb == 0) {
      int node = rand() % _num_hard;
      rotate(node);
    }
    // M2 : BStarSwap
    else if (perturb == 1) {
      int n1, n2;
      n1 = rand() % _num_hard;
      do {
        n2 = rand() % _num_hard;
      } while (n2 == n1);
      BStarSwap(n1, n2);
    }
    // M3 : BStarMove
    else if (perturb == 2) {
      int from, to;
      from = rand() % _num_hard;
      do {
        to = rand() % _num_hard;
      } while (to == from || _tree_info.tree[from].parent == to);
      BStarMove(from, to);
    }
    return perturb;
  } else if (_choice == SP) {
    int perturb = rand() % 4;

    if (perturb == 0) {
      int node = rand() % _num_hard;
      rotate(node);
    } else {
      // perturb 1 2 3
      int n1, n2;
      n1 = rand() % _num_hard;
      do {
        n2 = rand() % _num_hard;
      } while (n2 == n1);
      int type = rand() % 3;
      swapBlock(type, n1, n2);
      perturb = 1 + type;
    }
    return perturb;
  } else if (_choice == Slicing) {
    int perturb = rand() % 3;
    // cout << moveOption << endl;
    // Move1: Exchange 2 operands with no other operand in between
    if (perturb == 0) {
      // Pair of operators,operands index
      pair<vector<int>, vector<int>> indexes
          = Polish::getLocations(_slicing_info.expression);
      int randomPoint         = rand() % (indexes.second.size() - 1);
      int randomOperandIndex1 = indexes.second[randomPoint];
      int randomOperandIndex2;
      if (randomPoint < indexes.second.size() - 1) {
        randomOperandIndex2 = indexes.second[randomPoint + 1];
      } else {
        randomOperandIndex2 = indexes.second[randomPoint - 1];
      }
      string temp = _slicing_info.expression.at(randomOperandIndex1);
      _slicing_info.expression[randomOperandIndex1]
          = _slicing_info.expression.at(randomOperandIndex2);
      _slicing_info.expression[randomOperandIndex2] = temp;
    }
    // Move2: Complement a series of operators between two operands
    if (perturb == 1) {
      vector<pair<int, int>> validOperatorSeries
          = Polish::getRepOperators(_slicing_info.expression);
      // Checks if such operator/operands are present
      if (validOperatorSeries.size() > 0) {
        int randomPoint = rand() % (validOperatorSeries.size() - 1);
        for (int i = validOperatorSeries[randomPoint].first;
             i <= validOperatorSeries[randomPoint].second;
             i++) {
          _slicing_info.expression[i]
              = Polish::getCompliment(_slicing_info.expression[i]);
        }
      }
    }
    // Move3: Exchange adjecnt operator and operand if resultant is still
    // normalized polish expression
    if (perturb == 2) {
      vector<int> validIndices
          = Polish::getSurroundedOperands(_slicing_info.expression);
      // Checks if such operator/operands are present
      if (validIndices.size() > 0) {
        int    randomPoint = rand() % (validIndices.size() - 1);
        string temp = _slicing_info.expression.at(validIndices[randomPoint]);
        _slicing_info.expression[validIndices[randomPoint]]
            = _slicing_info.expression.at(validIndices[randomPoint] + 1);
        _slicing_info.expression[validIndices[randomPoint] + 1] = temp;
      }
    }
    return perturb;
  } else {
    return -1;
  }
}

bool FloorPlaner::simulatedAnnealing()
{
  _min_cost           = cost();
  _min_cost_floorplan = _base_info.hard_blocks;

  const int    k      = 1000;
  const int    N      = k * _num_hard;
  double       a      = log(0.1);
  double       b      = log(0.0001);
  const double T0     = _min_cost.cost / 1000;
  double       T      = T0;
  double       frozen = T0 * 0.0001;
  double       decade = 0.5;

  _in_fixed_outline = false;

  while (T >= frozen) {
    Cost cost1    = cost();
    int  movetime = 0;
    int  uphill   = 0;
    int  force_go = 0;
    int  reject   = 0;

    // BStarMove in same temperature k * n times.
    while (movetime < N) {
      if (_choice == BStarTree) {
        _old_hardblocks = _base_info.hard_blocks;
        _old_tree_info  = _tree_info;
      } else if (_choice == SP) {
        _old_hardblocks = _base_info.hard_blocks;
        _old_sp_info    = _sp_info;
      } else if (_choice == Slicing) {
        _old_hardblocks   = _base_info.hard_blocks;
        _old_slicing_info = _slicing_info;
      }

      int perturb = Perturbing();

      Cost cost2 = cost();

      // change state
      bool   change_state = false;
      double random       = (double) rand() / RAND_MAX;
      double delta_cost   = cost2.cost - cost1.cost;
      double temp         = exp(-delta_cost / T);
      // cout << "cost1.cost: " << cost1.cost << endl;
      // cout << "cost2.cost: " << cost2.cost << endl;
      // cout << -delta_cost / T << endl;
      // cout << exp(-delta_cost / T) << endl;
      if (delta_cost < 0 || random < exp(-delta_cost / T)) {
        if (delta_cost < 0) {
          uphill++;
        } else {
          force_go++;
        }
        change_state = true;
      }
      if (change_state) {
        // feasible solution with minimum cost
        if (cost2.width <= _side_length && cost2.height <= _side_length) {
          if (_in_fixed_outline) {
            if (cost2.cost < _fixed_in_min_cost.cost) {
              _fixed_in_min_cost      = cost2;
              _fixed_in_min_floorplan = _base_info.hard_blocks;
              if (_choice == BStarTree) {
                _fixed_in_min_tree_info = _tree_info;
              } else if (_choice == SP) {
                _fixed_in_min_sp_info = _sp_info;
              } else if (_choice == Slicing) {
                _fixed_in_min_slicing_info = _slicing_info;
              }
            }
          } else {
            _in_fixed_outline       = true;
            _fixed_in_min_cost      = cost2;
            _fixed_in_min_floorplan = _base_info.hard_blocks;
            if (_choice == BStarTree) {
              _fixed_in_min_tree_info = _tree_info;
            } else if (_choice == SP) {
              _fixed_in_min_sp_info = _sp_info;
            } else if (_choice == Slicing) {
              _fixed_in_min_slicing_info = _slicing_info;
            }
          }
        }
        // infeasible solution with minimum cost
        if (cost2.cost < _min_cost.cost) {
          _min_cost           = cost2;
          _min_cost_floorplan = _base_info.hard_blocks;
          if (_choice == BStarTree) {
            _min_cost_tree_info = _tree_info;
          } else if (_choice == SP) {
            _min_cost_sp_info = _sp_info;
          } else if (_choice == Slicing) {
            _min_cost_slicing_info = _slicing_info;
          }
        }

        cost1 = cost2;

      } else {
        reject++;
        if (_choice == BStarTree) {
          if (perturb == 0)
            _base_info.hard_blocks = _old_hardblocks;
          else
            _tree_info = _old_tree_info;

        } else if (_choice == SP) {
          if (perturb == 0)
            _base_info.hard_blocks = _old_hardblocks;
          else
            _sp_info = _old_sp_info;
        } else if (_choice == Slicing) {
          _base_info.hard_blocks = _old_hardblocks;
          _slicing_info          = _old_slicing_info;
        }
      }
      movetime++;
    }
    cout << "-------------: " << endl;
    cout << "温度：" << T << endl;
    cout << "下降率：" << uphill * 1.0 / movetime << endl;
    cout << "强行上升率：" << force_go * 1.0 / movetime << endl;
    cout << "拒绝率：" << reject * 1.0 / movetime << endl;
    cout << "cost: " << _min_cost.cost << endl;
    cout << "目标W: " << _side_length << endl;
    cout << "height: " << _min_cost.height << endl;
    cout << "width: " << _min_cost.width << endl;
    cout << "wire_length: " << _min_cost.wire_length << endl;

    T *= decade;
    if (T < frozen && _in_fixed_outline == false) {
      T = T0;
    }
  }

  if (_in_fixed_outline) {
    printf("\nFound feasible solution\n");
    printf("[       Width      ] : %d\n", _fixed_in_min_cost.width);
    printf("[       Height     ] : %d\n", _fixed_in_min_cost.height);
    printf("[       Area       ] : %.0f\n", _fixed_in_min_cost.area);
    printf("[     Wirelength   ] : %.0f\n", _fixed_in_min_cost.wire_length);
    printf("[        R         ] : %f\n", _fixed_in_min_cost.R);
    printf("[       Cost       ] : %f\n\n\n", _fixed_in_min_cost.cost);
    return true;
  } else {
    printf("Cannot found feasible solution\n");
    return false;
  }
}

void FloorPlaner::writeOutput(string output_file)
{
  if (_choice == BStarTree) {
    output_file += "BStar";
  } else if (_choice == SP) {
    output_file += "SP";
  } else if (_choice == Slicing) {
    output_file += "Slicing";
  }

  ofstream file;
  file.open(output_file);

  file << _side_length << " " << _side_length << "\n";
  file << _num_hard << "\n";
  file << "width: " << _fixed_in_min_cost.width << "  ";
  file << "height: " << _fixed_in_min_cost.height << "  ";
  file << "area: " << _fixed_in_min_cost.area << "  ";
  file << "wirelength: " << _fixed_in_min_cost.wire_length << "  ";
  file << "R: " << _fixed_in_min_cost.R << "\n";

  for (int i = 0; i < _num_hard; i++) {
    file << _fixed_in_min_floorplan[i].x << " " << _fixed_in_min_floorplan[i].y
         << " " << _fixed_in_min_floorplan[i].width << " "
         << _fixed_in_min_floorplan[i].height << " \n";
  }
  file.close();
}
