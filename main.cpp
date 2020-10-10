#include <iostream>
#include <stdio.h>
#include "Position.cpp"
using namespace std;

long operator"" _degr(unsigned long long val)
{
    return long(val);
}

int check_input_latitude(int input){
    while (input>90 || input<-90){
    std::cout << "invalid latitude. Please enter number from -90 to 90" << std::endl;
    std::cin >> input;
    };
    return input;
};

int check_input_longitude(int input){
    while (input>180 || input<-180){
    std::cout << "invalid longitude. Please enter number from -180 to 180" << std::endl;
    std::cin >> input;
    };
    return input;
};

int check_input_latitude_auto(int input){
    while (input>90 || input<-90){
    std::cout << "invalid latitude. Latitude set to 90" << std::endl;
    input = 90;
    };
    return input;
};

int check_input_longitude_auto(int input){
    while (input>180 || input<-180){
    std::cout << "invalid longitude. Longitude was set to 180" << std::endl;
    input = 180;
    };
    return input;
};

int filetest(){
    class Position pos1; //создание объектов
    class Position pos2;
    float inc_lat,inc_long; 
    float mult;
        
    std::cin >> inc_lat;
    check_input_latitude_auto(inc_lat);
    std::cin >> inc_long;
    check_input_longitude_auto(inc_long);
    pos1.setPosit(inc_lat, inc_long);
         
    std::cin >> inc_lat;
    check_input_latitude_auto(inc_lat);
    std::cin >> inc_long;
    check_input_longitude_auto(inc_long);
    pos2.setPosit (inc_lat, inc_long);
    
    std::cin >> mult;
         
         std::cout << "1st pos" << std::endl;
         pos1.formPos();
         pos1.printPos();
         std::cout << "2nd pos" << std::endl;
         pos2.formPos();
         pos2.printPos();
         
         std::cout << "p1+p2" << std::endl;
         pos1+pos2;
         
         
         std::cout << "p1-p2" << std::endl;
         pos1-pos2;
         
         std::cout << "b1*n" << std::endl;
         pos1*mult;
         
         std::cout << "b1/n" << std::endl;
         pos1/mult;
         
         std::cout << "p1=p2" << std::endl;
         pos1=pos2;
         
         std::cout << "End of file auto test. Good bye!" << std::endl;
         return 0;
    };

int printmenu(){
    std::cout << "What shall we do? 1 - 7" << std::endl;
    std::cout << "1 - show current position" << std::endl;
    std::cout << "2 - sum positions (+)" << std::endl;
    std::cout << "3 - minus positions (-)" << std::endl;
    std::cout << "4 - mult positions (*)" << std::endl;
    std::cout << "5 - div positions" << std::endl;
    std::cout << "6 - compare positions" << std::endl;
    std::cout << "7 -  change coordinates" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "8 - exit" << std::endl;
    std::cout << "9 - print help" << std::endl;
    };

main(){
    class Position pos1;
    class Position pos2;
    int inc_lat;
    int inc_long;
    int a = -1; //переменная для switch
    float mult;
    
    std::cout << "OOP lab #2. Author: Velesov Daniil M8O - 208B - 19." << std::endl;
    std::cout << "select work mode:" << std::endl;
      std::cout << "1 - auto test" << std::endl;
      std::cout << "2 - manual work mode" << std::endl;
      std::cout << "3 - exit" << std::endl;
      while (a != 3){
    std::cin >> a;
            if(a == 1){
                filetest();
                return 0;
                };
            if(a == 2){
    std::cout << "Hello there. It is a Position calculator.\nCan you please enter your 1st coordinates?" << std::endl;
    std::cout << "Enter latitude(int):" << std::endl;
    std::cin >> inc_lat;
    inc_lat = check_input_latitude(inc_lat);
    std::cout << "Enter longitude(int):" << std::endl;
    std::cin >> inc_long;
    inc_long = check_input_longitude(inc_long);
    pos1.setPosit(inc_lat * 1_degr,inc_long * 1_degr);
    pos1.formPos();
    
    std::cout << "Enter 2nd latitude(int):" << std::endl;
    std::cin >> inc_lat;
    inc_lat = check_input_latitude(inc_lat);
    std::cout << "Enter 2nd longitude(int):" << std::endl;
    std::cin >> inc_long;
    inc_long = check_input_longitude(inc_long);
    pos2.setPosit(inc_lat * 1_degr,inc_long * 1_degr);
    pos2.formPos();
    
    pos1.printPos();
    pos2.printPos();
    printmenu();
    while (a != 8){
    std::cin >> a;
        if(a==1){
           pos1.printPos();
           pos2.printPos();
        };
        if(a==2){
            pos1+pos2;
            std::cout << "DONE!" << std::endl;
        };
        
        if(a==3){
            pos1-pos2;
            std::cout << "DONE!" << std::endl;
        };
        
        if(a==4){
            std::cout << "Enter multiplier:" << std::endl;
            std::cin >> mult;
            pos1*mult;
            std::cout << "DONE!" << std::endl;
        };
        
        if(a==5){
            std::cout << "Enter divider:" << std::endl;
            std::cin >> mult;
            pos1/mult;
            std::cout << "DONE!" << std::endl;
        };
        
        if(a==6){
            pos1=pos2;
        };
        
        
        if(a==8){ //exit
            return 0;
        }
        if(a==9){
            printmenu();
        };
        if(a==7){
            std::cout << "Choose coordinates you want to change?" << std::endl;
            std::cout << "1 - 1st" << std::endl;
            std::cout << "2 - 2nd" << std::endl;
            std::cin >> a;
            std::cout << "Enter latitude(int):" << std::endl;
            std::cin >> inc_lat;
            inc_lat = check_input_latitude(inc_lat);
            std::cout << "Enter longitude(int):" << std::endl;
            std::cin >> inc_long;
            inc_long = check_input_longitude(inc_long);
            if (a == 1){
            pos1.setPosit(inc_lat * 1_degr,inc_long * 1_degr);
            pos1.formPos();
            };
            if (a == 2){
            pos2.setPosit(inc_lat * 1_degr,inc_long * 1_degr);
            pos2.formPos();
            };
        };
    };
    return 0;
};
};
};