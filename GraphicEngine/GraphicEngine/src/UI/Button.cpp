#include "UI/Button.h"

namespace UI
{
    Button::Button(const std::string& _label, const std::function<void(char, char, int, int)>& f, float _x, float _y, float _width, float _height, Type _ref)
		: Element(_x, _y, _width, _height, _ref),
		label(_label),
		isPressed(false),
		isHightlighted(false),
        m_callBack(f),
		bgColor({0.204, 0.596, 0.859, 1.0}),
		lblColor({1.0, 1.0, 1.0, 1.0})
	{

	}

	void Button::draw()
	{
		auto percent = 0.8f;
		if (isPressed) {
			drawSquare(Vector2(x_final, y_final + height_final * (1 - percent)), width_final, height_final * percent, bgColor, { 1.0, 0.0, 0.0, 0.0 });

			if (isHightlighted)
				drawStringCentered(label, Vector2(x_final + 1, y_final + height_final * (1 - percent) + 1), Vector2(width_final, height_final * percent), { 0.0, 0.0, 0.0, 0.0 });

			drawStringCentered(label, Vector2(x_final, y_final + height_final * (1 - percent)), Vector2(width_final, height_final * percent), lblColor);

		}
		else {
			Color secondSquare{ bgColor.r - 0.2f, bgColor.g - 0.2f, bgColor.b - 0.2f, bgColor.a };

			drawSquare(Vector2(x_final, y_final), width_final, height_final * percent, bgColor, { 1.0, 0.0, 0.0, 0.0 });
			drawSquare(Vector2(x_final, y_final + height_final * percent), width_final, height_final * (1.0f - percent), secondSquare, { 1.0, 0.0, 0.0, 0.0 });

			if (isHightlighted)
				drawStringCentered(label, Vector2(x_final + 1, y_final + 1), Vector2(width_final, height_final * percent), { 0.0, 0.0, 0.0, 0.0 });

			drawStringCentered(label, Vector2(x_final, y_final), Vector2(width_final, height_final * percent), lblColor);
		}

	}

    const std::string& Button::getLabel() const
    {
        return label;
    }

    void Button::setCallBack(const std::function<void(char, char, int, int)>& c)
    {
        m_callBack = c;
    }

    void Button::onMouseClick(int button, int state, int x, int y)
    {
        m_callBack(button, state, x, y);
    }
}