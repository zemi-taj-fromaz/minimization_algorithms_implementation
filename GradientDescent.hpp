#ifndef GRADIENTDESCENT_HPP
#define GRADIENTDESCENT_HPP

#include "MinAlgo.hpp"
#include "GoldenRatio.hpp"
#include <vector>

using namespace std;

class GradientDescent : public MinAlgo {
    private:

        GoldenRatio* goldenRatio;

        double e;

        function< vector<double>(vector<double>,bool) > gradient_descent;

        vector< function<double(vector<double>)> > partial_derivations;

    public:
        GradientDescent(Callable*, vector<function<double(vector<double>)>>);
        vector<double> __go__(vector<double>,bool);
        
};

#endif
