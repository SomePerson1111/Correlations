#include <fstream>
#include <iostream>
#include <string>
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



int main(int argc,char ** argv)
{
    //setlocale(LC_ALL, "Russian");
    
    std::vector<BattleData> AllData;
    const std::filesystem::path path{(argc > 1 ? argv[1] : ".")};

    for(const auto &p : std::filesystem::directory_iterator{path}){
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

            try{
                nlohmann::json J1 = nlohmann::json::parse(S1);//[0]["personal"].begin().value();
                nlohmann::json J2 = nlohmann::json::parse(S2);
                AllData.push_back(BattleData(J1,J2));
            }catch(std::exception & e){
                std::cout << "unable to parse" <<std::endl;
            }

            //std::cout << "created json" <<std::endl;

            //std::cout << BattleData(J1,J2)<<std::endl
        }
    }
    std::sort(AllData.begin(),AllData.end());

    std::ofstream ofs((argc > 2 ? argv[2] : "replayinfo.txt"));
    ofs<<BattleData::head()<<std::endl;
    std::sort(AllData.begin(),AllData.end());
    for(const auto & dat : AllData){
        ofs<<dat<<std::endl;
    }
    return 0;
}
#endif
