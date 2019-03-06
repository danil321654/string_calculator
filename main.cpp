#include "calc.h"
int main()
{
    while(1){
    std::vector<char> expr;
    getdata(&expr);
    double res=calculation(expr);
    showres(res);
    }
    return 0;
}
