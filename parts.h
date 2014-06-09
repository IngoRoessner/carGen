#ifndef PARTS_H_INCLUDED
#define PARTS_H_INCLUDED

namespace parts{
    class Body{

    };

    class Engine{

    };

    class GasEngine:Engine{

    };

    class ElectroEngine:Engine{

    };

    class Transmission{
    public:
        static constexpr int gears = 0;
    };

    class AutomaticTransmissionBase: public Transmission{
    };

    template<int gearCount>
    class AutomaticTransmission: public AutomaticTransmissionBase{
    public:
        static constexpr int gears = gearCount;
    };

    class ManuelTransmissionBase: Transmission{
    };

    template<int gearCount>
    class ManuelTransmission: ManuelTransmissionBase{
    public:
        static constexpr int gears = gearCount;
    };
}


#endif // PARTS_H_INCLUDED
