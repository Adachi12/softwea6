
import java.net.Socket
import java.nio.*
//import saito.*
import java.io.*

// import com.example.saito
// (テーブル名, 操作) とか (テーブル名, 操作, データ)
// テーブル名を4つ左にシフト、もしくは16倍

enum class DataBase(val id: Int) {
    CALORIE_TABLE(0x00),
    SAVED_ROUTE_TABLE(0x10),
    USEDLOG_TABLE(0x20),
    USER_TABLE(0x30),
    PASSWORD(0x40)
}

enum class Operation(val id: Int) {
    SELECT(0x00),
    UPDATE(0x01),
    INSERT(0x02),
    PASSWORD(0x03)
}

fun main(args: Array<String>) {
    var errnu: Int
    var recvBuf: String
    val db = JogDB()

    //errnu = db.sendMsg("Hello")
    //println(errnu)

    recvBuf = db.recvMsg()
    println(recvBuf)
}

class JogDB : Socket("ec2-54-90-205-238.compute-1.amazonaws.com", 60000, null, 0) {
    private val request_stream: OutputStream = this.getOutputStream()
    private val response_stream: InputStream = this.getInputStream()
    private val buf_size: Int = 1024

    // 引数3つ
    fun sendMsg(table: Int, operation: Int, data: String): Int {
        // val hed = (table shl 4) + operation
        val hed = table + operation
        val msg: String = hed.toString() + "\n" + data
        val charset = Charsets.UTF_8
        val byteArray = msg.toByteArray(charset)

        try {
            request_stream.write(byteArray)
        } catch (e: IOException) {
            return 1
        }

        return 0
    }

    // 引数2つ
    fun sendMsg(table: Int, operation: Int): Int {
        // val hed = (table shl 4) + operation
        val hed = table + operation
        val msg: String = hed.toString()
        val charset = Charsets.UTF_8
        val byteArray = msg.toByteArray(charset)

        try {
            request_stream.write(byteArray)
        } catch (e: IOException) {
            return 1
        }

        return 0
    }

    fun recvMsg() : String {
        val charset = Charsets.UTF_8
        var resp_buf = ByteArray(buf_size) { 0 }

        try {
            response_stream.read(resp_buf, 0, buf_size)
        } catch (e: IOException) {
            return ""
        }

        return resp_buf.toString(charset)
    }
}