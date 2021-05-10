#pragma once
#include "Simple2DGameEngine.hpp"
#include "MazeSolver.hpp"

using namespace GameEngine;
using namespace std;
class MazeDrawCell
{
private:
  Scene& scene;
  shared_ptr<RenderObject> base;
  shared_ptr<RenderObject> centerUpLine;
  shared_ptr<RenderObject> centerRightLine;
  shared_ptr<RenderObject> centerDownLine;
  shared_ptr<RenderObject> centerLeftLine;
  shared_ptr<RenderObject> enterUpLine;
  shared_ptr<RenderObject> enterRightLine;
  shared_ptr<RenderObject> enterDownLine;
  shared_ptr<RenderObject> enterLeftLine;
  shared_ptr<RenderObject> exitUpLine;
  shared_ptr<RenderObject> exitRightLine;
  shared_ptr<RenderObject> exitDownLine;
  shared_ptr<RenderObject> exitLeftLine;
public:
  Transform transform;
  void ShowLine(MazeCell::Direction enter, MazeCell::Direction exit);
  MazeDrawCell(Scene& scene, MazeCell& cell, Transform& transform);
};

