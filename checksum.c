# include <stdio.h>
# include <string.h>
# include <stdlib.h>

char str[1000];
int s1[1000], s2[1000], s3[1000];
int i, j, temp, set1=0, set2=0, set1_index, set2_index;

int tohex(int n, int *s){
	i = 0;
	// printf("hex: ");
	while(n){
		s[i++] = n%16;
		// printf("%d ", s[i-1]);
		n /= 16;
	}
	// printf("\n");
	return i;
}
int mod(int n){
	return (n<0)?-n:n;
}
void render(int n){
	j = 0;
	// printf("n: %d s3: ", n);
	for(i=0; i<2; i++){
		s1[i] += n;
		// printf("%d:", s1[i]);
		n = 0;
		if(s1[i]>15){
			n = s1[i]-15;
			s1[i] = 15;
		}
		s3[j++] = s1[i];
		// printf("%d ", s3[j-1]);
	}
	for(i=0; i<2; i++){
		s2[i] += n;
		n = 0;
		if(s2[i]>15){
			n = s2[i]-15;
			s2[i] = 15;
		}
		s3[j++] = s2[i];
		// printf("%d ", s3[j-1]);
	}
	// printf("\n");
}
void one_complement(){
	for(i=0; s3[i]!=-1; i++){
		s3[i] = 15 - s3[i];
	}
}
void find_checksum(){
	memset(s1, -1, sizeof(s1));
	memset(s2, -1, sizeof(s2));
	memset(s3, -1, sizeof(s3));


	set1_index = tohex(set1, s1);
	
	if (set1_index > 2)
		set2 += s1[2];


	set2_index = tohex(set2, s2);
	if(set2_index > 2)
		render(s2[2]);
	one_complement();
	
	printf("After one complement: ");
	for(i=3; i>=0; i--)
		printf("%X ", s3[i]);
	printf("\n");

}
void findsum(){
	for(i=1; i<strlen(str); i=i+2){
		// printf("%c %d ", str[i], str[i]);
		set1 += (int)str[i];
	}
	// printf("\n");

	for(i=0; i<strlen(str); i=i+2){
		// printf("%c %d ", str[i], str[i]);
		set2 += (int)str[i];
	}
	// printf("\n");

}
int main(){
	memset(str, '$', sizeof(str));
	scanf("%[^\n]s", str);
	
	printf("Sender's Side:\n");
	findsum();	
	
	find_checksum();
	
	printf("\n");
	printf("Receiver's Side: \n");
	// reset values for next iteration	
	set1=0;
	set2=0;
	findsum();
	set1 += s3[0] + s3[1]*16;
	set2 += s3[2] + s3[3]*16;
	
	find_checksum();

	// char hexstring[1000];
	// printf("\n");
	// printf("%x\n", set1);
	// printf("%d\n", strlen(str));
	return 0;
}

