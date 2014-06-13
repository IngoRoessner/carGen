#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

template<template<class> class... Mixins>
class Generator:public Mixins<Generator<Mixins...>>...{
public:
    Generator():Mixins<Generator<Mixins...>>(*this)...{}

    template<template<class> class part>
    static constexpr bool containsPart(){
        return partTemplateBaseOf<part, Mixins...>();
    }

    template<class part>
    static constexpr bool containsPart(){
        return partClassBaseOf<part, Mixins...>();
    }

private:

    template<template<class> class T1>
    static constexpr bool partTemplateBaseOf(){
        return false;
    }

    template<template<class> class T1, template<class> class T2, template<class> class... Tx>
    static constexpr bool partTemplateBaseOf(){
        return is_base_of<T1<Generator<Mixins...>>, T2<Generator<Mixins...>>>::value ? true : partTemplateBaseOf<T1, Tx...>();
    }

    template<typename T1>
    static constexpr bool partClassBaseOf(){
        return false;
    }

    template<typename T1, template<class> class T2, template<class> class... Tx>
    static constexpr bool partClassBaseOf(){
        return is_base_of<T1, T2<Generator<Mixins...>>>::value ? true : partClassBaseOf<T1, Tx...>();
    }
};

#endif // GENERATOR_H_INCLUDED
