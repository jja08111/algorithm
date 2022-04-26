class Solution {
    private fun generateCombination(
        total: String,
        part: String,
        countMap: MutableMap<String, Int>,
        start: Int,
        count: Int,
        n: Int,
    ) {
        if (count == n) {
            countMap[part] = if (countMap[part] == null) 1 else countMap.getValue(part) + 1  
            return
        }
        for (i in start until total.length) {
            generateCombination(total, part + total[i], countMap, i + 1, count + 1, n)
        }
    }

    private fun createAnswer(countMap: Map<String, Int>, course: IntArray): Array<String> {
        var answer = arrayOf<String>()
        val sortedCountList =
            countMap.toList().sortedWith(compareBy({ it.first.length }, { -it.second }))

        for (i in course) {
            var beforeOrderMaxCount = 2
            for (j in sortedCountList.indices) {
                val order = sortedCountList[j].first
                val count = sortedCountList[j].second

                if (order.length == i && beforeOrderMaxCount <= count) {
                    beforeOrderMaxCount = count.coerceAtLeast(beforeOrderMaxCount)
                    answer = answer.plus(order)
                }
            }
        }
        answer.sort()
        return answer
    }

    fun solution(orders: Array<String>, course: IntArray): Array<String> {
        val countMap = mutableMapOf<String, Int>()

        for (order in orders) {
            val part = ""
            val sortedOrder = order.toSortedSet().joinToString("")

            for (len in course) {
                generateCombination(sortedOrder, part, countMap, 0, 0, len)
            }
        }
        
        return createAnswer(countMap, course)
    }
}
