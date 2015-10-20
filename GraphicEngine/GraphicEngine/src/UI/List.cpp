#include "UI/List.h"

namespace UI
{
	List::List(float _x, float _y, float _width, float _height, Type _ref)
		: Element(_x, _y, _width, _height, _ref),
		bgColor({ 1.0, 0.0, 1.0, 1.0 }),
		lblColor({ 0.204, 0.0, 0.859, 1.0 }),
		multiple(false),
		currentPos(0),
		numberItemsInList(5)
	{
	}

	void List::addItem(const std::string& item)
	{
		items.push_back(item);
	}

	void List::setMultiple(bool _multiple)
	{
		multiple = _multiple;
	}

	bool List::getMultiple() const
	{
		return multiple;
	}

	void List::scrollDown()
	{
		currentPos++;
		if (currentPos > items.size() - numberItemsInList)
			currentPos = items.size() - numberItemsInList;
	}

	void List::scrollUp()
	{
		currentPos--;
		if (currentPos < 0)
			currentPos = 0;
	}



	void List::select(int index)
	{
		auto element = std::find(selected.begin(), selected.end(), index);
		if (multiple)
		{
			if (element != selected.end())
			{
				selected.erase(element);
			}
			else
			{
				if (index < items.size())
					selected.push_back(index);
			}
		}
		else
		{
			if (element != selected.end())
			{
				selected.clear();
			}
			else if (selected.size() == 0 && index < items.size())
			{
				selected.push_back(index);
			}
			else
			{
				selected.clear();
				selected.push_back(index);
			}
		}

		// Callback ??
	}

	void List::draw()
	{
		// Draw background
		drawSquare(Vector2(x_final, y_final), width_final, height_final, bgColor, { 0.0, 0.0, 0.0, 1.0 });

		// Draw items
		int size_scroll = 15;
		int numberItems = items.size();
		int step_item = height_final / numberItemsInList;
		for (int i = 0; i < ((numberItemsInList > numberItems) ? numberItems : numberItemsInList); ++i)
		{
			// Hightlight
			if (std::find(selected.begin(), selected.end(), i + currentPos) != selected.end())
			{
				drawSquare(Vector2(x_final + 1, y_final + step_item * i + 1), width_final - size_scroll - 3, step_item - 2, lblColor, { 0.0, 0.0, 0.0, 1.0 });
				drawStringCentered(items[i + currentPos], Vector2(x_final + 5, y_final + step_item * i), Vector2(width_final, step_item), bgColor, false, true);
			}
			else
			{
				drawStringCentered(items[i + currentPos], Vector2(x_final + 5, y_final + step_item * i), Vector2(width_final, step_item), lblColor, false, true);
			}
		}

		// Draw scrollbar
		
		int offset_tri = 3;
		int x_scroll = x_final + width_final - size_scroll - 1;
		int scrollbar_bg_size = (y_final + height_final - size_scroll - 1) - (y_final + 1 + size_scroll);

		// UP
		std::vector<Vector2> tri_up;
		tri_up.push_back(Vector2(x_scroll + offset_tri, y_final + size_scroll + 1 - offset_tri));
		tri_up.push_back(Vector2(x_scroll + size_scroll - offset_tri, y_final + size_scroll + 1 - offset_tri));
		tri_up.push_back(Vector2(x_scroll + size_scroll / 2.0f, y_final + 1 + offset_tri));

		drawSquare(Vector2(x_scroll, y_final + 1), size_scroll, size_scroll, lblColor, { 0.0, 0.0, 0.0, 1.0 });
		drawPolygon(tri_up, bgColor, {0.0, 0.0, 0.0, 1.0});

		// Scrollbar
		// BG
		drawSquare(Vector2(x_scroll, y_final + 1 + size_scroll), size_scroll, scrollbar_bg_size, { 0.8, 0.8, 0.8, 1.0 }, { 0.0, 0.0, 0.0, 1.0 });
		
		// Current
		int y_current = y_final + 2 + size_scroll;
		y_current += (numberItems != 0) ? scrollbar_bg_size / numberItems * currentPos : 0;
		int height_current = (numberItems != 0) ? scrollbar_bg_size / numberItems * numberItemsInList : 0;
		drawSquare(Vector2(x_scroll, y_current), size_scroll, height_current, lblColor, { 0.0, 0.0, 0.0, 1.0 });

		// DOWN
		std::vector<Vector2> tri_down;
		tri_down.push_back(Vector2(x_scroll + offset_tri, y_final + height_final - size_scroll - 1 + offset_tri));
		tri_down.push_back(Vector2(x_scroll + size_scroll - offset_tri, y_final + height_final - size_scroll - 1 + offset_tri));
		tri_down.push_back(Vector2(x_scroll + size_scroll / 2.0f, y_final + height_final - 1 - offset_tri));

		drawSquare(Vector2(x_scroll, y_final + height_final - size_scroll - 1), size_scroll, size_scroll, lblColor, { 0.0, 0.0, 0.0, 1.0 });
		drawPolygon(tri_down, bgColor, { 0.0, 0.0, 0.0, 1.0 });
	}

	void List::onMouseClick(MouseButton button, MouseState state, int x, int y)
	{
		int size_scroll = 15;
		// Scroll up
		if (x > x_final + width_final - size_scroll && y < y_final + size_scroll && state == MOUSE_DOWN)
		{
			scrollUp();
		}

		// Scroll down
		else if (x > x_final + width_final - size_scroll && y > y_final + height_final - size_scroll && state == MOUSE_DOWN)
		{
			scrollDown();
		}

		// Sélection d'un item (ou déselection => appel le callback en question)
		else if (x < x_final + width_final - size_scroll && state == MOUSE_DOWN)
		{
			int step_item = height_final / numberItemsInList;
			int y_relative = y - y_final;
			int sel = y_relative / step_item;
			select(sel + currentPos);
		}
	}

	void List::onMouseEnter(int x, int y)
	{

	}

	void List::onMouseExit(int x, int y)
	{

	}

}