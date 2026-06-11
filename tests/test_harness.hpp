// Bounce Adventure — minimal header-only test harness.
//
// Provides:
//   TEST_CASE(name)        — define a test. Auto-registered at static init.
//   CHECK(cond)            — non-fatal assertion; failure is reported and counted.
//   REQUIRE(cond)          — fatal assertion; failure short-circuits the test.
//
// Designed as a deliberate alternative to pulling in doctest/Catch2/etc. as
// third-party dependencies for a learning project. Roughly 70 lines of code.

#pragma once

#include <cstdio>
#include <exception>
#include <string>
#include <vector>

namespace test_harness
{
struct TestCase
{
    const char* name;
    void (*fn)();
};

inline std::vector<TestCase>& registry()
{
    static std::vector<TestCase> r;
    return r;
}

struct TestRegistrar
{
    TestRegistrar(const char* name, void (*fn)())
    {
        registry().push_back({name, fn});
    }
};

struct FailureCounter
{
    int count = 0;
};

// Thread-local so nested TEST_CASEs (if ever added) don't collide.
inline FailureCounter& current()
{
    static thread_local FailureCounter fc;
    return fc;
}

inline int runAll()
{
    int passed = 0;
    int failed = 0;
    for (const auto& tc : registry())
    {
        current().count = 0;
        std::printf("[ RUN      ] %s\n", tc.name);
        try
        {
            tc.fn();
        }
        catch (const std::exception& e)
        {
            std::fprintf(stderr, "    THREW std::exception: %s\n", e.what());
            ++current().count;
        }
        catch (...)
        {
            std::fprintf(stderr, "    THREW unknown exception\n");
            ++current().count;
        }

        if (current().count == 0)
        {
            std::printf("[       OK ] %s\n", tc.name);
            ++passed;
        }
        else
        {
            std::printf("[  FAILED  ] %s (%d failure(s))\n", tc.name, current().count);
            ++failed;
        }
    }
    std::printf("\n=== %d passed, %d failed, %d total ===\n",
                passed, failed, passed + failed);
    return failed;
}
} // namespace test_harness

#define TEST_CASE(name)                                                              \
    static void test_func_##name();                                                  \
    static ::test_harness::TestRegistrar test_reg_##name{#name, &test_func_##name};  \
    static void test_func_##name()

#define CHECK(cond)                                                                  \
    do                                                                               \
    {                                                                                \
        if (!(cond))                                                                 \
        {                                                                            \
            std::fprintf(stderr, "    CHECK failed: %s  (at %s:%d)\n",                \
                         #cond, __FILE__, __LINE__);                                 \
            ++::test_harness::current().count;                                       \
        }                                                                            \
    }                                                                                \
    while (false)

#define REQUIRE(cond)                                                                \
    do                                                                               \
    {                                                                                \
        if (!(cond))                                                                 \
        {                                                                            \
            std::fprintf(stderr, "    REQUIRE failed: %s  (at %s:%d)\n",              \
                         #cond, __FILE__, __LINE__);                                 \
            ++::test_harness::current().count;                                       \
            return;                                                                  \
        }                                                                            \
    }                                                                                \
    while (false)
