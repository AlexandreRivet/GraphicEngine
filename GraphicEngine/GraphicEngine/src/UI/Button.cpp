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
		float percent = 0.8f;
		float other_percent = 1.0f - percent;
		Vector2 pos(x_final, y_final);

		// Pour la gestion du bouton enfoncé
		if (isPressed) {
			other_percent /= 2.0f;
			pos.y += height_final * (1 - percent - other_percent);
		}

		// Rect principal bouton
		drawSquare(pos, width_final, height_final * percent, bgColor, { 1.0, 0.0, 0.0, 0.0 });
			
		// Effet 3D
		Color secondSquare{ bgColor.r - 0.2f, bgColor.g - 0.2f, bgColor.b - 0.2f, bgColor.a };
		drawSquare(Vector2(pos.x, pos.y + height_final * percent), width_final, height_final * other_percent, secondSquare, { 1.0, 0.0, 0.0, 0.0 });
		
		// Survol => ombre
		if (isHightlighted)
			drawStringCentered(label, Vector2(pos.x + 1, pos.y + 1), Vector2(width_final, height_final * percent), { 0.0, 0.0, 0.0, 0.0 }, true, true);

		// Label du texte
		drawStringCentered(label, pos, Vector2(width_final, height_final * percent), lblColor, true, true);

	}

    const std::string& Button::getLabel() const
    {
        return label;
    }

    void Button::setCallBack(const std::function<void(MouseButton, MouseState, int, int)>& c)
    {
        m_callBack = c;
    }

    void Button::onMouseClick(MouseButton button, MouseState state, int x, int y)
    {
        if (button == BUTTON_LEFT)
        {
            isPressed = !isPressed;

            if (state == MOUSE_DOWN)
                m_callBack(button, state, x, y);
        }
    }

	void Button::highlight()
	{
		isHightlighted = !isHightlighted;
	}
}
