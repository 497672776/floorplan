#include "fileparser.h"

#include <fstream>
#include <iostream>

FileParser::FileParser(const string& hardblocks_file,
                       const string& terminals_file,
                       const string& nets_file)
{
  parseHardblocks(hardblocks_file);
  parseTerminals(terminals_file);
  parseNets(nets_file);
}

// parse hardblocks file
void FileParser::parseHardblocks(const string& inputfile)
{
  ifstream file;
  file.open(inputfile);

  string rubbish_token, str, block_name;
  file >> rubbish_token >> rubbish_token >> _num_hard;
  file >> rubbish_token >> rubbish_token >> _num_terminal;
  _base_info.hard_blocks = vector<HardBlock>(_num_hard);
  for (int i = 0; i < _num_hard; i++) {
    file >> block_name;
    getline(file, str);

    size_t left_paren  = str.find("(");
    left_paren         = str.find("(", left_paren + 1);
    left_paren         = str.find("(", left_paren + 1);
    size_t comma       = str.find(",");
    comma              = str.find(",", comma + 1);
    comma              = str.find(",", comma + 1);
    size_t right_paren = str.find(")");
    right_paren        = str.find(")", right_paren + 1);
    right_paren        = str.find(")", right_paren + 1);

    char   buffer[100];
    int    width, height;
    size_t len  = str.copy(buffer, comma - left_paren - 1, left_paren + 1);
    buffer[len] = '\0';
    width       = atoi(buffer);
    len         = str.copy(buffer, right_paren - comma - 2, comma + 2);
    buffer[len] = '\0';
    height      = atoi(buffer);

    _base_info.hard_blocks[i].name   = block_name;
    _base_info.hard_blocks[i].id     = i;
    _base_info.hard_blocks[i].width  = width;
    _base_info.hard_blocks[i].height = height;
    _base_info.hard_blocks[i].x      = 0;
    _base_info.hard_blocks[i].y      = 0;

    _base_info.total_block_area += width * height;
  }
  for (auto iter : _base_info.hard_blocks) {
    _block_map[iter.name] = iter.id;
  }
  file.close();
}

// parse pl file
void FileParser::parseTerminals(const string& inputfile)
{
  ifstream file;
  file.open(inputfile);

  string nodeName;
  int    x, y;

  _base_info.terminals = vector<Terminal>(_num_terminal);
  for (int i = 0; i < _num_terminal; i++) {
    file >> nodeName >> x >> y;
    _base_info.terminals[i].name = nodeName;
    _base_info.terminals[i].id   = i + _num_hard;
    _base_info.terminals[i].x    = x;
    _base_info.terminals[i].y    = y;
  }
  for (auto iter : _base_info.terminals) {
    _terminal_map[iter.name] = iter.id;
  }
  file.close();
}

// parse nets file
void FileParser::parseNets(const string& inputfile)
{
  ifstream file;
  file.open(inputfile);

  string Num, colon, str, rubbish_token;
  file >> rubbish_token >> rubbish_token >> _num_net;
  file >> rubbish_token >> rubbish_token >> rubbish_token;
  _base_info.nets = vector<vector<int>>(_num_net);
  for (int i = 0; i < _num_net; i++) {
    int degree;
    file >> Num >> colon >> degree;
    for (int j = 0; j < degree; j++) {
      file >> str;
      int id;
      if (str[0] == 'p') {
        id = _terminal_map[str];
      } else if (str[0] == 's') {
        id = _block_map[str];
      }
      _base_info.nets[i].emplace_back(id);
    }
  }
  file.close();
}
