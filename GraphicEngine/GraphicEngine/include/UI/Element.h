#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "prerequisites.h"
#include <functional>

#include "Shapes.h"

namespace UI
{
	enum Type {PIXEL, PERCENT};

	struct RefValue
	{
		float value;
		Type ref;

		RefValue(float _value, Type _ref)
			: value(_value),
			ref(_ref)
		{}
	};

	template<typename T>
	class Rect
	{
		T x;
		T y;
		T w;
		T h;
	};		

    class Element
    {
    public:
        Element(float _x, float _y, float _width, float _height, Type _ref = PIXEL);

        virtual bool Element::setStyle(std::string style);	// non const because of clean up the string
        void computePosition(float w, float h);

        void setParent(Element* element);
        void addElement(Element* element);

        void render();
        virtual void draw() = 0;

        /**
         * Mouse Graphic event
         */
        virtual void onMouseClick(int button, int state, int x, int y){};
        virtual void onMouseEnter(int x, int y){};
        virtual void onMouseExite(int x, int y){};

	protected:

		RefValue x;								// Coordinate x (local)
		RefValue y;								// Coordinate y (local)
		RefValue width;							// Width (local)
		RefValue height;						// Height (local)

		float x_final;							// Coordinate x (viewport)
		float y_final;							// Coordinate y (viewport)
		float width_final;						// Width (viewport)
		float height_final;						// Height (viewport)

		Element* parent;						// Parent of the element
		std::vector<Element*> children;			// List of element children of this

	};

}

#endif