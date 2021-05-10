#include "MazeDrawCell.hpp"

void MazeDrawCell::ShowLine(MazeCell::Direction enter, MazeCell::Direction exit)
{
	base->primitives[0].color.y -= 51;
	base->primitives[0].color.z -= 51;
	switch (enter)
	{
	case MazeCell::Direction::UP:
		enterUpLine->enabled = true;
		switch (exit)
		{
		case MazeCell::Direction::UP:
			exitUpLine->enabled = true;
			centerRightLine->enabled = true;
			centerDownLine->enabled = true;
			centerLeftLine->enabled = true;
			break;
		case MazeCell::Direction::RIGHT:
			exitRightLine->enabled = true;
			break;
		case MazeCell::Direction::DOWN:
			exitDownLine->enabled = true;
			centerRightLine->enabled = true;
			break;
		case MazeCell::Direction::LEFT:
			exitLeftLine->enabled = true;
			centerRightLine->enabled = true;
			centerDownLine->enabled = true;
			break;
		default:
			break;
		}
		break;
	case MazeCell::Direction::RIGHT:
		enterRightLine->enabled = true;
		switch (exit)
		{
		case MazeCell::Direction::UP:
			exitUpLine->enabled = true;
			centerDownLine->enabled = true;
			centerLeftLine->enabled = true;
			break;
		case MazeCell::Direction::RIGHT:
			exitRightLine->enabled = true;
			centerDownLine->enabled = true;
			centerLeftLine->enabled = true;
			centerUpLine->enabled = true;
			break;
		case MazeCell::Direction::DOWN:
			exitDownLine->enabled = true;
			break;
		case MazeCell::Direction::LEFT:
			exitLeftLine->enabled = true;
			centerDownLine->enabled = true;
			break;
		default:
			break;
		}
		break;
	case MazeCell::Direction::DOWN:
		enterDownLine->enabled = true;
		switch (exit)
		{
		case MazeCell::Direction::UP:
			exitUpLine->enabled = true;
			centerLeftLine->enabled = true;
			break;
		case MazeCell::Direction::RIGHT:
			exitRightLine->enabled = true;
			centerLeftLine->enabled = true;
			centerUpLine->enabled = true;
			break;
		case MazeCell::Direction::DOWN:
			exitDownLine->enabled = true;
			centerLeftLine->enabled = true;
			centerUpLine->enabled = true;
			centerRightLine->enabled = true;
			break;
		case MazeCell::Direction::LEFT:
			exitLeftLine->enabled = true;
			break;
		default:
			break;
		}
		break;
	case MazeCell::Direction::LEFT:
		enterLeftLine->enabled = true;
		switch (exit)
		{
		case MazeCell::Direction::UP:
			exitUpLine->enabled = true;
			break;
		case MazeCell::Direction::RIGHT:
			exitRightLine->enabled = true;
			centerUpLine->enabled = true;
			break;
		case MazeCell::Direction::DOWN:
			exitDownLine->enabled = true;
			centerUpLine->enabled = true;
			centerRightLine->enabled = true;
			break;
		case MazeCell::Direction::LEFT:
			exitLeftLine->enabled = true;
			centerUpLine->enabled = true;
			centerRightLine->enabled = true;
			centerDownLine->enabled = true;
			break;
		default:
			break;
		}
		break;

	case MazeCell::Direction::START:
		switch (exit)
		{
		case MazeCell::Direction::UP:
			exitUpLine->enabled = true;
			break;
		case MazeCell::Direction::RIGHT:
			exitRightLine->enabled = true;
			break;
		case MazeCell::Direction::DOWN:
			exitDownLine->enabled = true;
			break;
		case MazeCell::Direction::LEFT:
			exitLeftLine->enabled = true;
			break;
		default:
			break;
		}
	break;
	default:
		break;
	}
}

MazeDrawCell::MazeDrawCell(Scene& scene, MazeCell& cell, Transform& transform) : scene(scene), transform(transform)
{
	base = make_shared<RenderObject>(true, this->transform, RenderLayer::BOTTOM, 2);
	scene.renderManager->AddRenderObject(base);
	switch (cell.type)
	{
	case MazeCell::Type::FREE:
		base->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255,255,255,255), Vector2f(0, 0), Vector2f(1, 1) });
		break;
	case MazeCell::Type::WALL:
		base->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(50,50,50,255), Vector2f(0, 0), Vector2f(1, 1) });
		break;
	case MazeCell::Type::EXIT:
		base->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(100,100,255,255), Vector2f(0, 0), Vector2f(1, 1) });
		break;
	default:
		break;
	}
	base->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::RECT, Vector4uc(0,0,0,255), Vector2f(0.1, 0.1), Vector2f(0.8, 0.8) });

	centerUpLine = make_shared<RenderObject>(false, this->transform, RenderLayer::MIDDLE, 1);
	centerRightLine = make_shared<RenderObject>(false, this->transform, RenderLayer::MIDDLE, 1);
	centerDownLine = make_shared<RenderObject>(false, this->transform, RenderLayer::MIDDLE, 1);
	centerLeftLine = make_shared<RenderObject>(false, this->transform, RenderLayer::MIDDLE, 1);
	scene.renderManager->AddRenderObject(centerUpLine);
	scene.renderManager->AddRenderObject(centerRightLine);
	scene.renderManager->AddRenderObject(centerDownLine);
	scene.renderManager->AddRenderObject(centerLeftLine);
	centerUpLine->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255,0,0,255), Vector2f(0.2, 0.2), Vector2f(0.6, 0.2) });
	centerRightLine->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255,0,0,255), Vector2f(0.6, 0.2), Vector2f(0.2, 0.6) });
	centerDownLine->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255,0,0,255), Vector2f(0.2, 0.6), Vector2f(0.6, 0.2) });
	centerLeftLine->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255,0,0,255), Vector2f(0.2, 0.2), Vector2f(0.2, 0.6) });

	enterUpLine = make_shared<RenderObject>(false, this->transform, RenderLayer::MIDDLE, 1);
	enterRightLine = make_shared<RenderObject>(false, this->transform, RenderLayer::MIDDLE, 1);
	enterDownLine = make_shared<RenderObject>(false, this->transform, RenderLayer::MIDDLE, 1);
	enterLeftLine = make_shared<RenderObject>(false, this->transform, RenderLayer::MIDDLE, 1);
	scene.renderManager->AddRenderObject(enterUpLine);
	scene.renderManager->AddRenderObject(enterRightLine);
	scene.renderManager->AddRenderObject(enterDownLine);
	scene.renderManager->AddRenderObject(enterLeftLine);
	enterUpLine->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255,0,0,255), Vector2f(0.6, 0), Vector2f(0.2, 0.4) });
	enterRightLine->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255,0,0,255), Vector2f(0.6, 0.6), Vector2f(0.4, 0.2) });
	enterDownLine->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255,0,0,255), Vector2f(0.2, 0.6), Vector2f(0.2, 0.4) });
	enterLeftLine->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255,0,0,255), Vector2f(0, 0.2), Vector2f(0.4, 0.2) });

	exitUpLine = make_shared<RenderObject>(false, this->transform, RenderLayer::MIDDLE, 1);
	exitRightLine = make_shared<RenderObject>(false, this->transform, RenderLayer::MIDDLE, 1);
	exitDownLine = make_shared<RenderObject>(false, this->transform, RenderLayer::MIDDLE, 1);
	exitLeftLine = make_shared<RenderObject>(false, this->transform, RenderLayer::MIDDLE, 1);
	scene.renderManager->AddRenderObject(exitUpLine);
	scene.renderManager->AddRenderObject(exitRightLine);
	scene.renderManager->AddRenderObject(exitDownLine);
	scene.renderManager->AddRenderObject(exitLeftLine);
	exitUpLine->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255,0,0,255), Vector2f(0.2, 0), Vector2f(0.2, 0.4) });
	exitRightLine->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255,0,0,255), Vector2f(0.6, 0.2), Vector2f(0.4, 0.2) });
	exitDownLine->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255,0,0,255), Vector2f(0.6, 0.6), Vector2f(0.2, 0.4) });
	exitLeftLine->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255,0,0,255), Vector2f(0, 0.6), Vector2f(0.4, 0.2) });
}
