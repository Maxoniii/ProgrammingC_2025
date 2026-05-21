#include <iostream>
#include "Spfere.hpp"
int main() {
    try{
        /*
        std::cout<<"Example 1:"<<std::endl;
        Spfere spfere(5.0f);
        std::cout<<"Spfere radius: "<<spfere.getRad()<<std::endl;
        std::cout<<"Spfere poverh area: "<< spfere.poverh()<<std::endl;
        std::cout<<"Spfere volume: "<< spfere.v()<<std::endl;*/


        std::cout<<"Example 2:"<<std::endl;
        Spfere spfere2;
        spfere2.setRad(5.0);
        std::cout<<"Spfere radius: "<<spfere2.getRad()<<std::endl;
        std::cout<<"Spfere poverh area: "<< spfere2.poverh()<<std::endl;
        std::cout<<"Spfere volume: "<< spfere2.v()<<std::endl;

        // std::cout<<"Example 3:"<<std::endl;
        // spfere.setRad(7.5f);
        // std::cout<<"Spfere radius"<<spfere.getRad()<<std::endl;
        // std::cout<<"Spfere poverh area"<< spfere.poverh()<<std::endl;
        // std::cout<<"Spfere volume"<< spfere.v()<<std::endl;


        // std::cout<<"Example 4:"<<std::endl;
        // std::cout<<"Spfere radius"<<spfere.getRad()<<std::endl;
        // std::cout<<"Spfere poverh area"<< spfere.poverh()<<std::endl;
        // std::cout<<"Spfere volume"<< spfere.v()<<std::endl;

    }
    catch(const std::invalid_argument& ex){
        std::cerr << ex.what()<<std::endl;
    }
    return 0;
}