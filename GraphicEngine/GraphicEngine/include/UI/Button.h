#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Element.h"

namespace UI
{
	class Button : public Element
	{
	public:

		Button(const std::string& _label, float _x, float _y, float _width, float _height, Type _ref = PIXEL);

		void draw();

		bool isPressed;

	private:
		std::string label;
		bool isHightlighted;
		// bool isPressed;

		Color bgColor;
		Color lblColor;
	};


}

#endif