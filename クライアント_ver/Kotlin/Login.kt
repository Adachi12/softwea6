package com.example.myapplication

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import androidx.appcompat.app.AlertDialog
import java.util.*
//import com.example.saito

class Login : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)
        val button1 = findViewById<Button>(R.id.button_Login)
        button1.setOnClickListener(buttonClick)
        val button2 = findViewById<Button>(R.id.button_passwasure_login)
        button2.setOnClickListener(buttonClick)
    }

    private val buttonClick = View.OnClickListener { view ->
        val editText1 = findViewById<View>(R.id.editTextID_login) as EditText           //ID
        val editText2 = findViewById<View>(R.id.editTextPassword_login) as EditText     //Password
        val str1 = editText1.text.toString()
        val str2 = editText2.text.toString()
        //val db = jogDB()    //データベースアクセス用のインスタンス生成

        when (view.id) {
            R.id.button_Login -> {
                //データベースからIDに対するパスワードを入手して

                //正しいかチェックして
                val flag2: Boolean = true    //仮で常に正常に入力されたとする

                //正しければジョギング開始モジュールへ
                if(flag2 == true){
                    //next Activity(現在は仮でLoginに飛ばす)
                    val intent = Intent(this, HomeMap::class.java)
                    // 渡したいデータとキーを指定する
                    intent.putExtra("ID", str1);
                    startActivity(intent)

                } else if(flag2 == false){
                    //エラーを表示する(入力項目に不備有)
                    AlertDialog.Builder(this)
                        .setTitle("Error")
                        .setMessage("IDもしくはパスワードが不適切です。")
                        .setPositiveButton("OK", { dialog, which ->
                            // OKが押された時の挙動
                        })
                        .show()

                } else {
                    //error(詳細不明)
                    //エラーを表示する(詳細不明のエラー)
                    AlertDialog.Builder(this)
                        .setTitle("Error")
                        .setMessage("予期せぬエラーが発生しました。製造元にお問い合わせしてください。")
                        .setPositiveButton("OK", { dialog, which ->
                            // OKが押された時の挙動
                        })
                        .show()
                    }
                }
            R.id.button_passwasure_login -> {
                //next Activity
                val intent = Intent(this, PassChangeActivity::class.java)
                startActivity(intent)
            }
            }
        }
}