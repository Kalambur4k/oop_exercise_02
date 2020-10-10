#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

class Position{
    private:
    int latitude; //широта
    int longitude; //долгота
    public:
    
    int setPosit(int inc_lat, int inc_long){
        latitude = inc_lat;
        longitude = inc_long;
    };
    
    int getPosLatit(){
        return latitude;
    };
    
    int getPosLongit(){
        return longitude;
    };
    
    int printPos(){
        std::cout << "Your current position is (" << getPosLatit() << "," << getPosLongit() << ")" << std::endl;
    };
    
    int formPos(){
        while (latitude > 90 || latitude < -90 || longitude > 180 || longitude < -180){
        if (latitude > 90){
            latitude = -90 + (latitude-180);
        };
        if (latitude < -90){
            latitude = 90 - abs(latitude+180);
        };
        if (longitude > 180){
            longitude = -180 + longitude-360;
        };
        if (longitude < -180){
            longitude = 180 - abs(longitude+360);
        };
        };
    };
    
    //сложение
    Position operator+(Position& p2){
        Position sum;
        sum.latitude = latitude + p2.latitude;
        sum.longitude = longitude + p2.longitude;
        sum.formPos();
        sum.printPos();
    };
    
    //вычитание
    Position operator-(Position& p2){
        Position min;
        min.latitude = latitude - p2.latitude;
        min.longitude = longitude - p2.longitude;
        min.formPos();
        min.printPos();
    };
    
    //Сравнение
    Position operator=(Position& p2){
        if (latitude < p2.latitude){
        std::cout << "1st coordinates is closer to the north than the 2nd." << std::endl;
        };
        if (latitude > p2.latitude){
        std::cout << "1st coordinates is closer to the south than the 2nd." << std::endl;    
        };
        if (latitude == p2.latitude){
        std::cout << "Coordinates have same latitude. " << std::endl;    
        };
        if (longitude < p2.longitude){
        std::cout << "1st coordinates is closer to the west than the 2nd." << std::endl;    
        };
        if (longitude > p2.longitude){
        std::cout << "1st coordinates is closer to the east than the 2nd." << std::endl;    
        };
        if (longitude == p2.longitude){
        std::cout << "Coordinates have same longitude. " << std::endl;    
        };
    };

    //умножение
    Position operator*(float n){
        Position mult;
        mult.latitude = latitude*n;
        mult.longitude = longitude*n;
        mult.formPos();
        mult.printPos();
    };
    
    //деление
    Position operator/(float n){
        Position mult;
        mult.latitude = latitude/n;
        mult.longitude = longitude/n;
        mult.formPos();
        mult.printPos();
    };
    
};
