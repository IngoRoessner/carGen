#ifndef DSL_H_INCLUDED
#define DSL_H_INCLUDED

#include "generator.h"
#include "parts.h"
#include <type_traits>

class EcoLine{};

struct EndElement{};

template<class DSLClass = EndElement, class... DSLClasses>
struct DSL{
    static_assert(true, "unknown DSLClass handling");
};

template<>
struct DSL<EndElement>{
    template<template<class>class... Parts>
    struct DefineParts{
        using  Result = Generator<Parts...>;
    };
};

template<class... DSLClasses>
struct DSL<EcoLine, DSLClasses...>{
    template<template<class>class... Parts>
    struct DefineParts{
        using  Result = typename DSL<DSLClasses...>::template DefineParts<Parts..., parts::ElectroEngine>::Result;
    };

    using Gen = typename DefineParts<>::Result;
};



#endif // DSL_H_INCLUDED
