#ifndef FLOORPLAN_SEQUENCEPAIR_H_
#define FLOORPLAN_SEQUENCEPAIR_H_

#include "common.h"

class SequencePair
{
 public:
  SequencePair(const vector<HardBlock>& hard_blocks);
  void   convertInfo(const vector<HardBlock>& hard_blocks);
  SPInfo getSPInfo() const { return _sp_info; }

 private:
  SPInfo _sp_info;
};

#endif