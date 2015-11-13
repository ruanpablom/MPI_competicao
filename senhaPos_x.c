#include <stdio.h>
#include <string.h>
#include <math.h>
#define D_T 64

int senha_pos(int i,char *passs);

int main(){
    char passs[10];
    senha_pos(10,passs);
    printf("%s\n",passs);
    return 0;
}

int senha_pos(int i,char *passs){
    int j=0,flag=0;
    int pass[i];
    char c_pass[] = "..........";
    char d[] = "./abcdefghijklmnopqrstuwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    long pos_x,pos_xx,k=0;
    int x = 0;
    int y = D_T;
    int s[i];
    char t[] = "..........";
    int r=0;
    int pos_atual;

    printf("Digite a posição da senha: ");
    scanf("%li",&pos_x);
    pos_xx=pos_x;
    for(j=0;j<i;j++){
        s[j]=0;
        pass[j]=0;
    }
    pos_atual=pos_x;
    while((pos_x/D_T) > 0){ 
        pos_atual = pos_x;
        while(pos_x/D_T > 0){ 
            pos_x /=D_T;
            x++;
        }
        s[i-x]++;
        t[i-x]=d[s[i-x]];
        //printf("%i\n",s[x]);
        pos_x = pow(D_T,x); 
        x=0;
        r = pos_x;
        pos_x = pos_x/D_T;
        //printf("%i\n",pos_x);
    }
    printf("%i %i %i\n",pos_x,pos_atual,pos_atual-(pos_x*D_T));
    if(r!=0)t[i-1] = d[pos_x-pos_atual];
    else t[i-1]= d[pos_xx-1];
    printf("%s\n",t);
    pos_x=pos_xx; 
    while(j!=-1){ 
        for(j = 0 ; j < D_T-1 ; j++){
            pass[i - 1] = j;
            c_pass[i - 1]=d[j];
            k++;
            //printf("%i %i\n",k,pos_x);
            if(k == pos_x){
                flag = 1;
                memcpy(passs,c_pass,i);
                return 1;
                break;
            }
            if(flag)break;
        }
        if(flag) break;
        pass[i-1] = 0;
        c_pass[i -1] = d[0];	
        for(j = i-2 ; j >= 0 ; j--){
            if(pass[j] < D_T-1){
                pass[j]++;
                c_pass[j]=d[pass[j]];
                break;
            }else{
                pass[j] = 0;
                c_pass[j]=d[0];
                continue;
            }
        }
    }
    //printf("%s\n",c_pass);
    
    return 0;
}
