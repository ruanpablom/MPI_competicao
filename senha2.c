#include <stdio.h>
#include <string.h>
#include <math.h>
#define D_T 64

void senha_pos(int i, char *c_pass, unsigned long salt);

int main(){
    int i;
    unsigned long s = pow(64,10)/26;
    unsigned long ss = s;
    char c_pass[] = "..........";
    for(i=0;i<26;i++){
        senha_pos(10,c_pass,ss);
        printf("%s\n",c_pass);
        ss+=s;
    }
    return 0;
}

void senha_pos(int i, char *c_pass, unsigned long salt){
    int j=0;
    int pass[i];
    char d[] = "./abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    for(j=0;j<i;j++)pass[j]=0;

    while((salt-D_T)>=1){
       salt-=D_T;
       for(j = i-2 ; j >= 0 ; j--){
           if(pass[j] < D_T-1){
               pass[j]++;
               c_pass[j] = d[pass[j]];
               break;
           }else{
               pass[j]=0;
               c_pass[j]=d[0];
               continue;
           }
       }
    }
    c_pass[i-1] = d[salt-1];
}
