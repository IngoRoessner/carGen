#ifndef DOKU_H_INCLUDED
#define DOKU_H_INCLUDED

#include <list>
#include <string>
#include <iostream>
#include <typeinfo>
#include <tuple>

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
};


#endif // DOKU_H_INCLUDED
