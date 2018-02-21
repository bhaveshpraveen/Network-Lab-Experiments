# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define dec printf("--------------------------------------------\n\n");
# define dec_sender printf("--------------Sender-----------------\n\n");
# define dec_receiver printf("--------------Receiver-----------------\n\n");

int sw=0, sf=0, sn=0, rn=0;	// Sender Side
int sender = 1;		// flag for sender or receiver. 0 for receiver and 1 for sender
int no_of_frames, m, frame_sent=-1, acknowledge_sent=-1;

int show_options(){
	int temp;
	if(sender){
		dec_sender;
		printf("1. Send Frame\n");
		printf("2. Frame Lost\n");
		printf("3. Ack Lost\n");
		printf("4. Receive acknowledgement\n");
		printf("5. Switch to receiver side\n");
	}	
	else {
		dec_receiver;
		printf("1. Receive Frame\n");
		printf("2. Send Acknowledgement\n");
		printf("3. Discard Frame\n");
		printf("4. Switch to sender side\n");
	}
	scanf("%d", &temp);
	return temp;
}
void show_values(){
	printf("sf = %d %d\nsn = %d %d\nrn = %d %d\n", sf, sf % (int)pow(2, m), sn, sn % (int)pow(2, m),  rn, rn % (int)pow(2, m));
}

int main(){
	scanf("%d %d", &no_of_frames, &m);
	sw = ((int)pow(2, m)) - 1;	
	while(1){
		int option;
		option = show_options();
		dec;
		if(sender){
				
			switch(option){
				case 1:
					if(sn-sf >= sw){
						printf("Window is full. So sending frame %d\n", sf % (int)pow(2, m));
						frame_sent = sf;
						break;
					}
					frame_sent = sn;
					if(sn < no_of_frames){
						printf("Frame %d sent\n", frame_sent % (int)pow(2, m));
						sn++ ;
					}
					else {
						printf("Sending frame %d\n", sf % (int)pow(2, m));
						frame_sent = sf;
					}
					break;
				case 2:
					printf("Frame %d lost\n", frame_sent % (int)pow(2, m));
					frame_sent = -1;
					break;	
				case 3:
					printf("Acknowlegment %d lost\n", acknowledge_sent % (int)pow(2, m));
					acknowledge_sent = -1;
					break;
				case 4:
					if(acknowledge_sent >= 0){
						sf = acknowledge_sent;
						printf("Acknowlegment %d received\n", acknowledge_sent % (int)pow(2, m));
					        acknowledge_sent = -1;	
						break;
					}
					printf("Did not receive any acknowledgement\n");
					break;
				case 5:
					printf("Switching to receiver side\n");
					sender = 0;
					break;
			}
			show_values();
		}
		else{
			switch(option){
				case 1:
					if(frame_sent < 0){
						printf("No frame to receive\n");
						break;
					}
					if(frame_sent < rn){
						printf("Frame %d already received. So sending acknowlegment %d.\n", frame_sent % (int)pow(2, m), rn % (int)pow(2, m));
						acknowledge_sent = rn;
					}
					else{
						if(rn == frame_sent){
							rn = (rn+1);
							printf("Frame %d received.\n", frame_sent % (int)pow(2, m));
						}
						else{
							printf("Discarding frame %d\n", frame_sent % (int)pow(2, m));
						}	
					}
					frame_sent = -1;
					break;
				case 2:
					acknowledge_sent = rn;
					printf("Sent Acknowlegment %d\n", rn % (int)pow(2, m));
					break;
				case 3:
					if(frame_sent){
						printf("Discarding Frame %d\n", frame_sent % (int)pow(2, m));
						frame_sent = -1;
						break;
					}
					printf("No frame to discard\n");
					break;
				case 4:
					printf("Switching to sender side.\n");
					sender = 1;
					break;
			}	
			show_values();
		}
		if(sf == no_of_frames && sn == no_of_frames){
			printf("All frames sent\n");
			break;
		}
	}
	return 0;
}
