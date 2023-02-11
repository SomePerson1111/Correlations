#include <iostream>
#include <vector>
#include <fstream>
#include "extract.hpp"

template <typename ArrayType>
double correlator(const ArrayType & arr,size_t t){
    double sum = 0;
    for(size_t i=0;i<arr.size()-t;++i){
        sum += arr[i]*arr[i+t];
    }
    return sum;
}

int main(int argc,char **argv){
    std::string filename;
    if(argc < 2){
        std::cout << "set default filename" <<std::endl;
        filename = "replayinfo.txt";
    }
    else    
        filename = argv[1]; 
    

    std::string vehicle = "";
    std::string param = "dmg";
    if(argc > 2)
        param = argv[2];
    if(argc > 3)
        vehicle = argv[3];
    std::vector<double> dynamics;

    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "can\'t open file" <<std::endl;
        return 0;
    }
    BattleData tmp;

    std::string s;
    std::getline(file,s);
    while(file >> tmp){
        if(vehicle.empty() || tmp.vehicle == vehicle)
            dynamics.push_back(tmp.get<double>(param));   
    }

    std::ofstream result("data.txt");
    for(size_t i=0;i<dynamics.size();++i){
        result  << dynamics[i] <<std::endl;
    }

    return 0;
}