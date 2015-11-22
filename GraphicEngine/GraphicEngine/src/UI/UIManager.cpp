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

	Element* UIManager::getLastMouseOverElement()
	{
		return m_lastMouseOverElement;
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
        Vector2 mouse((float)x, (float)y);

        MouseButton mouseButton = ((button == GLUT_LEFT_BUTTON) ? BUTTON_LEFT : ((button == GLUT_MIDDLE_BUTTON) ? BUTTON_MIDDLE : BUTTON_RIGHT));
        MouseState mouseState = ((state == GLUT_DOWN) ? MOUSE_DOWN : MOUSE_UP);

        if (mouseState == MOUSE_DOWN)
        {
            m_lastOnClickElems[mouseButton].clear();

			if (m_lastMouseOverElement != nullptr)
			{
				m_lastMouseOverElement->onMouseClick(mouseButton, mouseState, mouse);
				m_onFocusElement = m_lastMouseOverElement;

				m_lastOnClickElems[mouseButton].push_back(m_lastMouseOverElement);
			}
        }
        else
        {
            auto& elemClicked = m_lastOnClickElems[mouseButton];

            if (elemClicked.size() > 0)
            {
                std::for_each(elemClicked.begin(), elemClicked.end(), [mouseButton, mouseState, &mouse](Element* e)
                {
                    e->onMouseClick(mouseButton, mouseState, mouse);
                });
            }

            m_lastOnClickElems[mouseButton].clear();
        }
    }

    void UIManager::onMouseMove(int x, int y)
    {
        Vector2 mousePosition((float)x, (float)y);

        if (m_lastMouseOverElement == nullptr)
        {
            /**
             * Chercher dans les enfants de root si la souris survole un éléments
             * Recherche le plus précis
             */

            Element* childMostPrecise = nullptr;

            for (auto start = m_root.getChildren().begin(); start != m_root.getChildren().end(); ++start)
            {
                childMostPrecise = findPreciseUIElementInChild(*start, mousePosition);

                if (childMostPrecise != nullptr)
                    break;
            }

            m_lastMouseOverElement = childMostPrecise;
        }
        else
        {
            if (!isInside(m_lastMouseOverElement->getViewportBounds(), mousePosition))
            {
                /**
                * Si la souris ne survole plus l'élément le plus précis
                * Chercher le parent le plus précis
                * Si le parent trouvé n'est pas l'élément root
                * chercher dans ses enfants si il en existe un plus précis que le parent trouvé
                * si il y'a un enfant trouvé il devient le lastPrecise
                * sinon le parent devient le last
                */
                Element* parentMostPrecise = nullptr;
                Element* childMostPrecise = nullptr;

                parentMostPrecise = findPreciseUIElementInParent(m_lastMouseOverElement, mousePosition);

                if (parentMostPrecise == nullptr)
                    parentMostPrecise = &m_root;
                
                for (auto start = parentMostPrecise->getChildren().begin(); start != parentMostPrecise->getChildren().end(); ++start)
                {
                    childMostPrecise = findPreciseUIElementInChild(*start, mousePosition);

                    if (childMostPrecise != nullptr)
                        break;
                }

                if (childMostPrecise != nullptr)
                    m_lastMouseOverElement = childMostPrecise;
                else
                {
                    if (parentMostPrecise != &m_root)
                        m_lastMouseOverElement = parentMostPrecise;
                    else
                        m_lastMouseOverElement = nullptr;
                }
            }
            else
            {
                /**
                * Cherche si un enfant est plus précis que l'élément courant
                */

                Element* childMostPrecise = nullptr;

                for (auto start = m_lastMouseOverElement->getChildren().begin(); start != m_lastMouseOverElement->getChildren().end(); ++start)
                {
                    childMostPrecise = findPreciseUIElementInChild(*start, mousePosition);

                    if (childMostPrecise != nullptr)
                        break;
                }

                if (childMostPrecise != nullptr)
                    m_lastMouseOverElement = childMostPrecise;
            }
        }
    }

    void UIManager::onMouseDrag(int x, int y)
    {
        Vector2 mousePosition((float)x, (float)y);

        std::for_each(m_lastOnClickElems.begin(), m_lastOnClickElems.end(), [&mousePosition](std::pair<const MouseButton, std::vector<Element*>>& elementOnClick)
        {
            std::for_each(elementOnClick.second.begin(), elementOnClick.second.end(), [&mousePosition](Element* e)
            {
                e->onMouseDrag(mousePosition);
            });
        });
    }

	void UIManager::keyPressed(char c, bool special)
	{
		if (m_onFocusElement == nullptr)
			return;

		if (special)
			m_onFocusElement->specialPressed(c);
		else
			m_onFocusElement->keyPressed(c);
	}

	void UIManager::keyReleased(char c, bool special)
	{
		if (m_onFocusElement == nullptr)
			return;

		if (special)
			m_onFocusElement->specialReleased(c);
		else
			m_onFocusElement->keyReleased(c);
	}

    Element* UIManager::findPreciseUIElementInChild(Element* current, const Vector2& mousePosition, bool onEnter)
    {
        if (current->isVisible() && isInside(current->getViewportBounds(), mousePosition))
        {
            if (onEnter)
                current->onMouseEnter(mousePosition);

            auto& children = current->getChildren();
            Element* childMostPrecise = nullptr;

            for (auto e = children.begin(); e != children.end(); ++e)
            {
                Element* findMorePrecise = findPreciseUIElementInChild(*e, mousePosition, onEnter);

                if (findMorePrecise != nullptr)
                {
                    childMostPrecise = findMorePrecise;
                    break;
                }
            }

            if (childMostPrecise == nullptr)
            {
                childMostPrecise = current;
            }

            return childMostPrecise;
        }

        return nullptr;
    }

    Element* UIManager::findPreciseUIElementInParent(Element* current, const Vector2& mousePosition, bool onExit)
    {
        if (current->isVisible() && isInside(current->getViewportBounds(), mousePosition))
        {
            return current;
        }

        if (onExit)
            current->onMouseExit(mousePosition);

        if (current->getParent() != nullptr)
            return findPreciseUIElementInParent(current->getParent(), mousePosition, onExit);

        return nullptr;
    }
}