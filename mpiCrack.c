#define _GNU_SOURCE
#include<unistd.h>
#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<string.h>
#include"senha4.h"

#define T_M 10

int main(int argc, char **argv){
	int rank,size,i,j;
	MPI_Status status;
	//MPI_Request *request;
	char **pCrackL;
	char *dados;
	//char *dadosS;
	//char **saltL;
	PassSlice *slices;
	char fileName[] = "input.in";
	int qtPTC=0;
	//char *t;
	FILE *file;
	char src[14];
	int TP = 1;
	//MPI_File fh;
	//int filesize;
	//I_MPI_MT_MEMCPY=1;
	//int tDes = getDes();

	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size); 	

	//qtPTC = atoi(argv[1]);

	//pCrackL=(char*)malloc(qtPTC*getTDes()*sizeof(char));
	//saltL=(char*)malloc(qtPTC*getTS()*sizeof(char));


	if(rank == 0){	
		file = fopen(fileName,"r");

		for(i=0 ; fscanf(file,"%s",src)!=EOF ; i++ );
		fseek(file,0,SEEK_SET);	
		qtPTC = i;
		dados = (char*)malloc(qtPTC*(getTDes()+1)*sizeof(char));
		if(dados==NULL)exit(0);
		pCrackL = (char**)malloc(sizeof(char*)*(qtPTC+1));
		if(pCrackL==NULL)exit(0);
		for(i = 0 ; i < qtPTC ; i++)pCrackL[i]=&(dados[i*(getTDes()+1)]);

		for(i=0 ; i < (qtPTC-1) ; i++ ){
			fscanf(file,"%s",pCrackL[i]);
		}
		fclose(file);
		setTP(TP);
		for(i = 0 ; i < getTP() ; i++){
			slices = initSlices(size-1);		
			/*for(i=0;i<size-1;i++){
			  printf("%i\n",slices[i].interval);
			  printf("%i\n",slices[i].tPass);
			  printf("%s\n",slices[i].begin);
			  printf("%s\n",slices[i].end);	
			  }*/
			for(j=1;j<size-1;j++){
				MPI_Send(&TP,1,MPI_INT,i,2,MPI_COMM_WORLD);
				MPI_Send(&slices[i].begin,TP,MPI_CHAR,i,0,MPI_COMM_WORLD);
				MPI_Send(&slices[i].interval,1,MPI_UNSIGNED_LONG,i,1,MPI_COMM_WORLD);
			}
			TP++;
			setTP(TP);
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast (&qtPTC, 1, MPI_INT, 0, MPI_COMM_WORLD);	
	if(rank!=0){
		dados = (char*)malloc(qtPTC*(getTDes()+1)*sizeof(char));
		if(dados==NULL)exit(0);
		pCrackL = (char**)malloc(sizeof(char*)*(qtPTC+1));
		if(pCrackL==NULL)exit(0);
		for(i = 0 ; i < qtPTC ; i++)pCrackL[i]=&(dados[i*(getTDes()+1)]);
		MPI_Recv(&TP,1,MPI_INT,0,2,MPI_COMM_WORLD,&status);
		MPI_Recv(&slices[rank].begin,TP,MPI_CHAR,0,0,MPI_COMM_WORLD,&status);
		MPI_Recv(&slices[rank].interval,1,MPI_UNSIGNED_LONG,0,1,MPI_COMM_WORLD,&status);
	}
	//pCrackL=(char*)malloc(qtPTC*getTDes()*sizeof(char));
	//MPI_Bcast (&qtPTC, 1, MPI_INT, 0, MPI_COMM_WORLD);
	//MPI_Barrier(MPI_COMM_WORLD);
	//MPI_Bcast (dados, qtPTC*(getTDes()+1), MPI_CHAR, 0, MPI_COMM_WORLD);
	//for(i=0;i<qtPTC;i++)pCrackL[i] = &dados[i*(getTDes()+1)];
	//MPI_Bcast (saltL, qtPTC*getTS(), MPI_CHAR, 0, MPI_COMM_WORLD);
	//for(i = 0 ; i < qtPTC ; i++){
	//printf("%i %i \n",qtPTC,rank);
	//}
	//printf("%s\n",pCrackL[0]);
	//setTp(1);
	//openMP(pCrackL, saltL, qtPTC);

	MPI_Finalize();
	return 0;
}


