# 해결
이 문제는 쉬운 그리디 문제입니다.  
시간이 적게 소요되는 사람을 먼저 인출하게 만들면 됩니다.  
- 중요한 점은 제일 먼저 인출하는 시간은 결과에 사람수 만큼 인출하는 시간이 더해집니다.  
- 따라서 현재 인출하는 시간과 뒤에 현재사람을 포함한 뒤에 남은 사람들의 수를 곱하여 계산해나갑니다.

위 방법을 이용하여 한번의 탐색만으로 답을 얻을 수 있습니다.  
```c++
int getMinTime()
{
    int ret=0;
    sort(withdrawTime.begin(),withdrawTime.end());
    for(int i=0;i<people_num;++i)
    {
        int multiply_num=people_num-i;
        ret+=multiply_num*withdrawTime[i];
    }
    return ret;
}

```
