#ifndef MINALGO_HPP
#define MINALGO_HPP

#include <iostream>
#include <map>
#include <cmath>
#include <functional>
#include <vector>
#include <initializer_list>
#include "Callable.hpp"

using namespace std;

class MinAlgo {
    protected:
        Callable* callable;
        function<double(vector<double>)> l2_norm = [] (vector<double> vd){
                double ret = 0;
                for(auto d : vd){
                    ret += pow(d,2);
                }
                return sqrt(ret);
            };
    public:
        virtual vector<double> __go__(vector<double>,bool) = 0;
       // virtual ~MinAlgo(){ }
};

#endif