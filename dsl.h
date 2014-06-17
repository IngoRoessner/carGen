#ifndef DSL_H_INCLUDED
#define DSL_H_INCLUDED

#include "generator.h"
#include "parts.h"
#include <type_traits>
#include "dsl_partreduce.h"

#define CreateDSLClass(dslClass, additionalParts...) class dslClass{};\
template<class... DSLClasses>\
struct DSL<dslClass, DSLClasses...>{\
    template<template<template<class>class...>class PartsFor = Generator,template<class>class... Parts>\
    using Gen = typename DSL<DSLClasses...>::template Gen<PartsFor, Parts..., additionalParts>; \
};

struct DSLEndElement{};

template<class DSLClass = DSLEndElement, class... DSLClasses>
struct DSL{
    //should be false every time, but only evaluated if the this Template is instantiated
    static_assert(is_same<DSLClass, bool>::value, "Unknown DSLClass handling. The is no DSL specialization for given class");
};

template<>
struct DSL<DSLEndElement>{
    template<template<template<class>class...>class PartsFor = Generator, template<class>class... Parts>
    using Gen = typename Reduce<PartsFor, Parts...>::Gen;
};


class EcoLine{};
template<class... DSLClasses>
struct DSL<EcoLine, DSLClasses...>{
    template<template<template<class>class...>class PartsFor = Generator,template<class>class... Parts>
    using Gen = typename DSL<DSLClasses...>::template Gen<PartsFor, Parts..., parts::ElectroEngine>;
};


class StrictEcoLine{};
template<class... DSLClasses>
struct DSL<StrictEcoLine, DSLClasses...>{
    template<template<template<class>class...>class PartsFor = Generator,template<class>class... Parts>
    struct DefParts{
        using Gen2 = typename DSL<DSLClasses...>::template Gen<PartsFor, Parts..., parts::ElectroEngine>;
        static_assert(!(Gen2::template containsPart<parts::GasEngine>()), "Gas is not Eco");
    };

    template<template<template<class>class...>class PartsFor = Generator,template<class>class... Parts>
    using Gen = typename DefParts<PartsFor, Parts...>::Gen2;
};

CreateDSLClass(WoodenLine, parts::GasEngine, parts::ManuelTransmission)

CreateDSLClass(GoogleCar, parts::AutoPilot, parts::ElectroEngine, parts::AutomaticTransmission)

#endif // DSL_H_INCLUDED
