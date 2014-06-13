#ifndef PARTS_H_INCLUDED
#define PARTS_H_INCLUDED

#include <iostream>
#include <type_traits>

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

        void clutch(){
            cout<<"use clutch"<<endl;
        }

        void switchGear(){
            cout<<"use clutch"<<endl;
        }
    };


    template<class Generator>
    class CarClassification{
    private:
        Generator& generator;
    public:
        CarClassification(Generator& gen): generator(gen){
            static_assert(Generator::template containsPart<parts::Body>(), "a car neads a Body");
            static_assert(Generator::template containsPart<parts::Engine>(), "a car neads a Engine");
            static_assert(Generator::template containsPart<parts::Transmission>(), "a car neads a Transmission");
        };
    };


    template<class Generator>
    class AutoPilot{
    private:
        Generator& generator;

        template<class Gen>
        struct AutomaticClutch{
            static void run(Gen& generator){cout<<"no nead to use a clutch"<<endl;}
        };

        template<class Gen>
        struct ManuelClutch{
            static void run(Gen& generator){generator.clutch();}
        };

        template<class Gen>
        using UseClutch = typename conditional<Gen::template containsPart<parts::AutomaticTransmission>(),
                                        AutomaticClutch<Gen>,
                                        ManuelClutch<Gen>>
                                        ::type;

        void useClutch(){
            UseClutch<Generator>::run(generator);
        }

    public:
        AutoPilot(Generator& gen): generator(gen){
            static_assert(Generator::template containsPart<parts::Body>(), "a car neads a Body");
            static_assert(Generator::template containsPart<parts::Engine>(), "a car neads a Engine");
            static_assert(Generator::template containsPart<parts::Transmission>(), "a car neads a Transmission");

            useClutch();
        };
    };
}


#endif // PARTS_H_INCLUDED
