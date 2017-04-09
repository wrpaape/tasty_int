#ifndef CMAKE_TUTORIAL_CMAKE_TUTORIAL_CMAKE_TUTORIAL_HPP
#define CMAKE_TUTORIAL_CMAKE_TUTORIAL_CMAKE_TUTORIAL_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "cmake_tutorial/cmake_tutorial_base.hpp"
#include "cmake_tutorial/ct_helper.hpp"
#include <string>


template <typename T>
class CmakeTutorial : public CmakeTutorialBase
{
    template <typename T, typename ...Args>
    friend void ct_helper::announce(const std::string &func_name,
                                    const Args &...args);

public:
    CmakeTutorial();
    CmakeTutorial(const T &init);
    ~CmakeTutorial();
    T get();
    void set(const T &input);
    T sum(const T &...args);

private:
    static const std::string type_name;
    static const std::string author;
    static const double version;
    T value;
    T do_sum();
    T do_sum(const T &next,
             const T &...rem_args);
}

#include "cmake_tutorial/cmake_tutorial.ipp"

#endif // ifndef CMAKE_TUTORIAL_CMAKE_TUTORIAL_CMAKE_TUTORIAL_HPP
