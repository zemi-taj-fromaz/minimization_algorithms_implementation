#include "NewtonRaphson.hpp"

#include "Matrix.hpp"

NewtonRaphson::NewtonRaphson(Callable* callabl,vector< vector<function<double(vector<double>)> > > He,
                                vector< function<double(vector<double>)> > d){
    callable = callabl;
    H = He;
    dF = d;
    e = 1e-6;

    newton_raphson = [this](vector<double> x0,bool optimal_step){
        int n = x0.size();
        vector<double> x(x0);
        vector<vector<double>> b(n,x);
        vector<vector<double>> A(n,x);

        auto best_f = this->callable->__call__(x);
        int divergence_counter = 0;

        while(true){
            
            for(int i = 0; i < n; i++){
                b[i] = {this->dF[i](x)};
                for(int j = i; j < n; j++){

                    A[i][j] = this->H[i][j](x);
                    A[j][i] = A[i][j];

                }
            }


            Matrix* matrixA = new Matrix(A);
            Matrix* matrixB = new Matrix(b);

            matrixA->LUP_Decompose();

            Matrix* y;
            y = matrixA->forward_substitution(*matrixB);
            Matrix* gradMatrix;
            gradMatrix = matrixA->backward_substitution(*y);
            
            auto helper = gradMatrix->getMatrix();

            vector<double> grad;

            for(auto vd : helper){
                grad.push_back(vd[0]);
            }

            if(this->l2_norm(grad) < this->e) { cout<<"gradient too small\n";return x;}

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

                double optimal_lambda = this->goldenRatio->__go__({1},true)[0];

                for(auto val : grad){
                    val*=optimal_lambda;
                }
            }

            transform(x.begin(),x.end(),grad.begin(),x.begin(),minus<double>());

            auto curr_f = this->callable->__call__(x);
            if(curr_f < best_f){
                best_f = curr_f;
            } else {
                divergence_counter++;
                if(divergence_counter >= 10){
                    cout<<"DIVERGENCE!!!!\n";
                    return x;
                }
            }

        }

    
        return x;
    };
    
}

vector<double> NewtonRaphson::__go__(vector<double> vd, bool optimal_step){
    this->callable->resetNoOfCalls();
    return this->newton_raphson(vd,optimal_step); 
}
