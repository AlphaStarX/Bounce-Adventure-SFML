#include "test_harness.hpp"

int main()
{
    return ::test_harness::runAll() == 0 ? 0 : 1;
}
