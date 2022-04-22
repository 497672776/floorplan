#ifndef FLOORPLAN_FILEPARSER_H_
#define FLOORPLAN_FILEPARSER_H_

#include <map>
#include <string>
#include <vector>

#include "common.h"

using namespace std;

class FileParser
{
 public:
  FileParser(const string& hardblocks_file,
             const string& terminals_file,
             const string& nets_file);
  BaseInfo getBaseInfo() const { return _base_info; }

 private:
  void parseHardblocks(const string& inputfile);
  void parseTerminals(const string& inputfile);
  void parseNets(const string& inputfile);

  int _num_hard;
  int _num_terminal;
  int _num_net;

  BaseInfo _base_info;

  map<string, int> _block_map;
  map<string, int> _terminal_map;
};

#endif