#pragma once
#include "Simple2DGameEngine.hpp"
#include "MazeSolver.hpp"

using namespace GameEngine;
using namespace std;

class MazeDrawCell;
class MazeSolver;
class MazeDrawAgent;

class MazeDraw :
  public GameObject
{
public:
  MazeCell::Direction prevDirection;
  Transform transform;
  Transform cellTransform;
  int xPos;
  int yPos;
  shared_ptr<MazeSolver> mazeSolver;
  shared_ptr<MazeDrawAgent> mazeDrawAgent;
  vector<vector<shared_ptr<MazeDrawCell>>> mazeMatrix;
  MazeDraw(Scene& scene, shared_ptr<MazeSolver>& mazeSolver, Transform& transform);
  virtual void Update(float deltaTime);
};

