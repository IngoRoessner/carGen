#ifndef DOKU_H_INCLUDED
#define DOKU_H_INCLUDED

#include <list>
#include <string>
#include <iostream>
#include <typeinfo>
#include <tuple>
#include "configuration.h"


#define CreateDocuClass(part, content...) template<>\
class DocuElement<part>{\
public:\
    static string getSegmentName(){\
        return #part;\
    }\
    static string getSegmentContent(){\
        return #content;\
    }\
};


class Dummy{};

template<template<class> class Part>
class DocuElement{
public:
    static string getSegmentName(){
        string result = "unknown part, techid = ";
        result = result+(typeid(Part<Dummy>).name());
        return result;
    }

    static string getSegmentContent(){
        return "";
    }
};

//custom DocuElements

template<>
class DocuElement<parts::ElectroEngine>{
public:
    static string getSegmentName(){
        return "ElectroEngine";
    }

    static string getSegmentContent(){
        return "a engine driven by electric.";
    }
};

CreateDocuClass(parts::AutoPilot,
                ein autopilot, der dynamisch auf transmission reagiert
                aber bla \nzeilenumbruch)

//end custom DocuElements

template<template<class> class... Parts>
class Documentation{
private:
    list<tuple<string, string>> docuElementContent;
//static constexpr DocuElementBase docuElementContent[sizeof...(Parts<Dummy>)] = {DocuElement<Parts>()...};
public:
    Documentation():docuElementContent({make_tuple(DocuElement<Parts>::getSegmentName(), DocuElement<Parts>::getSegmentContent())...}){}

    list<tuple<string, string>>& getDocuElements(){
        return docuElementContent;
    }

    string getTxtDocu(){
        string result = "";
        for(const auto & element : docuElementContent){
            result = result + "name: " + get<0>(element) + "\n";
            result = result + "content: " + get<1>(element) + "\n";
            result = result + "\n";
        }
        return result;
    }

    template<template<class> class part>
    static constexpr bool containsPart(){
        return Config<Parts...>::template containsPart<part>();
    }

    template<class part>
    static constexpr bool containsPart(){
        return Config<Parts...>::template containsPart<part>();
    }
};


#endif // DOKU_H_INCLUDED
