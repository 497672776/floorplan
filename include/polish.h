#ifndef FLOORPLAN_POLISH_H_
#define FLOORPLAN_POLISH_H_

#include <string>
#include <vector>

using namespace std;

void polishUtilitesUnitTest();
class Polish
{
 private:
  Polish();

 public:
  static bool   isVerticalCut(string s);
  static bool   isHorizontalCut(string s);
  static bool   isValidCut(string s);
  static bool   isValidExpression(const vector<string>& experssion);
  static bool   isNormalizedExpression(const vector<string>& experssion);
  static int    getCutType(string s);
  static void   printExpression(const vector<string>& experssion);
  static string getCompliment(string s);
  static pair<vector<int>, vector<int>> getLocations(
      const vector<string>& expression);
  static vector<pair<int, int>> getRepOperators(
      const vector<string>& expression);
  static vector<int>  getSurroundedOperands(const vector<string>& expression);
  static const string VERTICAL_CUT;
  static const string HORIZONTAL_CUT;
};

#endif