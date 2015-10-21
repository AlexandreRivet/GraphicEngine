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
		std::string mText;
		int mPosCursor;
		
		Vector2 mSelection;			// start and end selection
		bool mSelected;

		Color lblColor;
	};


}

#endif