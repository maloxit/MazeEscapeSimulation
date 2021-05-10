#pragma once
#include "Simple2DGameEngine.hpp"

using namespace GameEngine;
using namespace std;

class MazeDrawAgent :
  public GameObject,
  public EventListener
{
private:
  Transform transform;
  float moveSpeed;
  shared_ptr<RenderObject> visuals;
public:
  Vector2f target;
  MazeDrawAgent(Scene& scene, Transform& transform);
  void BeginMove(Vector2f& target);
  virtual void Update(float deltaTime);
  virtual void HandleEvent(const SDL_Event& event);
};

