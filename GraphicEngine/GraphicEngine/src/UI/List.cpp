#include "UI/List.h"

namespace UI
{
	List::List(float _x, float _y, float _width, float _height, Type _ref)
		: Element(_x, _y, _width, _height, _ref),
		bgColor( 1.0f, 1.0f, 1.0f, 1.0f ),
		lblColor( 0.204f, 0.596f, 0.859f, 1.0f),
		multiple(false),
		currentPos(0),
		numberItemsInList(8)
	{
	}

	void List::addItem(const std::string& item)
	{
		items.push_back(item);
	}

	const std::string& List::getItem(uint index) const
	{
		//TODO secu
		return items[index];
	}

	std::string& List::getItem(uint index)
	{
		//TODO secu
		return items[index];
	}

	void List::editItem(uint index, const std::string& item)
	{
		items[index] = item;
	}

	void List::removeItem(uint index)
	{
		// Quand on supprime le dernier et qu'il y a plus d'item que la liste peut afficher en m�me temps
		if (index == items.size() - 1 && items.size() > numberItemsInList)
		{
			scrollUp();
		}

		items.erase(items.begin() + index);
	}

	void List::removeAll()
	{
		for (size_t i = 0, end = items.size(); i < end; ++i)
		{
			removeItem(0);
		}
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
        if (numberItemsInList > items.size())
            return;

		currentPos++;
		if (currentPos > items.size() - numberItemsInList)
			currentPos = items.size() - numberItemsInList;
	}

	void List::scrollUp()
	{
        if (numberItemsInList > items.size())
            return;

		if (currentPos > 0)
			currentPos--;
	}

	void List::select(uint index)
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
			deselectAll();
			if (index < items.size())	
				selected.push_back(index);
		}

		// Callback ??
	}

	void List::selectLast()
	{
		select(items.size() - 1);
	}

	void List::deselectAll()
	{
		selected.clear();
	}

	std::vector<int> List::getSelected() const
	{
		return selected;
	}

	void List::draw()
	{
		// Draw background
		drawSquare(Vector2(mViewportRect.x, mViewportRect.y), (int)mViewportRect.w, (int)mViewportRect.h, bgColor, { 0.0, 0.0, 0.0, 1.0 });

		// Draw items
		uint size_scroll = 15;
		uint numberItems = items.size();
		int step_item = (int)mViewportRect.h / numberItemsInList;
		for (uint i = 0; i < ((numberItemsInList > numberItems) ? numberItems : numberItemsInList); ++i)
		{
			// Hightlight
			if (std::find(selected.begin(), selected.end(), i + currentPos) != selected.end())
			{
				drawSquare(Vector2(mViewportRect.x + 1, mViewportRect.y + step_item * i + 1), mViewportRect.w - size_scroll - 3, step_item - 2, lblColor, { 0.0, 0.0, 0.0, 1.0 });
				drawStringCentered(items[i + currentPos], Vector2(mViewportRect.x + 5.f, (float)(mViewportRect.y + step_item * i)), Vector2(mViewportRect.w, (float)step_item), bgColor, false, true);
			}
			else
			{
				drawStringCentered(items[i + currentPos], Vector2(mViewportRect.x + 5.f, (float)mViewportRect.y + step_item * i), Vector2(mViewportRect.w, (float)step_item), lblColor, false, true);
			}
		}

		// Draw scrollbar
		
		int offset_tri = 3;
		int x_scroll = (int)(mViewportRect.x + mViewportRect.w - size_scroll - 1);
		int scrollbar_bg_size = (int)(mViewportRect.h - 2 * (size_scroll + 1));

		// UP
		std::vector<Vector2> tri_up;
		tri_up.push_back(Vector2((float)(x_scroll + offset_tri), (float)(mViewportRect.y + size_scroll - offset_tri)));
		tri_up.push_back(Vector2((float)(x_scroll + size_scroll / 2.0f), (float)(mViewportRect.y + offset_tri)));
		tri_up.push_back(Vector2((float)(x_scroll + size_scroll - offset_tri), (float)(mViewportRect.y + size_scroll - offset_tri)));

		drawSquare(Vector2((float)x_scroll, mViewportRect.y + 1.f), size_scroll, size_scroll, lblColor, { 0.f, 0.f, 0.f, 1.f});
		drawPolygon(tri_up, bgColor, {0.f, 0.f, 0.f, 1.f});

		// Scrollbar
		// BG
		drawSquare(Vector2(static_cast<int>(x_scroll), mViewportRect.y + 1.0f + static_cast<float>(size_scroll)), size_scroll, scrollbar_bg_size, { 0.8f, 0.8f, 0.8f, 1.0f }, { 0.0f, 0.0f, 0.0f, 1.0f });
		
		// Current
		if (numberItems > numberItemsInList)
		{
			float step = (numberItems != 0) ? scrollbar_bg_size / (float)numberItems : 0;
			int y_current = (int)(mViewportRect.y + 2 + size_scroll);
			y_current += step * currentPos;
			int height_current = (int)(numberItemsInList * step - 2);
			drawSquare(Vector2(x_scroll, y_current), size_scroll, height_current, lblColor, { 0.0, 0.0, 0.0, 1.0 });
		}

		// DOWN
		std::vector<Vector2> tri_down;
		tri_down.push_back(Vector2((float)(x_scroll + offset_tri), (float)(mViewportRect.y + mViewportRect.h - size_scroll - 1 + offset_tri)));
		tri_down.push_back(Vector2((float)(x_scroll + size_scroll - offset_tri), (float)(mViewportRect.y + mViewportRect.h - size_scroll - 1 + offset_tri)));
		tri_down.push_back(Vector2((float)(x_scroll + size_scroll / 2.0f), (float)(mViewportRect.y + mViewportRect.h - 1 - offset_tri)));

		drawSquare(Vector2((float)(x_scroll), (float)(mViewportRect.y + mViewportRect.h - size_scroll - 1)), size_scroll, size_scroll, lblColor, { 0.0, 0.0, 0.0, 1.0 });
		drawPolygon(tri_down, bgColor, { 0.0, 0.0, 0.0, 1.0 });
	}

    void List::onMouseClick(MouseButton button, MouseState state, const Vector2& mousePosition)
	{
		int size_scroll = 15;
		// Scroll up
        if (mousePosition.x > mViewportRect.x + mViewportRect.w - size_scroll && mousePosition.y < mViewportRect.y + size_scroll && state == MOUSE_DOWN && button == BUTTON_LEFT)
		{
			scrollUp();
		}

		// Scroll down
		else if (mousePosition.x > mViewportRect.x + mViewportRect.w - size_scroll && mousePosition.y > mViewportRect.y + mViewportRect.h - size_scroll && state == MOUSE_DOWN && button == BUTTON_LEFT)
		{
			scrollDown();
		}

		// S�lection d'un item (ou d�selection => appel le callback en question)
		else if (mousePosition.x < mViewportRect.x + mViewportRect.w - size_scroll && state == MOUSE_DOWN && button == BUTTON_LEFT)
		{
			int step_item = (int)(mViewportRect.h / numberItemsInList);
			int y_relative = (int)(mousePosition.y - mViewportRect.y);
			int sel = y_relative / step_item;
			select(sel + currentPos);
		}
		else
		{
			pos_y = mousePosition.y;
		}
	}

    void List::onMouseEnter(const Vector2&)
	{
	}

    void List::onMouseExit(const Vector2&)
	{
	}

    void List::onMouseDrag(const Vector2& mousePosition)
	{
		int size_scroll = 15;
        if (mousePosition.x > mViewportRect.x + mViewportRect.w - size_scroll && mousePosition.y > mViewportRect.y + size_scroll && mousePosition.y < mViewportRect.y + mViewportRect.h - size_scroll)
		{
			float delta_y = mousePosition.y - pos_y;
			delta_sum += delta_y;
			float delta_sum_abs = abs(delta_sum);
			float scrollbar_bg_size = mViewportRect.h - 2 * (size_scroll + 1);
			float step = (items.size() != 0) ? scrollbar_bg_size / (float)items.size() : 0;
			float size_step_scroll = scrollbar_bg_size / step;
			if (delta_sum_abs > size_step_scroll)
			{
				if (delta_sum < 0)
					scrollUp();
				else
					scrollDown();
				delta_sum = 0;
			}
            pos_y = mousePosition.y;
		}
	}

	void List::keyPressed(const char c)
	{
		switch (c)
		{
		case 101:
			scrollUp();
			break;
		case 103:
			scrollDown();
			break;
		}
	}

	void List::keyReleased(const char)
	{

	}

}