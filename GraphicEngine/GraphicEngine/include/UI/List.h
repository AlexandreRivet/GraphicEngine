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

		void select(uint index);
		std::vector<int> getSelected() const;
		void scrollDown();
		void scrollUp();

        void onMouseClick(MouseButton button, MouseState state, const Vector2& mousePosition);
        void onMouseEnter(const Vector2& mousePosition);
		void onMouseExit(const Vector2& mousePosition);
		void onMouseDrag(const Vector2& mousePosition);
		virtual void keyPressed(const char c);
		virtual void keyReleased(const char c);


	private:
		
		std::vector<std::string> items;
		std::vector<int> selected;
		bool multiple;

		uint currentPos;
		uint numberItemsInList;

		float pos_y = -1;
		float delta_sum = 0;

		Color bgColor;
		Color lblColor;
	};


}

#endif