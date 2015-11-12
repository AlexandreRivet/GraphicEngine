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

		void onMouseClick(MouseButton button, MouseState state, const Vector2& mousePosition);
        void onMouseDrag(const Vector2& mousePosition);

        virtual void onMouseEnter(const Vector2& mousePosition){ tools::unusedArg(mousePosition); };
        virtual void onMouseExit(const Vector2& mousePosition){ tools::unusedArg(mousePosition); };

	private:
		std::string mText;
		int mPosCursor;
		
		Vector2 mSelection;			// start and end selection
		bool mSelected;

		Color lblColor;
	};


}

#endif