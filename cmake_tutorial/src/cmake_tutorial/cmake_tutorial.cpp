#include "cmake_tutorial/cmake_tutorial.hpp"
#include "cmake_tutorial/cmake_tutorial_config.hpp"
#include <string>
#include <typeinfo>
#include <iostream>


template <typename T>
const std::string CmakeTutorial<T>::type_name(typeid(T).name());
template <>
const std::string CmakeTutorial<int>::author(CMAKE_TUTORIAL_AUTHOR);
template <>
const std::string CmakeTutorial<int>::version(CMAKE_TUTORIAL_VERSION);


inline void
announce()
{
    cout << "CMAKE_TUTORIAL_VERSION_MAJOR: " << CMAKE_TUTORIAL_VERSION_MAJOR << endl;
    cout << "CMAKE_TUTORIAL_VERSION_MINOR: " << CMAKE_TUTORIAL_VERSION_MINOR << endl;
}

int
main()
{
    announce();

    C

    return 0;
}

