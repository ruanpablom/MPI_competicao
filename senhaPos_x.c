#include <stdio.h>
#include <string.h>
#include <math.h>
#define D_T 64

int senha_pos(int i, char *c_pass);

int main(){
    char c_pass[] = "..........";
    senha_pos(10,c_pass);
    printf("%s\n",c_pass);
    return 0;
}

int senha_pos(int i, char *c_pass){
    int j=0;
    int pass[i];
    char d[] = "./abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    unsigned long pos_x,pos_aux;

    printf("Digite a posição da senha: ");
    scanf("%li",&pos_x);
    for(j=0;j<i;j++)pass[j]=0;

    pos_aux =  pos_x;

    /*while(1){
        if((pos_aux/(D_T)) > 1 ){
            beg++;
        }
        while((int)(pos_aux/(D_T)) > (D_T)){
            beg++;
            pos_aux = pos_aux/(D_T);
        }
        if(beg==1) pos_aux =(int)(pos_aux/(D_T));

        printf("pos: %d\n",beg);
        if(beg!=0){
            abc = (pos_xx - pow((D_T),beg))/pow((D_T),beg);
            printf("%i\n",abc);
            if(first){
                printf("letra: %c\n",d[abc+1]);
                first=0;
            }
            else printf("letra: %c\n",d[abc]);
        }else{
            printf("letra: %c\n",d[pos_xx-1]);
            break;
        }
        if(beg==1)  pos_xx = pos_x - (D_T)*((int)(pos_x/(D_T))); 
        else pos_xx = pos_xx - pow((D_T-1),beg); 
        beg = 0;
    }i*/
    
    int k,flag;
    while(j!=-1){ 
        for(j = 0 ; j < D_T ; j++){
            pass[i - 1] = j;
            c_pass[i - 1]=d[j];
            k++;
            if(k == pos_x){
                flag = 1;
                //memcpy(passs,c_pass,i);
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

}
