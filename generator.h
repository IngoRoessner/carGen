#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

#include "configuration.h"

template<template<class> class... Mixins>
class Generator:public Mixins<Generator<Mixins...>>...{
public:
    Generator():Mixins<Generator<Mixins...>>(*this)...{}

    template<template<class> class part>
    static constexpr bool containsPart(){
        return Config<Mixins...>::template containsPart<part>();
    }

    template<class part>
    static constexpr bool containsPart(){
        return Config<Mixins...>::template containsPart<part>();
    }
};

#endif // GENERATOR_H_INCLUDED
