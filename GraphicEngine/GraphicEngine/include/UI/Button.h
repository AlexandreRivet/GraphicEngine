#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <functional>

#include "Element.h"

namespace UI
{
	class Button : public Element
	{
	public:

		Button(const std::string& _label, const std::function<void(char, char, int, int)>& f, float _x, float _y, float _width, float _height, Type _ref = PIXEL);

		void draw();

        const std::string& getLabel() const;
        void setCallBack(const std::function<void(MouseButton, MouseState, int, int)>& c);

		void highlight();

		void onMouseClick(MouseButton button, MouseState state, int x, int y);

	private:
		std::string label;
		bool isHightlighted;
		bool isPressed;
        std::function<void(MouseButton, MouseState, int, int)> m_callBack;

		Color bgColor;
		Color lblColor;
	};


}

#endif