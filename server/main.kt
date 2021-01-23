import java.io.*
import java.net.Socket
import java.nio.ByteBuffer
import java.nio.charset.StandardCharsets
import java.util.*
import java.util.logging.Level
import java.util.logging.Logger
import kotlin.system.exitProcess

internal object Client {
    // ロガー構成
    val logger = Logger.getLogger(Client::class.java.name)

    // 受信データ初期化
    private var result = "false"
    private var userId: String = "00000000"

    // main function
    @JvmStatic
    fun main(args: Array<String>) {
        val db0 = JogDB(logger)
        testCalorieSelect(db0, logger)
        db0.close()

        val db1 = JogDB(logger)
        userId = testUserInsert(db1, logger)
        db1.close()

        val db2 = JogDB(logger)
        testUserUpdate(db2, logger)
        db2.close()

        val db3 = JogDB(logger)
        testUserSelect(db3, logger)
        db3.close()

        val db4 = JogDB(logger)
        testUsedlogInsert(db4, logger, userId)
        db4.close()
    }

    private fun testCalorieSelect(db: JogDB, logger: Logger) {
        // 受信データ初期化
        var calorieRecvData = Calorie("?", "?")

        // サーバ接続
        try {
            // SELECT実行
            calorieRecvData = db.calorieSelect()
        } catch (e: IOException) {
            logger.log(Level.WARNING, "Error : CALORIE SELECT")
            System.exit(1)
        }
        logger.log(Level.INFO, calorieRecvData.toString())
    }

    private fun testUserInsert(db: JogDB, logger: Logger): String {
        // 送信データ用意
        val sendData = User().create()
            .setPass("password")
            .setName("okamoto")
            .setWeight("65.0")
            .setHeight("178.0")
            .setAge("20")
            .setSex("1")
            .setBirth("2000-02-10")
            .setGoalTerm("2021-01-31")
            .setGoalWeight("68.0")
            .setMailAddress("220310b@ugs.kothi-tech.ac.jp")

        // サーバ接続
        try {
            // INSERT実行
            userId = db.userInsert(sendData)
        } catch (e: IOException) {
            logger.log(Level.WARNING, "Error : USER INSERT")
            exitProcess(1)
        }
        logger.log(Level.INFO, " = $userId")
        return userId
    }

    private fun testUserUpdate(db: JogDB, logger: Logger) {
        // 送信データ用意
        val sendData = User().create()
            .setUserId(userId)
            .setPass("new password")
            .setName("okamoto")
            .setWeight("66.0")
            .setHeight("177.5")
            .setAge("20")
            .setSex("1")
            .setBirth("2000-02-10")
            .setGoalTerm("2021-02-15")
            .setGoalWeight("68.0")
            .setMailAddress("220310b@ugs.kothi-tech.ac.jp")

        // サーバ接続
        try {
            // UPDATE実行
            result = db.userUpdate(sendData)
            logger.log(Level.INFO, result)
        } catch (e: IOException) {
            logger.log(Level.WARNING, "Error : USER UPDATE")
            exitProcess(1)
        }
    }

    private fun testUserSelect(db: JogDB, logger: Logger) {
        // サーバ接続
        try {
            // UPDATE実行
            val recvData = db.userSelect(userId)
            logger.log(Level.INFO, recvData.toInsertString())
        } catch (e: IOException) {
            logger.log(Level.WARNING, "Error : USER SELECT")
            exitProcess(1)
        } catch (e: Exception) {
            logger.log(Level.WARNING, "Error : USER SELECT")
            exitProcess(0)
        }
    }

    private fun testUsedlogInsert(db: JogDB, logger: Logger, userId: String): String {
        // 送信データ用意
        val sendData = UsedLog().create()
            .setUserId(userId)
            .setJogDatetime("2021-01-22")
            .setJogDistance("4.0")
            .setJogTime("00:15:40")
            .setBurnedCalorie("50")

        // サーバ接続
        try {
            // INSERT実行
            result = db.usedlogInsert(sendData)
        } catch (e: IOException) {
            logger.log(Level.WARNING, "Error : USER INSERT")
            exitProcess(1)
        }
        logger.log(Level.INFO, " = $userId")
        return result
    }
}

internal class JogDB(val logger: Logger) {
    private val socket = Socket("172.21.46.40", 60000, null, 0)
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
            return Calorie("?", "?")
        }

        // analyze message
        recvStr = String(recvBuffer, StandardCharsets.UTF_8)
        recvStr!!.split("\n").toTypedArray().also { recvData = it }
        return Calorie(recvData[0], recvData[1])
    }

    @Throws(IOException::class)
    fun userUpdate(updateData: User): String {
        // init
        Arrays.fill(sendBuffer, 0.toByte())
        Arrays.fill(recvBuffer, 0.toByte())

        // Debug
        logger.info("updateData = " + updateData.toUpdateString())

        // create message
        val dataBytes = updateData.toUpdateString().toByteArray()
        val buf = ByteArray(2 + dataBytes.size)
        val joiner = ByteBuffer.wrap(buf)
        joiner.put(0xd1.toByte())
        joiner.put('\n'.toByte())
        joiner.put(dataBytes)
        sendBuffer = joiner.array()

        // send message
        logger.info("send message length(USER UPDATE) = ${ sendBuffer.size.toString() }")
        sender!!.write(sendBuffer)

        // receive message
        try {
            receiver!!.read(recvBuffer, 0, 1024)
        } catch (e: IOException) {
            return "false"
        }

        // analyze message
        val recvStrArr: List<String> =
            String(recvBuffer, StandardCharsets.UTF_8)!!
            .split("\n")
        logger.info("server response(USER_TABLE UPDATE) = ${ recvStrArr[0] }")
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
            return ""
        }

        // analyze message
        val recvStrArr: List<String> =
            String(recvBuffer, StandardCharsets.UTF_8)!!
                .split("\n")
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
            logger.info("Read message : $n bytes")
        } catch (e: IOException) {
            return User().create()
        }

        // analyze message
        val recvStrArr: List<String> =
            String(recvBuffer, StandardCharsets.UTF_8)!!
                .split("\n")
        return User().create()
            .setUserId(recvStrArr[0])
            .setName(recvStrArr[1])
            .setWeight(recvStrArr[2])
            .setHeight(recvStrArr[3])
            .setAge(recvStrArr[4])
            .setSex(recvStrArr[5])
            .setBirth(recvStrArr[6])
            .setGoalWeight(recvStrArr[7])
            .setGoalTerm(recvStrArr[8])
            .setMailAddress(recvStrArr[9])
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
        return recvStrArr[0]
    }

    init {
        try {
            sender = socket.getOutputStream()
            receiver = socket.getInputStream()
        } catch (e: IOException) {
            logger.log(Level.WARNING, "Error : Connection")
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
    private var userId = "?"
    private var pass = "?"
    private var name = "?"
    private var weight = "?"
    private var height = "?"
    private var age = "?"
    private var sex = "?"
    private var birth = "?"
    private var goalWeight = "?"
    private var goalTerm = "?"
    private var mailAddress = "?"
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
