#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;

int sgn(int x) {
    if(!x) return 0;
    return x>0 ? 1 : -1;
}

int incr(int x) {
    if(x>0) return x+1;
    return x-1;
}

bool canConvert(const string& b, const string& t) {
    int diff=0;
    for(int i=0;i<b.size();++i)
        if(b[i]!=t[i])
            ++diff;
    return diff==1;
}

int solution(string begin, string target, vector<string> words) {
    if(find(words.begin(),words.end(),target)==words.end())
        return 0;
    
    int n=words.size();
    map<string,int> c;
    queue<string> q;
    
    q.push(begin); c[begin]=1;
    q.push(target); c[target]=-1;
    
    while(!q.empty()) {
        string here=q.front();
        q.pop();
        for(int i=0;i<n;++i) {
            string there=words[i];
            if(canConvert(here,there)) {
                map<string,int>::iterator it=c.find(there);
                if(it==c.end()) {
                    c[there]=incr(c[here]);
                    q.push(there);
                }
                else if(sgn(c[there])!=sgn(c[here]))
                    return abs(c[there])+abs(c[here])-1;
            }
        }
    }
    return 0;
}

int main()
{
    string begin="hit", end="cog";
    vector<string> words;
    for(int i=0;i<5;++i)
    {
        string s;
        cin>>s;
        words.push_back(s);
    }
    cout<<solution(begin,end,words);
    return 0;
}
