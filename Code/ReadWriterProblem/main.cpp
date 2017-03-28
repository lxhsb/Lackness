#include <iostream>
#include <unistd.h>
#include <thread>
#include <semaphore.h>
#include <vector>

using namespace std ;
class RWLock
{
private:
    sem_t rmutex ;
    sem_t wmutex;
    sem_t door ;
    int readerCount ;
public :
    RWLock() ;
    void RLock();
    void RUnLock();
    void WLock();
    void WUnLock();
};
RWLock::RWLock() {
    readerCount = 0 ;
    sem_init(&rmutex,0,1);
    sem_init(&wmutex,0,1);
    sem_init(&door,0,1);

}
void RWLock::RLock() {
    sem_wait(&door);
    sem_wait(&rmutex);
    if(readerCount == 0 )
    {
        sem_wait(&wmutex);
    }
    readerCount++ ;
    sem_post(&rmutex);
    sem_post(&door);
}
void RWLock::RUnLock() {
    sem_wait(&rmutex);
    readerCount -- ;
    if(readerCount == 0)
    {
        sem_post(&wmutex);
    }
    sem_post(&rmutex);

}
void RWLock::WLock() {

    sem_wait(&door);
    sem_wait(&wmutex);
}

void RWLock::WUnLock() {

    sem_post(&door);
    sem_post(&wmutex);
}

void reader(RWLock *lock,int i)
{

    printf("%d is going to read \n",i);
    lock->RLock();
    printf("%d reading \n",i);
    sleep(2);
    printf("%d read finish  \n",i);
    lock->RUnLock();


}
void writer(RWLock *lock ,int i )
{

    printf("%d is going to write \n",i);
    lock->WLock();
    printf("%d  writing \n",i);
    sleep(2);
    printf("%d write finish \n",i);
    lock->WUnLock();

}
int main() {
    vector<thread*>v ;
    RWLock lock ;
    for(int i = 0 ;i< 100 ;i++)
    {
        if(i%5 == 0 )
        {
            v.push_back(new thread(writer,&lock,i));
        }
        else
        {
            v.push_back(new thread(reader,&lock,i));
        }
    }
    for(auto x : v)
    {
        x->join();
    }

    return 0;
}