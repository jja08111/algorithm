# 해결
### 1. 직관적 해결
직관적으로 이 문제를 접근하면 재귀함수로 구현 할 수 있다.  
재귀함수를 passedTime일때 here번 곡이 재생될 확률을 반환하게 만든다.  
이 함수는 시간, 공간복잡도 문제에 걸려서 답이 될 수 없다.

### 2. 슬라이딩 윈도우 기법 이용
곡당 시간이 최대 4분이므로 sliding window기법을 이용하기 적당하다.  
하지만 이는 시간복잡도 문제를 해결할 수 없다.

### 3. 행렬의 거듭제곱 이용
https://jaimemin.tistory.com/387 

# 회고
행렬을 이용하는 방법은 피보나치가 한계이다.  
이해하기 위해서 복습이 필요하다.
