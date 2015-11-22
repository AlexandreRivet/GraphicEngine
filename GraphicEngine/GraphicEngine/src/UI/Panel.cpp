#include "UI/Panel.h"

#include <algorithm>
#include "Utils/utils.h"

namespace UI
{
	Panel::Panel(float _x, float _y, float _width, float _height, Type _ref)
		: Layout(_x, _y, _width, _height, _ref)
	{}

	void Panel::draw()
	{
		drawSquare(Vector2(mViewportRect.x, mViewportRect.y), (int)mViewportRect.w, (int)mViewportRect.h, { 0.2f, 0.25f, 0.3f, 1.0f }, { 1.0f, 0.0f, 0.0f, 0.0f });
	}
}