#ifndef FLOORPLAN_FLOORPLANER_H_
#define FLOORPLAN_FLOORPLANER_H_

#include "bstartree.h"
#include "common.h"
#include "fileparser.h"
#include "slicingnode.h"

class FloorPlaner
{
 public:
  enum Choice
  {
    BStarTree = 1,
    SP        = 2,
    Slicing   = 3
  };
  FloorPlaner(int             side_length,
              const BaseInfo& base_info,
              const TreeInfo& tree_info);
  FloorPlaner(int             side_length,
              const BaseInfo& base_info,
              const SPInfo&   sp_info);
  FloorPlaner(int                side_length,
              const BaseInfo&    base_info,
              const SlicingInfo& slicing_info);
  bool              simulatedAnnealing();
  vector<HardBlock> getFinalFloorplan() { return _fixed_in_min_floorplan; }
  Cost              getFinalCost() { return _fixed_in_min_cost; }
  void              writeOutput(string output_file);

 private:
  Cost                cost();
  std::pair<int, int> B2Floorplan();
  std::pair<int, int> SP2Floorplan();
  std::pair<int, int> SLicingFloorplan();
  void                assignOptimum(SlicingNode* root);
  void                processCords(SlicingNode* root);
  void                cleanupNodes();

  SlicingNode* polishToTree(const vector<string>& experssion);
  void         preorderTraverse(int node, bool left);
  double       computeHPWL(int width, int height);
  void         rotate(int node);
  void         BStarMove(int from, int to);
  void         BStarSwap(int n1, int n2);
  void         reverse(std::vector<int>& vec);
  SlicingNode* sizeNodes(SlicingNode& nodeA, SlicingNode& nodeB, int cutType);

  int LCS(std::vector<int>& s1, std::vector<int>& s2, bool width);

  void swapBlock(int swapType, int id1, int id2);
  int  Perturbing();

  int               _side_length;
  int               _num_hard;
  double            _area_normal      = 0;
  double            _wl_normal        = 0;
  bool              _in_fixed_outline = false;
  vector<int>       _contour;
  Cost              _min_cost, _fixed_in_min_cost;
  vector<HardBlock> _min_cost_floorplan, _fixed_in_min_floorplan;

  TreeInfo    _min_cost_tree_info, _fixed_in_min_tree_info;
  SPInfo      _min_cost_sp_info, _fixed_in_min_sp_info;
  SlicingInfo _min_cost_slicing_info, _fixed_in_min_slicing_info;

  BaseInfo    _base_info;
  TreeInfo    _tree_info;
  SPInfo      _sp_info;
  SlicingInfo _slicing_info;

  Choice _choice;

  vector<HardBlock> _old_hardblocks;
  TreeInfo          _old_tree_info;
  SPInfo            _old_sp_info;
  SlicingInfo       _old_slicing_info;

  static const string VERTICAL_CUT;
  static const string HORIZONTAL_CUT;

  map<string, int> _block_map;
};

#endif