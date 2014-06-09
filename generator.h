#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

#include "configuration.h"
#include "Restriction.h"

template<class Conf, class Restrictions, class... Mixins>
class Generator:public  Mixins...{
private:
    static const Restrictions restrictions;
public:
    Generator():Mixins()...{}
};

template<class... Mixins>
using CarGenerator = Generator<Config<Mixins...>, CarRestrictions<Config<Mixins...>>, Mixins...>;

#endif // GENERATOR_H_INCLUDED
