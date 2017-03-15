#include <iostream>
#include<string>
#include<cstring>
#include<vector>
#include<set>
#include<stack>
#include<queue>
#include<list>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<map>
#include<iomanip>
using namespace std;
#define whiel while
#define null NULL
#define eps 1e-8
#define INF 0x3f3f3f
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define read(x) scanf("%d",&x)
using namespace std ;
const int maxn = 1000+100 ;
int nxt[maxn];
void cal_nxt(string p)
{
    int l = p.size() ;
    int i = 0 ;
    int j =-1 ;
    memset(nxt,0,sizeof nxt);
    nxt[0]=-1;
    while(i<l)
    {
        if(j!=-1&&p[i]!=p[j])
        {
            j = nxt[j];
        }
        else
            {

                i++;
                j++;
                nxt[i]= j ;
            }



    }

}
int kmp_count(string m,string p)
{
    cout<<"main is "<<m<<" pattern is "<<p<<endl;
    int ans= 0 ;
    int m_len = m.size();
    int p_len = p.size();
    int i = 0,j = 0 ;
    while(i<m_len)
    {
        while(j != -1 && m[i]!=p[j])
        {

            j = nxt[j];
        }
        i++;
        j++;
        if(j>=p_len)
        {
            cout<<" end at "<<i<<endl;
            ans++ ;
            j =nxt[j];

        }
    }
    return ans;
}
int main()
{
	#ifndef ONLINE_JUDGE
	//freopen("/home/wyy/Desktop/input","r",stdin);
	#endif
	//ios::sync_with_stdio(false);
	string m , p ;//main pattern ;
	while(cin>>p>>m)
    {
        cal_nxt(p);
        for(int i = 0 ;i<p.size() ;i++)
        {

            cout<<nxt[i]+1<<" ";
        }
        cout<<endl;
        cout<<kmp_count(m,p)<<endl;

    }
    return 0 ;
}
