// -*- C++ -*-

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "cmake_tutorial/cmake_tutorial.hpp"
#include <string>
#include <iostream>



namespace ct_helper {

inline void
do_announce(const std::string &prefix)
{
    std::cout << ")" << std::endl;
}

template <typename Arg, typename ...Args>
inline void
do_announce(const std::string &prefix,
            const Arg &next,
            const Args &...rem_args)
{
    std::cout << prefix << next;
    do_announce(", ", rem_args...);
}


template <typename T>
inline void
announce(const std::string &func_name,
         const Args &...args)
{
    std::cout << "CmakeTutorial<"
              << CmakeTutorial<T>::type_name
              << ">::" << func_name << "(";

    do_announce("", args...);
}

} // ct_helper
