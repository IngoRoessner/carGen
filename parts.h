#ifndef PARTS_H_INCLUDED
#define PARTS_H_INCLUDED

namespace parts{
    class Body{

    };

    class GasEngine{

    };

    class ElectroEngine{

    };

    class Transmission{
    public:
        static constexpr int maxGears = 0;
    };

    class AutomaticTransmissionBase: Transmission{
    };

    template<int gearCount>
    class AutomaticTransmission: AutomaticTransmissionBase{
        static constexpr int maxGears = gearCount;
    };

    class ManualTransmissionBase: Transmission{
    };

    template<int gearCount>
    class ManualTransmission: ManualTransmissionBase{
        static constexpr int maxGears = gearCount;
    };
}


#endif // PARTS_H_INCLUDED
