# 해결
### 1. LIS
이 문제를 보면 가장먼저 LIS문제가 떠오른다.

이전에 만든 코드는 각각의 시작위치에서의 lis를 cache에 저장했다.

이 방법은 어떤 index의 lis가 어떻게 되는지 알 수 없다.
### 2. 응용
살짝 코드를 바꿔서 증가부분수열이 아닌 감소부분수열로 변경했다.(line:14)

그리고 반대쪽에서 같은 방법으로 작동하는 함수를 만들었다.

마지막으로 두개의 cache를 더한 값중 가장 큰값에 1을 빼주면 된다.

# 회고
코드를 더 깔끔하게 할 수 있을 것 같은데 좋은 생각이 떠오르질 않는다.
