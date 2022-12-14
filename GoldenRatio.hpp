#ifndef GOLDEN_RATIO_HPP
#define GOLDEN_RATIO_HPP

#include <iostream>
#include <cmath>
#include "MinAlgo.hpp"


class GoldenRatio : public MinAlgo {
    private:
        double e;
        double l;
        double r;
        double k;
        function<void(double,double,double&,double&)> unimodal;
        function<double(double,double)> golden_ratio;
        
    public:
        GoldenRatio(Callable*);
        vector<double> __go__(vector<double>,bool);
        
};

#endif