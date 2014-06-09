#ifndef RESTRICTION_H
#define RESTRICTION_H

#include <type_traits>

template<class Config>
class EmptyRestrictions
{

};

template<class Config>
class CarRestrictions
{
    static_assert(Config::containsDerivedPart<Transmission>(), "have to contains a transmission");
};

#endif // RESTRICTION_H
