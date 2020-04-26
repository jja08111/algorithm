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
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n,m;
int R[100];
double T[501][501];
double M[501][501];
int choice[102][502];
double cache[102][502];

double recognize(int segment, int previousMatch)
{
    if(segment==n)
        return 0;
    
    double& ret=cache[segment][previousMatch];
    if(ret!=1.0)
        return ret;
    
    ret=-1e200;
    int& choose=choice[segment][previousMatch];
    
    for(int thisMatch=0;thisMatch<m;++thisMatch)
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
