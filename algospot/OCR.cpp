// 핵심만 정리하자면 크게 2가지 단계가 있다.
// 1. 조건부 확률 부분을 수식으로 만들어 최적화 하기
// 2. 재구성하기

// 1.
// 조건부 확률 P(원문Q|분류기가 인식한 문장R)을 최대화 하는 원문 Q를 찾아야 한다.
// 입력에서 원문이 Q일때 분류기가 R을 반환할 확률을 알 수 있다.
// 이를 이용하기 위해 베이즈 정리를 사용한다.
// P(Q|R)=P(R|Q)*P(Q)/P(R)
//
// P(R)은 모든 Q에 대해 같으므로 pass
// P(R|Q)는 원문이 Q일때 분류기가 R을 반환할 확률이니 M값을 이용하여 구할 수 있다.
//  (i=0~n-1)πM(Q[i],R[i])  
// M(a,b)는 a를 b로 분류할 확률이다.
// P(Q)는 문장이 원본일 확률이며 트릭을 이용해
// 첫번째 나타날 확률도 그전조각->다음조각 확률에 포함한다.
//
// 2.
// 재구성은 최적해를 구할때 어떤 단어를 선택했을때 확률이 높은지 기록하면 된다.

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int n,len;
int R[100];
double T[501][501];
double M[501][501];
int choice[102][502];
double cache[102][502];

// 현재단어 segment, 이전 단어 previousMatch 일때 최대확률
double recognize(int segment, int previousMatch)
{
    if(segment==len)
        return 0;
    
    double& ret=cache[segment][previousMatch];
    if(ret!=1.0)
        return ret;
    
    //음의 무한대
    ret=-1e200;
    int& choose=choice[segment][previousMatch];
    
    for(int thisMatch=1;thisMatch<=n;++thisMatch)
    {
        double cand=T[previousMatch][thisMatch]+M[thisMatch][R[segment]]+recognize(segment+1,thisMatch);
        if(ret<cand)
        {
            ret=cand;
            choose=thisMatch;
        }
    }
    return ret;
}

//입력받은 단어들의 목록
string corpus[501];

string reconstruct(int segment, int previousMatch)
{
    int choose=choice[segment][previousMatch];
    string ret=corpus[choose];
    if(segment<len-1)
        ret=ret+" "+reconstruct(segment+1,choose);
    return ret;
}

void initialize(int len)
{
    for (int i = 0; i < len; i++)
       for (int j = 0; j <= n; j++)
           cache[i][j] = 1.0;
}

int main(void)
{
    int m;
    
    cin>>n>>m;
    
    for(int i=1;i<=n;++i)
        cin>>corpus[i];
    
    // 가상의 시작단어를 이용하여 코드 간편화
    for(int i=1;i<=n;++i)
    {
        scanf("%lf",&T[0][i]);
        T[0][i]=log(T[0][i]);
    }
    
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
        {
            scanf("%lf",&T[i][j]);
            T[i][j]=log(T[i][j]);
        }
    
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
        {
            scanf("%lf",&M[i][j]);
            M[i][j]=log(M[i][j]);
        }
    
    for(int i=0;i<m;++i)
    {
        cin>>len;
        initialize(len);
        
        for(int i=0;i<len;++i)
        {
            string input;
            cin>>input;
            for(int j=1;j<=n;++j)
                if(input==corpus[j])
                {
                    R[i]=j;
                    break;
                }
        }
        recognize(0,0);
        cout<<reconstruct(0,0)<<endl;
    }
}
