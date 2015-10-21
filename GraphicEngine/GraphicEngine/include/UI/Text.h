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

		void draw();

	private:
		std::string content;

		Color bgColor;
		Color lblColor;
	};

}

#endif