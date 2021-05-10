#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <execution>

struct MazeCell
{
public:
  enum class Type : char
  {
    WALL,
    FREE,
    EXIT
  } type;
  enum class Direction : char
  {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NONE,
    START
  } from;
  static void PrintDirection(Direction direction)
  {
    switch (direction)
    {
    case MazeCell::Direction::UP:
      std::cout << "UP";
      break;
    case MazeCell::Direction::RIGHT:
      std::cout << "RIGHT";
      break;
    case MazeCell::Direction::DOWN:
      std::cout << "DOWN";
      break;
    case MazeCell::Direction::LEFT:
      std::cout << "LEFT";
      break;
    case MazeCell::Direction::START:
      std::cout << "START";
      break;
    case MazeCell::Direction::NONE:
      std::cout << "NONE";
      break;
    default:
      break;
    }
  }
  static Direction NextClockDirection(Direction direction)
  {
    switch (direction)
    {
    case MazeCell::Direction::UP:
      return MazeCell::Direction::RIGHT;
    case MazeCell::Direction::RIGHT:
      return MazeCell::Direction::DOWN;
    case MazeCell::Direction::DOWN:
      return MazeCell::Direction::LEFT;
    case MazeCell::Direction::LEFT:
      return MazeCell::Direction::UP;
    default:
      return Direction::NONE;
      break;
    }
  }
  static Direction OpositeDirection(Direction direction)
  {
    switch (direction)
    {
    case Direction::UP:
      return Direction::DOWN;
    case Direction::RIGHT:
      return Direction::LEFT;
    case Direction::DOWN:
      return Direction::UP;
    case Direction::LEFT:
      return Direction::RIGHT;
    default:
      return Direction::NONE;
      break;
    }
  }
};

class MazeSolver
{
public:
  
  std::vector<std::vector<MazeCell>> mazeMatrix;
  int xSize;
  int ySize;
  struct Agent
  {
    int xPos;
    int yPos;
  }agent;
  MazeSolver(std::istream& mazeFile);
  MazeCell::Direction Move();
private:
  bool NeighbourPos(int xPos, int yPos, MazeCell::Direction direction, int& xOut, int& yOut)
  {
    switch (direction)
    {
    case MazeCell::Direction::UP:
      if (yPos - 1 >= 0)
      {
        xOut = xPos;
        yOut = yPos - 1;
        return true;
      }
      break;
    case MazeCell::Direction::RIGHT:
      if (xPos + 1 < xSize)
      {
        xOut = xPos + 1;
        yOut = yPos;
        return true;
      }
      break;
    case MazeCell::Direction::DOWN:
      if (yPos + 1 < ySize)
      {
        xOut = xPos;
        yOut = yPos + 1;
        return true;
      }
      break;
    case MazeCell::Direction::LEFT:
      if (xPos - 1 >= 0)
      {
        xOut = xPos - 1;
        yOut = yPos;
        return true;
      }
      break;
    default:
      throw std::exception("NeighbourPos eror");
      break;
    }
    return false;
  }
};

