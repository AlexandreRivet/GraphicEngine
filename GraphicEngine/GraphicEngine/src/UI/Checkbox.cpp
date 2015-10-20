#include "UI/Checkbox.h"

#include "Utils/utils.h"

namespace UI
{
	Checkbox::Checkbox(float _x, float _y, float _width, float _height, Type _ref)
		: Element(_x, _y, _width, _height, _ref),
		isChecked(false),
		isHightlighted(false),
		bgColor({ 1.0, 1.0, 1.0, 1.0 })
	{}

	void Checkbox::draw()
	{
		auto thickeness = 3;
		// Contour
		if (isHightlighted)
		{
            drawSquare(Vector2(x_final, y_final), static_cast<int>(width_final), static_cast<int>(height_final), { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 });
		}
		else
		{
            drawSquare(Vector2(x_final, y_final), static_cast<int>(width_final), static_cast<int>(height_final), { 0.3, 0.3, 0.3, 1.0 }, { 0.0, 0.0, 0.0, 1.0 });
		}

		// Background
        drawSquare(Vector2(x_final + 3, y_final + 3), static_cast<int>(width_final - 2 * thickeness), static_cast<int>(height_final - 2 * thickeness), bgColor, { 0.0, 0.0, 0.0, 1.0 });

		Color checked;
		if (isChecked)
			checked = { 0.0, 0.0, 0.0, 1.0 };
		else
			checked = { 0.8, 0.8, 0.8, 1.0 };
		// Tick
		std::vector<Vector2> firstpoly;
		firstpoly.push_back(Vector2(x_final + thickeness + 1.0f, y_final + 2.0f * height_final / 3.0f));
		firstpoly.push_back(Vector2(x_final + 1.0f * width_final / 3.0f, y_final + height_final - thickeness - 1.0f));
		firstpoly.push_back(Vector2(x_final + 1.0f * width_final / 3.0f + 3.0f, y_final + height_final - thickeness - 4.0f));
		firstpoly.push_back(Vector2(x_final + thickeness + 4.0f, y_final + 2.0f * height_final / 3.0f - 3.0f));
		drawPolygon(firstpoly, checked, { 0.0, 0.0, 0.0, 1.0 });

		std::vector<Vector2> secondPoly;
		secondPoly.push_back(Vector2(x_final + 1.0f * width_final / 3.0f, y_final + height_final - thickeness - 1.0f));
		secondPoly.push_back(Vector2(x_final + width_final - thickeness - 1.0f, y_final + 1.0f * width_final / 3.0f));
		secondPoly.push_back(Vector2(x_final + width_final - thickeness - 4.0f, y_final + 1.0f * width_final / 3.0f - 3.0f));
		secondPoly.push_back(Vector2(x_final + 1.0f * width_final / 3.0f - 3.0f, y_final + height_final - thickeness - 4.0f));
		drawPolygon(secondPoly, checked, { 0.0, 0.0, 0.0, 1.0 });
		
	}

    void Checkbox::onMouseClick(int button, int state, int x, int y)
    {
		isChecked = !isChecked;

        tools::unusedArg(button, state, x, y);
    }

}