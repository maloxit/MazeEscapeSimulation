#include "MazeDraw.hpp"
#include "MazeDrawCell.hpp"
#include "MazeDrawAgent.hpp"
#include "MazeSolver.hpp"

MazeDraw::MazeDraw(Scene& scene, shared_ptr<MazeSolver>& mazeSolver, Transform& transform) : GameObject(scene, true), mazeSolver(mazeSolver), transform(transform), cellTransform(Vector2f(), Vector2f())
{
  cellTransform = Transform(Vector2f(0, 0), Vector2f(this->transform.size.x / mazeSolver->xSize, this->transform.size.y / mazeSolver->ySize));
  xPos = mazeSolver->agent.xPos;
  yPos = mazeSolver->agent.yPos;
  cellTransform.position.x = this->transform.position.x + cellTransform.size.x * xPos;
  cellTransform.position.y = this->transform.position.y + cellTransform.size.y * yPos;
  prevDirection = MazeCell::Direction::START;
  mazeDrawAgent = make_shared<MazeDrawAgent>(scene, cellTransform);
  scene.AddGameObject(static_pointer_cast<GameObject, MazeDrawAgent>(mazeDrawAgent));
  scene.eventManager->AddEventListener(static_pointer_cast<EventListener, MazeDrawAgent>(mazeDrawAgent));
  mazeMatrix.reserve(mazeSolver->ySize);
  for (int y = 0; y < mazeSolver->ySize; y++)
  {
    mazeMatrix.push_back(vector<shared_ptr<MazeDrawCell>>());
    mazeMatrix[y].reserve(mazeSolver->xSize);
    for (int x = 0; x < mazeSolver->xSize; x++)
    {
      cellTransform.position.x = this->transform.position.x + cellTransform.size.x * x;
      cellTransform.position.y = this->transform.position.y + cellTransform.size.y * y;
      auto mazeDrawCell = make_shared<MazeDrawCell>(scene, mazeSolver->mazeMatrix[y][x], cellTransform);
      mazeMatrix[y].push_back(mazeDrawCell);
    }
  }
}

void MazeDraw::Update(float deltaTime)
{
  if (!mazeDrawAgent->enabled)
  {
    auto nextDirection = mazeSolver->Move();
    if (nextDirection == MazeCell::Direction::START || nextDirection == MazeCell::Direction::NONE)
    {
      enabled = false;
      if (mazeSolver->agent.xPos > xPos)
      {
        nextDirection = MazeCell::Direction::RIGHT;
      }
      if (mazeSolver->agent.xPos < xPos)
      {
        nextDirection = MazeCell::Direction::LEFT;
      }
      if (mazeSolver->agent.yPos > yPos)
      {
        nextDirection = MazeCell::Direction::DOWN;
      }
      if (mazeSolver->agent.yPos < yPos)
      {
        nextDirection = MazeCell::Direction::UP;
      }
    }
    MazeCell::PrintDirection(nextDirection);
    cout << endl;
    mazeMatrix[yPos][xPos]->ShowLine(prevDirection, nextDirection);
    xPos = mazeSolver->agent.xPos;
    yPos = mazeSolver->agent.yPos;
    auto newTarget = Vector2f(this->transform.position.x + cellTransform.size.x * xPos, this->transform.position.y + cellTransform.size.y * yPos);
    mazeDrawAgent->BeginMove(newTarget);
    prevDirection = MazeCell::OpositeDirection(nextDirection);
  }
}
