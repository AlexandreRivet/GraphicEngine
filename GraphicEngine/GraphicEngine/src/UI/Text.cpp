#include "UI/Text.h"

namespace UI
{
	Text::Text(const std::string& _label, float _x, float _y, float _width, float _height, Type _ref)
		: Element(_x, _y, _width, _height, _ref),
		content(_label),
		bgColor({ 0.204f, 0.596f, 0.859f, 1.0f }),
		lblColor({ 1.0f, 1.0f, 1.0f, 1.0f })
	{

	}

	void Text::draw()
	{
		drawStringCentered(content, Vector2(mViewportRect.x, mViewportRect.y), Vector2(mViewportRect.w, mViewportRect.h), lblColor, false, true);
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
