package com.example.omanco

import android.app.AlertDialog
import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.RadioButton
import androidx.appcompat.app.AppCompatActivity
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

class ChangeUserInfo : AppCompatActivity() {
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
        setContentView(R.layout.activity_change_user)  // レイアウトファイルの読み込み

            // テキストボックス内に表示させる内容
            val Shincho: String = "148.9"
            val Taiju: String = "100.9"
            val GoalWeight: String = "78.8"
            val GoalPeriod: String = "18"
            //
            val userHeight = findViewById<EditText>(R.id.edit_UserHeight_Change_OCE) as EditText
            userHeight.setText(Shincho)
            val userWeight = findViewById<EditText>(R.id.edit_UserWeight_Change_OCE) as EditText
            userWeight.setText(Taiju)
            //
            val userGoalWeight = findViewById<EditText>(R.id.edit_UserGoalWeight_Change_OCE) as EditText
            userGoalWeight.setText(GoalWeight)
            val userGoalPeriod = findViewById<EditText>(R.id.edit_UserGoalPeriod_Change_OCE) as EditText
            userGoalPeriod.setText(GoalPeriod)

            // button.setOnClickListenerでクリックイベントを取得
            val button1 = findViewById<Button>(R.id.button_Determine_ChangeUserInfo_OCE)
            button1.setOnClickListener(buttonClick)
            val radio1 = findViewById<RadioButton>(R.id.radiobutton_UserChange_man_OCE)
            radio1.setOnClickListener(buttonClick)
            val radio2 = findViewById<RadioButton>(R.id.radiobutton_UserChange_woman_OCE)
            radio2.setOnClickListener(buttonClick)

    }

    private val buttonClick = View.OnClickListener { view ->
         when (view.id) { // idに対応して処理を変える。
             R.id.radiobutton_UserChange_man_OCE -> {
                 val radioButton1 = findViewById<RadioButton>(R.id.radiobutton_UserChange_man_OCE)
                 val checked = radioButton1.isChecked
                 if (checked) {
                     // 1つ目のRadioButtonが選択された時の処理
                     val radioButton2 = findViewById<RadioButton>(R.id.radiobutton_UserChange_woman_OCE)
                     radioButton2.isChecked = false  //2つ目のボタンの選択解除
                 }
             }
             R.id.radiobutton_UserChange_woman_OCE -> {
                 val radioButton1 = findViewById<RadioButton>(R.id.radiobutton_UserChange_woman_OCE)
                 val checked = radioButton1.isChecked
                 if (checked) {
                     // 2つ目のRadioButtonが選択された時の処理
                     val radioButton2 = findViewById<RadioButton>(R.id.radiobutton_UserChange_man_OCE)
                     radioButton2.isChecked = false //1つ目のボタンの選択解除
                 }
             }
             R.id.button_Determine_ChangeUserInfo_OCE -> {
//                 thread {
                 try {
                     var sex: String = "1" // 性別
                     val editText0 = findViewById<View>(R.id.edit_UserName_Change_OCE) as EditText    // 名前
                     val editText1 = findViewById<View>(R.id.edit_UserWeight_Change_OCE) as EditText  //体重
                     val editText2 = findViewById<View>(R.id.edit_UserHeight_Change_OCE) as EditText  //身長
                     val editText3 = findViewById<View>(R.id.edit_UserGoalWeight_Change_OCE) as EditText // 目標体重
                     val editText4 = findViewById<View>(R.id.edit_UserGoalPeriod_Change_OCE) as EditText // 目標期間の年
                     val editText5 = findViewById<View>(R.id.edit_UserGoalPeriod_Change_OCE2) as EditText // 目標期間の月
                     val editText6 = findViewById<View>(R.id.edit_UserGoalPeriod_Change_OCE3) as EditText // 目標期間の日
                     //
                     val str0 = editText0.text.toString()   // 名前
                     val str1 = editText1.text.toString()   // 体重
                     val str2 = editText2.text.toString()   // 身長
                     val str3 = editText3.text.toString()   // 目標体重
                     val str4 = editText4.text.toString()   // 目標期間の年
                     val str5 = editText5.text.toString()   // 目標期間の月
                     val str6 = editText6.text.toString()   // 目標期間の日
                     //
                     val num1 = str1.toDouble()
                     val num2 = str2.toDouble()
                     val num3 = str3.toDouble()
                     val num4 = str4.toInt()
                     val num5 = str5.toInt()
                     val num6 = str6.toInt()
                     val radioButton1 = findViewById<RadioButton>(R.id.radiobutton_UserChange_woman_OCE)
                     val radioButton2 = findViewById<RadioButton>(R.id.radiobutton_UserChange_man_OCE)
                     //
                     if (radioButton1.isChecked == true) { sex = "0" }
                     else if (radioButton2.isChecked == true) { sex = "1" }
                     val flag: Boolean = isCheckInput(num1, num2, num3, num4, num5, num6)
                     println("チェック前 $num1, $num2, $num3, $num4, $num5, $num6")
                         if (flag == true && (radioButton1.isChecked == true || radioButton2.isChecked == true)) {
                             //DataBaseへ送信してから(年齢について...生年月日は必要なく年齢だけでいいのか→年、月、日を送るそう)
                             println("チェック後 $num1, $num2, $num3, $num4, $num5, $num6")
                             var result: String = ""
                             thread {
                                 var db = JogDB()
                                 val aa = runUserSelect(db) // どうにか持ってこよう
                                 db.close()
                                 val Pass = aa.pass
                                 val Age = aa.age
                                 val Birth = aa.birth
                                 val MailAdd = aa.mailAddress
                                 // ここに、結果を反映させる処理を書く
                                 // 送信データ用意
                                 //
                                 // ID受け取り
                                 val intent: Intent = getIntent()
                                 val id1: String = intent.extras?.getString("ID", "a") ?: ""
                                 val ID = id1
                                 val sendData = User().create()
                                         .setUserId(ID)
                                         .setPass(Pass)         // パスワード
                                         .setName(str0)         // 0 名前
                                         .setWeight(str1)       // 1 体重
                                         .setHeight(str2)       // 2 身長
                                         .setAge(Age)           // 年齢
                                         .setSex(sex)           // 性別
                                         .setBirth(Birth)       // 誕生日
                                         .setGoalTerm(str4 + "-" + str5 + "-" + str6) // 年-月-日
                                         .setGoalWeight(str3)  // 3 目標体重
                                         .setMailAddress(MailAdd) // メアド

                                 // サーバ接続
                                 db = JogDB()
                                     // UPDATE実行
                                result = db.userUpdate(sendData)
                                     db.close()
                                }
                             Thread.sleep(1_000)  // wait for 1 second
                             println(result + "result")
                                     if (result.equals("true")) {
                                         AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                                                 .setTitle("変更完了")
                                                 .setMessage("ユーザ情報の変更が完了しました。")
                                                 .setPositiveButton("OK", { dialog, which ->
                                                     // OKが押されたら
                                                     // ユーザ情報確認へ飛ぶ(CheckUserInfo)
                                                     val intent = Intent(this, MainActivity::class.java)
                                                     //
                                                     val intent1: Intent = getIntent()
                                                     val id1: String = intent1.extras?.getString("ID", "a")
                                                             ?: ""
                                                     intent.putExtra("ID", id1)
                                                     //
                                                     startActivity(intent)
                                                 })
                                                 .show()
                                     } else {
                                         AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                                                 .setTitle("Error")
                                                 .setMessage("予期せぬエラーが発生しました。製造元にお問い合わせしてください。")
                                                 .setPositiveButton("OK", { dialog, which ->
                                                     // OKが押された時の挙動
                                                     val intent = Intent(this, CheckUserInfo::class.java)
                                                     startActivity(intent)
                                                 })
                                                 .show()
                                     }

                                 //「登録が完了しました」のダイアログを出して


                         } else if (flag == false || (radioButton1.isChecked == false && radioButton2.isChecked == false)) {
                             //エラーを表示する(入力項目に不備有)
                             println("elseの中 $num1, $num2, $num3, $num4, $num5, $num6")
                             AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                                     .setTitle("Error")
                                     .setMessage("入力項目に不備があります。")
                                     .setPositiveButton("OK", { dialog, which ->
                                         // OKが押された時の挙動
                                     })
                                     .show()
                         } else {
                             //error(詳細不明)
                             //エラーを表示する(入力項目に不備有)
                             AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                                     .setTitle("Error")
                                     .setMessage("予期せぬエラーが発生しました。製造元にお問い合わせしてください。")
                                     .setPositiveButton("OK", { dialog, which ->
                                         // OKが押された時の挙動
                                     })
                                     .show()
                         }
                     } catch (e: Exception){
                         //エラーを表示する(入力項目に不備有)
                         AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                                 .setTitle("Error")
                                 .setMessage("入力項目に不備があります。")
                                 .setPositiveButton("OK", { dialog, which ->
                                     // OKが押された時の挙動
                                 })
                                 .show()
                     }
                 }
         }
/* else -> { val intent = Intent(this, StartJogging::class.java) */
    }

    //入力項目が適切かチェックする関数
    private fun isCheckInput(weight: Double, height: Double, goalWeight: Double,
                             goalTerm_year: Int, goalTerm_month: Int, goalTerm_day: Int): Boolean {
        try {
            if (
                    0.0 < weight && weight < 1000.0                                                     // 体重
                    && 50.0 < height && height < 300.0                                                  // 身長
                    && 0.0 < goalWeight && goalWeight < 1000.0                                          // 目標体重
                    && 0 <= goalTerm_year && goalTerm_year <= 10000                                 // 目標期間の年
                    && 1 <= goalTerm_month && goalTerm_month <= 12                                  // 目標期間の月
                    && 1 <= goalTerm_day && goalTerm_day <= 31                                      // 目標期間の日
            ) {
                return true
            } else {
                return false
            }
        } catch(e: Exception) {
            return false
        }
    }
}
