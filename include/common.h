#ifndef FLOORPLAN_COMMON_H_
#define FLOORPLAN_COMMON_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "slicingnode.h"

using namespace std;

typedef struct hardBlockStruct
{
  string name;
  int    id;
  int    width;
  int    height;
  int    x;
  int    y;
} HardBlock;

typedef struct terminalStruct
{
  string name;
  int    id;
  int    x;
  int    y;
} Terminal;

typedef struct baseInfoStuct
{
  vector<HardBlock>   hard_blocks;
  vector<Terminal>    terminals;
  vector<vector<int>> nets;
  double              total_block_area;
} BaseInfo;

typedef struct nodeStruct
{
  int parent;
  int leftchild;
  int rightchild;
} Node;

typedef struct treeInfoStruct
{
  vector<Node> tree;
  int          root;
} TreeInfo;

typedef struct costStruct
{
  double area;
  double wire_length;
  double R;  // aspect ratio
  int    width;
  int    height;
  double cost;
} Cost;

typedef struct SequencePairStruct
{
  std::vector<int> s1;
  std::vector<int> s2;
  std::vector<int> s1_idx;
  std::vector<int> s2_idx;

  void swapBlock(bool s1, int id1, int id2);

} SPInfo;

typedef struct SlicingTreeStruct
{
  vector<string>                      expression;
  unordered_map<string, SlicingNode*> nodes;

} SlicingInfo;

#endif