#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void rand_matrix_builder(time_t seconds,float **matrix,int L, int C){
	srand((unsigned int)seconds);	// Random seed
	printf("Building matrix...\n");
	for (int l = 0; l < L; l++)
		for (int c = 0; c < C; c++)
			//matrix[l][c] = 1;
			matrix[l][c] = 10*((float)(rand()-(RAND_MAX>>1))/((float)(RAND_MAX)));
			//printf("a(%d,%d)=%.2f\t",l,c,matrix[l][c]);
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
	time_t seconds;
	time(&seconds);
	
	if(argc < 5)		// Are there 2 matrix dimensions?
		return -1;
		
	// Getting parameters
	int dims[4];
	for(int i=1;i<argc;i++){
		dims[i-1] = atoi(argv[i]);
		printf("%d string: %s inteiro: %d\n", i,argv[i],dims[i-1]);
	}
	
	// Building matrices
	float **m1=(float**)malloc((dims[0])*sizeof(float*));
	for(int l = 0 ; l < dims[0] ; l++)
		m1[l]=(float*)malloc((dims[1])*sizeof(float));
	rand_matrix_builder(seconds,m1,dims[0],dims[1]);
	//matrix_printer(m1,dims[0],dims[1]);
	printf("a(%d,%d)=%.2f\n",dims[0],dims[1],m1[dims[0]-1][dims[1]-1]);
	
	float **m2=(float**)malloc((dims[2])*sizeof(float*));
	for(int l = 0 ; l < dims[2] ; l++)
		m2[l]=(float*)malloc((dims[3])*sizeof(float));
	rand_matrix_builder(seconds+1,m2,dims[2],dims[3]);
	//matrix_printer(m2,dims[2],dims[3]);
	printf("a(%d,%d)=%.2f\n",dims[2],dims[3],m2[dims[2]-1][dims[3]-1]);
			
	
	
	int length = snprintf( NULL, 0, "%ld", seconds );
	char *now = malloc(length + 1);
	snprintf( now, length + 1, "%ld", seconds );
	
	srand((unsigned int)seconds);	// Random seed
	
	
	printf("Seconds since January 1, 1970 = %ld\n", seconds);
	printf("Número aleatório %f\n", 10*((float)(rand()-(RAND_MAX>>1))/((float)(RAND_MAX))));
	printf("Número aleatório %f\n", 10*((float)(rand()-(RAND_MAX>>1))/((float)(RAND_MAX))));
	printf("string: %s | long int: %ld\n",now, seconds);
	
	
	
	// Saving  matrices
	char m1_name[100] = "m1_";
	printf("%s\n",m1_name);
	strcat(m1_name,now);
	printf("%s\n",m1_name);
	strcat(m1_name,".dat");
	printf("%s\n",m1_name);
	char m2_name[100] = "m2_";
	strcat(m2_name,now);
	strcat(m2_name,".dat");
	printf("%s\n",m2_name);
	
	FILE * fp1;
	fp1 = fopen (m1_name, "w+");
	FILE * fp2;
	fp2 = fopen (m2_name, "w+");
	
	
	
	fclose(fp1);
	fclose(fp2);
	//getchar();
	free(now);
	for(int l = 0 ; l < dims[0] ; l++)
		free(m1[l]);
	free(m1);
	for(int l = 0 ; l < dims[2] ; l++)
		free(m2[l]);
	free(m2);
	//getchar();
	
	
	return(0);
}