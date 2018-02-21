# include <stdio.h>
# include <stdlib.h>


# define pn printf("\n")
# define f(i, n) for(i=0; i<n; i++)
# define fr(i, n) for(i=n-1; i>=0; i--)

int input_word[50];
int word_with_checksum[50];
int i_length, i, j, r, n, r_temp, temp, tmp_bit=0;
int r_values[50];
int r_values1[50];


int power(int a, int b){
	int i, j;
	j = 1;	
	for(i = 0; i < b; i++){
		j = j * a;
	}
	return j;
}
void take_input_and_find_ans(int *r_values){

	for(i = 0;  i < i_length; i++){
		scanf("%d", &input_word[i]);
	}
	for(i=0, j=0; j<n; j++){
		if(j == 0 || j == 1 || j == 3 || j == 7 || j == 15 || j == 31 || j == 63)
			word_with_checksum[j] = -1;
		else {
			word_with_checksum[j] = input_word[i++];
		}
	}
	
	// f(i, i_length){
	// 	printf("%d ", input_word[i]);
	// }
	// pn;
	
	// printf("Encoded Word: ");
	// fr(i, n){
	// 	printf("%d ", word_with_checksum[i]);
	// }
	// pn;
	
	
	temp = 0;
	r_temp = r;
	while(r_temp > temp){
		for(i = 1; i <= n; i++){
			if (i == 1 || i == 2 || i == 4 || i == 8 ||  i == 16 || i == 32 || i == 64)
				continue;
			
			if ((i & (1 << temp)) != 0){
				// printf("%d:%d ", i, word_with_checksum[i-1]);
				tmp_bit = tmp_bit ^ word_with_checksum[i-1];			
			}
		}
		// pn;
		// printf("%d\n", tmp_bit);
		r_values[temp++] = tmp_bit;
		tmp_bit = 0;
		
	}

}

int main(){ 
	
	scanf("%d", &i_length);
	
	r = 1;
	n = i_length + r;
	while(n > power(2, r) - 1){
		r++;
		n++;
	}
	printf("r = %d n = %d\n", r, n);

	take_input_and_find_ans(r_values);
	printf("Checksum: ");
	for(i=r-1; i>=0; i--)
		printf("%d ", r_values[i]);
	pn;

	take_input_and_find_ans(r_values1);
	printf("Checksum: ");
	for(i=r-1; i>=0; i--)
		printf("%d ", r_values1[i]);
	pn;
	
	printf("Res: ");
	for(i=r-1; i>=0; i--)
		printf("%d ", r_values[i] ^ r_values1[i]);
	pn;
	
}


