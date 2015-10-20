#ifndef _CHECKBOX_H_
#define _CHECKBOX_H_

#include "Element.h"

namespace UI
{
	class Checkbox : public Element
	{
	public:

		Checkbox(float _x, float _y, float _width = 30.0f, float _height = 30.0f, Type _ref = PIXEL);

		void draw();

		bool isChecked;

        void onMouseClick(int button, int state, int x, int y);
	private:
		
		bool isHightlighted;

		Color bgColor;
	};

}

#endif