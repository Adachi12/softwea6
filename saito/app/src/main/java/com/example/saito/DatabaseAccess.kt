package saito

import java.net.Socket
import java.nio.*
import java.io.*

// import saito.*
// close()

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
    ​
    //errnu = db.sendMsg("Hello")
    //println(errnu)
    ​
    recvBuf = db.recvMsg()
    println(recvBuf)
}

class CALORIE(val name: String, val calorie: String) {
    //println()
}

class USEDLOG(val date: String, val mileage: String, val time: String, val calorie: String) {
}

class USER(val id: String, val name: String, val weight: String, val height: String,
           val age: String, val sex: String, val birth: String, val goal_weight: String,
           val goal_term: String, val mail_address: String) {

}

​
class JogDB : Socket("ec2-54-90-205-238.compute-1.amazonaws.com", 60000, null, 0) {
    private val request_stream: OutputStream = this.getOutputStream()
    private val response_stream: InputStream = this.getInputStream()
    private val buf_size: Int = 1024
    ​
    // 引数3つ
    fun sendMsg(table: Int, operation: Int, data: String): Int {
        val hed = table + operation
        val msg: String = hed.toString() + "\n" + data
        val charset = Charsets.UTF_8
        val byteArray = msg.toByteArray(charset)
        ​
        try {
            request_stream.write(byteArray)
        } catch (e: IOException) {
            return 1
        }
        ​
        return 0
    }

    // 引数2つ
    fun sendMsg(table: Int, operation: Int): Int {
        val hed = table + operation
        val msg: String = hed.toString()
        val charset = Charsets.UTF_8
        val byteArray = msg.toByteArray(charset)
        ​
        try {
            request_stream.write(byteArray)
        } catch (e: IOException) {
            return 1
        }
        ​
        return 0
    }
    ​
    fun recvMsg() : Int {
        val charset = Charsets.UTF_8
        var resp_buf = ByteArray(buf_size) { 0 }
        ​
        try {
            response_stream.read(resp_buf, 0, buf_size)
        } catch (e: IOException) {
            return 1
        }

        return 0
    }

    fun recvMsgCalorie() : CALORIE {
        val charset = Charsets.UTF_8
        var resp_buf = ByteArray(buf_size) { 0 }
        ​
        try {
            response_stream.read(resp_buf, 0, buf_size)
        } catch (e: IOException) {
            return CALORIE("失敗","失敗")
        }

        val str = resp_buf.toString(charset)
        val str_list = str.split("\n")
        val resp_data = CALORIE(str_list.get(0), str_list.get(1))

        return resp_data
    }

    fun recvMsgUsedlog() : List<List<String>> {
        val charset = Charsets.UTF_8
        var resp_buf = ByteArray(buf_size) { 0 }
        ​
        try {
            response_stream.read(resp_buf, 0, buf_size)
        } catch (e: IOException) {
            return USEDLOG()
        }

        val recData: List<String> = resp_buf.toString().split("\n")
        var returnData: List<List<String>> =
                recData.map { it.split("\n").map{ it.removePrefix("[")} }
        returnData.map { it.map{println("$it\n")} }
        ​
        return returnData
    }

    fun recvMsgUser() : USER {
        val charset = Charsets.UTF_8
        var resp_buf = ByteArray(buf_size) { 0 }
        ​
        try {
            response_stream.read(resp_buf, 0, buf_size)
        } catch (e: IOException) {
            return USER("失敗", "失敗", "失敗", "失敗",
                    "失敗", "失敗", "失敗", "失敗",
                    "失敗", "失敗")
        }

        val str = resp_buf.toString(charset)
        val str_list = str.split("\n")
        val resp_data = USER(str_list.get(0), str_list.get(1), str_list.get(2), str_list.get(3),
                str_list.get(4), str_list.get(5), str_list.get(6), str_list.get(7),
                str_list.get(8), str_list.get(9))

        return resp_data
    }
}