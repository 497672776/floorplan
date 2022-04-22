#ifndef FLOORPLAN_SLICINGNODE_H
#define FLOORPLAN_SLICINGNODE_H

#include <float.h>

#include <cmath>
#include <list>
#include <string>

#include "iostream"
#include "size.h"
using namespace std;
class SlicingNode
{
 private:
  string               id;
  bool                 nodeType;  // 1: Hard, 0: Soft
  double               softArea;
  double               softMinAspect;
  double               softMaxAspect;
  int                  cutType;  // 1(vertical), 2(horizontal), 3(endNode)
  SlicingNode*         parent;
  SlicingNode*         left;
  SlicingNode*         right;
  Size                 optimumSize;
  list<Size>           sizeOptions;
  pair<double, double> llCord;
  pair<double, double> urCord;

 public:
  // Constructors
  SlicingNode(const string& id,
              double        softArea,
              double        softMinAspect,
              double        softMaxAspect);
  SlicingNode(const string& id, list<Size>& sizeOptions);
  SlicingNode(int          cutType,
              SlicingNode* left,
              SlicingNode* right,
              list<Size>&  sizeOptions);
  // Property
  bool isEndNode();
  // Getter Setters
  int                  getCutType() const;
  bool                 isNodeType() const;
  const Size           getOptimumSize() const;
  void                 setOptimumSize(Size& optimumSize);
  SlicingNode*         getParent() const;
  SlicingNode*         getRight() const;
  SlicingNode*         getLeft() const;
  list<Size>&          getSizeOptions();
  double               getSoftArea() const;
  double               getSoftMaxAspect() const;
  double               getSoftMinAspect() const;
  void                 setParent(SlicingNode* parent);
  void                 setLeft(SlicingNode* left);
  void                 setRight(SlicingNode* right);
  const string&        getId() const;
  pair<double, double> getLLCord();
  pair<double, double> getURCord();
  void                 setLLCord(pair<double, double> xCord);
  void                 setURCord(pair<double, double> yCord);
  // Static Constants
  static const int  VERTICAL_CUT   = 1;
  static const int  HORIZONTAL_CUT = 2;
  static const int  END_NODE       = 3;
  static const bool HARD           = true;
  static const bool SOFT           = false;
};

#endif
