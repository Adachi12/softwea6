import java.io.IOException
import java.io.InputStream
import java.io.OutputStream
import java.net.Socket
import java.nio.ByteBuffer
import java.nio.charset.StandardCharsets
import java.util.*
import java.util.logging.Logger
import kotlin.system.exitProcess


internal class JogDB() {
    private val logger = Logger.getLogger(JogDB::class.java.name)
    private val socket = Socket("54.90.205.238", 60000, null, 0)
    private var sender: OutputStream? = null
    private var receiver: InputStream? = null
    private var sendBuffer: ByteArray
    private val recvBuffer: ByteArray
    fun close(): Boolean {
        try {
            sender!!.close()
            receiver!!.close()
            socket.close()
        } catch (e: IOException) {
            return false
        }
        return true
    }

    @Throws(IOException::class)
    fun calorieSelect(): Calorie {
        var recvStr: String?
        val recvData: Array<String>

        // init
        Arrays.fill(sendBuffer, 0.toByte())
        Arrays.fill(recvBuffer, 0.toByte())

        // create message
        sendBuffer[0] = 0xa0.toByte()

        // send message
        sender!!.write(sendBuffer)

        // receive message
        try {
            receiver!!.read(recvBuffer, 0, 1024)
        } catch (e: IOException) {
            logger.warning("Error! CALORIE_TABLE SELECT")
            return Calorie("?", "?")
        }

        // analyze message
        recvStr = String(recvBuffer, StandardCharsets.UTF_8)
        logger.info("receive String = $recvStr")
        recvStr!!.split("\n").toTypedArray().also { recvData = it }
        return Calorie(recvData[0], recvData[1])
    }

    @Throws(IOException::class)
    fun userUpdate(updateData: User): String {
        // init
        Arrays.fill(sendBuffer, 0.toByte())
        Arrays.fill(recvBuffer, 0.toByte())

        // Debug

        // create message
        val dataBytes = updateData.toUpdateString().toByteArray()
        val buf = ByteArray(2 + dataBytes.size)
        val joiner = ByteBuffer.wrap(buf)
        joiner.put(0xd1.toByte())
        joiner.put('\n'.toByte())
        joiner.put(dataBytes)
        sendBuffer = joiner.array()

        // send message
        sender!!.write(sendBuffer)

        // receive message
        try {
            receiver!!.read(recvBuffer, 0, 1024)
        } catch (e: IOException) {
            return "false"
        }

        // analyze message
        logger.info("receive String = ${String(recvBuffer, StandardCharsets.UTF_8)!!}")
        val recvStrArr: List<String> =
                String(recvBuffer, StandardCharsets.UTF_8)!!
                        .split("\n")
        return recvStrArr[0]
    }

    @Throws(IOException::class)
    fun userInsert(insertData: User): String {
        // init
        Arrays.fill(sendBuffer, 0.toByte())
        Arrays.fill(recvBuffer, 0.toByte())

        // create message
        val dataBytes = insertData.toInsertString().toByteArray()
        val buf = ByteArray(2 + dataBytes.size)
        val joiner = ByteBuffer.wrap(buf)
        joiner.put(0xd2.toByte())
        joiner.put('\n'.toByte())
        joiner.put(dataBytes)
        sendBuffer = joiner.array()

        // send message
        sender!!.write(sendBuffer)

        // receive message
        try {
            receiver!!.read(recvBuffer, 0, 1024)
        } catch (e: IOException) {
            logger.warning("Error : USER_TABLE INSERT")
            return ""
        }

        // analyze message
        val recvStrArr: List<String> =
                String(recvBuffer, StandardCharsets.UTF_8)!!
                        .split("\n")
        logger.info("receive String = ${String(recvBuffer, StandardCharsets.UTF_8)!!}")
        return recvStrArr[0]
    }

    @Throws(IOException::class)
    fun userSelect(userId: String): User {
        // init
        Arrays.fill(sendBuffer, 0.toByte())
        Arrays.fill(recvBuffer, 0.toByte())

        // create message
        val dataBytes = userId.toByteArray()
        val buf = ByteArray(2 + dataBytes.size)
        val joiner = ByteBuffer.wrap(buf)
        joiner.put(0xd0.toByte())
        joiner.put('\n'.toByte())
        joiner.put(dataBytes)
        sendBuffer = joiner.array()

        // send message
        sender!!.write(sendBuffer)

        // receive message
        try {
            val n = receiver!!.read(recvBuffer, 0, 1024)
        } catch (e: IOException) {
            return User().create()
        }

        // analyze message
        val recvStrArr: List<String> =
                String(recvBuffer, StandardCharsets.UTF_8)!!
                        .split("\n")
        logger.info("receive String = ${String(recvBuffer, StandardCharsets.UTF_8)!!}")
        return User().create()
                .setUserId(recvStrArr[0])
                .setPass(recvStrArr[1])
                .setName(recvStrArr[2])
                .setWeight(recvStrArr[3])
                .setHeight(recvStrArr[4])
                .setAge(recvStrArr[5])
                .setSex(recvStrArr[6])
                .setBirth(recvStrArr[7])
                .setGoalWeight(recvStrArr[8])
                .setGoalTerm(recvStrArr[9])
                .setMailAddress(recvStrArr[10])
    }

    fun usedlogInsert(insertData: UsedLog): String {
        // init
        Arrays.fill(sendBuffer, 0.toByte())
        Arrays.fill(recvBuffer, 0.toByte())

        // create message
        val dataBytes = insertData.toInsertString().toByteArray()
        val buf = ByteArray(2 + dataBytes.size)
        val joiner = ByteBuffer.wrap(buf)
        joiner.put(0xc2.toByte())
        joiner.put('\n'.toByte())
        joiner.put(dataBytes)
        sendBuffer = joiner.array()

        // send message
        sender!!.write(sendBuffer)

        // receive message
        try {
            receiver!!.read(recvBuffer, 0, 1024)
        } catch (e: IOException) {
            return ""
        }

        // analyze message
        val recvStrArr: List<String> =
                String(recvBuffer, StandardCharsets.UTF_8)!!
                        .split("\n")
        logger.info("receive String = ${String(recvBuffer, StandardCharsets.UTF_8)!!}")
        return recvStrArr[0]
    }

    @Throws(IOException::class)
    fun usedlogSelect(userId: String): MutableList<UsedLog> {
        // init
        Arrays.fill(sendBuffer, 0.toByte())
        Arrays.fill(recvBuffer, 0.toByte())

        // create message
        val dataBytes = userId.toByteArray()
        val buf = ByteArray(2 + dataBytes.size)
        val joiner = ByteBuffer.wrap(buf)
        joiner.put(0xc0.toByte())
        joiner.put('\n'.toByte())
        joiner.put(dataBytes)
        sendBuffer = joiner.array()

        // send message
        sender!!.write(sendBuffer)

        // receive message
        try {
            val recvStr = receiver!!.read(recvBuffer, 0, 1024)
        } catch (e: IOException) {
//            return UsedLog().create()
        }

        // analyze message
        val recvStrArr: List<String> =
                String(recvBuffer, StandardCharsets.UTF_8)!!
                        .split("]\n")

        val n: Int = recvStrArr[0].toInt()
        val recvDatasArr: MutableList<UsedLog> = mutableListOf(UsedLog())
        for (i in 1..n) {
            val recvDataArr: List<String> =
                    recvStrArr[i].split("\n")
            recvDatasArr.add(
                    UsedLog().create()
                            .setUserId(recvDataArr[0])
                            .setJogDatetime(recvDataArr[1])
                            .setJogDistance(recvDataArr[2])
                            .setJogTime(recvDataArr[3])
                            .setBurnedCalorie(recvDataArr[4])
            )
        }

        logger.info("receive String = ${String(recvBuffer, StandardCharsets.UTF_8)!!}")
        return recvDatasArr
    }

    init {
        try {
            sender = socket.getOutputStream()
            receiver = socket.getInputStream()
        } catch (e: IOException) {
            exitProcess(1)
        }
        sendBuffer = ByteArray(1024)
        recvBuffer = ByteArray(1024)
    }
}

internal class Calorie(val foodName: String, val foodCalorie: String) {
    override fun toString(): String {
        return """
            $foodName
            $foodCalorie
            """.trimIndent()
    }
}

internal class User {
    var userId = "?"
    var pass = "?"
    var name = "?"
    var weight = "?"
    var height = "?"
    var age = "?"
    var sex = "?"
    var birth = "?"
    var goalWeight = "?"
    var goalTerm = "?"
    var mailAddress = "?"
    fun create(): User {
        return User()
    }

    fun setUserId(id: String): User {
        userId = id
        return this
    }

    fun setPass(pass: String): User {
        this.pass = pass
        return this
    }

    fun setName(name: String): User {
        this.name = name
        return this
    }

    fun setWeight(weight: String): User {
        this.weight = weight
        return this
    }

    fun setHeight(height: String): User {
        this.height = height
        return this
    }

    fun setAge(age: String): User {
        this.age = age
        return this
    }

    fun setSex(sex: String): User {
        this.sex = sex
        return this
    }

    fun setBirth(birth: String): User {
        this.birth = birth
        return this
    }

    fun setGoalWeight(goalWeight: String): User {
        this.goalWeight = goalWeight
        return this
    }

    fun setGoalTerm(goalTerm: String): User {
        this.goalTerm = goalTerm
        return this
    }

    fun setMailAddress(mailAddress: String): User {
        this.mailAddress = mailAddress
        return this
    }

    fun toInsertString(): String {
        val sj = StringJoiner("\n")
        sj.add(pass)
                .add(name)
                .add(weight)
                .add(height)
                .add(age)
                .add(sex)
                .add(birth)
                .add(goalWeight)
                .add(goalTerm)
                .add(mailAddress)
        return sj.toString()
    }

    fun toUpdateString(): String {
        val sj = StringJoiner("\n")
        sj.add(userId)
                .add(pass)
                .add(name)
                .add(weight)
                .add(height)
                .add(age)
                .add(sex)
                .add(birth)
                .add(goalWeight)
                .add(goalTerm)
                .add(mailAddress)
        return sj.toString()
    }
}

internal class UsedLog {
    private var userId = "?"
    private var jog_datetime = "?"
    private var jog_distance = "?"
    private var jog_time = "?"
    private var burned_calorie = "?"

    fun create(): UsedLog {
        return UsedLog()
    }

    fun setUserId(userId: String): UsedLog {
        this.userId = userId
        return this
    }

    fun setJogDatetime(datetime: String): UsedLog {
        this.jog_datetime = datetime
        return this
    }

    fun setJogDistance(distance: String): UsedLog {
        this.jog_distance = distance
        return this
    }

    fun setJogTime(time: String): UsedLog {
        this.jog_time = time
        return this
    }

    fun setBurnedCalorie(calorie: String): UsedLog {
        this.burned_calorie = calorie
        return this
    }

    fun toInsertString(): String {
        val sj = StringJoiner("\n")
        sj.add(userId)
                .add(jog_datetime)
                .add(jog_distance)
                .add(jog_time)
                .add(burned_calorie)
        return sj.toString()
    }
}