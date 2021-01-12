package com.example.sample1

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity

// DisplayRecordメソッドは、DBから取得したデータと
// 「手動でアクティビティを追加する」と書かれたボタンを表示する

class AddActivityManually : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_record)  // レイアウトファイルの読み込み

        // button.setOnClickListenerでクリックイベントを取得
        /*    val button1 = findViewById<Button>(R.id.button_UserInfo_OCE)
             button1.setOnClickListener(buttonClick) */
    }
}