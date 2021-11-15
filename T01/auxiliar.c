#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
	// Initializations
	time_t seconds;
	time(&seconds);
	
	if(argc < 5)		// Are there 2 matrix dimensions?
		return -1;
		
	// Getting parameters
	int dims[4];
	for(int i=1;i<argc;i++)
		dims[i-1] = atoi(argv[i]);
	
	int length = snprintf( NULL, 0, "%ld", seconds );
	char *now = malloc(length + 1);
	snprintf( now, length + 1, "%ld", seconds );
	
	
	// Matrices file names
	char m1_name[100] = "";
	sprintf(m1_name,"%dx%d_",dims[0],dims[1]);
	char m2_name[100] = "";
	sprintf(m2_name,"%dx%d_",dims[2],dims[3]);
	if(argc < 7){
		strcat(m1_name,now);
		strcat(m2_name,now);
		strcat(m1_name,"_m1");
		strcat(m1_name,".dat");
		strcat(m2_name,"_m2");
		strcat(m2_name,".dat");
	}else{
		strcat(m1_name,argv[5]);
		strcat(m2_name,argv[6]);
	}
	
	// Matrices creation and store
	
	srand((unsigned int)seconds);	// Random seed
	FILE * fp1;
	fp1 = fopen (m1_name, "w+");
	fprintf(fp1,"%d %d\n",dims[0],dims[1]);
	for (int l = 0; l < dims[0]; l++)
		for (int c = 0; c < dims[1]; c++)
			fprintf(fp1,"c%d%d %f\n",l,c,10*((float)(rand()-(RAND_MAX>>1))/((float)(RAND_MAX))));
	FILE * fp2;
	fp2 = fopen (m2_name, "w+");
	fprintf(fp2,"%d %d\n",dims[2],dims[3]);
	for (int l = 0; l < dims[2]; l++)
		for (int c = 0; c < dims[3]; c++)
			fprintf(fp2,"c%d%d %f\n",l,c,10*((float)(rand()-(RAND_MAX>>1))/((float)(RAND_MAX))));
		
	fclose(fp1);
	fclose(fp2);
	free(now);	
	
	return(0);
}