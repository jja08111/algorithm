#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector<vector<int> > adj;
vector<int> discovered, sccId;
stack<int> st;
int sccCounter, vertexCounter;

// 두 구간 a와 b가 서로 겹치지 않는지를 확인한다.
bool disjoint(const pair<int,int>& a, const pair<int,int>& b)
{
    return a.second<=b.first || b.second<=a.first;
}

// meetings[]가 각 팀이 하고 싶어하는 회의 시간의 목록일 때,
// 이를 2-SAT 문제로 변환한 뒤 함의 그래프를 생성한다.
// i번 팀은 meetings[2*i] 혹은 meetings[2*i+1] 중 하나 시간에 회의실을 써야 한다.
void makeGraph(const vector<pair<int,int> >& meetings)
{
    int vars=meetings.size();
    // 그래프는 각 변수마다 두 개의 정점을 갖는다.
    adj.clear(); adj.resize(vars*2);
    for(int i=0;i<vars;i+=2)
    {
        // 각 팀은 i번 회의나 j번 회의 둘 중 하나는 해야 한다.
        // (i or j) 절을 추가한다.
        int j=i+1;
        adj[i*2+1].push_back(j*2); // ~i -> j
        adj[j*2+1].push_back(i*2); // ~j -> i
        adj[i*2].push_back(j*2+1); // i -> ~j
        adj[j*2].push_back(i*2+1); // j -> ~i
    }
    for(int i=0;i<vars;++i)
        for(int j=0;j<i;++j)
        {
            // i번 회의와 j번 회의가 서로 겹칠 경우
            if(!disjoint(meetings[i],meetings[j]))
            {
                // i번 회의가 열리지 않거나, j번 회의가 열리지 않아야 한다.
                // (~i or ~j) 절을 추가한다.
                adj[i*2].push_back(j*2+1); // i -> ~j
                adj[j*2].push_back(i*2+1); // j -> ~i
            }
        }
}

int scc(int here)
{
    int ret=discovered[here]=vertexCounter++;
    st.push(here);
    for(int i=0;i<adj[here].size();++i)
    {
        int there=adj[here][i];
        if(discovered[there]==-1)
            ret=min(ret,scc(there));
        else if(sccId[there]==-1)
            ret=min(ret,discovered[there]);
    }
    if(ret==discovered[here])
    {
        while(true)
        {
            int t=st.top();
            st.pop();
            sccId[t]=sccCounter;
            if(t==here) break;
        }
        sccCounter++;
    }
    return ret;
}

vector<int> tarjanSCC()
{
    discovered=sccId=vector<int>(adj.size(),-1);
    sccCounter=vertexCounter=0;
    for(int i=0;i<adj.size();++i)
        if(discovered[i]==-1)
            scc(i);
    
    return sccId;
}

// adj에 함의 그래프의 인접 리스트 표현이 주어질 떄, 2-SAT 문제의 답을 반환한다.
vector<int> solve2SAT()
{
    int n=adj.size(); // 변수의 수
    // 함의 그래프의 정점들을 SCC 별로 묶는다.
    vector<int> label=tarjanSCC();
    // 이 SAT 문제를 푸는 것이 불가능한지 확인한다. 한 변수를 나타내는 두 정점이
    // 같은 강결합 요소에 속해있을 경우 답이 없다.
    for(int i=0;i<n;i+=2)
        if(label[i]==label[i+1])
            return vector<int>();
    
    // SAT 문제를 푸는 것이 가능하다. 답을 생성하자.
    vector<int> value(n,-1);
    // tarjan 알고리즘에서 SCC 번호는 위상정렬의 역순으로 배정된다.
    // SCC 번호의 역순으로 각 정점을 정렬하면 위상 정렬 순서가 된다.
    vector<pair<int,int> > order;
    for(int i=0;i<n;++i)
        order.push_back(make_pair(-label[i],i));
    sort(order.begin(), order.end());
    
    // 각 정점에 값을 배정한다.
    for(int i=0;i<n;++i)
    {
        int vertex=order[i].second;
        int variable=vertex/2, isTrue=(vertex%2==0);
        if(value[variable]!=-1)
            continue;
        // ~A가 A보다 먼저 나왔으면 A는 참
        // A가 ~A보다 먼저 나왔으면 A는 거짓 
        value[variable]=!isTrue;
    }
    return value;
}

int main(void)
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int n;
        cin>>n;
        
        vector<pair<int,int> > meetings(2*n);
        for(int i=0;i<n;++i)
        {
            int a,b,c,d;
            cin>>a>>b>>c>>d;
            meetings[2*i]=make_pair(a,b);
            meetings[2*i+1]=make_pair(c,d);
        }
        
        makeGraph(meetings);
        vector<int> ret=solve2SAT();
        
        if(ret.empty())
        {
            cout<<"IMPOSSIBLE"<<endl;
            continue;
        }
        cout<<"POSSIBLE"<<endl;
        for(int i=0;i<n*2;++i)
            if(ret[i])
                cout<<meetings[i].first<<" "<<meetings[i].second<<endl;
    }
    return 0;
}
