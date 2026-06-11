#pragma once

#include "BounceAdventure/Core/Scene.hpp"

#include <memory>
#include <vector>

namespace BounceAdventure
{
enum class PendingActionType
{
    Push,
    Pop,
    Replace,
    Clear
};

class SceneManager
{
public:
    void push(std::unique_ptr<Scene> scene);
    void pop();
    void replace(std::unique_ptr<Scene> scene);
    void clear();

    void processPendingChanges();

    Scene* current();
    const Scene* current() const;

    bool empty() const;

private:
    void applyPush(std::unique_ptr<Scene> scene);
    void applyPop();
    void applyReplace(std::unique_ptr<Scene> scene);
    void applyClear();

    std::vector<std::unique_ptr<Scene>> m_scenes;

    struct PendingChange
    {
        PendingActionType type;
        std::unique_ptr<Scene> scene;
    };
    std::vector<PendingChange> m_pendingChanges;
};
}
