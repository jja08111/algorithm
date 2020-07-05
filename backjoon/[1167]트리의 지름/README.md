# 해결 
## 1. set 이용 
첫 번째 시도는 "알고리즘 문제 해결 전략"에 나온 문제 '요새'의 코드를 응용하였다.  
트리의 지름은 잎-잎의 거리와 루트-잎의 거리 중 더 큰값이므로 set<int>를 이용하여 별도의 정렬을 거치지 않고 문제를 해결했다.  
```c++
const int MAX=100001;

// adj[here]=(there,dist)
vector<pair<int,int> > adj[MAX];
bool visited[MAX];
// 잎과 잎 사이의 거리 중 가장 긴 값
int longest=0;

int getDiameter(int here)
{
    visited[here]=true;
    
    set<int> heights;
    for(int i=0;i<adj[here].size();++i)
    {
        int cand=adj[here][i].first;
        int dist=adj[here][i].second;
        if(!visited[cand])
        {
            heights.insert(dist+getDiameter(cand));
        }
    }
    
    if(heights.empty())
        return 0;
        
    set<int>::iterator it=heights.end();
    int back = *(--it);
    if(heights.size()>=2)
    {
        int back2 = *(--it);
        longest=max(longest,back+back2);
    }
    return back;
}

int main()
{
    int n;
    cin>>n;
    
    for(int i=0;i<n;++i)
    {
        int here;
        cin>>here;
        while(true)
        {
            int there, dist;
            
            scanf("%d",&there);
            if(there==-1) 
                break;
            scanf("%d",&dist);
            
            adj[here].push_back(make_pair(there,dist));
        }
    }
    
    //잎-잎 거리와 루트-잎 거리 중 더 큰 값을 출력
    int h=getDiameter(1);
    int ret=max(h,longest);
    cout<<ret;
    
    return 0;
}
```

## 2. 루트에서 가장 먼 점부터 찾아보자 
다른 방법으로는 루트에서 가장 먼 노드를 찾고 그 노드와 가장 멀리 떨어진 노드의 거리를 계산하면 트리의 지름을 구할 수 있다.   
```c++
int longest, farthestNode;

void getDiameter(int here, int dist)
{
    if(visited[here])
        return;
    
    visited[here]=true;
    if(longest<dist)
    {
        longest=dist;
        farthestNode=here;
    }
    
    for(int i=0;i<adj[here].size();++i)
    {
        int there=adj[here][i].first;
        int candDist=adj[here][i].second;
        getDiameter(there,candDist+dist);
    }
}

int main()
{
    int n;
    cin>>n;
    
    for(int i=0;i<n;++i)
    {
        int here;
        cin>>here;
        while(true)
        {
            int there, dist;
            
            scanf("%d",&there);
            if(there==-1) 
                break;
            scanf("%d",&dist);
            
            adj[here].push_back(make_pair(there,dist));
        }
    }
    // 루트에서 가장 먼 정점을 찾음
    longest=0;
    getDiameter(1,0);
    
    // 루트에서 가장 먼 정점과 가장 멀리 떨어진 정점과의 거리를 구한다.
    longest=0;
    memset(visited,false,sizeof(visited));
    getDiameter(farthestNode,0);
    cout<<longest;
    
    return 0;
}
```
