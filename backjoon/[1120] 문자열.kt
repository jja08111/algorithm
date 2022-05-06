import java.util.*

fun main() = with(Scanner(System.`in`)) {
    val input = nextLine().split(" ")
    val a = input[0]
    val b = input[1]
    var ret = 987654321

    for (i in 0..(b.length - a.length)) {
        var count = 0
        for (bIdx in i until (i + a.length)) {
            val aIdx = bIdx - i
            if (a[aIdx] != b[bIdx]) {
                count++
            }
        }
        ret = minOf(ret, count)
    }
    println(ret)
}

