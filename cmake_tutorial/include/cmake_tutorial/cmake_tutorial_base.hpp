#ifndef CMAKE_TUTORIAL_CMAKE_TUTORIAL_CMAKE_TUTORIAL_BASE_HPP
#define CMAKE_TUTORIAL_CMAKE_TUTORIAL_CMAKE_TUTORIAL_BASE_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include <string>


class CmakeTutorialBase
{
    template <typename T>
    friend void cmake_tutorial_test<T>();
}


#endif // ifndef CMAKE_TUTORIAL_CMAKE_TUTORIAL_CMAKE_TUTORIAL_BASE_HPP

