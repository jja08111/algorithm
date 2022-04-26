class Solution {
    private fun generateCombination(
        total: String,
        part: String,
        combination: MutableList<String>,
        start: Int,
        count: Int,
        n: Int,
    ) {
        if (count == n) {
            combination.add(part)
            return
        }
        for (i in start until total.length) {
            generateCombination(total, part + total[i], combination, i + 1, count + 1, n)
        }
    }

    private fun createAnswer(countMap: Map<String, Int>, course: IntArray): Array<String> {
        var answer = arrayOf<String>()
        val sortedCountList =
            countMap.toList().sortedWith(compareBy({ it.first.length }, { -it.second }))

        for (i in course) {
            var beforeOrderMaxCount = 2
            for (j in sortedCountList.indices) {
                val item = sortedCountList[j].first
                val count = sortedCountList[j].second

                if (item.length == i && beforeOrderMaxCount <= count) {
                    beforeOrderMaxCount = count.coerceAtLeast(beforeOrderMaxCount)
                    answer = answer.plus(item)
                }
            }
        }
        answer.sort()
        return answer
    }

    fun solution(orders: Array<String>, course: IntArray): Array<String> {
        val countMap = mutableMapOf<String, Int>()
        val combinations = mutableListOf<String>()

        for (order in orders) {
            val part = ""
            val sortedOrder = order.toCharArray().sorted().joinToString("")

            for (len in course) {
                generateCombination(sortedOrder, part, combinations, 0, 0, len)
            }
        }

        for (element in combinations) {
            countMap[element] = if (countMap[element] == null) 1 else countMap.getValue(element) + 1
        }

        return createAnswer(countMap, course)
    }
}
