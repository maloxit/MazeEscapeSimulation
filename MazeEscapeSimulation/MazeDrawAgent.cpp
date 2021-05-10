#include "MazeDrawAgent.hpp"

MazeDrawAgent::MazeDrawAgent(Scene& scene, Transform& transform) : GameObject(scene, false), EventListener(true), transform(transform)
{
	moveSpeed = 50.f;
	visuals = make_shared<RenderObject>(true, this->transform, RenderLayer::TOP, 1);
	scene.renderManager->AddRenderObject(visuals);
	visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(100,255,100,255), Vector2f(0.3, 0.3), Vector2f(0.4, 0.4) });
}

void MazeDrawAgent::BeginMove(Vector2f& target)
{
	this->target = target;
	enabled = true;
}

void MazeDrawAgent::Update(float deltaTime)
{
	float step = deltaTime * moveSpeed;
	if (transform.MoveLin(target, step))
	{
		enabled = false;
	}
}

void MazeDrawAgent::HandleEvent(const SDL_Event& event)
{
	if (event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == 1)
		{
			moveSpeed *= 2;
		}
		else if (event.button.button == 3)
		{
			moveSpeed /= 2;
		}
	}
}
