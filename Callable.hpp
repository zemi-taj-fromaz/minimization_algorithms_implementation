#ifndef CALLABLE_HPP
#define CALLABLE_HPP
#include <iostream>
#include <vector>
#include <map>
#include <functional>

using namespace std;


class Callable {
    protected:
        function<double(vector<double>)> f;
        int no_of_calls;
        map<vector<double>,double> map;
    public:
        Callable(function<double(vector<double>)>&);
        double __call__(vector<double>);
        int getNoOfCalls();
        void resetNoOfCalls();
};


#endif