#pragma once

#include "data-types.hxx"

#include <random>

static std::default_random_engine generator;

I32 r32ir(const I32 l, const I32 r) {
    std::uniform_int_distribution<I32> distribution(l, r);
    return distribution(generator);
}

I64 r64ir(const I64 l, const I64 r) {
    std::uniform_int_distribution<I64> distribution(l, r);
    return distribution(generator);
}