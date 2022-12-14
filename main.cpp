//CTRL+SHIFT+P for user snippets
#include <bits/stdc++.h>
#include <functional>
#include "GoldenRatio.hpp"
#include "Callable.hpp"
#include "GradientDescent.hpp"
#include "GaussNewton.hpp"
#include "NewtonRaphson.hpp"

using namespace std;

#define iterator vector<int>::iterator
#define ll long long

function<double(vector<double>)> f1 = [](vector<double> vd){
    double x1 = vd[0];
    double x2 = vd[1];
    return 100*pow(x2-pow(x1,2),2) + pow(1-x1,2);
};

function<double(vector<double>)> f2 = [](vector<double> vd){
    double x1 = vd[0];
    double x2 = vd[1];
    return pow(x1-4,2) + 4*pow(x2-2,2);
};

function<double(vector<double>)> f3 = [](vector<double> vd){
    double x1 = vd[0];
    double x2 = vd[1];

    return pow(x1 - 2, 2) + pow(x2 + 3, 2);
};

function<double(vector<double>)> f4 = [](vector<double> vd){
    double x1 = vd[0];
    double x2 = vd[1];
    return pow(x1,4)/4 - pow(x1,2) + 2*x1 + pow(x2 - 1, 2);
};

int main(int argc,char** argv){

    switch(stoi(argv[1])){
        case 1:{
            function<double(vector<double>)> f3_partial_x1 = [](vector<double> vd){
                return 2*(vd[0]-2);
            };

            function<double(vector<double>)> f3_partial_x2 = [](vector<double> vd){
                return 2*(vd[1]+3);
            };


            vector<function<double(vector<double>)>> partial_derivations({f3_partial_x1,f3_partial_x2});
            Callable* callable1 = new Callable(f3);

            GradientDescent* gradDescent = new GradientDescent(callable1,partial_derivations);
     

            cout<<"Gradient Descent w/o line search: \n";
            auto min1 = gradDescent->__go__({0,0},false);
            cout<<callable1->getNoOfCalls()<<endl;
            cout<<"[";
            for(auto d: min1){
                cout<<d<<" ";
            }cout<<"]\n"<<endl;

            cout<<"Gradient Descent with line search: \n";
            min1 = gradDescent->__go__({0,0},true);
            cout<<callable1->getNoOfCalls()<<endl;
            cout<<"[";
            for(auto d: min1){
                cout<<d<<" ";
            }cout<<"]\n"<<endl;;
            
            break;
            }
        case 2:
            {       
                function<double(vector<double>)> f1_partial_x1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return -400*(x2 - pow(x1,2))*x1 - 2*(1 - x1);
                };
                function<double(vector<double>)> f1_partial_x2 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return 200*(x2 - pow(x1,2));
                };
                vector<function<double(vector<double>)>> partial_derivations({f1_partial_x1,f1_partial_x2});
                Callable* callable1 = new Callable(f1);
                GradientDescent* gradDescent = new GradientDescent(callable1,partial_derivations);
                cout<<"Gradient Descent with line search for f1: \n";
                auto min1 = gradDescent->__go__({-1.9,2},true);
                cout<<callable1->getNoOfCalls()<<endl;
                cout<<"[";
                for(auto d: min1){
                    cout<<d<<" ";
                }cout<<"]\n"<<endl;




                Callable* callable2 = new Callable(f1);
                function<double(vector<double>)> f1_partial_x1x1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return -400*(x2 - 3*pow(x1,2)) + 2;
                };
                function<double(vector<double>)> f1_partial_x1x2 = [](vector<double> vd){
                    return -400*vd[0];
                };
                function<double(vector<double>)> f1_partial_x2x2 = [](vector<double> vd){
                    return 200;
                };
                vector<function<double(vector<double>)>> HesseRow1({f1_partial_x1x1,f1_partial_x1x2});
                vector<function<double(vector<double>)>> HesseRow2({f1_partial_x1x2,f1_partial_x2x2});
                vector< vector<function<double(vector<double>)> > > H({HesseRow1,HesseRow2});
                NewtonRaphson* newtonRapshon = new NewtonRaphson(callable2,H,partial_derivations);
                cout<<"NewtonRaphson with line search for f1: \n";
                min1 = newtonRapshon->__go__({-1.9,2},true);
                cout<<callable2->getNoOfCalls()<<endl;
                cout<<"[";
                for(auto d: min1){
                    cout<<d<<" ";
                }cout<<"]\n"<<endl;




                function<double(vector<double>)> f2_partial_x1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return 2*(x1 - 4);
                };
                function<double(vector<double>)> f2_partial_x2 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return 8*(x2 - 2);
                };
                vector<function<double(vector<double>)>> partial_derivations2({f2_partial_x1,f2_partial_x2});
                Callable* callable3 = new Callable(f2);
                GradientDescent* gradDescent2 = new GradientDescent(callable3,partial_derivations2);
                cout<<"Gradient Descent with line search for f2: \n";
                min1 = gradDescent2->__go__({0.1,0.3},true);
                cout<<callable3->getNoOfCalls()<<endl;
                cout<<"[";
                for(auto d: min1){
                    cout<<d<<" ";
                }cout<<"]\n"<<endl;



                Callable* callable4 = new Callable(f2);
                function<double(vector<double>)> f2_partial_x1x1 = [](vector<double> vd){
                    return 2;
                };
                function<double(vector<double>)> f2_partial_x1x2 = [](vector<double> vd){
                    return 0;
                };
                function<double(vector<double>)> f2_partial_x2x2 = [](vector<double> vd){
                    return 8;
                };
                vector<function<double(vector<double>)>> HesseRow21({f2_partial_x1x1,f2_partial_x1x2});
                vector<function<double(vector<double>)>> HesseRow22({f2_partial_x1x2,f2_partial_x2x2});
                vector< vector<function<double(vector<double>)> > > H2({HesseRow21,HesseRow22});
                NewtonRaphson* newtonRapshon2 = new NewtonRaphson(callable4,H2,partial_derivations2);
                cout<<"NewtonRaphson with line search for f2: \n";
                min1 = newtonRapshon2->__go__({0.1,0.3},true);
                cout<<callable2->getNoOfCalls()<<endl;
                cout<<"[";
                for(auto d: min1){
                    cout<<d<<" ";
                }cout<<"]\n"<<endl;

                break;
            }
        case 3 : 
            {
                function<double(vector<double>)> f4_partial_x1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return pow(x1,3) - 2*x1 + 2;
                };
                function<double(vector<double>)> f4_partial_x2 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return 2 * (x2 - 1);
                };
                vector<function<double(vector<double>)>> partial_derivations({f4_partial_x1,f4_partial_x2});
                function<double(vector<double>)> f4_partial_x1x1 = [](vector<double> vd){
                    return 3 * pow(vd[0],2) - 2;
                };
                function<double(vector<double>)> f4_partial_x1x2 = [](vector<double> vd){
                    return 0;
                };
                function<double(vector<double>)> f4_partial_x2x2 = [](vector<double> vd){
                    return 2;
                };
                vector<function<double(vector<double>)>> HesseRow21({f4_partial_x1x1,f4_partial_x1x2});
                vector<function<double(vector<double>)>> HesseRow22({f4_partial_x1x2,f4_partial_x2x2});
                vector< vector<function<double(vector<double>)> > > H({HesseRow21,HesseRow22});
                Callable* callable1 = new Callable(f4);
                NewtonRaphson* newtonRapshon1 = new NewtonRaphson(callable1,H,partial_derivations);
                cout<<"NewtonRaphson w/o line search for f4: \n";
                auto min1 = newtonRapshon1->__go__({3,3},true);
                cout<<callable1->getNoOfCalls()<<endl;
                cout<<"[";
                for(auto d: min1){
                    cout<<d<<" ";
                }cout<<"]\n"<<endl;



                Callable* callable2 = new Callable(f4);
                NewtonRaphson* newtonRapshon2 = new NewtonRaphson(callable2,H,partial_derivations);
                cout<<"NewtonRaphson w/o line search for f4: \n";
                min1 = newtonRapshon2->__go__({1,2},true);
                cout<<callable2->getNoOfCalls()<<endl;
                cout<<"[";
                for(auto d: min1){
                    cout<<d<<" ";
                }cout<<"]\n"<<endl;

            
                break;
            }
        case 4 : 
            {

                function<double(vector<double>)> g1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return 10*(x2 - pow(x1,2));
                };
                function<double(vector<double>)> g2 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return (1-x1);
                };
                vector<function<double(vector<double>)>> G({g1,g2});

                function<double(vector<double>)> g1_partial_x1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return -20*x1;
                };
                function<double(vector<double>)> g1_partial_x2 = [](vector<double> vd){
                    return 10;
                };
                function<double(vector<double>)> g2_partial_x1 = [](vector<double> vd){
                    return -1;
                };
                function<double(vector<double>)> g2_partial_x2 = [](vector<double> vd){
                    return 0;
                };
                vector<vector<function<double(vector<double>)>>> J;
                J.push_back({g1_partial_x1,g1_partial_x2});
                J.push_back({g2_partial_x1,g2_partial_x2});

                

                Callable* callable1 = new Callable(f1);

                GaussNewton* gaussNewton= new GaussNewton(callable1,J,G);

        
                cout<<"GaussNewton w/o line search for f1: \n";
                auto min1 = gaussNewton->__go__({-1.9,2},false);
                cout<<callable1->getNoOfCalls()<<endl;
                cout<<"[";
                for(auto d: min1){
                    cout<<d<<" ";
                }cout<<"]\n"<<endl;
            break;
        }
        case 5 : {
                function<double(vector<double>)> g1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return pow(x1,2) + pow(x2,2) - 1;
                };
                function<double(vector<double>)> g2 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return x2-pow(x1,2);
                };
                vector<function<double(vector<double>)>> G({g1,g2});

                function<double(vector<double>)> g1_partial_x1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return 2*x1;
                };
                function<double(vector<double>)> g1_partial_x2 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return 2*x2;
                };
                function<double(vector<double>)> g2_partial_x1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return -2*x1;
                };
                function<double(vector<double>)> g2_partial_x2 = [](vector<double> vd){
                    return 1;
                };
                vector<vector<function<double(vector<double>)>>> J;
                J.push_back({g1_partial_x1,g1_partial_x2});
                J.push_back({g2_partial_x1,g2_partial_x2});

                function<double(vector<double>)> f_peti = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    return pow( pow(x1,2) + pow(x2,2) - 1 ,2) + pow( x2 - pow(x1,2) ,2);
                };

                Callable* callable1 = new Callable(f_peti);

                GaussNewton* gaussNewton= new GaussNewton(callable1,J,G);

        
                cout<<"GaussNewton w/o line search for (-2,2): \n";
                auto min1 = gaussNewton->__go__({-2,2},false);
                cout<<callable1->getNoOfCalls()<<endl;
                cout<<"[";
                for(auto d: min1){
                    cout<<d<<" ";
                }cout<<"]\n"<<endl;

                cout<<"GaussNewton w/o line search for (2,2): \n";
                min1 = gaussNewton->__go__({2,2},false);
                cout<<callable1->getNoOfCalls()<<endl;
                cout<<"[";
                for(auto d: min1){
                    cout<<d<<" ";
                }cout<<"]\n"<<endl;

                cout<<"GaussNewton w/o line search for (2,-2): \n";
                min1 = gaussNewton->__go__({2,-2},false);
                cout<<callable1->getNoOfCalls()<<endl;
                cout<<"[";
                for(auto d: min1){
                    cout<<d<<" ";
                }cout<<"]\n"<<endl;
            break;
        }
        case 6 : {

                function<double(vector<double>)> g1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return x1 * exp(x2) + x3 - 3;
                };

                function<double(vector<double>)> g2 = [](vector<double> vd){
                        double x1 = vd[0];
                        double x2 = vd[1];
                        double x3 = vd[2];
                        return x1 * exp(x2*2) + x3 - 4;
                };

                function<double(vector<double>)> g3 = [](vector<double> vd){
                        double x1 = vd[0];
                        double x2 = vd[1];
                        double x3 = vd[2];
                        return x1 * exp(x2*3) + x3 - 4;
                    };

                function<double(vector<double>)> g4 = [](vector<double> vd){
                        double x1 = vd[0];
                        double x2 = vd[1];
                        double x3 = vd[2];
                        return x1 * exp(x2*5) + x3 - 5;
                    };
                
                function<double(vector<double>)> g5 = [](vector<double> vd){
                        double x1 = vd[0];
                        double x2 = vd[1];
                        double x3 = vd[2];
                        return x1 * exp(x2*6) + x3 - 6;
                    };
                
                function<double(vector<double>)> g6 = [](vector<double> vd){
                        double x1 = vd[0];
                        double x2 = vd[1];
                        double x3 = vd[2];
                        return x1 * exp(x2*7) + x3 - 8;
                    };
                
                
                vector<function<double(vector<double>)>> G({g1,g2,g3,g4,g5,g6});

                function<double(vector<double>)> g1_partial_x1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return exp(x2);
                };
                function<double(vector<double>)> g1_partial_x2 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return x1*exp(x2);
                };
                function<double(vector<double>)> g1_partial_x3 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return 1;
                };

                function<double(vector<double>)> g2_partial_x1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return exp(x2*2);
                };
                function<double(vector<double>)> g2_partial_x2 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return x1*2*exp(x2*2);
                };
                function<double(vector<double>)> g2_partial_x3 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return 1;
                };

                function<double(vector<double>)> g3_partial_x1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return exp(x2*3);
                };
                function<double(vector<double>)> g3_partial_x2 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return x1*3*exp(x2*3);
                };
                function<double(vector<double>)> g3_partial_x3 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return 1;
                };

                function<double(vector<double>)> g4_partial_x1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return exp(x2*5);
                };
                function<double(vector<double>)> g4_partial_x2 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return x1*5*exp(x2*5);
                };
                function<double(vector<double>)> g4_partial_x3 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return 1;
                };

                function<double(vector<double>)> g5_partial_x1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return exp(x2*6);
                };
                function<double(vector<double>)> g5_partial_x2 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return x1*6*exp(x2*6);
                };
                function<double(vector<double>)> g5_partial_x3 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return 1;
                };

                function<double(vector<double>)> g6_partial_x1 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return exp(x2*7);
                };
                function<double(vector<double>)> g6_partial_x2 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return x1*7*exp(x2*7);
                };
                function<double(vector<double>)> g6_partial_x3 = [](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    return 1;
                };


                vector<vector<function<double(vector<double>)>>> J;
                J.push_back({g1_partial_x1,g1_partial_x2,g1_partial_x3});
                J.push_back({g2_partial_x1,g2_partial_x2,g2_partial_x3});
                J.push_back({g3_partial_x1,g3_partial_x2,g3_partial_x3});
                J.push_back({g4_partial_x1,g4_partial_x2,g4_partial_x3});
                J.push_back({g5_partial_x1,g5_partial_x2,g5_partial_x3});
                J.push_back({g6_partial_x1,g6_partial_x2,g6_partial_x3});

                vector<pair<int,int>> vpii;
                vpii.push_back({1,3});
                vpii.push_back({2,4});
                vpii.push_back({3,4});
                vpii.push_back({5,5});
                vpii.push_back({6,6});
                vpii.push_back({7,8});

                function<double(vector<double>)> f_sesti = [vpii](vector<double> vd){
                    double x1 = vd[0];
                    double x2 = vd[1];
                    double x3 = vd[2];
                    
                    double ret = 0;
                    for(auto p : vpii){
                        ret += pow(x1*exp(x2*p.first) + x3 - p.second , 2);
                    }
                    return ret;
                };

                Callable* callable1 = new Callable(f_sesti);

                GaussNewton* gaussNewton= new GaussNewton(callable1,J,G);

        
                cout<<"GaussNewton : \n";
                auto min1 = gaussNewton->__go__({1,1,1},false);
                cout<<callable1->getNoOfCalls()<<endl;
                cout<<"[";
                for(auto d: min1){
                    cout<<d<<" ";
                }cout<<"]\n"<<endl;
            

            break;
        }
    
    }
    


  
    return 0;
}
