#include "UI/Element.h"

#include "Utils/Utils.h"

#include <algorithm>

namespace UI
{

	Element::Element(float _x, float _y, float _width, float _height, Type _ref)
		: 
		x(_x, _ref),
		y(_y, _ref),
		width(_width, _ref),
		height(_height, _ref)
	{
		
	}

	bool Element::setStyle(std::string style)
	{
		std::transform(style.begin(), style.end(), style.begin(), ::tolower);		// pour sécuriser ce qu'envoit l'utilisateur
		style.erase(std::remove_if(style.begin(), style.end(), [](char c)
		{
			return c == ' ';
		}), style.end());

		std::vector<std::string> elements( Utils::split(style, ';') );	// split en fonction du ;

		for (auto element = elements.begin(); element != elements.end(); ++element)
		{
			std::vector<std::string> keyValue(Utils::split(*element, ':'));
			
			if (keyValue.size() != 2)
				return false;

			std::string& key = keyValue.front();
			std::string& value = keyValue.back();

			if (value.size() < 2)
				return false;

			auto lastLetter = value.substr(value.length() - 2, 2);

			float floatValue;
			Type type;

			if (lastLetter.back() == '%')
			{
				floatValue = ::atof(value.substr(0, value.length() - 1).c_str());
				type = PERCENT;
			}
			else if (lastLetter.front() == 'p' && lastLetter.back() == 'x')
			{
				if (value.size() < 3)
					return false;

				floatValue = ::atof(value.substr(0, value.length() - 2).c_str());
				type = PIXEL;
			}
			else
			{
				return false;
			}

			RefValue* valueToFill = nullptr;


			if (key == "x")
			{
				valueToFill = &x;
			}
			else if (key == "y")
			{
				valueToFill = &y;
			}
			else if (key == "width")
			{
				valueToFill = &width;
			}
			else if (key == "height")
			{
				valueToFill = &height;
			}

			if (valueToFill == nullptr)
				return false;

			valueToFill->value = floatValue;
			valueToFill->ref = type;			
		}

		return true;

	}

	void Element::computePosition(float w, float h)			// au cas où pour gérer
	{
		// Mise à jour de la position finale
		if (parent == nullptr)
		{
			x_final = ((x.ref == PERCENT) ? w * x.value / 100.0f : x.value);
			y_final = ((y.ref == PERCENT) ? h * y.value / 100.0f : y.value);
			width_final = ((width.ref == PERCENT) ? w * width.value / 100.0f : width.value);
			height_final = ((height.ref == PERCENT) ? h * height.value / 100.0f : height.value);
		}
		else
		{
			float x_p = parent->x_final;
			float y_p = parent->y_final;
			float w_p = parent->width_final;
			float h_p = parent->height_final;

			x_final = ((x.ref == PERCENT) ? w_p * x.value / 100.0f : x.value) + x_p;
			y_final = ((y.ref == PERCENT) ? h_p * y.value / 100.0f : y.value) + y_p;
			width_final = ((width.ref == PERCENT) ? w_p * width.value / 100.0f : width.value);
			height_final = ((height.ref == PERCENT) ? h_p * height.value / 100.0f : height.value);
		}

		// Mise à jour de la position des fils
		int numberChildren = children.size();
		for (int i = 0; i < numberChildren; ++i)
		{
			children[i]->computePosition(w, h);
		}
	}

	void Element::setParent(Element* element)
	{
		parent = element;
	}

	void Element::addElement(Element* element)
	{
		element->setParent(this);
		children.push_back(element);	
	}

	void Element::render()
	{
		draw();

		int numberChildren = children.size();
		for (int i = 0; i < numberChildren; ++i)
		{
			children[i]->render();
		}
	}

}