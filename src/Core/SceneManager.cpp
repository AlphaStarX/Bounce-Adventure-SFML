#include "BounceAdventure/Core/SceneManager.hpp"

namespace BounceAdventure
{
void SceneManager::push(std::unique_ptr<Scene> scene)
{
    m_pendingChanges.push_back({PendingActionType::Push, std::move(scene)});
}

void SceneManager::pop()
{
    m_pendingChanges.push_back({PendingActionType::Pop, nullptr});
}

void SceneManager::replace(std::unique_ptr<Scene> scene)
{
    m_pendingChanges.push_back({PendingActionType::Replace, std::move(scene)});
}

void SceneManager::clear()
{
    m_pendingChanges.push_back({PendingActionType::Clear, nullptr});
}

void SceneManager::processPendingChanges()
{
    for (auto& change : m_pendingChanges)
    {
        switch (change.type)
        {
            case PendingActionType::Push:
                applyPush(std::move(change.scene));
                break;
            case PendingActionType::Pop:
                applyPop();
                break;
            case PendingActionType::Replace:
                applyReplace(std::move(change.scene));
                break;
            case PendingActionType::Clear:
                applyClear();
                break;
        }
    }
    m_pendingChanges.clear();
}

void SceneManager::applyPush(std::unique_ptr<Scene> scene)
{
    if (scene)
    {
        m_scenes.push_back(std::move(scene));
    }
}

void SceneManager::applyPop()
{
    if (!m_scenes.empty())
    {
        m_scenes.pop_back();
    }
}

void SceneManager::applyReplace(std::unique_ptr<Scene> scene)
{
    applyPop();
    applyPush(std::move(scene));
}

void SceneManager::applyClear()
{
    m_scenes.clear();
}

Scene* SceneManager::current()
{
    return m_scenes.empty() ? nullptr : m_scenes.back().get();
}

const Scene* SceneManager::current() const
{
    return m_scenes.empty() ? nullptr : m_scenes.back().get();
}

bool SceneManager::empty() const
{
    return m_scenes.empty();
}
}
