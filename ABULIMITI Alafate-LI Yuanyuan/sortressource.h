#ifndef SORTRESSOURCE_H
#define SORTRESSOURCE_H
#include<cstdio>
#include<iostream>
#include <QString>
#include <vector>
#include <algorithm>
using namespace std;

class SortRessource{
    public:
        SortRessource(){

        }
        bool operator()(vector<int> v1, vector<int> v2)
        {
           if(v1.size()>=3 && v2.size()>=3)
           {
               if((v1.at(1)>v2.at(1)) ||
                       (((v1.at(1)==v2.at(1))&&((v1.at(2)>=v2.at(2))))))
               {
                   return false;
               }
               else
               {
                   return true;
               }
           }
           else
           {
               return false;
           }
        }
};
#endif // SORTRESSOURCE_H
