#ifndef _TEXT_H_
#define _TEXT_H_

#include <functional>

#include "Element.h"

namespace UI
{
	class Text : public Element
	{
	public:

		Text(const std::string& _text, float _x, float _y, float _width, float _height, Type _ref = PIXEL);

		void setText(const std::string& text);
		const std::string& getText() const;
		void setCenterStyle(bool hor, bool ver);

		void draw();

        virtual void onMouseEnter(const Vector2& mousePosition){ tools::unusedArg(mousePosition); };
        virtual void onMouseExit(const Vector2& mousePosition){ tools::unusedArg(mousePosition); };

	private:
		std::string content;

		bool mHorCentered;
		bool mVerCentered;

		ColorStruct bgColor;
		ColorStruct lblColor;
	};

}

#endif