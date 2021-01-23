package com.example.myapplication

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity

// DisplayRecordメソッドは、DBから取得したデータと
// 「手動でアクティビティを追加する」と書かれたボタンを表示する
class CheckRecord : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_record)  // レイアウトファイルの読み込み

        // button.setOnClickListenerでクリックイベントを取得
        val button1 = findViewById<Button>(R.id.button_AddActivityManually_record_OCE1)
        button1.setOnClickListener(buttonClick)
        val button2 = findViewById<Button>(R.id.button_AddActivityManually_record_OCE2)
        button2.setOnClickListener(buttonClick)
        val button3 = findViewById<Button>(R.id.button_AddActivityManually_record_OCE3)
        button3.setOnClickListener(buttonClick)
        val button4 = findViewById<Button>(R.id.button_AddActivityManually_record_OCE4)
        button4.setOnClickListener(buttonClick)
        val button5 = findViewById<Button>(R.id.button_AddActivityManually_record_OCE5)
        button5.setOnClickListener(buttonClick)
    }

    private val buttonClick = View.OnClickListener { view ->
        when (view.id) { // idに対応して処理を変える。
            // MainActivityのところを変えると、そこに画面遷移をする。
            // Intent intent = new Intent(this, ::class.java)で画面指定
            // startActivity(intent)で、画面を開く
            R.id.button_AddActivityManually_record_OCE1 ->{
                // ここに結果を反映させる
                val intent = Intent(this, AddActivityManually1::class.java)
                startActivity(intent)}
            R.id.button_AddActivityManually_record_OCE2 ->{
                // ここに結果を反映させる
                val intent = Intent(this, AddActivityManually2::class.java)
                startActivity(intent)}
            R.id.button_AddActivityManually_record_OCE3 ->{
                // ここに結果を反映させる
                val intent = Intent(this, AddActivityManually3::class.java)
                startActivity(intent)}
            R.id.button_AddActivityManually_record_OCE4 ->{
                // ここに結果を反映させる
                val intent = Intent(this, AddActivityManually4::class.java)
                startActivity(intent)}
            R.id.button_AddActivityManually_record_OCE5 ->{
                // ここに結果を反映させる
                val intent = Intent(this, AddActivityManually5::class.java)
                startActivity(intent)}
        }
    }
}