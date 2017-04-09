#ifndef CMAKE_TUTORIAL_CMAKE_TUTORIAL_CT_HELPER_HPP
#define CMAKE_TUTORIAL_CMAKE_TUTORIAL_CT_HELPER_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include <string>


namespace ct_helper {

template <typename T>
void
announce(const std::string &func_name,
         const Args &...args);
    
} // ct_helper

#include "cmake_tutorial/ct_helper.ipp"

#endif // ifndef CMAKE_TUTORIAL_CMAKE_TUTORIAL_CT_HELPER_HPP
