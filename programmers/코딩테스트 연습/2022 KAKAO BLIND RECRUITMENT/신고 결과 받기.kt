class Solution {
    fun solution(id_list: Array<String>, report: Array<String>, k: Int): IntArray {
        var answer: IntArray = intArrayOf()

        val reportedCount = mutableMapOf<String, Int>()
        val reporterListMap = mutableMapOf<String, ArrayList<String>>()

        report.forEach {
            val reporter = it.split(" ")[0]
            val responder = it.split(" ")[1]

            when {
                reporterListMap[reporter] == null -> reporterListMap[reporter] = arrayListOf(responder)
                // 중복 신고의 경우 무시한다.
                reporterListMap[reporter]!!.contains(responder) -> return@forEach
                else -> reporterListMap[reporter]!!.add(responder)
            }

            reportedCount[responder] =
                if (reportedCount[responder] == null) 1 else reportedCount.getValue(responder) + 1
        }

        id_list.forEach {
            var count = 0

            val reportList = reporterListMap[it]
            reportList?.forEach { responder ->
                if (reportedCount[responder] ?: -1 >= k) {
                    count++
                }
            }

            answer = answer.plus(count)
        }

        return answer
    }
}
