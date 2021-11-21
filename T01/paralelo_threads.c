#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>


#define TID_CONV (int)(size_t)tid
	
//pthread_t threads[NTHREAD];
pthread_t* threads;
int status;
void *thread_return;
float **m1;
float **m2;
int L1,C1,L2,C2;
int P;
int nthreads;
int* index_ini;
int* l_ini; 
int* l_end; 
int* c_ini; 
int* c_end; 
FILE** fpv;
char** threads_file_names;
char* output_dir_name;
unsigned int ifnames_len[2];
char* input_files_names[2];
time_t *thread_tic, *thread_toc;

void matrix_printer(float **matrix,int L, int C){	
	for (int l = 0; l < L; l++){
		printf("\n");
		for (int c = 0; c < C; c++)
			printf("a(%d,%d)=%.2f\t",l,c,matrix[l][c]);
	}
	printf("\n\n");
}

void* matrix_paralel_product(void* tid){
	int TID = TID_CONV;					// void* tid to int
	
	// Output file creation
	threads_file_names[TID] = (char*)malloc((2*(ifnames_len[0]+ifnames_len[1])+50)*sizeof(char));
	sprintf(threads_file_names[TID],"thr/%s_%s_%d/%s_%s_thr_%d_result.dat",input_files_names[0],input_files_names[1],P,input_files_names[0],input_files_names[1],TID);
	//printf("Thread %d file name\n\t%s\n\n",TID,threads_file_names[TID]);
	fpv[TID] = fopen(threads_file_names[TID], "w+");
	fprintf(fpv[TID],"%d %d\n",L1,C2);
	
	index_ini[TID] = P*(TID);
	l_ini[TID] = index_ini[TID]/C2;
	l_end[TID] = ((index_ini[TID]+P)/C2);
	c_ini[TID] = index_ini[TID]%C2;
	c_end[TID] = (index_ini[TID]+P)%C2;
	if(l_end[TID]>=L1){
		l_end[TID]=L1-1;
		c_end[TID]=C2;
	}
	//printf("TID=%d index_ini[TID]:%d>>l_ini[TID]: %d\tl_end[TID]: %d\tc_ini[TID]: %d\tc_end[TID]: %d\n",TID,index_ini[TID],l_ini[TID], l_end[TID],c_ini[TID],c_end[TID]);
	
	// Matrix product
	float temp;
	for(int l = l_ini[TID] ; l < l_end[TID] ; l++){
		for (int c=c_ini[TID]; c < C2; c++){
			temp = 0;
			for (int rc=0; rc < C1; rc++)
				temp+=m1[l][rc]*m2[rc][c];
			//printf("c%d%d %f\n",l,c,temp);
			fprintf(fpv[TID],"c%d%d %f\n",l,c,temp);
		}
		c_ini[TID] = 0;
	}
	for (int c=c_ini[TID]; c < c_end[TID]; c++){
			temp = 0;
			for (int rc=0; rc < C1; rc++)
				temp+=m1[l_end[TID]][rc]*m2[rc][c];
			//printf("c%d%d %f\n",l_end[TID],c,temp);
			fprintf(fpv[TID],"c%d%d %f\n",l_end[TID],c,temp);
	}
	time(&thread_toc[TID]);
	fprintf(fpv[TID],"%li ",thread_toc[TID]-thread_tic[TID]);
	fclose(fpv[TID]);
	pthread_exit(NULL);
}


int main (int argc, char *argv[]) {
	// Initializations
	clock_t tic, toc;
	tic = clock();
	
	time_t s_start, s_end;
	time(&s_start);
	
	char dummy_s[100];
	float dummy_f;
	
	if(argc < 4)		// Are there 2 matrices names?
		return -1;
	
	// Getting P
	P = atoi(argv[3]);
	
	// Getting files info
	ifnames_len[0] = strlen(argv[1]);
	input_files_names[0]= (char*)malloc((ifnames_len[0]-4)*sizeof(char));
	strncpy(input_files_names[0], argv[1], ifnames_len[0]-4);
	
	ifnames_len[1] = strlen(argv[2]);
	input_files_names[1]= (char*)malloc((ifnames_len[1]-4)*sizeof(char));
	strncpy(input_files_names[1], argv[2], ifnames_len[1]-4);
	
	output_dir_name = (char*)malloc((ifnames_len[0]+ifnames_len[1]+10)*sizeof(char));
	sprintf(output_dir_name,"thr/%s_%s_%d",input_files_names[0],input_files_names[1],P);
	printf("%s\n",output_dir_name);
	struct stat st = {0};

	if (stat(output_dir_name, &st) == -1) {
		mkdir(output_dir_name, 0666);
	}else{
		printf("Já existe o diretório\n");
	}
	
	// Reading matrix 1
	FILE * fp1;
	fp1 = fopen (argv[1], "r");
	fscanf(fp1,"%d %d",&L1,&C1);
	
	m1=(float**)malloc(L1*sizeof(float*));
	for(int l = 0 ; l < L1 ; l++){
		m1[l]=(float*)malloc(C1*sizeof(float));
		for (int c=0; c < C1; c++)
			fscanf(fp1,"%s %f", dummy_s, &(m1[l][c]));
	}
	fclose(fp1);   // Closing matrix files
	//matrix_printer(m1,L1, C1);
	
	// Reading matrix 1
	FILE * fp2;
	ifnames_len[1] = strlen(argv[2]);
	fp2 = fopen (argv[2], "r");
	fscanf(fp2,"%d %d",&L2,&C2);
	
	m2=(float**)malloc(L2*sizeof(float*));
	for(int l = 0 ; l < L2 ; l++){
		m2[l]=(float*)malloc(C2*sizeof(float));
		for (int c=0; c < C2; c++)
			fscanf(fp2,"%s %f", dummy_s, &(m2[l][c]));
	}
	fclose(fp2);	// Closing matrix files
	
	//matrix_printer(m2,L2,C2);
	
/* 	float **result=(float**)malloc(L1*sizeof(float*));
	for(int l = 0 ; l < L1 ; l++){
		result[l]=(float*)calloc(C2,sizeof(float));
		for (int c=0; c < C2; c++)
			for (int rc=0; rc < C1; rc++)
				result[l][c]+=m1[l][rc]*m2[rc][c];
	} */
	//matrix_printer(result,L1,C2);
	
	
	//printf("Matrix dimensions>> L1: %d\tC1: %d\tL2: %d\tC2: %d\n",L1, C1, L2, C2);
	
	// Preparing threads and auxiliary variables
	nthreads = ceil((((float)L1*C2)/P));
	index_ini = (int*)malloc(nthreads*sizeof(int));
	l_ini = (int*)malloc(nthreads*sizeof(int)); 
	l_end = (int*)malloc(nthreads*sizeof(int)); 
	c_ini = (int*)malloc(nthreads*sizeof(int)); 
	c_end = (int*)malloc(nthreads*sizeof(int)); 
	//printf("nthreads: %d\tL1: %d\tC2: %d\tP: %d\n",nthreads,L1,C2,P);
	threads = (pthread_t*)malloc(nthreads*sizeof(pthread_t));
	fpv = (FILE**)malloc(nthreads*sizeof(FILE*));
	threads_file_names = (char**)malloc(nthreads*sizeof(char*));
	thread_tic = (time_t*)malloc(nthreads*sizeof(time_t));
	thread_toc = (time_t*)malloc(nthreads*sizeof(time_t));

	
	for (int i = 0; i < nthreads; i++){
		//printf("Creating threads\n");
		time(&thread_tic[i]); 
		status = pthread_create(&threads[i], NULL, matrix_paralel_product, (void *)(size_t) i);
		if (status){
			printf("Error in thread %d creation\n",i);
			return -1;
		}
	}
	
	for (int i = 0; i < nthreads; i++){
		//printf("Waiting for thread %d\n",i);
		status = pthread_join(threads[i], &thread_return);
		//printf("The thread %d is over\n",i);
		if (status){
			printf("Error in thread %d end\n",i);
			return -1;
		}
	}
	
	
	
	// Saving 
/* 	FILE * fp3;
	char result_name[100]="";
	char str_temp1[100]="";
	char str_temp2[100]="";
	sprintf(result_name,"thr/%s_%s_result.dat",strncpy(str_temp1, argv[1], strlen(argv[1])-4),strncpy(str_temp2, argv[2], strlen(argv[2])-4));
	fp3 = fopen (result_name, "w+");
	fprintf(fp3,"%d %d\n",L1,C2); */
	//printf("result_name: %s \n",result_name);
	//puts("It's here\n");
	
/* 	
	for (int l = 0; l < L1; l++)
		for (int c = 0; c < C2; c++)
			fprintf(fp3,"c%d%d %f\n",l,c,result[l][c]);
	 */
	
	// Freeing memory
	for(int l = 0 ; l < L1 ; l++)
		free(m1[l]);
	free(m1);
	for(int l = 0 ; l < L2 ; l++)
		free(m2[l]);
	free(m2);
	//for(int l = 0 ; l < L1 ; l++)
	//	free(result[l]);
	//free(result);
	free(threads);
	free(index_ini);
	free(l_ini); 
	free(l_end); 
	free(c_ini); 
	free(c_end); 
	free(input_files_names[0]);
	free(input_files_names[1]);
	free(output_dir_name);
	// Final time measurment
	toc = clock();
	//printf("\nThe process takes %f clocks cicles\n", ((double)(toc-tic)))/CLOCKS_PER_SEC;
	time(&s_end);
/* 	fprintf(fp3,"%li\n",s_end-s_start);
	fclose(fp3); */
	//fclose(fpv);
	//fclose(threads_file_names);
	//printf("\nThe process takes %li seconds\n", s_end-s_start);
	return(0);
}