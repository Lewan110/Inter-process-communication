#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <signal.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#define WRITE 1
#define READ 0
#define FIFO "my_fifo_2"
#define FIFOPID "PID"


int main(){
int odp1,odp2,m;
FILE *fp2;


fp2= fopen("pid.txt", "r");
fscanf(fp2, "%d", &m);
fclose(fp2);
printf("Proces macierzysty %d\n",m);
for(;;){
printf("Podaj co chcesz zrobic:\n");
printf("1 -Zabij proces\n");
printf("2 -Uspij proces\n");
printf("3 -Wznow proces\n");
scanf("%d[^\n]", &odp1);
switch(odp1){
	
	case 1:
		printf("Ktory proces?\n");
		printf("1 -K1\n");
		printf("2 -K2\n");
		printf("3 -K3\n");
		scanf("%d[^\n]", &odp2);

		switch(odp2){
			case 1:
			printf("Zabilem K1\n");
			kill(m+1, SIGUSR2);
			break;

			case 2:
			printf("Zabilem K2\n");
			kill(m+2,SIGUSR2);
			break;

			case 3:
			printf("Zabilem K3\n");
			kill(m+3,SIGUSR2);
			break;
		
		}
		break;

	case 2:
		printf("Ktory proces?\n");
		printf("1 -K1\n");
		printf("2 -K2\n");
		printf("3 -K3\n");
		scanf("%d[^\n]", &odp2);

		switch(odp2){
			case 1:
			printf("Uspilem K1\n");
			kill(m+1, SIGUSR1);
			break;

			case 2:
			printf("Uspilem K2\n");
			kill(m+2, SIGUSR1);
			break;

			case 3:
			printf("Uspilem K3\n");
			kill(m+3, SIGUSR1);
			break;
		
		}
		break;
	case 3:
		printf("Ktory proces?\n");
		printf("1 -K1\n");
		printf("2 -K2\n");
		printf("3 -K3\n");
		scanf("%d[^\n]", &odp2);

		switch(odp2){
			case 1:
			printf("Wznowilem K1\n");
			kill(m+1, SIGCONT);
			kill(m+2, SIGCONT);
			kill(m+3, SIGCONT);
			break;

			case 2:
			printf("Wznowilem K2\n");
			kill(m+1, SIGCONT);
			kill(m+2, SIGCONT);
			kill(m+3, SIGCONT);
			break;

			case 3:
			printf("Wznowilem K3\n");
			kill(m+1, SIGCONT);
			kill(m+2, SIGCONT);
			kill(m+3, SIGCONT);
			break;
		
		}
		break;


}
}


wait();
return 0;

}
