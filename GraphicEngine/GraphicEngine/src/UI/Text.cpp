#include "UI/Text.h"

namespace UI
{
	Text::Text(const std::string& _label, float _x, float _y, float _width, float _height, Type _ref)
		: Element(_x, _y, _width, _height, _ref),
		content(_label),
		bgColor({ 0.204, 0.596, 0.859, 1.0 }),
		lblColor({ 1.0, 1.0, 1.0, 1.0 })
	{

	}

	void Text::draw()
	{
		drawStringCentered(content, Vector2(x_final, y_final), Vector2(width_final, height_final), lblColor, false, true);
	}

	const std::string& Text::getText() const
	{
		return content;
	}

	void Text::setText(const std::string& text)
	{
		content = text;
	}
}
