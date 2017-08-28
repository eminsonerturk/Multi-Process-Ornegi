#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *producer( void *ptr );
void *consumer( void *ptr );
int data;
int turn;
pthread_mutex_t mutex;
int main()
{
    pthread_t thread1, thread2;
    
    turn =0;
    const char *message1 = "Thread 1";
    const char *message2 = "Thread 2";
    int  iret1, iret2;
    pthread_mutex_init(&mutex,NULL);
    data =0;
    iret1 = pthread_create( &thread1, NULL, producer, (void*) message1);
    iret2 = pthread_create( &thread2, NULL, consumer, (void*) message2);
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
}
void *producer( void *ptr )
{
    int i =0;
    for(;;){
        pthread_mutex_lock(&mutex);
        if(turn == 0){
            data ++;
            i++;
            printf("producer %d \n",data);
            turn = 1;
            if(i==10){   pthread_mutex_unlock(&mutex); break; }
        }
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

void *consumer( void *ptr )
{
    int i =0;
    for(;;){
        pthread_mutex_lock(&mutex);
        if(turn == 1){
            data --;
            i++;
            printf("consumer %d \n",data);
            turn = 0;
            if(i==10){  pthread_mutex_unlock(&mutex); break; }
        }
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

