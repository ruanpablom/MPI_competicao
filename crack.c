#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <crypt.h>
#define P_T 10
#define D_T 64

int main(int argc, char **argv){
    int j=1,k=0,i;
    char d[] = "./abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int *pass=NULL;
    char *c_pass=NULL;
    char pass_s[15];
    char *salt;
    char *result;
    int ok;
    FILE *f;

    salt = (char*)malloc(2*sizeof(char));	

    f = fopen(argv[1],"r");	
    while(fscanf(f,"%s",pass_s)!=EOF){
        memcpy(salt,pass_s,2);
        for(i = 1 ; i < P_T ; i++){		
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
                    result = crypt(c_pass, salt);
                    ok = strcmp (result, pass_s);	
                    if(!ok){
                        printf("é NoIx porra! A senha é: %s\n", c_pass);
                        break;
                    }
                }

                if(!ok) break;
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
            if(!ok)break;

        }
    }
    fclose(f);
    return 0;
}

//senha unica
