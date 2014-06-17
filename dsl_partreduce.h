#ifndef DSL_PARTREDUCE_H_INCLUDED
#define DSL_PARTREDUCE_H_INCLUDED

#include "configuration.h"
#include "generator.h"
#include <type_traits>

template<class T>
struct ReducerEndElement{};

template<template<template<class>class...>class PartsFor, template<class>class In = ReducerEndElement, template<class>class... InParts>
struct Reduce{
    template<template<class>class... OutParts>
    using Result = typename conditional<Config<OutParts...>::template containsPart<In>(),
                        typename Reduce<PartsFor,InParts...>::template Result<OutParts...>,
                        typename Reduce<PartsFor,InParts...>::template Result<OutParts..., In>>
                        ::type;

    using Gen = Result<>;
};

template<template<template<class>class...>class PartsFor>
struct Reduce<PartsFor, ReducerEndElement>{
    template<template<class>class... OutParts>
    using Result = PartsFor<OutParts...>;
};



#endif // DSL_PARTREDUCE_H_INCLUDED
