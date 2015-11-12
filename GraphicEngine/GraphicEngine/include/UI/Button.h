#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <functional>

#include "Element.h"

namespace UI
{
	class Button : public Element
	{
	public:

		Button(const std::string& label, const std::function<void(char, char, const Vector2& mousePosition)>& f, float x, float y, float width, float height, Type ref = PIXEL);
		Button(const std::string& label, const std::function<void(char, char, const Vector2& mousePosition)>& f, const Rect<RefValue>& localRect);

		void computeState();
		void draw();

        const std::string& getLabel() const;
		void setLabel(const std::string& label);

        void setCallBack(const std::function<void(MouseButton, MouseState, const Vector2& mousePosition)>& c);

		void onMouseClick(MouseButton button, MouseState state, const Vector2& mousePosition);
		void onMouseEnter(const Vector2& mousePosition);
		void onMouseExit(const Vector2& mousePosition);

	private:
		std::string mLabel;

		bool mIsHightlighted;
		bool mIsPressed;
        std::function<void(MouseButton, MouseState, const Vector2& mousePosition)> mCallBack;

		Color mLabelColor;

		// Variable saved for calculations 
		Rect<float> mFirstRect;
		Rect<float> mSecondRect;
	};

}

#endif