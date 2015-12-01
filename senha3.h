#ifndef SENHA3_H
#define SENHA3_h

//Global variables
int MAQ = 26;
int P_T = 10;
int D_T = 64;
int nCRACK = 30;

//Functions
char *senha_pos(int i, char *c_pass, unsigned long int salt, int MAQ, int P_T, int D_T);
long unsigned int lpow(long unsigned int base, int expoente);
char **initPassInits(char *initP,char **initsV,unsigned long int qtPasss, int procss, int P_T, int D_T);

#endif
