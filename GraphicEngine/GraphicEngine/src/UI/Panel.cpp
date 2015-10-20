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
		drawSquare(Vector2(x_final, y_final), width_final, height_final, { 0.2, 0.25, 0.3, 0.0 }, { 1.0, 0.0, 0.0, 0.0 });
	}
}