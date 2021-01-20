package com.example.myapplication

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import androidx.appcompat.app.AlertDialog
import saito.DataBase
import saito.JogDB
import saito.Operation
import java.util.*
import saito.*

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
        val db = JogDB()    //データベースアクセス用のインスタンス生成

        when (view.id) {
            R.id.button_passchange -> {
                //idとそれに対応するメアドをデータベースから入手して
                val dataInsert = db.sendMsg(DataBase.USER_TABLE.id, Operation.SELECT.id, str1)
                //idとメアドが正しいか調べて
                val flag2 :Boolean
                if(dataInsert.mail_address == str2){
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
                    val dataInsert = db.sendMsg(DataBase.USER_TABLE.id, Operation.SELECT.id, id)
                    val dataInsert = db.sendMsg(DataBase.USER_TABLE.id, Operation.INSERT.id, dataInsert.id + "\nlogin_name\n"+ dataInsert.pass
                            +"\nname\n"+dataInsert.weight+"\n"+dataInsert.height+"\n"+dataInsert.age+"\n"+dataInsert.sex+"\n"+dataInsert.birth+"\n"+dataInsert.goal_weight+"\n"+dataInsert.goal_term+"\n"+str2)
                    //ログイン画面へ
                    val intent = Intent(this, Login::class.java)
                    startActivity(intent)
                } else if(flag2 == false && dataInsert.mail_address == str2) {
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