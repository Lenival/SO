#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

float **m1;
float **m2;
int L1,C1,L2,C2;
	
void rand_matrix_builder(time_t seconds,float **matrix,int L, int C){
	srand((unsigned int)seconds);	// Random seed
	printf("Building matrix...\n");
	for (int l = 0; l < L; l++)
		for (int c = 0; c < C; c++)
			matrix[l][c] = 10*((float)(rand()-(RAND_MAX>>1))/((float)(RAND_MAX)));
}

void matrix_printer(float **matrix,int L, int C){	
	for (int l = 0; l < L; l++){
		printf("\n");
		for (int c = 0; c < C; c++)
			printf("a(%d,%d)=%.2f\t",l,c,matrix[l][c]);
	}
	printf("\n\n");
}



int main (int argc, char *argv[]) {
	// Initializations
	clock_t tic, toc;
	tic = clock();
	
	time_t s_start, s_end;
	time(&s_start);
	
	char dummy_s[100];
	float dummy_f;
	
	int L1,C1,L2,C2;
		if(argc < 3)		// Are there 2 matrices names?
			return -1;
		
	
	// Reading matrices
	FILE * fp1;
	fp1 = fopen (argv[1], "r");
	fscanf(fp1,"%d %d",&L1,&C1);
	
	//float **m1=(float**)malloc(L1*sizeof(float*));
	m1=(float**)malloc(L1*sizeof(float*));
	for(int l = 0 ; l < L1 ; l++){
		m1[l]=(float*)malloc(C1*sizeof(float));
		for (int c=0; c < C1; c++)
			fscanf(fp1,"%s %f", dummy_s, &(m1[l][c]));
	}
	//matrix_printer(m1,L1, C1);
		
	FILE * fp2;
	fp2 = fopen (argv[2], "r");
	fscanf(fp2,"%d %d",&L2,&C2);
	
	//float **m2=(float**)malloc(L2*sizeof(float*));
	m2=(float**)malloc(L2*sizeof(float*));
	for(int l = 0 ; l < L2 ; l++){
		m2[l]=(float*)malloc(C2*sizeof(float));
		for (int c=0; c < C2; c++)
			fscanf(fp2,"%s %f", dummy_s, &(m2[l][c]));
	}
	//matrix_printer(m2,L2,C2);
	
	// Closing matrix files
	fclose(fp1);
	fclose(fp2);
	
	// Opening result matrix file
	FILE * fp3;
	char result_name[100]="seq/";
	char str_temp1[100]="";
	char str_temp2[100]="";
	sprintf(result_name,"%s_%s_result.dat",strncpy(str_temp1, argv[1], strlen(argv[1])-4),strncpy(str_temp2, argv[2], strlen(argv[2])-4));
	fp3 = fopen (result_name, "w+");
	fprintf(fp3,"%d %d\n",L1,C2);
	
	// Matrix product
	float temp;
	for(int l = 0 ; l < L1 ; l++){
		for (int c=0; c < C2; c++){
			temp = 0;
			for (int rc=0; rc < C1; rc++)
				temp+=m1[l][rc]*m2[rc][c];
			fprintf(fp3,"c%d%d %f\n",l,c,temp);
		}
	}
	
	// Freeing memory
	for(int l = 0 ; l < L1 ; l++)
		free(m1[l]);
	free(m1);
	for(int l = 0 ; l < L2 ; l++)
		free(m2[l]);
	free(m2);
	
	// Final time measurment
	toc = clock();
	printf("\nThe process takes %f clocks cicles\n", ((double)(toc-tic)))/CLOCKS_PER_SEC;
	time(&s_end);
	fprintf(fp3,"%li\n",s_end-s_start);
	fclose(fp3);
	printf("\nThe process takes %li seconds\n", s_end-s_start);
	return(0);
}