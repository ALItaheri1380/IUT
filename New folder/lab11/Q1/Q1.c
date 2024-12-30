#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_SIZE 4
#define MAX_THREAD 3
int arr_1[MAX_SIZE]; int arr_2[MAX_SIZE] , result = 0;
pthread_mutex_t mutex;   


void* routine(void* args){
    int thread_num = *(int*)args;
    int f = thread_num * (MAX_SIZE/MAX_THREAD) , l = (thread_num + 1) * (MAX_SIZE/MAX_THREAD); 
    if (l > MAX_SIZE || thread_num == MAX_THREAD - 1) l = MAX_SIZE + 1;

    int* res = malloc(sizeof(int)); *res = 0;
    for(int i = f ; i < l ; i++) *res += arr_1[i]*arr_2[i];
    
    pthread_mutex_lock(&mutex);
    result += *res; 
    pthread_mutex_unlock(&mutex);
    free(args);
    pthread_exit((void*)res);
}

int main(){
    pthread_t th[MAX_THREAD];
    pthread_mutex_init(&mutex, NULL);

    printf("plz enter the values of array 1 : \n");
    for(int i = 0; i < MAX_SIZE; i++) scanf("%d",&arr_1[i]);
    printf("plz enter the values of array 2 : \n");
    for(int i = 0; i < MAX_SIZE; i++) scanf("%d",&arr_2[i]);

    for(int i=0 ; i<MAX_THREAD; i++){
        int *arg = malloc(sizeof(int));
        *arg = i;
        pthread_create(&th[i],NULL,routine,arg);
    }
    
    for (int i = 0; i < MAX_THREAD; i++) pthread_join(th[i],NULL);

    printf("\n%d\n", result);

    pthread_mutex_destroy(&mutex);
    return 0;
}
