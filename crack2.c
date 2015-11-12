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
    char pass_s[*argv[2]][15];
    char salt[*argv[2]][3];
    char *result;
    int ok;
    FILE *f;

    f = fopen(argv[1],"r");

    for(i=0;i<*argv[2];i++){
        fscanf(f,"%s",pass_s[i]);
        memcpy(salt[i],pass_s[i],2);
    }

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
        while(j!=-1){ 
            for(j = 0 ; j < D_T ; j++){ 
                pass[i - 1] = j;
                c_pass[i -1] = d[j];
                for(k=P_T-1;k>=0;k--){
                    for(h = 0 ; h < *argv[2] ; h++){
                        result = crypt(&c_pass[k], salt[h]);
                        ok = strcmp (result, pass_s[h]);
                        printf("Passei aqui!\n");        
                        if(!ok){
                            printf("é NoIx porra! A senha é: %s\n", &c_pass[k]);
                            //break;
                            ok=1;
                        }
                    } 
                }
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
