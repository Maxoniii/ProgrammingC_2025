#pragma once 



class Spfere{
public:
    Spfere();
    Spfere(double rad);
            
    double poverh() const;
    double v() const;

    void setRad(double rad);
    double getRad()const;

private:
    bool IsRadValid(double rad) const;
    double rad_; 
};