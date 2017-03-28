#include <iostream>
#include <unistd.h>
#include <thread>
#include <semaphore.h>
#include <vector>

using namespace std ;
class RWLock
{
private:
    sem_t mutex ;
    sem_t db ;
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
    sem_init(&mutex,0,1);
    sem_init(&db,0,1);

}
void RWLock::RLock() {
    sem_wait(&mutex);
    readerCount++;
    if(readerCount == 1)
    {
        sem_wait(&db);
    }
    sem_post(&mutex);
}
void RWLock::RUnLock() {
    sem_wait(&mutex);
    readerCount--;
    if(readerCount == 0)
    {
        sem_post(&db);
    }
    sem_post(&mutex);
}
void RWLock::WLock() {
    sem_wait(&db);
}

void RWLock::WUnLock() {
    sem_post(&db);
}

void reader(RWLock *lock,int i)
{
    printf("%d is going to read \n",i);
    lock->RLock();
    printf("%d reading \n",i);
    sleep(2);
    lock->RUnLock();
    printf("%d read finish  \n",i);

}
void writer(RWLock *lock ,int i )
{
    printf("%d is going to write \n",i);
    lock->WLock();
    printf("%d  writing \n",i);
    sleep(2);
    lock->WUnLock();
    printf("%d write finish \n",i);
}
int main() {
    vector<thread*>v ;
    RWLock lock ;
    for(int i = 0 ;i< 100 ;i++)
    {
        if(i%3 == 0 )
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