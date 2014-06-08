#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

#include <type_traits>

template<class... parts>
class Config{
public:
    template<class part>
    constexpr bool containsPart(){
        return partEquals<part, parts...>();
    }

private:
    template<typename T1>
    constexpr bool partEquals(){
        return false;
    }

    template<typename T1, typename T2, typename... Tx>
    constexpr bool partEquals(){
        return is_same<T1, T2>::value ? true : partEquals<T1, Tx...>();
    }
};

#endif // CONFIGURATION_H_INCLUDED
