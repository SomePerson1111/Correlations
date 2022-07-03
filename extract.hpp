#ifndef EXTRACT_HPP
#define EXTRACT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

std::string extractJson(std::istream &is){
	std::vector<char> stack;

    std::string S;

	char c;
    while(!is.eof()){
         is>>c;

         if(c == '['){
             S += c;
             stack.push_back('[');
         }
         else if(c == '{'){
             S += c;
             stack.push_back('{');
         }
         else if(c == '}' || c == ']'){
             S += c;
             stack.pop_back();
             if(stack.size() == 0)
                 break;
         }
         else{
             if(stack.size())
                S += c;
         }
	}
    return S;
}


int extractDmg(const nlohmann::json &J2){
    //std::cout << "dmg: " << J2[0]["personal"].begin().value()["damageDealt"] <<std::endl;
    return J2[0]["personal"].begin().value()["damageDealt"];
}

int extractWin(const nlohmann::json &J2){
    int team = J2[0]["personal"].begin().value()["team"];
    int winnerTeam = J2[0]["common"]["winnerTeam"];
    //int finishReason = J2[0]["common"]["finishReason"];


    //std::cout << "win: " << team << " "<<winnerTeam <<std::endl;
    //std::cout << "team: " << team << ", winnerteam: " << winnerTeam << ", finishReason" << finishReason <<std::endl;
    if(team == winnerTeam){
        return 1;
    }
    else if(winnerTeam!= 1 && winnerTeam != 2){
        return 0;
    }
    else{
        return -1;
    }
}

float extractHitPercent(const nlohmann::json &J2){
    int directHits = J2[0]["personal"].begin().value()["directHits"];
    int shots = J2[0]["personal"].begin().value()["shots"];

    //std::cout << "HitPercent: " << directHits/((float)shots) <<std::endl;

    return directHits/((float)shots);
}

std::string extractDateTime(const nlohmann::json &J1){
    return J1["dateTime"];
}

std::string extractVehicle(const nlohmann::json &J1){
    std::string S = "vehicle";
    try {
        S = J1["playerVehicle"];
    } catch (std::exception e) {
        std::cout << e.what() <<std::endl;
    }
    //std::cout << "vehicle: " << S <<std::endl;
    return S;
}

std::string extractMap(const nlohmann::json &J1){
    std::string S = "map";

    try {
        S = J1["mapDisplayName"];
    } catch (std::exception e) {
        std::cout << e.what() <<std::endl;
    }
    //::cout << "map: " << S <<std::endl;
    return S;
}

#define chekItem(item) if(item < Y.item) return false; if(item > Y.item) return true;
struct DateTime{
    int year,month,day;
    int hour,minut,second;

    DateTime(){}
    DateTime(int year,int month,int day,int hour,int minut,int second):
        year(year),month(month),day(day),hour(hour),minut(minut),second(second){}

    DateTime(const std::string &S):year(std::stoi(S.substr(6,4))),
         month(std::stoi(S.substr(3,2))),day(std::stoi(S.substr(0,2))),
         hour(std::stoi(S.substr(10,2))),minut(std::stoi(S.substr(13,2))),
         second(std::stoi(S.substr(16,2))){}

    friend std::ostream &operator << (std::ostream &os,const DateTime & Date){
        return os << "{" << "Date: " << Date.day << "." << Date.month << "." << Date.year << ", " <<
              "Time: " << Date.hour << ":" << Date.minut << ":"<< Date.second << "}";
    }

    bool operator >= (const DateTime & Y)const{


        chekItem(year);
        chekItem(month);
        chekItem(day);
        chekItem(hour);
        chekItem(minut);
        chekItem(second);
        return true;
    }
    bool operator > (const DateTime &Y)const{

        //#define chekItem(item) if(item < Y.item) return false; if(item > Y.item) return true;
        chekItem(year);
        chekItem(month);
        chekItem(day);
        chekItem(hour);
        chekItem(minut);
        chekItem(second);
        return false;
    }
    bool operator < (const DateTime & Y)const{return Y>(*this);}
    bool operator <= (const DateTime & Y)const{return Y>=(*this);}
};


#endif
