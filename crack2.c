#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <crypt.h>
#define P_T 10
#define D_T 64

int main(int argc, char **argv){
    int j=1,k=0,i,h;
    char d[] = "./abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int *pass=NULL;
    char *c_pass=NULL;
    char **pass_s;
    char **salt;
    char *result;
    int ok;
    FILE *f;
    int qtd_p =(int)atoi(argv[2]);

    f = fopen(argv[1],"r");

    pass_s = (char**)malloc(qtd_p*sizeof(char*));
    salt = (char**)malloc(qtd_p*sizeof(char*));
    for(i = 0 ; i < qtd_p ; i++){
        pass_s[i] = (char*)malloc((P_T+1)*sizeof(char));
        salt[i] = (char*)malloc((P_T+1)*sizeof(char));
    }

    for(i=0;i<qtd_p;i++){
        fscanf(f,"%s",pass_s[i]);
        memcpy(salt[i],pass_s[i],2);
        printf("%s\n",pass_s[i]);
    }
    printf("%i\n",qtd_p);

    //while(fscanf(f,"%s",pass_s)!=EOF){
    // memcpy(salt,pass_s,2);
    for(i = P_T ; i <= P_T ; i++){		
        if(pass!=NULL) free(pass);
        if(c_pass!=NULL) free(c_pass);	
        pass = (int*)malloc(i*sizeof(int));
        if(pass == NULL)break;
        c_pass = (char*)malloc(i*sizeof(char));
        if(c_pass==NULL)break;
        for(j=0;j<i;j++){
            pass[j]=0;
            c_pass[j]=d[0];
        }
        j=0;
        int q = 0;
        while(j!=-1){
            if(q==qtd_p)break;
            for(j = 0 ; j < D_T ; j++){ 
                pass[i - 1] = j;
                c_pass[i -1] = d[j];
                for(k=P_T-1;k>=0;k--){
                    for(h = 0 ; h < qtd_p ; h++){ 
                        if(salt[h][0]!='\0'){
                            result = crypt(&c_pass[k], salt[h]);
                            ok = strcmp (result, pass_s[h]);
                            if(!ok){ 
                                //break;
                                ok=1;
                                salt[h][0]='\0';
                                q++;
                                printf("A %dª senha é: %s\n",h+1, &c_pass[k]);
                                if(q==qtd_p)break;
                            }
                        }
                    }
                    if(q==qtd_p)break;
                }
                if(q==qtd_p)break;
                //if(!ok)break; 
            }

            //if(!ok) break;
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
        //if(!ok)break;
    }
    //}
    fclose(f);
    return 0;
}

//senha unica
