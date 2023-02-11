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
        filename = "data.txt";
    }
    else    
        filename = argv[1]; 
    

    
    std::vector<double> dynamics;

    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "can\'t open file" <<std::endl;
        return 0;
    }
    double tmp;
    while(file >> tmp){
        dynamics.push_back(tmp);  
    }


    double mean =0;
    double sigma = 0;
    for(const auto &v: dynamics){
        mean += v;
        sigma += v*v;
    }
    mean /= dynamics.size();
    sigma /= dynamics.size();
    sigma = sqrt(sigma-mean*mean+1e-6);

    std::cout << "mean is " << mean << std::endl;
    std::cout << "sigma is " << sigma << std::endl;
    double del = 1;
    if(argc > 2 and argv[2] == "norm")
        std::swap(sigma,del);
    for(auto &v: dynamics){
        v = (v-mean)/del;
    }

    bool fac2 = (argc > 3 and argv[3] == "/N");


    std::ofstream result("result.txt");
    result << "t\tautocorrelator\tstd"<<std::endl;
    for(size_t i=0;i<std::min((size_t)dynamics.size()/2,(size_t)20);++i){
        double fac = fac2 ? 1.0/(dynamics.size()-i) : 1;
        result  << i << "\t" << correlator(dynamics,i)*fac<< "\t" << sqrt(dynamics.size()-i) *fac*sigma*sigma<<std::endl;
    }

    return 0;
}