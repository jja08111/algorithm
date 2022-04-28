class Solution {
    fun solution(s: String): Int {
        var answer = s.length

        for (level in 1..(s.length / 2)) {
            val sb = StringBuilder()
            var lo = 0
            while (lo <= s.length - level) {
                val hi = lo + level
                val pivot = s.substring(lo, hi)
                var nextLo = lo + level
                var count = 1

                while (nextLo <= s.length - level) {
                    val nextHi = nextLo + level
                    val next = s.substring(nextLo, nextHi)
                    if (next == pivot) {
                        count++
                        nextLo += level
                    } else {
                        break
                    }
                }
                if (count >= 2) {
                    sb.append(count)
                }
                sb.append(s.substring(lo, lo + level))
                lo = nextLo
                if (lo > s.length - level) {
                    sb.append(s.substring(lo, s.length))
                }
            }
            answer = answer.coerceAtMost(sb.length)
        }

        return answer
    }
}
