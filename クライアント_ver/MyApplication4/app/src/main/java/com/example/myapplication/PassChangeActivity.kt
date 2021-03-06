package com.example.myapplication

import User
import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity

class PassChangeActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_pass_change)
        val button1 = findViewById<Button>(R.id.button_passchange)
        button1.setOnClickListener(buttonClick)
    }

    private val buttonClick = View.OnClickListener { view ->
        val editText1 = findViewById<View>(R.id.editTextID_passchange) as EditText          //id
        val editText2 = findViewById<View>(R.id.editTextNewMail_passchange) as EditText     //メアド
        val editText3 = findViewById<View>(R.id.editTextNewPass_passchange) as EditText     //新しいパスワード
        val str1 = editText1.text.toString()
        val str2 = editText2.text.toString()
        val str3 = editText3.text.toString()
        var recvData: User = User().create()
        var flag2: Boolean

        /*
        Thread {
            val db = JogDB()    //データベースアクセス用のインスタンス生成
            try {
                // Select実行
                recvData = db.userSelect(str1)
            } catch (e: IOException) {
                exitProcess(1)
            } catch (e: Exception) {
                exitProcess(0)
            }
            db.close()
        }
         */

        when (view.id) {
            R.id.button_passchange -> {
                //idとそれに対応するメアドをデータベースから入手して

                //idとメアドが正しいか調べて
                if("a09319" == str2){
                    //正しければ適切なパスワードかチェックして
                    flag2 = isCheckInput(str3)
                } else {
                    flag2 = false
                    //不適切ならエラー表示
                    AlertDialog.Builder(this)
                            .setTitle("Error")
                            .setMessage("入力されたidが存在しません。\nまたは、メールアドレスが不適切です。")
                            .setPositiveButton("OK", { dialog, which ->
                                // OKが押された時の挙動
                            })
                            .show()
                }

                //適切ならデータベースにUPDATEして
                if (flag2 == true) {
                    //パスワード更新
                    /*
                    Thread {
                        val db = JogDB()    //データベースアクセス用のインスタンス生成
                        // 送信データ用意
                        val sendData = User().create()
                                .setUserId(str1)
                                .setPass(str3)
                                .setName(recvData.name)
                                .setWeight(recvData.weight)
                                .setHeight(recvData.height)
                                .setAge(recvData.age)
                                .setSex(recvData.sex)
                                .setBirth(recvData.birth)
                                .setGoalTerm(recvData.goalTerm)
                                .setGoalWeight(recvData.goalWeight)
                                .setMailAddress(recvData.mailAddress)
                        // サーバ接続
                        try {
                            // UPDATE実行
                            val result = db.userUpdate(sendData)
                        } catch (e: IOException) {
                            exitProcess(1)
                        }
                        db.close()
                    }
                     */
                    //ログイン画面へ
                    val intent = Intent(this, Login::class.java)
                    startActivity(intent)
                } else if(flag2 == false && recvData.mailAddress == str2) {
                    //不適切ならエラー表示
                    AlertDialog.Builder(this)
                            .setTitle("Error")
                            .setMessage("新しいパスワードが不適切です。")
                            .setPositiveButton("OK", { dialog, which ->
                                // OKが押された時の挙動
                            })
                            .show()
                }
            }

        }
    }

    //入力項目が適切かチェックする関数
    private fun isCheckInput(pass: String): Boolean {
        try {
            if (0 < pass.length && pass.length < 33){       //password
                return true
            } else {
                return false
            }
        } catch(e: Exception) {
            return false
        }
    }
}