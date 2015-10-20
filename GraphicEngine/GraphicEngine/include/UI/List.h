#ifndef _LIST_H_
#define _LIST_H_

#include "Element.h"

namespace UI
{
	class List : public Element
	{
	public:

		List(float _x, float _y, float _width, float _height, Type _ref = PIXEL);

		void draw();

	private:
		
		std::vector<std::string> items;
		std::vector<int> selected;
		bool multiple;

		int currentPos;
		int numberItemsInList;

		Color bgColor;
		Color lblColor;
	};


}

#endif