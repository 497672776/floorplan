#include "slicingnode.h"

#include "string"

SlicingNode::SlicingNode(const std::string& id,
                         double             softArea,
                         double             softMinAspect,
                         double             softMaxAspect)
{
  this->id            = id;
  this->nodeType      = SOFT;
  this->cutType       = END_NODE;
  this->softArea      = softArea;
  this->softMinAspect = softMinAspect;
  this->softMaxAspect = softMaxAspect;
  // Makes 3 sizes out-of the ratios given
  double l = sqrt(softArea * softMinAspect);
  double w = sqrt(softArea / softMinAspect);
  // TODO: Add rotations
  Size sMin(l, w);
  this->sizeOptions.push_back(sMin);
  l = sqrt(softArea * softMaxAspect);
  w = sqrt(softArea / softMaxAspect);
  Size sMax(l, w);
  this->sizeOptions.push_back(sMax);
  if (softMaxAspect > 1 && softMinAspect < 1) {
    double l = sqrt(softArea);
    double w = sqrt(softArea);
    Size   sOne(l, w);
    this->sizeOptions.push_back(sOne);
  }
  this->parent = NULL;
  this->left   = NULL;
  this->right  = NULL;
  this->llCord = pair<double, double>(0, 0);
  this->urCord = pair<double, double>(0, 0);
}
// Constructor to make hard blocks
SlicingNode::SlicingNode(const string& id, list<Size>& sizeOptions)
{
  this->id            = id;
  this->nodeType      = HARD;
  this->cutType       = END_NODE;
  this->sizeOptions   = sizeOptions;
  this->parent        = NULL;
  this->left          = NULL;
  this->right         = NULL;
  this->softArea      = 0;
  this->softMinAspect = 0;
  this->softMaxAspect = 0;
  this->llCord        = pair<double, double>(0, 0);
  this->urCord        = pair<double, double>(0, 0);
}
// Constructor to make nodes with cut specification
SlicingNode::SlicingNode(int          cutType,
                         SlicingNode* left,
                         SlicingNode* right,
                         list<Size>&  sizeOptions)
{
  if (cutType == VERTICAL_CUT) {
    if (left != NULL && right != NULL)
      // FIXME: Potential space complexity issues here
      this->id = "v_" + left->getId() + "_" + right->getId();
    else
      this->id = "v_invalid";
    this->cutType = cutType;
  } else if (cutType == HORIZONTAL_CUT) {
    if (left != NULL && right != NULL)
      // FIXME: Potential space complexity issues here
      this->id = "h_" + left->getId() + "_" + right->getId();
    else
      this->id = "h_invalid";
    this->cutType = cutType;
  } else {
    // TODO: Throw exception or strong error
    cout << "\nInvalid Cut Given\n";
    this->cutType = VERTICAL_CUT;
    if (left != NULL && right != NULL)
      this->id = "v_" + left->getId() + "_" + right->getId();
    else
      this->id = "invalid";
  }
  this->left = left;
  left->setParent(this);
  this->right = right;
  right->setParent(this);
  this->sizeOptions   = sizeOptions;
  this->parent        = NULL;
  this->softArea      = 0;
  this->softMinAspect = 0;
  this->softMaxAspect = 0;
  this->nodeType      = HARD;
  this->llCord        = pair<double, double>(0, 0);
  this->urCord        = pair<double, double>(0, 0);
}
bool SlicingNode::isEndNode()
{
  bool isEnd = false;
  if (this->left == NULL && this->right == NULL) {
    isEnd = true;
  }
  return isEnd;
}
int SlicingNode::getCutType() const
{
  return cutType;
}

SlicingNode* SlicingNode::getLeft() const
{
  return left;
}

bool SlicingNode::isNodeType() const
{
  return nodeType;
}

const Size SlicingNode::getOptimumSize() const
{
  if (this->parent == NULL) {
    double minArea = DBL_MAX;
    Size   minSize;
    for (auto it : sizeOptions) {
      if (minArea > it.getLength() * it.getWidth()) {
        minArea = it.getLength() * it.getWidth();
        minSize = it;
      }
    }
    return minSize;
  } else {
    return this->optimumSize;
  }
}

void SlicingNode::setOptimumSize(Size& optimumSize)
{
  this->optimumSize = optimumSize;
}

SlicingNode* SlicingNode::getParent() const
{
  return parent;
}

SlicingNode* SlicingNode::getRight() const
{
  return right;
}

list<Size>& SlicingNode::getSizeOptions()
{
  return sizeOptions;
}

double SlicingNode::getSoftArea() const
{
  return softArea;
}

double SlicingNode::getSoftMaxAspect() const
{
  return softMaxAspect;
}

void SlicingNode::setParent(SlicingNode* parent)
{
  this->parent = parent;
}

void SlicingNode::setLeft(SlicingNode* left)
{
  this->left = left;
}

void SlicingNode::setRight(SlicingNode* right)
{
  this->right = right;
}

double SlicingNode::getSoftMinAspect() const
{
  return softMinAspect;
}

const string& SlicingNode::getId() const
{
  return id;
}

pair<double, double> SlicingNode::getLLCord()
{
  return llCord;
}

pair<double, double> SlicingNode::getURCord()
{
  return urCord;
}

void SlicingNode::setLLCord(pair<double, double> llCord)
{
  this->llCord = llCord;
}
void SlicingNode::setURCord(pair<double, double> urCord)
{
  this->urCord = urCord;
}
