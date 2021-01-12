package com.example.sample1

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.content.Intent

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_oce)

        // button.setOnClickListenerでクリックイベントを取得
        val button1 = findViewById<Button>(R.id.button_UserInfo_OCE)
        button1.setOnClickListener(buttonClick)
        val button2 = findViewById<Button>(R.id.button_Record_OCE)
        button2.setOnClickListener(buttonClick)
        val button3 = findViewById<Button>(R.id.button_Inquiry_OCE)
        button3.setOnClickListener(buttonClick)
    }


    private val buttonClick = View.OnClickListener { view ->
        // whenはswichのこと
        when (view.id) { // idに対応して処理を変える。
            // MainActivityのところを変えると、そこに画面遷移をする。
            // Intent intent = new Intent(this, ::class.java)で画面指定
            // startActivity(intent)で、画面を開く
            R.id.button_UserInfo_OCE ->{ val intent = Intent(this, CheckUserInfo::class.java)
                startActivity(intent)}
            R.id.button_Record_OCE -> {val intent = Intent(this, CheckRecord::class.java)
                startActivity(intent)}
            R.id.button_Inquiry_OCE -> {val intent = Intent(this, AddActivityManually::class.java)
                startActivity(intent)}
/*
            else -> { val intent = Intent(this, StartJogging::class.java)
*/
        }
    }
}