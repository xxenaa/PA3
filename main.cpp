#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <cmath>

using namespace std;
struct info{
    string elias;
    int pos;
};
static pthread_mutex_t bsem;
static int p=0;
static pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void *decode (void *str){
    struct info *ptr= (struct info*)str;
     
     pthread_mutex_lock(&bsem);
    
     while(ptr->pos!=p){
         pthread_cond_wait(&empty, &bsem);
     }
     
     int x;
     x=stoi(ptr->elias);
     int d=0;
         for (int i=0; x>0;i++){
             int a=x%2;
             if(a==1){
             d+= pow(2,i);
             }
             x=x/10;
         }
    
    cout<<char(d);
    
     pthread_mutex_unlock(&bsem);
     
  
     
     pthread_mutex_lock(&bsem);
     p++;
        pthread_cond_broadcast(&empty);
    
     pthread_mutex_unlock(&bsem);
        return NULL;
    }

int main(int argc, char ** argv)
{
    string text;
    vector<string> vect;
    vector<string> code;
    vector<string> position;
   
    
    while(getline(cin,text)){
        vect.push_back(text);
   
    }
     
    for(int i=0; i< vect.size();i++){
         istringstream s (vect.at(i));
         string x,y;
         s>>x>>y;
        code.push_back(x);
        position.push_back(y);
     }
   
    struct info in[vect.size()];
    pthread_t tid[vect.size()];
          
          
    for(int i=0; i<vect.size() ;i++){
              in[i].elias=code.at(i);
              int num= stoi(position.at(i));
              in[i].pos=num;
              
             pthread_create(&tid[i], NULL, decode ,&in[i]);
          }
    for (int i = 0; i < vect.size(); i++)
            pthread_join(tid[i], NULL);
        

    return 0;
}
