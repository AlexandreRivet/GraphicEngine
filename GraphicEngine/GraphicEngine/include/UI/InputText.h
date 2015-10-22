#ifndef _INPUTTEXT_H_
#define _INPUTTEXT_H_

#include "Element.h"

namespace UI
{
	class InputText : public Element
	{
	public:

		InputText(float _x, float _y, float _width, float _height, Type _ref = PIXEL);

		void computeState();
		void draw();

		bool isPressed;

		void onMouseClick(MouseButton button, MouseState state, int x, int y);
		void onMouseDrag(int x, int y);

	private:
		std::string mText;
		int mPosCursor;
		
		Vector2 mSelection;			// start and end selection
		bool mSelected;

		Color lblColor;
	};


}

#endif