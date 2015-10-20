#include "UI\UIManager.h"

#include "Utils/utils.h"
#include "Utils/Rect.h"

#include "Utils/freeglut_include.h"

namespace UI
{
    UIManager::UIManager()
        : m_root(0.0f, 0.0f, 100.0f, 100.0f, PERCENT)
    {}

    Element* UIManager::getRoot()
    {
        return &m_root;
    }

    void UIManager::render()
    {
        m_root.render();
    }

    void UIManager::computePosition(float w, float h)
    {
        m_root.computePosition(w, h);
    }

    bool hasClicked(MouseButton button, MouseState state, const Vector2& mouse, Element* e)
    {
        auto bounding = e->getFinalBounds();

        if (isInside(bounding, mouse))
        {
            auto& children = e->getChildren();

            if (children.size() == 0)
            {
                e->onMouseClick(button, state, mouse.x, mouse.y);
                return true;
            }
            else
            {
                int childHasClickedCount = 0;

                std::for_each(children.begin(), children.end(), [&childHasClickedCount, button, state, &mouse](Element* child)
                {
                    if (hasClicked(button, state, mouse, child))
                        ++childHasClickedCount;
                });

                if (childHasClickedCount == 0)
                {
                    e->onMouseClick(button, state, mouse.x, mouse.y);
                    childHasClickedCount = 1;
                }

                return childHasClickedCount != 0;
            }
        }

        return false;
    }

    void UIManager::onMouseClick(int button, int state, int x, int y)
    {
        //find the best Element to click button
        
        auto& child = m_root.getChildren();
        Vector2 mouse(x, y);

		MouseButton mouseButton = ((button == GLUT_LEFT_BUTTON) ? BUTTON_LEFT : ((button == GLUT_MIDDLE_BUTTON) ? BUTTON_MIDDLE : BUTTON_RIGHT ));
		MouseState mouseState = ((state == GLUT_DOWN) ? MOUSE_DOWN : MOUSE_UP);

		std::for_each(child.begin(), child.end(), [mouseButton, mouseState, mouse](Element* e)
        {
			hasClicked(mouseButton, mouseState, mouse, e);
        });
    }

    void UIManager::onMouseMove(int x, int y)
    {
    }

    void UIManager::onMouseDrag(int x, int y)
    {
    }
}