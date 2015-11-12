#ifndef _CHECKBOX_H_
#define _CHECKBOX_H_

#include "Element.h"

namespace UI
{
	class Checkbox : public Element
	{
	public:

		Checkbox(bool* toggleFlag, float _x, float _y, float _width = 20.0f, float _height = 20.0f, Type _ref = PIXEL);

		bool isChecked() const;

		void computeState();
		void draw();

        void setToggleFlag(bool*);

        void onMouseClick(MouseButton button, MouseState state, const Vector2& mousePosition);

	private:
		
		bool mIsChecked;

        bool* mToggleflag;

		// Variable saved for calculations 
		Rect<float> mFirstRect;
		std::vector<std::vector<Vector2>> mTickPolys;

	};

}

#endif