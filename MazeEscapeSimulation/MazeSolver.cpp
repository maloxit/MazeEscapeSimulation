#include "MazeSolver.hpp"

MazeSolver::MazeSolver(std::istream& mazeFile)
{
  mazeFile >> xSize >> ySize;
  char* line = new char[xSize + 1];
  mazeFile.getline(line, xSize);
  mazeMatrix.reserve(ySize);
  agent = { -1, -1 };
  for (int y = 0; y < ySize; y++)
  {
    mazeMatrix.push_back(std::vector<MazeCell>());
    mazeMatrix[y].reserve(xSize);
    mazeFile.getline(line, xSize + 1);
    for (int x = 0; x < xSize; x++)
    {
      switch (line[x])
      {
      case ' ':
        mazeMatrix[y].push_back(MazeCell{ MazeCell::Type::FREE, MazeCell::Direction::NONE });
        break;
      case '#':
        mazeMatrix[y].push_back(MazeCell{ MazeCell::Type::WALL, MazeCell::Direction::NONE });
        break;
      case 'S':
        mazeMatrix[y].push_back(MazeCell{ MazeCell::Type::FREE, MazeCell::Direction::START });
        agent.xPos = x;
        agent.yPos = y;
        break;
      case 'E':
        mazeMatrix[y].push_back(MazeCell{ MazeCell::Type::EXIT, MazeCell::Direction::NONE });
        break;
      default:
        break;
      }
    }
  }
  delete[] line;
}

MazeCell::Direction MazeSolver::Move()
{
  MazeCell cell = mazeMatrix[agent.yPos][agent.xPos];
  int directionCount;
  MazeCell::Direction bestDirection = MazeCell::Direction::NONE;
  MazeCell::Direction nextDirection;
  if (cell.from == MazeCell::Direction::START)
  {
    directionCount = 4;
    nextDirection = MazeCell::Direction::UP;
  }
  else
  {
    directionCount = 3;
    nextDirection = MazeCell::NextClockDirection(cell.from);
  }
  for (int i = 0; i < directionCount; i++, nextDirection = MazeCell::NextClockDirection(nextDirection))
  {
    int xNext, yNext;
    if (NeighbourPos(agent.xPos, agent.yPos, nextDirection, xNext, yNext))
    {
      MazeCell nextCell = mazeMatrix[yNext][xNext];
      if (nextCell.type == MazeCell::Type::EXIT)
      {
        bestDirection = nextDirection;
        mazeMatrix[yNext][xNext].from = MazeCell::OpositeDirection(nextDirection);
        agent = { xNext, yNext };
        return MazeCell::Direction::START;
      }
      if (nextCell.type == MazeCell::Type::FREE && nextCell.from == MazeCell::Direction::NONE && bestDirection == MazeCell::Direction::NONE)
      {
        bestDirection = nextDirection;
      }
    }
  }
  if (bestDirection == MazeCell::Direction::NONE)
  {
    if (cell.from == MazeCell::Direction::START)
    {
      return MazeCell::Direction::NONE;
    }
    NeighbourPos(agent.xPos, agent.yPos, cell.from, agent.xPos, agent.yPos);
    return cell.from;
  }
  else
  {
    int xNext, yNext;
    NeighbourPos(agent.xPos, agent.yPos, bestDirection, xNext, yNext);
    mazeMatrix[yNext][xNext].from = MazeCell::OpositeDirection(bestDirection);
    agent = { xNext, yNext };
    return bestDirection;
  }
}
