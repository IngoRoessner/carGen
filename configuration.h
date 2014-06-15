#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

template<template<class> class... Mixins>
class Config{
public:
    template<template<class> class part>
    static constexpr bool containsPart(){
        return partTemplateBaseOf<part, Mixins...>();
    }

    template<class part>
    static constexpr bool containsPart(){
        return partClassBaseOf<part, Mixins...>();
    }
private:
    struct Dummy{};

    template<template<class> class T1>
    static constexpr bool partTemplateBaseOf(){
        return false;
    }

    template<template<class> class T1, template<class> class T2, template<class> class... Tx>
    static constexpr bool partTemplateBaseOf(){
        return is_base_of<T1<Dummy>, T2<Dummy>>::value ? true : partTemplateBaseOf<T1, Tx...>();
    }

    template<typename T1>
    static constexpr bool partClassBaseOf(){
        return false;
    }

    template<typename T1, template<class> class T2, template<class> class... Tx>
    static constexpr bool partClassBaseOf(){
        return is_base_of<T1, T2<Dummy>>::value ? true : partClassBaseOf<T1, Tx...>();
    }
};

#endif // CONFIGURATION_H_INCLUDED
