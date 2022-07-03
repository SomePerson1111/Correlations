#include <fstream>
#include <iostream>
#include <string>
#include "D:\\soft\\libs\\json\\single_include\\nlohmann\\json.hpp"
#include "extract.hpp"

#include <list>
#include <filesystem>
#include <sstream>
#include <algorithm>

#ifdef TEST_ALL
int main()
{
    std::fstream F("D:/Download/16562466293325_ussr_R159_SU_130PM_sweden.wotreplay");
    if(!F.is_open()){
        std::cout << "couldnt open file" <<std::endl;
        return -1;
    }
    auto S1 = extractJson(F);
    std::cout << "S1 exracted" << std::endl;
    auto S2 = extractJson(F);
    std::cout << "S2 exracted" << std::endl;

    //std::cout << S1 <<std::endl;
    //std::cout << S2 <<std::endl;


    std::fstream fp("part1.json",std::ios::out);
    std::fstream sp("part2.json",std::ios::out);
    fp << S1;
    sp << S2;

    //std::cout << S2 << std::endl;
    nlohmann::json J1 = nlohmann::json::parse(S1);//[0]["personal"].begin().value();
    nlohmann::json J2 = nlohmann::json::parse(S2);
    std::cout << "dmg = "<<extractDmg(J2) <<std::endl;
    std::cout << "win = "<<extractWin(J2) <<std::endl;
    std::cout << "hitperc = "<<extractHitPercent(J2) <<std::endl;
    std::cout << "date = "<<extractDateTime(J1) <<std::endl;
    /*
    for(auto it = J.items().begin();it != J.items().end();++it){
        std::cout << it.key() << std::endl;
    }
    */
    return 0;
}
#else

struct BattleData{
    int dmg,win;
    float hitp;
    std::string vehicle,map,date;
    BattleData(){}
    BattleData(const nlohmann::json &J1,const nlohmann::json &J2):
        dmg(extractDmg(J2)),
        win(extractWin(J2)),
        hitp(extractHitPercent(J2)),
        vehicle(extractVehicle(J1)),
        map(extractMap(J1)),
        date(extractDateTime(J1)){}

    bool operator > (const BattleData & D){
        return date > D.date;
    }
    bool operator < (const BattleData & D){
        return date < D.date;
    }
    bool operator >= (const BattleData & D){
        return date > D.date;
    }
    bool operator <= (const BattleData & D){
        return date < D.date;
    }


    static const std::string head(){return "date\tmap\tvehicle\twin\tdmg\thitp";};

    std::string toString()const{
        std::stringstream S;
        S << date << "\t" <<  map<< "\t" <<  vehicle <<  "\t" <<  win << "\t" << dmg << "\t" << hitp;
        return S.str();
    }

    friend std::ostream & operator << (std::ostream & os,const BattleData & D){
        return os << D.toString();
    }

};

int main(int argc,char ** argv)
{
    //setlocale(LC_ALL, "Russian");
    if(argc < 2){
        std::cout << "need path to replays" << std::endl;
        return 0;
    }
    std::vector<BattleData> AllData;
    std::string path = argv[1];

    for(const auto &p : std::filesystem::directory_iterator(path)){
        if(p.is_regular_file() && p.path().filename().extension().string() == ".wotreplay"){
            std::cout << p.path().string() << std::endl;
            std::ifstream F(p.path().string());
            if(!F.is_open()){
                std::cout << "couldnt open file" <<std::endl;
                return -1;
            }
            auto S1 = extractJson(F);
            //std::cout << "S1 exracted" << std::endl;
            auto S2 = extractJson(F);
            //std::cout << "S2 exracted" << std::endl;

            nlohmann::json J1 = nlohmann::json::parse(S1);//[0]["personal"].begin().value();
            nlohmann::json J2 = nlohmann::json::parse(S2);

            //std::cout << "created json" <<std::endl;

            //std::cout << BattleData(J1,J2)<<std::endl;

            AllData.push_back(BattleData(J1,J2));
        }
    }
    std::sort(AllData.begin(),AllData.end());

    std::ofstream ofs("replayinfo.txt");
    ofs<<BattleData::head()<<std::endl;
    for(const auto & dat : AllData){
        ofs<<dat<<std::endl;
    }
    return 0;
}
#endif
