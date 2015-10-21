#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <functional>

#include "Element.h"

namespace UI
{
	class Button : public Element
	{
	public:

		Button(const std::string& label, const std::function<void(char, char, int, int)>& f, float x, float y, float width, float height, Type ref = PIXEL);
		Button(const std::string& label, const std::function<void(char, char, int, int)>& f, const Rect<RefValue>& localRect);

		void computeState();
		void draw();

        const std::string& getLabel() const;
		void setLabel(const std::string& label);

        void setCallBack(const std::function<void(MouseButton, MouseState, int, int)>& c);

		void onMouseClick(MouseButton button, MouseState state, int x, int y);

	private:
		std::string mLabel;

		bool mIsHightlighted;
		bool mIsPressed;
        std::function<void(MouseButton, MouseState, int, int)> mCallBack;

		Color mLabelColor;

		// Rect 
		Rect<float> mFirstRect;
		Rect<float> mSecondRect;
	};

}

#endif