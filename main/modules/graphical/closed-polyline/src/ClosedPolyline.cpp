#include "ClosedPolyline.h"

#include "Line.h"

ClosedPolyline::ClosedPolyline(const Color& color, float thickness)
  : OpenPolyline{ color, thickness }
{}

ClosedPolyline::ClosedPolyline(std::initializer_list<Position> nodes,
                               const Color& color,
                               float thickness)
  : OpenPolyline{ nodes, color, thickness }
{
  if (NodesCount() > 2) {
    OpenPolyline::Add(At(0));
  }
}

void
ClosedPolyline::Add(const Position& node)
{
  if (NodesCount() == 2) {
    OpenPolyline::Add(node);
    OpenPolyline::Add(At(0));
  } else if (NodesCount() > 2) {
    OpenPolyline::Remove(At(NodesCount() - 1));
    OpenPolyline::Add(node);
    OpenPolyline::Add(At(0));
  } else {
    OpenPolyline::Add(node);
  }
}
