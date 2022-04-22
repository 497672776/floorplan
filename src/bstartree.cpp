#include "bstartree.h"

#include <queue>

BStarTree::BStarTree(const vector<HardBlock>& hard_blocks)
{
  convertInfo(hard_blocks);
}

void BStarTree::convertInfo(const vector<HardBlock>& hard_blocks)
{
  int num_hard    = hard_blocks.size();
  _tree_info.tree = vector<Node>(num_hard);
  queue<int>  bfs;
  vector<int> insert(num_hard, 0);

  _tree_info.root                         = rand() % num_hard;
  _tree_info.tree[_tree_info.root].parent = -1;
  bfs.push(_tree_info.root);
  insert[_tree_info.root] = 1;

  int i = num_hard - 1;
  while (!bfs.empty()) {
    int parent     = bfs.front();
    int left_child = -1, right_child = -1;
    bfs.pop();

    if (i > 0) {
      do {
        left_child = rand() % num_hard;
      } while (insert[left_child]);
      _tree_info.tree[parent].leftchild = left_child;
      bfs.push(left_child);
      insert[left_child] = 1;
      i--;

      if (i > 0) {
        do {
          right_child = rand() % num_hard;
        } while (insert[right_child]);
        _tree_info.tree[parent].rightchild = right_child;
        bfs.push(right_child);
        insert[right_child] = 1;
        i--;
      }
    }
    _tree_info.tree[parent].leftchild  = left_child;
    _tree_info.tree[parent].rightchild = right_child;
    if (left_child != -1)
      _tree_info.tree[left_child].parent = parent;
    if (right_child != -1)
      _tree_info.tree[right_child].parent = parent;
  }

  _tree_info.root = _tree_info.root;
  _tree_info.tree = _tree_info.tree;
}