#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include "a2_helper.h"

int flag = 0;
int time_c = 0;
int cnt=0;
int f14 = 0;
int done14 = 0;
int start14 = 0;
pthread_t th4[43];
sem_t *sem_w, *sem_r, *sem, *sem54, *sem53, *sem14, *sem14b;
/*void syn(sem_t *sem, int n)
{
    sem_wait(sem);
    if(n == 14)
    {

        sem_wait(sem_r);
        sem_wait(sem_r);
        sem_wait(sem_r);
        sem_wait(sem_r);
        sem_wait(sem_r);
        sem_wait(sem_r);

    }

    sem_wait(sem_w);
    info(BEGIN, 4, n);
    sem_post(sem_w);
}
void rec(sem_t *sem, int n)
{
    if(n == 14)
    {
        info(END, 4, n);

        sem_post(sem_r);
        sem_post(sem_r);
        sem_post(sem_r);
        sem_post(sem_r);
    }
    else
    {
        sem_wait(sem_r);
        info(END, 4, n);
        sem_post(sem_r);
    }
    sem_post(sem);
}
*/
void* thread_5_function(void* arg)
{
    int* n = (int*) arg;
	
    if(*n == 3)
    	sem_wait(sem53);
    		
    info(BEGIN, 5, *n);
    	
    info(END, 5, *n);
    
    if(*n == 4)
    	sem_post(sem54);

    return 0;
}

void* thread_4_function(void* arg)
{
    int* n = (int*) arg;

    /*syn(sem, *n);

    rec(sem, *n);*/
	sem_wait(sem);
	
	if(*n == 14)
	{
	
		sem_wait(sem_r);
		
		start14 = 1;
		

		
		info(BEGIN, 4, 14);
		
		int val;
		sem_getvalue(sem, &val);
		if(val != 0)
		sem_trywait(sem14b);

		info(END, 4, 14);
		
		done14 = 1;
		
		
		sem_post(sem14);
		sem_post(sem14);
		sem_post(sem14);
		sem_post(sem14);
		sem_post(sem14);
		//sem_post(sem14);
		sem_post(sem_r);
		
		
	}
	
	else if(start14 && !done14)
	{
		int val;
		sem_getvalue(sem, &val);
		
		info(BEGIN, 4, *n);
		
		if(val == 0)
			{
			printf("\nOK\n");
			sem_post(sem14b);
			}
			
		sem_wait(sem14);
		//pthread_join(th4[13], NULL);
		info(END, 4, *n);
	}else
	{

    info(BEGIN, 4, *n);
    	
    sem_wait(sem_r);
    info(END, 4, *n);
    sem_post(sem_r);
    
	}
	sem_post(sem);
	
    return 0;
}

void* thread_3_function(void* arg)
{
    int* n = (int*) arg;
    	
    if(*n == 1)
    	sem_wait(sem54);
    	
    info(BEGIN, 3, *n);
    	
    if(*n == 3)
        while(flag == 0)
        {
            time_c ++;
        }
    	
    info(END, 3, *n);
    
    if(*n == 1)
    	sem_post(sem53);
    	
    return 0;
}
int main()
{
    init();
    info(BEGIN, 1, 0);
    //pid_t pid1 = getpid();
    //printf("PROCESS 1 : %d\n", pid1);
    pid_t pid2 = fork();
    if(pid2 == 0)
    {
        info(BEGIN, 2, 0);
        pid_t pid3 = fork();
        if(pid3 == 0)
        {
            info(BEGIN, 3, 0);
            sem53 = sem_open("/semafor53", O_CREAT, 0600, 0);
            sem54 = sem_open("/semafor54", O_CREAT, 0600, 0);
            pthread_t th3[4];
            int *n;
            n = malloc(sizeof(int));
            *n = 1;
            pthread_create(&th3[0], NULL, thread_3_function, n);
            pthread_join(th3[0], NULL);
            n = malloc(sizeof(int));
            *n = 3;
            pthread_create(&th3[1], NULL, thread_3_function, n);
            n = malloc(sizeof(int));
            *n = 2;
            while(time_c < 1000)
            {

            }
            pthread_create(&th3[3], NULL, thread_3_function, n);
            pthread_join(th3[3], NULL);
            flag = 1;
            pthread_join(th3[1], NULL);
            n = malloc(sizeof(int));
            *n = 4;
            pthread_create(&th3[2], NULL, thread_3_function, n);
            pthread_join(th3[2], NULL);
            pid_t pid4 = fork();
            if(pid4 > 0)
            {
                //printf("PROCESS 4 : %d %d\n", pid4, getpid());
                pid_t pid6 = fork();
                if(pid6 > 0)
                {
                    //printf("PROCESS 6 : %d %d\n", pid6, getpid());
                    waitpid(pid6, NULL, 0);
                }
                else if(pid6 == 0)
                {
                    info(BEGIN, 6, 0);

                    info(END, 6, 0);
                    exit(0);
                }
                waitpid(pid4, NULL, 0);
            }
            else if(pid4 == 0)
            {
                info(BEGIN, 4, 0);
                //pthread_t th4[43];
                sem = sem_open("/semafor0", O_CREAT | O_EXCL, 0600, 6);
                sem14 = sem_open("/semafor14", O_CREAT | O_EXCL, 0600, 0);
                sem14b = sem_open("/semafor14b", O_CREAT | O_EXCL, 0600, 0);
                sem_w = sem_open("/semaforw", O_CREAT | O_EXCL, 0600, 6);
                sem_r = sem_open("/semaforr", O_CREAT | O_EXCL, 0600, 1);

                int *n;
                for(int i = 0; i < 43; i ++)
                {
                    /*while(cnt > 5)
                    {
                    }*/
                    n = malloc(sizeof(int));
                    *n = i + 1;
                    pthread_create(&th4[i], NULL, thread_4_function, n);
                }
                for(int i = 0; i < 43; i ++)
                    pthread_join(th4[i], NULL);
                pid_t pid7 = fork();
                if(pid7 > 0)
                {
                    //printf("PROCESS 7 : %d %d\n", pid7, getpid());
                    waitpid(pid7, NULL, 0);
                }
                else if(pid7 == 0)
                {
                    info(BEGIN, 7, 0);

                    info(END, 7, 0);
                    exit(0);
                }
                info(END, 4, 0);
                exit(0);
            }
            info(END, 3, 0);
            exit(0);
        }
        else if (pid3 > 0)
        {
            //printf("PROCESS 3 : %d %d\n", pid3, getpid());
            pid_t pid5 = fork();
            if(pid5 > 0)
            {
                //printf("PROCESS 5 : %d %d\n", pid5, getpid());
                waitpid(pid2, NULL, 0);
                waitpid(pid3, NULL, 0);
                waitpid(pid5, NULL, 0);
            }
            else if(pid5 == 0)
            {
                info(BEGIN, 5, 0);
		sem54 = sem_open("/semafor54", O_CREAT, 0600, 0);
		sem53 = sem_open("/semafor53", O_CREAT, 0600, 0);
		pthread_t th5[5];
		for(int i = 0; i < 5; i ++)
		{
		int* id = malloc(sizeof(int));
		*id = i + 1;
		pthread_create(&th5[i], NULL, thread_5_function, id);
		}
		
		for(int i = 0; i < 5; i ++)
		pthread_join(th5[i], NULL);
                info(END, 5, 0);
                exit(0);
            }
        }
        info(END, 2, 0);
        exit(0);
    }
    else if (pid2 > 0)
    {
        waitpid(pid2, NULL, 0);
    }
	
	sem_unlink("/semafor0");
    sem_unlink("/semaforw");
    sem_unlink("/semaforr");
    sem_unlink("/semafor53");
    sem_unlink("/semafor54");
    sem_unlink("/semafor14");
    sem_unlink("/semafor14b");
    info(END, 1, 0);
    return 0;
}
