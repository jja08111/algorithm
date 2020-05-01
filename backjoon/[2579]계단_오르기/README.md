# 해결
동적 계획법의 memoization, 재귀함수를 이용하였습니다.

# 회고
범위를 벗어나거나 연속으로 3개의 계단을 걸을때 음의 무한대의 수를 반환하지 않아서 틀렸었습니다. \n

if(consecutiveStep>=3 || here>n)
        return 0;
