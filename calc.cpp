#include "calc.h"

void getdata(std::vector<char> *expr)
{
    std::string expr_str;
    std::cin>>expr_str;

    if(expr_str[0]=='-')
        expr->push_back('0');

    for(auto i: expr_str) 
        expr->push_back(i);
}
bool IsOper(char expr_ch)
{
    bool f=0;
    char opers[5] {'+','-','*','/','^'};
    
    for(auto i: opers)
        if(expr_ch==i)
            f=1;
    
    return f;
}
bool IsDigit(char expr_ch)
{

    bool f=0;
    char digits[10] {'0','1','2','3','4','5','6','7','8','9'};
    
    for(auto i: digits)
        if(expr_ch==i)
            f=1;
            
    return f;
}
int whatOper(char expr_ch)
{
    switch (expr_ch)
    {
        case '+': {return 0;break;} 
        case '-': {return 1;break;} 
        case '*': {return 2;break;} 
        case '/': {return 3;break;} 
        case '^': {return 4;break;} 
    }
}
double whatDigit(char expr_ch)
{
    switch (expr_ch)
    {
        case '0': {return 0;break;} 
        case '1': {return 1;break;}
        case '2': {return 2;break;}
        case '3': {return 3;break;}
        case '4': {return 4;break;}
        case '5': {return 5;break;}
        case '6': {return 6;break;}
        case '7': {return 7;break;}
        case '8': {return 8;break;} 
        case '9': {return 9;break;}
    }
}
double calculation(std::vector<char> expr)
{
    std::vector<double> digits;
    std::vector<int> opers;

    double res=0;
    for(int i=0;i<expr.size();i++)
        {
            if(expr[i]=='(')
                digits.push_back(brackets_count(&expr));
            else if(IsDigit(expr[i])) {
                double dgt = 0;
                int index=1;
                int numIter=i;
                bool indicator=1;
                while ((IsDigit(expr[numIter])|expr[numIter]=='.'|expr[numIter]==',')&& numIter<expr.size())
                {   
                    if(expr[numIter]=='.'|expr[numIter]==',') {
                            indicator=0;
                            index=1;
                            numIter++;
                            }
                    else {
                            if(indicator) {
                                dgt*=10;
                                dgt+=whatDigit(expr[numIter]);}
                            else {
                                dgt+=whatDigit(expr[numIter])/(pow(10,index));
                                index++;}
                            numIter++;
                    }
                }
                i=numIter;
                digits.push_back(dgt);
                }//определить число
            if(IsOper(expr[i])) 
                opers.push_back(whatOper(expr[i]));
        }
   
    for(int i=digits.size()-1;i>0;i--) {
        if(opers[i-1]==4){
            if(abs(digits[i]-(int)digits[i-1])==0 | digits[i-1]>0)
            digits[i]=pow((digits[i-1]),(digits[i]));
        else{ 
                try 
                    {  
                        int d=1/digits[i];
                        if (d%2==0 &&digits[i-1]<0 )
                        {
                            throw 228; //генерировать целое число 123
                        }
                        digits[i]=0-pow((0-digits[i-1]),(digits[i]));   
                    }
                    catch(int i)//сюда передастся число 123
                    {
                       std:: cout << "Ошибка №" << i << " - извлечение корня четной степени из отрицательного числа" << std::endl;
                       exit(0);

                    }
                    

            }
            digits.erase(digits.begin()+i-1);
            opers.erase(opers.begin()+i-1);
            }
        }

    for(int i=1;i<digits.size();i++) 
        if(opers[i-1]==1)digits[i]=0-(digits[i]);
    
        for(int i=1;i<digits.size();i++)
            {
                if(opers[i-1]==2){
                    digits[i]*=digits[i-1];
                    digits.erase(digits.begin()+i-1);
                    opers.erase(opers.begin()+i-1);
                    i--;
                }
                if(opers[i-1]==3){
                    digits[i]=(digits[i-1])/(digits[i]);
                    digits.erase(digits.begin()+i-1);
                    opers.erase(opers.begin()+i-1);
                    i--;
                    }
            }
     for(auto i : digits) res +=i; 
    
    return res;
}
void showres(double res)
{
    std::cout<<res<<std::endl;
}
double brackets_count(std::vector<char> *expr)
    {
        std::vector<char> expr_in_brackets;
        int pos1=0;
        int pos2=0;
        int ind=0;

        for(int i=0;i<expr->size();i++){
            
            if((*expr)[i]==')'){
                ind--; 
                if(ind==0){pos2=i;break;}}
            
            if(ind!=0) 
                expr_in_brackets.push_back((*expr)[i]);
            
            if((*expr)[i]=='('){
                ind++;
                if(ind==1)
                    pos1=i;
                
                if((*expr)[pos1+1]=='-')
                    expr_in_brackets.push_back('0');}
            }   
        expr->erase(expr->begin()+pos1,expr->begin()+pos2+1);
        double newNum =calculation(expr_in_brackets);
        return newNum;
    }