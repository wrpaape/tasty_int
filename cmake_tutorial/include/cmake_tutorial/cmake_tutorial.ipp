// -*- C++ -*-

// EXTERNAL DEPENDENCIES
// =============================================================================
#include "cmake_tutorial/cmake_tutorial.hpp"



// PUBLIC
// =============================================================================
template <typename T>
inline
CmakeTutorial<T>::CmakeTutorial()
{
    announce(__func__);
}

template <typename T>
inline
CmakeTutorial<T>::CmakeTutorial(const T &init)
    : value(init)
{
    announce(__func__, init);
}


template <typename T>
inline
CmakeTutorial<T>::~CmakeTutorial()
{
    announce(__func__);
}


template <typename T>
inline T
CmakeTutorial<T>::get()
{
    announce(__func__);
    return value;
}


template <typename T>
inline void
CmakeTutorial<T>::set(const T &input)
{
    announce(__func__, input);
    value = input;
}


template <typename T>
inline T
CmakeTutorial<T>::sum(const T &...args)
{
    announce(__func__, args...);
    return do_sum(args...);
}



// PRIVATE
// =============================================================================
template <typename T>
inline T
CmakeTutorial<T>::do_sum()
{
    return ::get();
}

template <typename T>
inline T
CmakeTutorial<T>::do_sum(const T &next,
                         const T &...rem_args)
{
    return next + do_sum(rem_args...);
}
