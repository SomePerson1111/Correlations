#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <chrono>
#include <fstream>

template <typename value_type = double>
class m_gen{
    mutable std::mt19937 gen;
    mutable std::discrete_distribution<> d;
    std::vector<value_type> values;
    value_type mean_,std_;
public:
    m_gen(std::vector<double> probs,std::vector<value_type> values):
    gen(std::chrono::system_clock::now().time_since_epoch().count()),
    d(probs.begin(),probs.end()),values(std::move(values)),mean_(0),std_(0){
        if(this->values.size() != probs.size()){
            std::cout  << "warning, sizes are incompatible" <<std::endl;
        }
        double Pfull  = 0;
        for(size_t i=0;i<probs.size();++i){
            Pfull += probs[i];
            mean_ += probs[i]*this->values[i];
            std_ += probs[i]*this->values[i]*this->values[i];
        }
        mean_ /= Pfull;
        std_ /= Pfull;
        std_ -= mean_*mean_;
        std_ = sqrt(std_);
    }
    auto operator ()() const{
        return values[d(gen)];
    }
    auto operator ()(size_t n) const{
        value_type sum =0;
        for(size_t i=0;i<n;++i){
            sum += this->operator()();
        }
        return sum/n;
    }

    auto mean() const{return mean_;}
    auto sigma() const{return std_;}
};

template <typename Gen>
void print_session(Gen && G,size_t iter_num,size_t epoch_num){
    for(size_t ep =0;ep<epoch_num;++ep){
        std::cout << "raund " << std::setfill('0') << std::setw(3) << ep + 1 << ":\t" << G(iter_num) <<std::endl;
    }
}

int main(int argc,char**argv)
{
    size_t iter_num = 20;
    size_t epoch_num = 1;
    if(argc > 1){
        iter_num = std::stoi(argv[1]);
    }
    if(argc > 2){
        epoch_num = std::stoi(argv[2]);
    }

    std::vector<double> probs;
    std::vector<double> values;
    std::string gen_filename = (argc > 3 ? argv[3] : "gen.txt");
    std::ifstream ifs(gen_filename);
    if(!ifs.is_open()){
        std::cout << "can\'t open file " << gen_filename <<std::endl;
        probs = {1,4,6,8,10,8,6,4,1};
        values = {0,1000,2000,3000,4000,5000,6000,7000,8000};
    }else{
        double pr,val;
        while(ifs>>pr>>val){
            probs.push_back(pr);
            values.push_back(val);
        }
    }

    m_gen<double> G(probs,values);
    std::cout << "mean = " << G.mean() << ", std = " << G.sigma() << std::endl;

    print_session(G,iter_num,epoch_num);
}