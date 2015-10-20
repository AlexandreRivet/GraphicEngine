#include "UI\UIManager.h"

#include "Utils/utils.h"
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

    void UIManager::onMouseClick(int button, int state, int x, int y)
    {
        //find the best Element to click button
        m_root.onMouseClick(button, state, x, y);
    }

    void UIManager::onMouseMove(int x, int y)
    {
    }
}