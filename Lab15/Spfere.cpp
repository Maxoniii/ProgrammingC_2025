#include "Spfere.hpp"
#include <iostream>
#include <exception>

Spfere::Spfere(){
    rad_=1;
}

Spfere::Spfere(double rad){
    setRad(rad);
}



void Spfere::setRad(double rad){
    if(!IsRadValid(rad)){
        throw std::invalid_argument("Rad must be positive");
    }
    rad_=rad;
}



double Spfere::getRad()const{
    return rad_;
}

bool Spfere::IsRadValid(double rad) const{
    return rad>0;
}

double Spfere::poverh()const{
    return 4.0f * 3.14*rad_*rad_;
}

double Spfere::v()const{
    return (4.0f/3.0f) * 3.14 * rad_*rad_*rad_;

}