
#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cmath>
void getdata(std::vector<char>*);
bool IsOper(char);
bool IsDigit(char);
int whatOper(char);
double whatDigit(char);
double calculation(std::vector<char>);
void showres(double);
double brackets_count(std::vector<char>*);
