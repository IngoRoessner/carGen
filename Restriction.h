#ifndef RESTRICTION_H
#define RESTRICTION_H

#include <type_traits>
#include "parts.h"
#include "configuration.h"

constexpr bool isEven(int number){ return number%2 == 0;}

template<class Config>
class EmptyRestrictions
{

};

template<class Conf>
class CarRestrictions
{
public:
    static constexpr bool body = Conf::template containsDerivedPart<parts::Body>();
    static_assert(Conf::template containsDerivedPart<parts::Transmission>(), "must contains a transmission");
    static_assert(Conf::template containsDerivedPart<parts::Engine>(), "must contains a Engine");
    static_assert(Conf::template containsDerivedPart<parts::Body>(), "must contains a Body");
    static_assert(!(Conf::template containsDerivedPart<parts::ElectroEngine>()) || isEven(Conf::PreGenCar::gears), "only even gear count for ElectoEngines");
};

#endif // RESTRICTION_H
