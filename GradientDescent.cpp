#include "GradientDescent.hpp"
#include <cmath>

GradientDescent::GradientDescent(Callable* call, vector<function<double(vector<double>)>> partials){
    callable = call;
    partial_derivations = partials;
    e = 1e-6;

    gradient_descent = [this] (vector<double> x0,bool optimal_step) {
        int n = x0.size();
        vector<double> grad(n,0);
        vector<double> x(x0);

        double f_best = this->callable->__call__(x);
        int divergence_counter = 0;
        int i = 0;
        auto der = this->partial_derivations;
        while(true){
           // cout<<"step "<<i<<"\n";
            if( divergence_counter >= 10) {
                cout<<"Algorithm started to diverge!"<<endl;
                return x;
            }

            
            //cout<<"Gradient : [";
            int j  = 0;
            for(auto partial : der){
                grad[j] = partial(x);
              //  cout<<grad[j]<<" ";
                j++;
            }//cout<<"]\n";


            double norm = this->l2_norm(grad);
            //cout<<"norm : "<<norm<<"\n";

            if (norm < this->e ){
                cout<<"gradient too small\n";
                return x;
            }

            if(optimal_step){
                function<double(vector<double>)> find_optimal_step_function = [this,x,grad](vector<double> vd){
                    
                    vector<double> tmp(x);
                    double lambda = vd[0];

                    for (int i = 0; i < tmp.size(); i++)
                    {
                        tmp[i] -= grad[i]*lambda;
                    }
                    
                    return this->callable->__call__(tmp);
                };

                Callable* callable = new Callable(find_optimal_step_function);
                this->goldenRatio = new GoldenRatio(callable);

                double optimal_lambda = this->goldenRatio->__go__({2},true)[0];

                // cout<<"OPTIMAL STEP : "<<optimal_lambda<<endl;
                for(int k = 0; k < grad.size(); k++){
                    grad[k]*=optimal_lambda;
                }
            }

            transform(x.begin(),x.end(),grad.begin(),x.begin(),minus<double>());

            // cout<<"X [";
            // for(auto c: x){
            //     cout<<c<<" ";
            // }cout<<"]\n";

            double f = this->callable->__call__(x);
            
            if(f < f_best){
                f_best = f;
                divergence_counter = 0;
            } else {
                divergence_counter++;
            }
            i++;
        }

        return x;
    };

}

vector<double> GradientDescent::__go__(vector<double> vd,bool optimal_step){
    this->callable->resetNoOfCalls();
    return gradient_descent(vd,optimal_step);
}