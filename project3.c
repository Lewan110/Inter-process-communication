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

int main(int argc, char *argv[]) {


char file_name[100];
int read_from_file,var,rng,urnd,value;
int my_pipe[2];
pipe(my_pipe);
FILE * file;
FILE *fp;
char hex[30];
int tab[1000];
int enter=0;
int i=0;
umask(0);
mkfifo(FIFO, 0666);
sleep(1);

int arg1 = atoi(argv[1]);
if (fork() == 0) {
		switch (arg1) {

		case 1:
			
			for (;;) {
			printf("Podaj  %d. liczbe\n", i + 1);
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
			printf("Podaj nazwe pliku \n");
			scanf("%99s", file_name);
			const char *txt = ".txt";
   			strcat(file_name, txt);
			if ((file = fopen(file_name, "r")) == NULL) {
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
			close(my_pipe[WRITE]);
			
			for(;;){
			read(my_pipe[READ], &hex, sizeof(hex)); 
			if(enter==5){enter=0;printf("\n");}
			fprintf( stderr, "k3: %s",hex);
			fflush(NULL);
			printf(" ");
			enter++;
			sleep(3);
			}
}
wait();
return 0;
}
