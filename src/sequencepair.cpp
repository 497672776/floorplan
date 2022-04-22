#include "sequencepair.h"

#include <algorithm>

SequencePair::SequencePair(const vector<HardBlock>& hard_blocks)
{
  convertInfo(hard_blocks);
}

void SequencePair::convertInfo(const vector<HardBlock>& hard_blocks)
{
  int                    num_hard = hard_blocks.size();
  vector<pair<int, int>> weight_map(num_hard);

  for (int i = 0; i < num_hard; i++) {
    weight_map.at(i).first  = i;                      // block id
    weight_map.at(i).second = hard_blocks[i].height;  // correspond weight
  }

  // sort by weight
  std::sort(weight_map.begin(),
            weight_map.end(),
            [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
              return p1.second < p2.second;
            });
  _sp_info.s1.resize(num_hard);
  _sp_info.s2.resize(num_hard);
  _sp_info.s1_idx.resize(num_hard);
  _sp_info.s2_idx.resize(num_hard);

  // do swap
  // let sum of first half weight  approximate equal to sum of other half
  // weight.
  for (int i = num_hard / 4; i < num_hard / 2; i++) {
    std::pair<int, int> temp        = weight_map.at(i);
    weight_map.at(i)                = weight_map.at(i + num_hard / 2);
    weight_map.at(i + num_hard / 2) = temp;
  }

  // s1 = <l1,l2>
  // s1 = <l1,l2>
  std::vector<int> l1;
  l1.resize(num_hard / 2);
  std::vector<int> l2;
  l2.resize(num_hard - num_hard / 2);
  for (int i = 0; i < num_hard / 2; i++)
    l1.at(i) = weight_map.at(i).first;
  for (int i = num_hard / 2; i < num_hard; i++)
    l2.at(i - num_hard / 2) = weight_map.at(i).first;

  // build sequence
  for (int i = 0; i < num_hard / 2; i++)
    _sp_info.s1.at(i) = l1.at(i);
  for (int i = num_hard / 2; i < num_hard; i++)
    _sp_info.s1.at(i) = l2.at(i - num_hard / 2);
  for (int i = 0; i < num_hard - num_hard / 2; i++)
    _sp_info.s2.at(i) = l2.at(i);
  for (int i = num_hard - num_hard / 2; i < num_hard; i++)
    _sp_info.s2.at(i) = l1.at(i - (num_hard - num_hard / 2));

  for (int i = 0; i < _sp_info.s1.size(); i++)
    _sp_info.s1_idx.at(_sp_info.s1.at(i)) = i;
  for (int i = 0; i < _sp_info.s1.size(); i++)
    _sp_info.s2_idx.at(_sp_info.s2.at(i)) = i;
}
