// 必要に応じてサーバ上のDBからユーザ情報をリクエストし、表示する
package com.example.omanco

// AppCompactActivityは、support library action barの機能を使ったactivityベースのクラス？
import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import java.io.IOException
//
import java.io.*
import java.net.Socket
import java.nio.ByteBuffer
import java.nio.charset.StandardCharsets
import java.util.*
import java.util.logging.Level
import java.util.logging.Logger
import kotlin.concurrent.thread
import kotlin.system.exitProcess

// レイアウトファイルにあるレイアウトのidを指定して読み込み
//val linearLayout = findViewById(R.id.LinearLayout_UI_OCE) as LinearLayout

// CheckUserInfoクラスは、AppcompatActivityクラスを継承している
// AppCompatActivityクラスは、画面制御の基本的な機能を提供している
// その中のonCreateメソッドは、アクティビティが起動されたときに呼び出される
// そのメソッドのさらに中のsetContentViewは、画面に表示するビューの設定
class CheckUserInfo : AppCompatActivity() {
    private fun runUserSelect(db: JogDB): User {
        // サーバ接続
        try {
            val recvData = db.userSelect("0") // ユーザデータがrecvDataに
//            bufferedReader.close()
            return recvData
        } catch (e: IOException) {
            println("IOExceptionだよう。")
            exitProcess(1)
        } catch (e: Exception) {
            println("Exceptionだよ。")
            exitProcess(0)
        }
    }
    override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            setContentView(R.layout.activity_user)  // レイアウトファイルの読み込み
        thread {
            // テキストボックス内に表示させる内容
            val db = JogDB()
/*
            val file = File("strage")
            val bufferedReader = file.bufferedReader()
*/
//        val ID = bufferedReader.readLine()
            val intent: Intent = getIntent()
            val id1: String = intent.extras?.getString("ID", "a") ?:""
            val ID = id1
//            bufferedReader.close()
            val aa = runUserSelect(db) // どうにか持ってこよう
            val Name: String = aa.name
            var Sex: String = aa.sex
            val Shincho: String = aa.height
            val num1 = Shincho.toDouble()
            val Taiju: String = aa.weight
            val num2 = Taiju.toDouble()
            //
            val Birth: String = aa.birth // 誕生日
            val Age: String = aa.age
            val GoalWeight: String = aa.goalWeight
            val num3 = GoalWeight.toDouble()
            val GoalMade: Double = num2 - num3
            val mokuhyoMade = GoalMade.toString()
            val GoalPeriod: String = aa.goalTerm
            val BMI = num2 / Math.pow(num1 / 100, 2.0)
            //
            when(Sex) {
                "1" -> {
                    Sex = "男性"
                }
                "0" -> {
                    Sex = "女性"
                }
            }
            //
            val userName = findViewById<TextView>(R.id.edit_UserName_OCE) as TextView
            userName.setText(Name)
            val userSex = findViewById<TextView>(R.id.edit_UserSex_OCE) as TextView
            userSex.setText(Sex)
            val userHeight = findViewById<TextView>(R.id.edit_UserHeight_OCE) as TextView
            userHeight.setText(Shincho)
            val userWeight = findViewById<TextView>(R.id.edit_UserWeight_OCE) as TextView
            userWeight.setText(Taiju)
            val userBMI = findViewById<TextView>(R.id.edit_UserBMI_OCE) as TextView
            userBMI.setText(BMI.toString())
            val userID = findViewById<TextView>(R.id.edit_UserID_OCE) as TextView
            userID.setText(ID)
            //
            val userBirth = findViewById<TextView>(R.id.edit_UserBirth_OCE) as TextView
            userBirth.setText(Birth)
            val userAge = findViewById<TextView>(R.id.edit_UserAge_OCE) as TextView // 年齢
            userAge.setText(Age)
            val userGoalWeight = findViewById<TextView>(R.id.edit_UserGoalWeight_OCE) as TextView
            userGoalWeight.setText(GoalWeight)
            val userGoalMade = findViewById<TextView>(R.id.edit_UserGoalMade_OCE) as TextView
            userGoalMade.setText(mokuhyoMade)
            val userGoalPeriod = findViewById<TextView>(R.id.edit_UserGoalPeriod_OCE) as TextView
            userGoalPeriod.setText(GoalPeriod)

            // button.setOnClickListenerでクリックイベントを取得
            val button1 = findViewById<Button>(R.id.button_CheckUserInfo_OCE)
            button1.setOnClickListener(buttonClick)
        }
    }

    private val buttonClick = View.OnClickListener { view ->
        when (view.id) { // idに対応して処理を変える。
            // MainActivityのところを変えると、そこに画面遷移をする。
            // Intent intent = new Intent(this, ::class.java)で画面指定
            // startActivity(intent)で、画面を開く
            R.id.button_CheckUserInfo_OCE -> {
                val intent = Intent(this, ChangeUserInfo::class.java)
                // ここに、結果を反映させる処理を書く。
                val intent1: Intent = getIntent()
                val id1: String = intent1.extras?.getString("ID", "a") ?:""
                intent.putExtra("ID", id1)
                //
                startActivity(intent)
            }
/* else -> { val intent = Intent(this, StartJogging::class.java) */
        }
    }
}