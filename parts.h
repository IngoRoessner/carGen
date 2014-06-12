#ifndef PARTS_H_INCLUDED
#define PARTS_H_INCLUDED

namespace parts{
    template<class Generator>
    class Body{
    private:
        Generator& generator;
    public:
        Body(Generator& gen): generator(gen){}
    };

    class Engine{

    };

    template<class Generator>
    class GasEngine:Engine{
    private:
        Generator& generator;
    public:
        GasEngine(Generator& gen): generator(gen){}
    };


    template<class Generator>
    class ElectroEngine:Engine{
    private:
        Generator& generator;
    public:
        ElectroEngine(Generator& gen): generator(gen){}
    };


    class Transmission{

    };


    template<class Generator>
    class AutomaticTransmission: public Transmission{
    private:
        Generator& generator;
    public:
        AutomaticTransmission(Generator& gen): generator(gen){}
    };


    template<class Generator>
    class ManuelTransmission: Transmission{
    private:
        Generator& generator;
    public:
        ManuelTransmission(Generator& gen): generator(gen){}
    };


    template<class Generator>
    class CarClassification{
    private:
        Generator& generator;
    public:
        CarClassification(Generator& gen): generator(gen){
            static_assert(Generator::template containsPart<parts::Body>(), "a car neads a Body");
            static_assert(Generator::template containsDerivedPart<parts::Engine>(), "a car neads a Engine");
            static_assert(Generator::template containsDerivedPart<parts::Transmission>(), "a car neads a Transmission");
        };
    };
}


#endif // PARTS_H_INCLUDED
