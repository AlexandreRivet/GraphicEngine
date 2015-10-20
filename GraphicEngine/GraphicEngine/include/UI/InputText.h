#ifndef _INPUTTEXT_H_
#define _INPUTTEXT_H_

#include "Element.h"

namespace UI
{
	class InputText : public Element
	{
	public:

		InputText(float _x, float _y, float _width, float _height, Type _ref = PIXEL);

		void draw();

		bool isPressed;

	private:
		std::string text;
		int posCursor;
		
		Vector2 selection;
		bool selected;

		Color bgColor;
		Color lblColor;
	};


}

#endif