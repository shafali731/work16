#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

int main(){
  key_t key;
  int shmid;
  char * data;

  key = ftok(".", 'R');
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  data = shmat(shmid, (void *)0, 0);

  if(data[0]){
      printf("Content:\n%s\n",data);
  	}
  	else
  	{
      printf("The segment was just created! No data in it,\n");
  	}

  printf("Do you want to change the data in the segment?? y/n \n");

  char * response = malloc(2);
  fgets(response, 200, stdin);

  if (response[0] == 'y'){
      printf("Please enter a new string: ");
    //  fflush(stdout);
      fgets(response, 200, stdin);
      strcpy(data, response);
    }

    if(data[0]){
        printf("Content:\n%s\n",data);
      }

  printf("Do you want to clear that? y/n \n");
  fgets(response, 200, stdin);


  if (response[0] == 'y'){
    shmctl(shmid, IPC_RMID, NULL);
  }
  return 0;
}
