#include "UI\UIManager.h"

#include "Utils/utils.h"
#include "Utils/Rect.h"

#include "Utils/freeglut_include.h"

#include <memory>
namespace UI
{
    UIManager::UIManager()
        : m_root(0.0f, 0.0f, 100.0f, 100.0f, PERCENT),
        m_lastMouseOverElement(nullptr)
    {
    }

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

    void UIManager::onMouseClick(int button, int state, int x, int y)
    {
        //find the best Element to click button
        
        auto& child = m_root.getChildren();
        Vector2 mouse(x, y);

		MouseButton mouseButton = ((button == GLUT_LEFT_BUTTON) ? BUTTON_LEFT : ((button == GLUT_MIDDLE_BUTTON) ? BUTTON_MIDDLE : BUTTON_RIGHT ));
		MouseState mouseState = ((state == GLUT_DOWN) ? MOUSE_DOWN : MOUSE_UP);

        if (mouseState == MOUSE_DOWN)
        {
            m_lastOnClickElems[mouseButton].clear();

            std::for_each(child.begin(), child.end(), [mouseButton, mouseState, mouse, this](Element* e)
            {
                hasClicked(mouseButton, mouseState, mouse, e);
            });
        }
        else
        {
            auto& elemClicked = m_lastOnClickElems[mouseButton];

            if (elemClicked.size() > 0)
            {
                std::for_each(elemClicked.begin(), elemClicked.end(), [mouseButton, mouseState, x, y](Element* e)
                {
                    e->onMouseClick(mouseButton, mouseState, x, y);
                });
            }

            m_lastOnClickElems[mouseButton].clear();
        }
    }

    void UIManager::onMouseMove(int x, int y)
    {
        /**
         * if last more precise is not null check if mouse is already inside current element
         *
         */
    }

    void UIManager::onMouseDrag(int x, int y)
    {
        std::for_each(m_lastOnClickElems.begin(), m_lastOnClickElems.end(), [x, y](std::pair<const MouseButton, std::vector<Element*>>& elementOnClick)
        {
            std::for_each(elementOnClick.second.begin(), elementOnClick.second.end(), [x, y](Element* e)
            {
                e->onMouseDrag(x, y);
            });
        });
    }

    bool UIManager::hasClicked(MouseButton button, MouseState state, const Vector2& mouse, Element* e)
    {
        auto bounding = e->getViewportBounds();

        if (e->isVisible() && isInside(bounding, mouse))
        {
            auto& children = e->getChildren();

            if (children.size() == 0)
            {
                e->onMouseClick(button, state, mouse.x, mouse.y);
                m_lastOnClickElems[button].push_back(e);

                return true;
            }
            else
            {
                int childHasClickedCount = 0;

                std::for_each(children.begin(), children.end(), [&childHasClickedCount, button, state, &mouse, this](Element* child)
                {
                    if (hasClicked(button, state, mouse, child))
                        ++childHasClickedCount;
                });

                if (childHasClickedCount == 0)
                {
                    e->onMouseClick(button, state, mouse.x, mouse.y);
                    childHasClickedCount = 1;

                    m_lastOnClickElems[button].push_back(e);
                }

                return childHasClickedCount != 0;
            }
        }

        return false;
    }

    Element* findPreciseUIElement(Element* start, int x, int y)
    {
        if (!start->isVisible())
            return nullptr;

        if (isInside(start->getViewportBounds(), Vector2(x, y)))
        {
            auto& children = start->getChildren();
            Element* preciseUiElement = nullptr;

            for (auto e = children.begin(); e != children.end(); ++e)
            {
                Element* findMorePrecise = findPreciseUIElement(*e, x, y);

                if (findMorePrecise != nullptr)
                {
                    preciseUiElement = findMorePrecise;
                    break;
                }
            }

            if (preciseUiElement == nullptr)
            {
                preciseUiElement = start;
            }

            return preciseUiElement;
        }

        return nullptr;
    }
}