#pragma once
#ifndef UTILS_VECTOR_HPP
#define UTILS_VECTOR_HPP

template<typename TData>
struct Vector {
    UInt64 space;
    UInt64 size;
    TData *data;
};

#endif  // UTILS_VECTOR_HPP
