package com.example.myapplication

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import androidx.appcompat.app.AppCompatActivity

// DisplayRecordメソッドは、DBから取得したデータと
// 「手動でアクティビティを追加する」と書かれたボタンを表示する

class AddActivityManually : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_change_record)  // レイアウトファイルの読み込み

        // button.setOnClickListenerでクリックイベントを取得
        val button1 = findViewById<Button>(R.id.button_confirm_AAM_OCE)
        button1.setOnClickListener(buttonClick)
    }

    private val buttonClick = View.OnClickListener { view ->
        when (view.id) { // idに対応して処理を変える。
            // MainActivityのところを変えると、そこに画面遷移をする。
            // Intent intent = new Intent(this, ::class.java)で画面指定
            // startActivity(intent)で、画面を開く
            R.id.button_confirm_AAM_OCE ->{

                // ここに、結果を反映させる処理を書く。
                val recordMileage = findViewById<EditText>(R.id.edit_mileage_OCE) as EditText
                val Mileage = recordMileage.getText()
                //
                val recordDay = findViewById<EditText>(R.id.edit_day_OCE) as EditText
                val Day_month = recordDay.getText()
                val recordDay2 = findViewById<EditText>(R.id.edit_day_OCE2) as EditText
                val Day_day = recordDay2.getText()
                //
                val recordStartTime = findViewById<EditText>(R.id.edit_startTime_OCE) as EditText
                val StartTime_hour = recordStartTime.getText()
                val recordStartTime2 = findViewById<EditText>(R.id.edit_startTime_OCE2) as EditText
                val StartTime_minute = recordStartTime2.getText()
                //
                val exerciseTime = findViewById<EditText>(R.id.edit_exerciseTime_OCE) as EditText
                val exerciseTime_hour = exerciseTime.getText()
                val exerciseTime2 = findViewById<EditText>(R.id.edit_exerciseTime_OCE2) as EditText
                val exerciseTime_minute = exerciseTime2.getText()
                val exerciseTime3 = findViewById<EditText>(R.id.edit_exerciseTime_OCE3) as EditText
                val exerciseTime_second = exerciseTime3.getText()

                // 反映させた後は、記録確認へ飛ぶ(CheckRecord)
                val intent = Intent(this, CheckRecord::class.java)
                startActivity(intent)}
/* else -> { val intent = Intent(this, StartJogging::class.java) */
        }
    }
}