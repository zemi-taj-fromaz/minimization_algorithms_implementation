#include "Callable.hpp"

Callable::Callable(function<double(vector<double>)>& func){
    f = func;
    no_of_calls = 0;
}
double Callable::__call__(vector<double> vd){
    no_of_calls++;
    if(map.find(vd) == map.end()){
        map[vd] = this->f(vd);
        return map[vd];
    }
    return map[vd];
}

int Callable::getNoOfCalls(){
    return no_of_calls;
}

void Callable::resetNoOfCalls(){
    no_of_calls = 0;
    return;
}
