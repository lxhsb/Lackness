#include <iostream>
#include<semaphore.h>
#include <unistd.h>
#include <thread>
using namespace std ;
sem_t writer ;//写等待 0有 1没
sem_t reader ;//读等待 0有 1 没
void doRead(int cnt )
{
    cout<<cnt<<" is going to read"<<endl;
    sem_wait(&writer);//w--
    sem_post(&reader);//r++
    cout<<cnt <<" is reading"<<endl;
    sleep(5);
    cout<<cnt<<" read finish"<<endl;
    sem_wait(&reader);//r--
    sem_post(&writer);//w++
}
void doWrite(int cnt)
{

    cout<<cnt<<" is going to write"<<endl;
    sem_wait(&writer);
 //   sem_wait(&reader);
    cout<<cnt <<" is writing"<<endl;
    sleep(5);
    cout<<cnt<<" write finish"<<endl;
    sem_post(&writer);
}
int main() {
    for(int i = 0 ;i<10 ;i++)
    {
        if(i%3)
        {
            thread x(writer,i);
        }
        else
        {
            thread x(reader,i);
        }
    }

    return 0;
}