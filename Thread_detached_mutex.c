/*esercizio thread – mutex: thread genera 10 thread detached, i thread secondario aumentano di 1 la variabile globale e terminano, quando la varg globale è 9 si deve eliminare*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

#define N 10

int VAR = 0; //buffer
pthread_mutex_t mutex;

void *f(void *arg){
    printf("\nThread here, incrementing VAR...");
    while(1){ //volendo si può anche togliere il while
        pthread_mutex_lock(&mutex); //si blocca fino a quando non entra
        VAR=VAR+1;
        printf("\nVAR = %d ",VAR);
        pthread_mutex_unlock(&mutex);
        pthread_exit(EXIT_SUCCESS);
    }
}    


int main(){
    pthread_t thread[N];
    int res;

    pthread_mutex_init(&mutex,0);
    printf("\nMutex inizializzato, creo i %d thread",N);
    for(int i=0;i<N;i++){
        res=pthread_create(thread[i],detachstate,f,NULL); //creo direttamente detached i thread
        if(res!=0){
            perror("Create fail");
            exit(EXIT_FAILURE);
        }

    }

    if(VAR==9){
        sleep(1);
        pthread_mutex_lock(&mutex);
        printf("\nVAR = %d Finisco ",VAR);
        pthread_mutex_unlock(&mutex);
        pthread_mutex_destroy(&mutex);
        exit(EXIT_SUCCESS);
    }

}