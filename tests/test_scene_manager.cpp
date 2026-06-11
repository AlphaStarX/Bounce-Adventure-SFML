#include "BounceAdventure/Core/Scene.hpp"
#include "BounceAdventure/Core/SceneManager.hpp"

#include "test_harness.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

using namespace BounceAdventure;

namespace
{
// A minimal scene used only to satisfy the abstract Scene interface and to
// verify scene ownership / identity in SceneManager.
class CountingScene : public Scene
{
public:
    explicit CountingScene(int tag)
        : m_tag(tag)
    {
    }

    int tag() const { return m_tag; }

    void handleEvent(const sf::Event&) override {}
    void update(float) override {}
    void render(sf::RenderWindow&) override {}

private:
    int m_tag;
};
} // namespace

TEST_CASE(SceneManager_NewInstanceIsEmpty)
{
    SceneManager mgr;
    CHECK(mgr.empty());
    CHECK(mgr.current() == nullptr);
    CHECK(mgr.current() == nullptr); // const overload too
}

TEST_CASE(SceneManager_PushMakesCurrentAfterProcess)
{
    SceneManager mgr;
    mgr.push(std::make_unique<CountingScene>(1));
    // Pending change has not been applied yet.
    CHECK(mgr.current() == nullptr);
    mgr.processPendingChanges();
    REQUIRE(mgr.current() != nullptr);
    CHECK(static_cast<CountingScene*>(mgr.current())->tag() == 1);
    CHECK(!mgr.empty());
}

TEST_CASE(SceneManager_MultiplePushesFormStack)
{
    SceneManager mgr;
    mgr.push(std::make_unique<CountingScene>(1));
    mgr.push(std::make_unique<CountingScene>(2));
    mgr.push(std::make_unique<CountingScene>(3));
    mgr.processPendingChanges();
    REQUIRE(mgr.current() != nullptr);
    CHECK(static_cast<CountingScene*>(mgr.current())->tag() == 3);
    // Pop the top, then top should be 2.
    mgr.pop();
    mgr.processPendingChanges();
    CHECK(static_cast<CountingScene*>(mgr.current())->tag() == 2);
}

TEST_CASE(SceneManager_PopOnEmptyIsSafe)
{
    SceneManager mgr;
    mgr.pop();
    mgr.processPendingChanges();
    CHECK(mgr.empty());
    CHECK(mgr.current() == nullptr);
}

TEST_CASE(SceneManager_ReplaceSwapsTopScene)
{
    SceneManager mgr;
    mgr.push(std::make_unique<CountingScene>(1));
    mgr.processPendingChanges();

    mgr.replace(std::make_unique<CountingScene>(99));
    mgr.processPendingChanges();

    REQUIRE(mgr.current() != nullptr);
    CHECK(static_cast<CountingScene*>(mgr.current())->tag() == 99);
    // Replace should not accumulate a stack; depth is still 1.
    mgr.pop();
    mgr.processPendingChanges();
    CHECK(mgr.empty());
}

TEST_CASE(SceneManager_ClearEmptiesTheStack)
{
    SceneManager mgr;
    mgr.push(std::make_unique<CountingScene>(1));
    mgr.push(std::make_unique<CountingScene>(2));
    mgr.push(std::make_unique<CountingScene>(3));
    mgr.processPendingChanges();
    REQUIRE(!mgr.empty());

    mgr.clear();
    mgr.processPendingChanges();
    CHECK(mgr.empty());
    CHECK(mgr.current() == nullptr);
}

TEST_CASE(SceneManager_DefersChangesUntilProcessPendingChanges)
{
    // This is the core safety property: a scene that mutates the stack during
    // its own update must not see the stack mutate under it. The pending
    // change should not become visible until processPendingChanges() runs.
    SceneManager mgr;
    auto first = std::make_unique<CountingScene>(1);
    CountingScene* firstPtr = first.get();
    mgr.push(std::move(first));
    mgr.processPendingChanges();
    REQUIRE(mgr.current() == firstPtr);

    // Queue a new scene. It should NOT yet be the current scene.
    mgr.push(std::make_unique<CountingScene>(2));
    CHECK(mgr.current() == firstPtr);
    CHECK(mgr.current() != nullptr);
    CHECK(static_cast<CountingScene*>(mgr.current())->tag() == 1);

    mgr.processPendingChanges();
    CHECK(static_cast<CountingScene*>(mgr.current())->tag() == 2);
}

TEST_CASE(SceneManager_QueuedActionsAreAppliedInOrder)
{
    // A sequence of pending actions should be applied in the order they were
    // queued, so a "pop then push" reads as a replace.
    SceneManager mgr;
    mgr.push(std::make_unique<CountingScene>(1));
    mgr.processPendingChanges();

    mgr.pop();
    mgr.push(std::make_unique<CountingScene>(2));
    mgr.processPendingChanges();

    REQUIRE(mgr.current() != nullptr);
    CHECK(static_cast<CountingScene*>(mgr.current())->tag() == 2);
    // Depth should be exactly 1 (one pop + one push).
    mgr.pop();
    mgr.processPendingChanges();
    CHECK(mgr.empty());
}
