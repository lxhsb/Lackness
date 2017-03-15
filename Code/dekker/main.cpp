#include <bits/stdc++.h>
#include <thread>
void print(std::string x )
{
    for(int i = 0 ;i<3 ;i++)
    {
        std::cout<<"it is "<<x<<" now "<<std::endl;
    }
}
bool flag[2];
volatile int turn ;
void t0_func()
{
    int time = 0 ;
    while(time++<10)
    {
        flag[0]=1 ;//我要进入
        while(flag[1])//你也想进去
        {
            if(turn)//如果该你了
            {
                flag[0]= 0;//我就先不进去了
                while(turn==1 )//等你
                {
                    //do nothing
                }
                flag[0]=1;//我该进去了
            }
        }
        print("t0");//临界区
        turn =1 ;//该你了
        flag[0]= false;//我出去了
    }
}
void t1_func()
{
    int time = 0 ;
    while(time++<10)
    {
        flag[1]=1 ;
        while(flag[0])
        {
            if(turn == 0 )
            {
                flag[1] = 0 ;
                while(turn == 0 )
                {
                }
                flag[1]=1;
            }
        }
        print("t1");
        turn = 0 ;
        flag[1] = 0 ;
    }
}
int main()
{
    std::thread t0(t0_func),t1(t1_func);
    t0.join();
    t1.join();




    return 0;
}