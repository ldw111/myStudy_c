#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>


using namespace std;

class Test
{
public:
	static Test *instance();
	pthread_t tid[3];
	virtual ~Test()
	{
		cout << "************";
	}
	static int a;
	static void *thr_fn1(void *arg);
	static void *thr_fn2(void *arg);
private:
	Test() {};
	static Test *p_thiz;
};

Test *Test::p_thiz = NULL;
int Test::a = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

Test *Test::instance()
{
	if(p_thiz == NULL)
	{
		if(p_thiz == NULL)
		{
			p_thiz = new Test;
	
		}
	}
	return p_thiz;
}

void *Test::thr_fn1(void *arg)
{
	for(int i = 0;i < 10000;i++)
	{
		pthread_mutex_lock(&mutex);
		a++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void *Test::thr_fn2(void *arg)
{
	return NULL;
}

int main(int argc,char *argv[])
{/*
	Test *p = Test::instance();
	pthread_create(&p->tid[0],NULL,p->thr_fn1,NULL);
	pthread_create(&p->tid[1],NULL,p->thr_fn1,NULL);
	pthread_join(p->tid[0],NULL);
	pthread_join(p->tid[1],NULL);
	cout << p->a << endl;*/
	/*time_t t = time(NULL);
	struct tm *_tm_;
	_tm_ = localtime(&t);
	cout << _tm_->tm_sec << endl;*/
	pid_t pid;
	cout << "hello" << endl;
	cout << "world!";
	pid = fork();
	cout << endl;
	if(pid > 0)
	{
		wait(NULL);
		printf("parent");
	}
	else
	{
		printf("child");
		exit(1);
		//return 1;
	}
    cout << endl;
	return 0;
}
