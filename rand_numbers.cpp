#include <iostream>
#include <string>
#include <cmath>
#include <time.h>
double rnd(){
    return rand()/(RAND_MAX+0.0);
}

int main(int argc, char const *argv[])
{
    size_t it = (argc > 1 ? std::stoi(argv[1]) : 10);
    double A1 = (argc > 2 ? std::stoi(argv[2]) : 1000);
    double A2 = (argc > 3 ? std::stoi(argv[3]) : 1000);
    srand(time(0));
    for(size_t i=0;i<it;++i){
        std::cout << 4000 + A1*sin(0.1*i)+A2*(2*rnd()-1) <<std::endl;
    }

    return 0;
}
