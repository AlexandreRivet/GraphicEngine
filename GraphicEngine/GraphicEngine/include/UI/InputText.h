#ifndef _INPUTTEXT_H_
#define _INPUTTEXT_H_

#include "Element.h"

namespace UI
{
	class InputText : public Element
	{
	public:

		InputText(float _x, float _y, float _width, float _height, Type _ref = PIXEL);

		void setText(const std::string& text);
		const std::string& getText() const;
		void computeState();
		void draw();

		void onMouseClick(MouseButton button, MouseState state, const Vector2& mousePosition);
        void onMouseDrag(const Vector2& mousePosition);

        virtual void onMouseEnter(const Vector2& mousePosition){ tools::unusedArg(mousePosition); };
        virtual void onMouseExit(const Vector2& mousePosition){ tools::unusedArg(mousePosition); };
		void keyPressed(const char c);
		void keyReleased(const char c);
		void specialPressed(const char c);
		void specialReleased(const char c);

	private:
		std::string mText;
		int mPosCursor;
		
		Vector2 mSelection;			// start and end selection
		bool mSelected;

		Color lblColor;
	};


}

#endif