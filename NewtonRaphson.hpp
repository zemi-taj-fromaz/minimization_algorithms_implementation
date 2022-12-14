#ifndef NEWTON_RAPHSON_HPP
#define NEWTON_RAPHSON_HPP

#include "MinAlgo.hpp"
#include "GoldenRatio.hpp"

class NewtonRaphson : public MinAlgo {
    private:
        double e;
        GoldenRatio* goldenRatio;
        vector< vector<function<double(vector<double>)> > > H;
        vector< function<double(vector<double>)> > dF;

        function<vector<double>(vector<double>,bool)> newton_raphson;

    public:
        NewtonRaphson(Callable*,
                        vector< vector<function<double(vector<double>)> > >,
                            vector< function<double(vector<double>)> >);
        vector<double> __go__(vector<double>,bool);

};

#endif