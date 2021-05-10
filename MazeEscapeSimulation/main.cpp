#include "Simple2DGameEngine.hpp"
#include "MazeSolver.hpp"
#include "MazeDraw.hpp"
#include <fstream>
#include <iostream>

using namespace GameEngine;
using namespace std;

int main(int c, char* v[])
{
  auto window = make_shared<GameWindow>(1000, 1000);
  auto eventManager = make_shared<EventManager>(window);
  auto renderManager = make_shared<RenderManager>(window, Vector4uc(0,0,0,255));
  auto scene = make_shared<Scene>(eventManager, renderManager);

  ifstream mazeFile;
  mazeFile.open("maze.txt");
  auto solver = make_shared<MazeSolver>(mazeFile);
  mazeFile.close();
  int maxSize = max(solver->xSize, solver->ySize);
  auto mainTransform = Transform(Vector2f(0, 0), Vector2f(1000 * solver->xSize / (float)maxSize, 1000 * solver->ySize / (float)maxSize));
  auto mazeDraw = make_shared<MazeDraw>(*scene, solver, mainTransform);
  scene->AddGameObject(static_pointer_cast<GameObject, MazeDraw>(mazeDraw));
  scene->Run();
  return 0;
}