// Lab 6 written by Caleb Latimer ej1297
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
using namespace std;

void *first(void *);
void *second(void *);

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; // thread1 mutex
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER; // thread2 mutex

int x = 19530; // global var that is being manipulated

int main() {
    cout << "x = " << x << endl << endl;
    int t1, t2;
    pthread_t thread1, thread2;
    pthread_mutex_lock(&mutex2);
    if((t1 = pthread_create( &thread1, NULL, first, NULL))) {
        printf("Thread creation failed: %d\n", t2);
    }

    if((t2 = pthread_create( &thread2, NULL, second, NULL))) {
        printf("Thread creation failed: %d\n", t2);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return(0);
  }

void *first(void *){ // function for thread1
  for(int i = 1; i <=5; i++){
  pthread_mutex_lock(&mutex1);
  x = x-5;
  cout << "Iteration " << i <<endl;
  cout << "Thread1: x = " << x << endl;
  pthread_mutex_unlock(&mutex2);
  }
}

void *second(void *){ // function for thread2
  for(int i = 1; i<=5; i++){
  pthread_mutex_lock(&mutex2);
  x = x/5;
  cout << "Thread2: x = " << x << endl << endl;
  pthread_mutex_unlock(&mutex1);
  }
}
