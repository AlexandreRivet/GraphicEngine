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

		void addItem(const std::string& item);
		void setMultiple(bool _multiple);
		bool getMultiple() const;

		void select(int index);
		void scrollDown();
		void scrollUp();

		void onMouseClick(MouseButton button, MouseState state, int x, int y);
		void onMouseEnter(int x, int y);
		void onMouseExit(int x, int y);

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