#include "GoldenRatio.hpp"

GoldenRatio::GoldenRatio(Callable* call){
    callable = call;
    l = 0;
    r = 0;
    e = 1e-6;
    k = (sqrt(5)-1)/2;

    unimodal = [this](double h,double tocka,double& left,double& right){
        left = tocka - h;
        right = tocka + h;
        double m;
        double fl,fm,fr;
        int step = 1;
        //cout<<"        prije pozivanja\n";
        fm = this->callable->__call__({tocka});
        //cout<<"kaj\n";
        fl = this->callable->__call__({left});
        //cout<<"kaj\n";
        fr = this->callable->__call__({right});
        //cout<<"        nakon pozivanja\n";

        if(fm < fr && fm <fl) return;

        if(fm > fr){
            do{
                left = m;
                m = right;
                fm = fr;
                step*=2;
                right = tocka + h*step;
                fr= this->callable->__call__({right});
            }while(fm > fr);
        } else {
            do{
                right = m;
                m = left;
                fm = fl;
                step*=2;
                left = tocka - h*step;
                fl = this->callable->__call__({left});
            }while(fm > fl);
        }
    };

    golden_ratio = [this](double a, double b){
        double c = b - this->k*(b - a);
        double d = a + this->k*(b - a);
        double fc,fd;
        fc = this->callable->__call__({c});
        fd = this->callable->__call__({d});
        while((b - a) > this->e){
            if(fc < fd){
                b = d;
                d = c;
                c = b - this->k*(b - a);
                fd = fc;
                fc = this->callable->__call__({c});
            } else {
                a = c;
                c = d;
                d = a + this->k*(b - a);
                fc = fd;
                fd = this->callable->__call__({d});
            }
        }
        return (a + b)/2;
    };
}

vector<double> GoldenRatio::__go__(vector<double> vd,bool optimal_step){
    //cout<<"go GoldenRation\n";
    if(vd.size() == 1){
        //cout<<"    find unimodal\n";
        double x0 = vd[0];
        double h = 0.5;
        unimodal(h,x0,this->l,this->r);
    }
    //cout<<"    find minimum\n";
    return {golden_ratio(this->l,this->r)};
}
