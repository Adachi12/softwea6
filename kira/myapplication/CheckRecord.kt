package com.example.myapplication

import android.content.Intent
import android.os.Bundle
import android.text.util.Linkify
import android.view.View
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

// DisplayRecordメソッドは、DBから取得したデータと
// 「手動でアクティビティを追加する」と書かれたボタンを表示する

class CheckRecord : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_record)  // レイアウトファイルの読み込み

        // button.setOnClickListenerでクリックイベントを取得
        val button1 = findViewById<Button>(R.id.button_AddActivityManually_record_OCE)
        button1.setOnClickListener(buttonClick)
    }

    private val buttonClick = View.OnClickListener { view ->
        when (view.id) { // idに対応して処理を変える。
            // MainActivityのところを変えると、そこに画面遷移をする。
            // Intent intent = new Intent(this, ::class.java)で画面指定
            // startActivity(intent)で、画面を開く
            R.id.button_AddActivityManually_record_OCE ->{ val intent = Intent(this, AddActivityManually::class.java)
                startActivity(intent)}
        }
    }
}