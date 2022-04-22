#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "bstartree.h"
#include "common.h"
#include "fileparser.h"
#include "floorplaner.h"
#include "sequencepair.h"
#include "slicingtree.h"

using namespace std;

/* main */
int main(int argc, char** argv)
{
  // seed
  int seed = 1542959801;
  srand(seed);

  string hardblocks_file  = argv[1];
  string terminals_file   = argv[2];
  string nets_file        = argv[3];
  string output_file      = argv[4];
  double dead_space_ratio = atof(argv[5]);

  // Read testcase
  FileParser* file_parser
      = new FileParser(hardblocks_file, terminals_file, nets_file);
  BaseInfo base_info = file_parser->getBaseInfo();

  // get the width or height of fixied_in
  double fixed_outline_area
      = base_info.total_block_area * (1 + dead_space_ratio);
  int side_length = sqrt(fixed_outline_area) * 1;

  // // BstarTree
  BStarTree* b_star_tree = new BStarTree(base_info.hard_blocks);
  TreeInfo   tree_info   = b_star_tree->getTreeInfo();

  FloorPlaner* floor_planer_bstar
      = new FloorPlaner(side_length, base_info, tree_info);
  if (floor_planer_bstar->simulatedAnnealing()) {
    // Write output floorplan file
    floor_planer_bstar->writeOutput(output_file);
  } else {
    cout << "We can't find the solution!" << endl;
  }

  // // SP
  SequencePair* sequence_pair = new SequencePair(base_info.hard_blocks);
  SPInfo        sp_info       = sequence_pair->getSPInfo();

  FloorPlaner* floor_planer_sp
      = new FloorPlaner(side_length, base_info, sp_info);
  if (floor_planer_sp->simulatedAnnealing()) {
    // Write output floorplan file
    floor_planer_sp->writeOutput(output_file);
  } else {
    cout << "We can't find the solution!" << endl;
  }

  // SlcingTree
  SlicingTree* slicing_tree = new SlicingTree(base_info.hard_blocks);
  SlicingInfo  slicing_info = slicing_tree->getSlicingInfo();

  FloorPlaner* floor_planer_slcing
      = new FloorPlaner(side_length, base_info, slicing_info);
  if (floor_planer_slcing->simulatedAnnealing()) {
    // Write output floorplan file
    floor_planer_slcing->writeOutput(output_file);
  } else {
    cout << "We can't find the solution!" << endl;
  }

  // Total Runtime
  double runtime = clock();
  printf("[  Total Run time  ]: %f sec\n", runtime / CLOCKS_PER_SEC);
  return 0;
}
