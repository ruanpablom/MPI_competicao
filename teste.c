#include<stdio.h>
#include<math.h>
#define P_T 4
#define D_T 62

int main(){
    int j=1,k=0,i;
    char d[] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
    int pass[P_T] ={};
    
    while(j!=-1){
        for(j = 0 ; j < D_T ; j++){ 
            pass[P_T - 1] = j;
            for(i = 0 ; i < P_T ; i++); //printf("%c",d[pass[i]]);
            //printf("\n");
        }
        pass[P_T-1] = 0;
        for(j = P_T-2 ; j >= 0 ; j--){
            if(pass[j] < D_T-1){
                pass[j]++;
                break;
            }else{
                pass[j] = 0;
                continue;
            }
        }
    }

    return 0;
}
