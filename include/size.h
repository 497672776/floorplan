#ifndef FLOORPLAN_SIZE_H_
#define FLOORPLAN_SIZE_H_


class Size
{
 private:
  double length;  // x2-x1
  double width;   // y2-y1
 public:
  Size();
  Size(double length, double width);
  double      getLength() const;
  void        setLength(double length);
  double      getWidth() const;
  void        setWidth(double width);
  static bool compareLengths(Size a, Size b);
  static bool compareWidths(Size a, Size b);
  static bool compareArea(Size a, Size b);
};

#endif