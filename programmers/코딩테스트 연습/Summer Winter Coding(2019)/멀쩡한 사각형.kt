class Solution {
    fun gcd(a: Long, b: Long): Long = if (b == 0L) a else gcd(b, a % b)

    fun solution(w: Int, h: Int): Long {
        val lw = w.toLong()
        val lh = h.toLong()
        return lw * lh - (lw + lh - gcd(lw, lh))
    }
}
