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
#define FIFO "my_fifo_22"
#define FIFOPID "PID"

int main(int argc, char *argv[]) {


char nazwa_pliku[100];
int read_from_file,var,rng,urnd,value;
int my_pipe[2];
pipe(my_pipe);
FILE * file;
FILE *fp;
FILE *fp2;
char hex[30];
int tab[1000];
int enter=0;
int i=0;
umask(0);
mkfifo(FIFO, 0666);
mkfifo(FIFOPID, 0666);
int Process2;
int m = getpid(); 
fp2=fopen("pid.txt", "w");			
fprintf (fp2, "%d", m); 
fclose (fp2); 

printf("Proces macierzysty: %d\n", m);
int arg1 = atoi(argv[1]);


void M_end(int sig){
printf("\nJa tu tylko sprzatam\n");
//unlink(fp);
//kill(m, SIGQUIT);
}

void K1_kill(int sig) {
    printf("\notrzymalem sigusr-ginee\n");
    kill(m+2, SIGQUIT);
    kill(m+3, SIGQUIT);
    kill(m,SIGCONT);
    kill(m+1, SIGQUIT);
    
    
 

}
void K2_kill(int sig) {
printf("\notrzymalem sigusginer-ginee\n");
    kill(m+3, SIGQUIT);
    kill(m+1, SIGQUIT);
    kill(m,SIGCONT);
    kill(m+2, SIGQUIT);
    

}
void K3_kill(int sig) {
printf("\notrzymalem sigusr-ginee\n");
    kill(m+1, SIGQUIT);
    kill(m+2, SIGQUIT);
    kill(m,SIGCONT);
    kill(m+3, SIGQUIT);
    

}



void K1_sleep(int sig) {
  //  printf("\notrzymalem sigusr2-zasypiam\n");
    kill(m+2, SIGSTOP);
    kill(m+3, SIGSTOP);
    kill(m+1, SIGSTOP);
}

void K2_sleep(int sig) {
   // printf("\notrzymalem sigusr2-zasypiam\n");
    kill(m+3, SIGSTOP);
    kill(m+1, SIGSTOP);
    kill(m+2, SIGSTOP);
}

void K3_sleep(int sig) {
   // printf("\notrzymalem sigusr2-zasypiam\n");
    kill(m+1, SIGSTOP);
    kill(m+2, SIGSTOP);
    kill(m+3, SIGSTOP);
}

/*
void K1_wakeup(int sig) {
int static i=0;
do{
    //printf("\notrzymalem sigcont - budze sie\n");
    kill(m+2, SIGCONT);
    kill(m+3, SIGCONT);
i++;
}while(i<1);
}
void K2_wakeup(int sig) {
    //printf("\notrzymalem sigcont - budze sie\n");
int static i=0;
do{
    kill(m+1, SIGCONT);
    kill(m+3, SIGCONT);
i++;
}while(i<1);
}
void K3_wakeup(int sig) {
    //printf("\notrzymalem sigcont - budze sie\n");
int static i=0;
do{
    kill(m+1, SIGCONT);
    kill(m+2, SIGCONT);
i++;
}while(i<1);
}
*/
if (fork() == 0) {
signal(SIGUSR1, K1_sleep); 
signal(SIGUSR2, K1_kill);
//signal(SIGCONT, K1_wakeup);
		switch (arg1) {

		case 1:
			
			for (;;) {
			printf("Podaj: \n");
			scanf("%d[^\n]", &value);
			if(value==-1)break;
			tab[i]=value;
			i++;
			}
			i=0;
			for (;;) {
			fp = fopen(FIFO, "w");			
			fprintf(fp, "%d\n", tab[i]);
			fclose(fp);
			i++;
			sleep(3);
		}

			
		case 2:
			printf("Podaj nazwe pliku: \n");
			scanf("%99s", nazwa_pliku);
			const char *txt = ".txt";
   			strcat(nazwa_pliku, txt);
			if ((file = fopen(nazwa_pliku, "r")) == NULL) {
			printf("Plik nie istnieje\n");
			exit(1);
		} 
			else {
		
			while(1) {
				fscanf(file, "%d", &read_from_file);
				fp = fopen(FIFO, "w");			
				fprintf(fp, "%d\n", read_from_file);
				fclose(fp);
				sleep(3);
			
				
			}
			fclose(file);
			}
	
		case 3:
			for(;;){
			urnd = open("/dev/urandom", O_RDONLY);
			read(urnd, &rng, sizeof(int));
			//printf("K1 stworzylem %d\n", rng);
			fflush(NULL);
 			close(urnd);
			fp = fopen(FIFO, "w");			
			fprintf(fp, "%d\n", rng);
			fclose(fp);
 			sleep(3);
			}
		}
}
if (fork() == 0) {
signal(SIGUSR1, K2_sleep); 
signal(SIGUSR2, K2_kill);
//signal(SIGCONT, K2_wakeup);
			while(1){
				fp = fopen(FIFO, "r");
				fscanf(fp, "%d", &var);
				fclose(fp);
				//printf("K2 otrzymalem : %d\n", var);
				fflush(NULL);
				sprintf(hex, "%x", var);
				write(my_pipe[WRITE], &hex, sizeof(hex));
				//printf("K2 w. hex %s\n",hex);
				fflush(NULL);
				sleep(3);
				}
}

if (fork() == 0) {
signal(SIGUSR1, K3_sleep); 
signal(SIGUSR2, K3_kill);
//signal(SIGCONT, K3_wakeup);
			close(my_pipe[WRITE]);
			
			for(;;){
			read(my_pipe[READ], &hex, sizeof(hex)); 
			if(enter==5){enter=0;printf("\n");}
			fprintf( stderr, "%s",hex);
			fflush(NULL);
			printf(" ");
			fflush(NULL);
			enter++;
			sleep(3);
			}
}else{
	signal(SIGCONT, M_end);
	//kill(m, SIGSTOP);
}
wait();
return 0;
}
