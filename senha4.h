#ifndef SENHA4_H
#define senha4_H

typedef struct sliceOfPass{
    char *begin;
    char *end;
    unsigned long int interval;
    int tPass;
}PassSlice;

char *passwsToCrack(char *fileName, int qtWords, char *dados);
char *saltsForPassws(char *passws, int qtPassws);
PassSlice *initSlices(int nprocs);
char *senha_pos(char *i_pass, unsigned long int interv);
long unsigned int lpow(long unsigned int base, int expoente);
int setTp(int TP);
int crack(char *initPa, char **pCrackL, char **saltL, int qtPCRACK, int intervalo);
int getTDes();
int getTS();
int openMP(char **passwdsTC, char **saltFP, int qtPTC);
int getTP();
void setTP(int TP);

#endif
