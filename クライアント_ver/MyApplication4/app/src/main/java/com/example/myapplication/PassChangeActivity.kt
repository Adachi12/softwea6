package com.example.myapplication

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity

//import com.example.saito

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
        //val db = jogDB()    //データベースアクセス用のインスタンス生成

        when (view.id) {
            R.id.button_passchange -> {
                //idとそれに対応するメアドをデータベースから入手して

                //idとメアドが正しいか調べて

                //正しければ適切なパスワードかチェックして
                val flag2: Boolean = isCheckInput(str3)

                //適切ならデータベースにUPDATEして
                if (flag2 == true) {
                    //パスワード更新

                    //ログイン画面へ
                    val intent = Intent(this, Login::class.java)
                    startActivity(intent)
                } else {
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