import java.util.*

class Solution {
    companion object {
        val DIR = arrayOf(0 to 1, 1 to 0, 0 to -1, -1 to 0)
    }

    fun inRange(y: Int, x: Int): Boolean {
        return y in 0..4 && x in 0..4
    }

    fun hasDist(board: Array<String>, y: Int, x: Int): Boolean {
        val queue: Queue<Pair<Pair<Int, Int>, Int>> = LinkedList()
        val discovered = Array(5) { Array(5) { false } }
        queue.add(y to x to 0)
        discovered[y][x] = true

        while (queue.isNotEmpty()) {
            val top = queue.poll()!!
            val cy = top.first.first
            val cx = top.first.second
            val dist = top.second

            if (dist > 2) {
                return true
            } else if (dist > 0 && board[cy][cx] == 'P') {
                return false
            }

            for (i in 0 until 4) {
                val ny = DIR[i].first + cy
                val nx = DIR[i].second + cx

                if (inRange(ny, nx) && !discovered[ny][nx] && board[ny][nx] != 'X') {
                    discovered[ny][nx] = true
                    queue.add(ny to nx to (dist + 1))
                }
            }
        }
        return true
    }

    fun solution(places: Array<Array<String>>): IntArray {
        var answer: IntArray = intArrayOf()

        places.forEach { board ->
            var ok = true

            for ((y, line) in board.withIndex()) {
                for ((x, ch) in line.withIndex()) {
                    if (ch == 'P') {
                        val result = hasDist(board, y, x)
                        if (!result) {
                            ok = false
                            break
                        }
                    }
                }
                if (!ok) break
            }
            answer += if (ok) 1 else 0
        }

        return answer
    }
}
