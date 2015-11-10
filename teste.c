#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#define P_T 10
#define D_T 64

int main(int argc, char **argv){
    int j=1,k=0,i;
    char d[] = {"./abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
    int *pass=NULL;
	char *c_pass=NULL;
	char pass_s[14];
	char *salt;
  	char *result;
  	int ok;
	FILE *f;

	f = fopen(argv[1],"rt");	

	for(i = 1 ; i < P_T ; i++){
		fscanf(f,"%s",pass_s);
		memcpy(salt,pass_s,2);
		if(pass!=NULL) free(pass);
		if(c_pass!=NULL) free(c_pass);
    	pass = (int*)malloc(i*sizeof(int));
		c_pass = (char*)malloc(i*sizeof(char));
		while(j!=-1){
		    for(j = 0 ; j < D_T ; j++){ 
		        pass[P_T - 1] = j;
		        for(i = 0 ; i < P_T ; i++) sprintf(c_pass,"%c",d[pass[i]]);
				result = crypt(c_pass, salt);
				ok = strcmp (result, pass_s) == 0;
				if(ok){
					printf("é NoIx porra! A senha é: %s\n", c_pass);
					break;
				}
		    }
			if(ok) break;
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
	
	}
	fclose(f);
    return 0;
}

//senha unica
