# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define ll long long

int len_dataword;
int orig_dataword[1000];
int dataword[1000];
int len_polynomial;
int polynomial[1000];
int quo[1000];
int i, j, temp, l, h;


int exor(int a, int b){
	return (a==b)?0:1;
}

void crc(int *dataword){
	// printf("l h: %d %d\n", l, h);
	// printf("dataword: ");
	// for(i=0; i<len_dataword+len_polynomial-1; i++)
		// printf("%d", dataword[i]);
	// printf("\n");

	while(h<=len_dataword+len_polynomial-1){
		quo[l] = dataword[l];
		if(dataword[l] == 0){
			l++;	
			// printf("dataword: ");
			for(i=l;i<h;i++){
				// printf("%d:",dataword[i]);
				dataword[i] = exor(dataword[i], 0);
				// printf("%d ", dataword[i]);
			}
			// printf("\n");
		}
		else {
			l++;	
			// printf("dataword: ");
			for(i=l, j=1; j<len_polynomial; j++, i++){
				// printf("%d:",dataword[i]);
				dataword[i] = exor(dataword[i], polynomial[j]);
				// printf("%d ", dataword[i]);
			}
		}
		// printf("res: %d %d\n", l, h);
		// printf("temp res: ");
		// for(i=l; i<h; i++)
			// printf("%d ", dataword[i]);
		// printf("\n");
		h++;
		
	}
	
}
void output(){
	printf("quotient: ");
	for(i=0; quo[i]!=-1; i++)
		printf("%d ", quo[i]);
	printf("\n");

	printf("Encoded Word: ");
	for(i=0; i<len_dataword+len_polynomial-1;i++)
		printf("%d", orig_dataword[i]);
	printf("\n");

}

void res(){
	printf("Res: ");
	for(int i=0; i<len_polynomial-1; i++){
		printf("%d", orig_dataword[l+i]);
	}
	printf("\n");
}

int main(){
	memset(orig_dataword, -1, sizeof(orig_dataword));
	memset(dataword, -1, sizeof(dataword));
	memset(polynomial, -1, sizeof(polynomial));
	memset(quo, -1, sizeof(quo));

	scanf("%d", &len_dataword);
	for(i=0; i<len_dataword; i++){
		scanf("%d", &dataword[i]);
		orig_dataword[i] = dataword[i];
	}

	scanf("%d", &len_polynomial);
	for(i=0; i<len_polynomial; i++)
		scanf("%d", &polynomial[i]);
	
	for(i=len_dataword; i<len_dataword+len_polynomial-1; i++)
		dataword[i] = 0;

	l = 0;
	h = len_polynomial;
	crc(dataword);	
	for(int i=0; i<len_polynomial-1; i++){
		orig_dataword[i+len_dataword] = dataword[l+i];
	}
	output();
	// for(i=0; i<len_dataword+len_polynomial-1;i++)	
		// printf("%d", dataword[i]);
	// printf("\n");

	printf("Sender's side:\n");
	// Ask Ma'am if it is necessary to corrupt the data	
	printf("Corrupting data.......\n");
	orig_dataword[rand()%(len_dataword+len_polynomial-1)] = rand() %(len_dataword+len_polynomial-1);

	// Resetting the values
	l = 0;
	h = len_polynomial;
	
	crc(orig_dataword);
	res();
	return 0;
}
