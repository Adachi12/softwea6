package com.example.myapplication
//package saito

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.RadioButton
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import java.util.*
import kotlin.concurrent.thread

//入力項目ごとに字数制限とかをつけんと、害悪利用者によって破壊されるかも
class AccountRegister : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_accountregister)
        Thread(Runnable {
            val button1 = findViewById<Button>(R.id.button_accountregister)
            button1.setOnClickListener(buttonClick)
            val radioButton1 = findViewById<RadioButton>(R.id.sex_man_accountregister)
            radioButton1.setOnClickListener(buttonClick)
            val radioButton2 = findViewById<RadioButton>(R.id.sex_woman_accountregister)
            radioButton2.setOnClickListener(buttonClick)
        }).start()
    }

    private val buttonClick = View.OnClickListener { view ->
        //val db = jogDB()    //データベースアクセス用のインスタンス生成
        var userId: String = "a"
        when (view.id) {
            R.id.sex_man_accountregister -> {
                val radioButton1 = findViewById<RadioButton>(R.id.sex_man_accountregister)
                val checked = radioButton1.isChecked
                if (checked) {
                    // 1つ目のRadioButtonが選択された時の処理
                    val radioButton2 = findViewById<RadioButton>(R.id.sex_woman_accountregister)
                    radioButton2.isChecked = false  //2つ目のボタンの選択解除
                }
            }
            R.id.sex_woman_accountregister -> {
                val radioButton1 = findViewById<RadioButton>(R.id.sex_woman_accountregister)
                val checked = radioButton1.isChecked
                if (checked) {
                    // 2つ目のRadioButtonが選択された時の処理
                    val radioButton2 = findViewById<RadioButton>(R.id.sex_man_accountregister)
                    radioButton2.isChecked = false //1つ目のボタンの選択解除
                }
            }
            R.id.button_accountregister -> {

                try{

                    val editText1 = findViewById<View>(R.id.editTextNumber_weight_accountregister) as EditText  //体重
                    val editText2 = findViewById<View>(R.id.editTextNumber_height_accountregister) as EditText  //身長
                    val editText3 = findViewById<View>(R.id.editTextNumber_year_accountregister) as EditText    //生年月日
                    //val editText4 = findViewById<View>(R.id.editTextID) as EditText             //ID
                    val editText5 = findViewById<View>(R.id.editTextPassword_accountregister) as EditText       //Password
                    val editText6 = findViewById<View>(R.id.editTextEmailAddress_accountregister) as EditText   //メアド
                    val editText7 = findViewById<View>(R.id.editTextNumber_GoalWeight_accountregister) as EditText       //目標体重
                    val editText8 = findViewById<View>(R.id.editTextNumber_GoalTime_accountregister) as EditText   //目標期間
                    val str1 = editText1.text.toString()
                    val str2 = editText2.text.toString()
                    val str3 = editText3.text.toString()//生年月日
                    //val str4 = editText4.text.toString()
                    val str5 = editText5.text.toString()//Password
                    val str6 = editText6.text.toString()//メアド
                    val str7 = editText7.text.toString()
                    val str8 = editText8.text.toString()//目標期間
                    val num1 = str1.toDouble()//体重
                    val num2 = str2.toDouble()//身長
                    val num3 = str7.toDouble()//目標体重
                    val radioButton1 = findViewById<RadioButton>(R.id.sex_woman_accountregister)
                    val radioButton2 = findViewById<RadioButton>(R.id.sex_man_accountregister)
                    val flag :Boolean = isCheckInput(num1, num2, str3, str5, str6, num3, str8)

                    if(flag == true && (radioButton1.isChecked == true || radioButton2.isChecked == true)) {

                        thread {
                            //DataBaseへ送信してから(年齢について...生年月日は必要なく年齢だけでいいのか→年、月、日を送るそう)
                            var sex = ""
                            if(radioButton1.isChecked == true){ //性別について
                                sex = "0"       //女性
                            } else {
                                sex = "1"       //男性
                            }
                            //年齢について
                            val calendar: Calendar = Calendar.getInstance(TimeZone.getTimeZone("Asia/Tokyo"), Locale.JAPAN);
                            val nowYear: Int = calendar.get(Calendar.YEAR) //現在の西暦を入手
                            val age1: Int = nowYear - str3.substring(0, 4).toInt()
                            val age: String = age1.toString()
                            //birth(生年月日)について
                            val birth: String = str3.substring(0, 4) + "-" + str3.substring(4, 6) + str3.substring(0, 4) + "-" + str3.substring(6, 8)
                            //GoalTerm(目標期間)
                            val goalTerm: String = str8.substring(0, 4) + "-" + str8.substring(4, 6) + "-" + str8.substring(6, 8)

                            val db = JogDB()
                            // 送信データ用意
                            val sendData = User().create()
                                    .setPass(str5)
                                    .setName("aaa")
                                    .setWeight(str1)
                                    .setHeight(str2)
                                    .setAge(age)
                                    .setSex(sex)
                                    .setBirth(birth)
                                    .setGoalTerm(goalTerm)
                                    .setGoalWeight(str7)
                                    .setMailAddress(str6)
                            println("sendData.toUpdateString() = " + sendData.pass)
                            // サーバ接続
                            // INSERT実行
                            userId = db.userInsert(sendData)
                            db.close()
                        }
                        Thread.sleep(1_000)

                        if ( userId.equals("a") ) {
                            //「登録が完了しました」のダイアログを出して
                            AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                                    .setTitle("登録失敗")
                                    .setMessage("登録に失敗しました．")
                                    .setPositiveButton("OK", { dialog, which ->
                                    })
                                    .show()
                        } else {
                            //「登録が完了しました」のダイアログを出して
                            AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                                    .setTitle("登録完了")
                                    .setMessage("登録が完了しました。\nメールアドレスはパスワード変更の際に利用します。\nあなたのIDは" + userId + "です。\nIDは次回からのログインに利用します。")
                                    .setPositiveButton("OK", { dialog, which ->
                                        // OKが押されたら
                                        //ログインしてジョギング開始モジュールに進む

                                         val intent = Intent(this, HomeMap2::class.java)
                                        // 渡したいデータとキーを指定する
                                        val intent1: Intent = getIntent()
                                        val id1: String = intent1.extras?.getString("ID", "a") ?:""
                                        intent.putExtra("ID", id1)
                                               startActivity(intent)

                                    })
                                    .show()
                        }

                    } else if((radioButton1.isChecked == false && radioButton2.isChecked == false)) {
                        //エラーを表示する(性別ボタンクリック無し)
                        AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                                .setTitle("Error")
                                .setMessage("性別が選択されていません。")
                                .setPositiveButton("OK", { dialog, which ->
                                    // OKが押された時の挙動
                                })
                                .show()
                    } else if(flag == false || (radioButton1.isChecked == false && radioButton2.isChecked == false)) {
                        //エラーを表示する(入力項目に不備有)
                        AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                                .setTitle("Error")
                                .setMessage("入力項目に不適切な入力があります。")
                                .setPositiveButton("OK", { dialog, which ->
                                    // OKが押された時の挙動
                                })
                                .show()
                    } else {
                        //error(詳細不明)
                        //エラーを表示する(入力項目に不備有)
                        AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                                .setTitle("Error")
                                .setMessage("予期せぬエラーが発生しました。")
                                .setPositiveButton("OK", { dialog, which ->
                                    // OKが押された時の挙動
                                })
                                .show()
                    }
                } catch(e: Exception){
                    //エラーを表示する(入力項目に不備有)
                    AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                            .setTitle("Error")
                            .setMessage("入力項目に不備があります。\n(または、サーバとの通信に失敗した可能性があります。)")
                            .setPositiveButton("OK", { dialog, which ->
                                // OKが押された時の挙動
                            })
                            .show()
                }
            }
        }
    }

    //入力項目が適切かチェックする関数
    private fun isCheckInput(weight: Double, height: Double, year: String, pass: String, mail: String, goalWeight: Double, goalTime: String): Boolean {
        try {
            val calendar: Calendar = Calendar.getInstance(TimeZone.getTimeZone("Asia/Tokyo"), Locale.JAPAN);
            val nowYear: Int = calendar.get(Calendar.YEAR) //現在の西暦を入手
            if (
                    0 < weight && weight < 1000                                                         //体重
                    && 50 < height && height < 300                                                      //身長
                    && 1900 < year.substring(0, 4).toInt() && year.substring(0, 4).toInt() <= nowYear   //年(生年月日)
                    && 0 < year.substring(4, 6).toInt() && year.substring(4, 6).toInt() < 13            //月(生年月日)
                    && 0 < year.substring(6, 8).toInt() && year.substring(6, 8).toInt() < 32            //日(生年月日)
                    && 0 < pass.length && pass.length < 33                                              //password
                    && 0 < mail.length && mail.length < 31                                              //mailaddres
                    && 0 < goalWeight && goalWeight < 1000                                              //目標体重
                    && nowYear < goalTime.substring(0, 4).toInt() && goalTime.substring(0, 4).toInt() <= 2500   //年(目標期間)
                    && 0 < goalTime.substring(4, 6).toInt() && goalTime.substring(4, 6).toInt() < 13            //月(目標期間)
                    && 0 < goalTime.substring(6, 8).toInt() && goalTime.substring(6, 8).toInt() < 32            //日(目標期間)
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