#include "UI/InputText.h"

namespace UI
{
	InputText::InputText(float _x, float _y, float _width, float _height, Type _ref)
		: Element(_x, _y, _width, _height, _ref),
		bgColor({ 1.0, 1.0, 1.0, 1.0 }),
		lblColor({ 0.204, 0.596, 0.859, 1.0 }),
		posCursor(0),
		selected(false),
		selection(0, 0)
	{

	}

	void InputText::draw()
	{
		// auto thickeness = 2.0f;
		drawSquare(Vector2(x_final, y_final), width_final, height_final, bgColor, { 0.0, 0.0, 0.0, 1.0 });

		if (selected) 
		{
			int start = selection.x;
			int end = selection.y;

			// First part
			drawStringCentered(text.substr(0, start), Vector2(x_final + 2, y_final), Vector2(width_final, height_final), lblColor, false, true);

			// Selected
			int start_selected = getXCoordInString(text, Vector2(x_final + 2, y_final), start);
			int end_selected = getXCoordInString(text, Vector2(x_final + 2, y_final), end);

			drawSquare(Vector2(start_selected, y_final + 2), end_selected - start_selected, height_final - 4, { 1.0 - bgColor.r, 1.0 - bgColor.g, 1.0 - bgColor.b, bgColor.a }, { 0.0, 0.0, 0.0, 1.0 });
			drawStringCentered(text.substr(start, end - start), Vector2(start_selected, y_final), Vector2(width_final, height_final), { 1.0 - lblColor.r, 1.0 - lblColor.g, 1.0 - lblColor.b, lblColor.a }, false, true);

			// Last part
			drawStringCentered(text.substr(end), Vector2(end_selected, y_final), Vector2(width_final, height_final), lblColor, false, true);

		}
		else
		{
			if (text.size() == 0) 
			{
				drawStringCentered("Text here...", Vector2(x_final + 2, y_final), Vector2(width_final, height_final), { 0.7, 0.7, 0.7, 1.0 }, false, true);
			}
			else 
			{
				drawStringCentered(text, Vector2(x_final + 2, y_final), Vector2(width_final, height_final), lblColor, false, true);

				int cursorX = getXCoordInString(text, Vector2(x_final + 2, y_final), posCursor);

				drawLine(Vector2(cursorX, y_final + 2), Vector2(cursorX, y_final + height_final - 4), lblColor, 1.0);
			}
			
		}
	}

}