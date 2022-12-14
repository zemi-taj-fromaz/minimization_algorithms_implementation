#include "GaussNewton.hpp"
#include "GoldenRatio.hpp"
#include "Matrix.hpp"

GaussNewton::GaussNewton(Callable* call, vector< vector< function< double(vector<double>)> > > Jot,vector< function< double(vector<double>)> > Ge){
    callable = call;
    G = Ge;
    J = Jot;
    e = 1e-6;

    gauss_newton = [this](vector<double> x0,bool optimal_step){
        int n = x0.size();
        vector<double> x(x0);

        vector<vector<double>> J_res(n,x);
        vector<vector<double>> G_res;

        auto best_f = this->callable->__call__(x);
        int divergence_counter = 0;
        auto jot = this->J;
        auto ge = this->G;
        while(true){                
            G_res.clear();
            for(int i = 0; i < n; i++){
                for(int j = 0; j <n ;j++){
                    auto partial = jot[i][j];
                    J_res[i][j] = partial(x);
                }
                auto partial_G = ge[i];
                G_res.push_back({partial_G(x)});
            }

            Matrix* matrixJ = new Matrix(J_res);
            Matrix* matrixJT = new Matrix(J_res);
            matrixJT->T();
            Matrix* Gtrix = new Matrix(G_res);
            // cout<<"G je ";
            // Gtrix->Print();
            Matrix A = (*matrixJT) * (*matrixJ);
            matrixJ->T();
            Matrix g = (*matrixJT) * (*Gtrix);
            Gtrix->T();

            Matrix* y;


            // cout<<"J(X) je";
            // matrixJ->Print();
            // cout<<"A je";
            // A.Print();
            // cout<<"g je";
            // g.Print();

            A.LUP_Decompose();
            y = A.forward_substitution(g);
            Matrix* gradMatrix;
            gradMatrix = A.backward_substitution(*y);
            // cout<<"GRAD : ";
            // gradMatrix->Print();
            auto helper = gradMatrix->getMatrix();
            vector<double> grad;

            for(auto vd : helper){
                grad.push_back(vd[0]);
            }

            if(this->l2_norm(grad) < this->e) {cout<<"gradijent premalen\n"; return x;};

            

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

                double optimal_lambda = this->goldenRatio->__go__(x,true)[0];

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

vector<double> GaussNewton::__go__(vector<double> vd, bool optimal_step){
    this->callable->resetNoOfCalls();
    return this->gauss_newton(vd,optimal_step); 
}