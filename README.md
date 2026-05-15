This file can be used by .c or .cpp project for to know CPU, RAM ,DISK and POWER usage. 
how you can use it simply ->
1. creat folder
2. past this file named -> SystemManager.h
3. creat Main.cpp file in the same folder
4. past this code there and run it
#include <iostream>
#include "SystemManager.h"

int main(){
    SystemInfo <float> sys;
    while(true){
       std::cout << sys.CPU()  << std::endl;
       std::cout << sys.RAM()  << std::endl;
       std::cout << sys.DISK("D:\\" ,"C:\\" ,"E:\\") <<"%"<< std::endl;
       std::cout << sys.POWER()<< std::endl;
    }
}


