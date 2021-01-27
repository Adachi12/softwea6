package com.example.myapplication

import JogDB
import User
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import androidx.appcompat.app.AlertDialog
import java.util.*
import java.io.IOException
import java.lang.Math.log
import java.util.logging.Level
import kotlin.math.log
import kotlin.system.exitProcess
import java.util.logging.Logger
import kotlin.concurrent.thread
import kotlin.system.exitProcess
import java.net.Socket
import java.nio.ByteBuffer
import java.nio.charset.StandardCharsets

class Login : AppCompatActivity() {
    private val logger = Logger.getLogger(JogDB::class.java.name)

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
        var recvData: User = User().create()

        when (view.id) {
            R.id.button_Login -> {
                //データベースからIDに対するパスワードを入手して
                try {
                    thread {
                        val db = JogDB()
                        recvData = db.userSelect(str1)
                        db.close()

                        //正しいかチェックして
                        logger.info("recvPass = ${recvData.pass}")
                        logger.info("inputPass = $str2")
                        if (recvData.pass == str2) {
                            logger.info("ログイン成功しました")
                            val intent = Intent(this, TopActivity::class.java)
                            intent.putExtra("ID", str1)
                            startActivity(intent)
                            //エラーを表示する(入力項目に不備有)
                        } else {
                            //エラーを表示する(入力項目に不備有)
                            AlertDialog.Builder(this)
                                    .setTitle("Error")
                                    .setMessage("IDもしくはパスワードが不適切です。")
                                    .setPositiveButton("OK", { dialog, which ->
                                        // OKが押された時の挙動
                                    })
                                    .show()
                        }
                    }
                } catch (e: java.lang.Exception) {
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