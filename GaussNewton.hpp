#ifndef GAUSS_NEWTON_HPP
#define GAUSS_NEWTON_HPP

#include "MinAlgo.hpp"
#include "GoldenRatio.hpp"

class GaussNewton : public MinAlgo {
    private:
        double e;
        GoldenRatio* goldenRatio;
        function<vector<double>(vector<double>,bool)> gauss_newton;

        vector< vector< function< double(vector<double>)> > > J;
        vector< function< double(vector<double>)> > G;
    public:
        GaussNewton(Callable*,vector< vector< function< double(vector<double>)> > >,vector< function< double(vector<double>)> >);
        vector<double> __go__(vector<double>,bool);
        
};


#endif