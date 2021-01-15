package com.example.myapplication

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

// DisplayRecordメソッドは、DBから取得したデータと
// 「手動でアクティビティを追加する」と書かれたボタンを表示する
class AddActivityManually1 : AppCompatActivity() {
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
                val mileage = recordMileage.getText()
                val Mileage = mileage.toString()
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

                // データの受け渡し
                val setter = findViewById<TextView>(R.id.UserActivity_OCE1) as TextView
                setter.setText(" 走行距離:" +Mileage+ "km" + "  日付:" +Day_month.toString()+ "/" +Day_day.toString()+ "\n スタート:"
                        +StartTime_hour.toString()+ ":" +StartTime_minute.toString()+ "走行時間:" +exerciseTime_hour.toString()+ ":"
                        +exerciseTime_minute.toString()+ ":" +exerciseTime_second.toString())

                // 反映させた後は、記録確認へ飛ぶ(CheckRecord)
                val intent = Intent(this, CheckRecord::class.java)
                startActivity(intent)}
/* else -> { val intent = Intent(this, StartJogging::class.java) */
        }
    }
}

class AddActivityManually2 : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_change_record)  // レイアウトファイルの読み込み
        val button1 = findViewById<Button>(R.id.button_confirm_AAM_OCE)
        button1.setOnClickListener(buttonClick)
    }
    private val buttonClick = View.OnClickListener { view ->
        when (view.id) { // idに対応して処理を変える。
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

                // データの受け渡し
                val setter = findViewById<TextView>(R.id.button_AddActivityManually_record_OCE2) as TextView
                setter.setText(" 走行距離:" +Mileage+ "km" + "  日付:" +Day_month+ "/" +Day_day+ "\n" + "スタート:"
                        +StartTime_hour+ ":" +StartTime_minute+ "走行時間:" +exerciseTime_hour+":" +exerciseTime_minute+ ":"
                        +exerciseTime_second)

                // 反映させた後は、記録確認へ飛ぶ(CheckRecord)
                val intent = Intent(this, CheckRecord::class.java)
                startActivity(intent)}
/* else -> { val intent = Intent(this, StartJogging::class.java) */
        }
    }
}

class AddActivityManually3 : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_change_record)  // レイアウトファイルの読み込み
        val button1 = findViewById<Button>(R.id.button_confirm_AAM_OCE)
        button1.setOnClickListener(buttonClick)
    }
    private val buttonClick = View.OnClickListener { view ->
        when (view.id) { // idに対応して処理を変える。
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

                // データの受け渡し
                val setter = findViewById<TextView>(R.id.button_AddActivityManually_record_OCE3) as TextView
                setter.setText(" 走行距離:" +Mileage+ "km" + "  日付:" +Day_month+ "/" +Day_day+ "\n" + "スタート:"
                        +StartTime_hour+ ":" +StartTime_minute+ "走行時間:" +exerciseTime_hour+":" +exerciseTime_minute+ ":" +exerciseTime_second)

                // 反映させた後は、記録確認へ飛ぶ(CheckRecord)
                val intent = Intent(this, CheckRecord::class.java)
                startActivity(intent)}
/* else -> { val intent = Intent(this, StartJogging::class.java) */
        }
    }
}

class AddActivityManually4 : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_change_record)  // レイアウトファイルの読み込み
        val button1 = findViewById<Button>(R.id.button_confirm_AAM_OCE)
        button1.setOnClickListener(buttonClick)
    }
    private val buttonClick = View.OnClickListener { view ->
        when (view.id) { // idに対応して処理を変える。
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

                // データの受け渡し
                val setter = findViewById<TextView>(R.id.button_AddActivityManually_record_OCE4) as TextView
                setter.setText(" 走行距離:" +Mileage+ "km" + "  日付:" +Day_month+ "/" +Day_day+ "\n" + "スタート:"
                        +StartTime_hour+ ":" +StartTime_minute+ "走行時間:" +exerciseTime_hour+":" +exerciseTime_minute+ ":" +exerciseTime_second)

                // 反映させた後は、記録確認へ飛ぶ(CheckRecord)
                val intent = Intent(this, CheckRecord::class.java)
                startActivity(intent)}
/* else -> { val intent = Intent(this, StartJogging::class.java) */
        }
    }
}

class AddActivityManually5 : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_change_record)  // レイアウトファイルの読み込み
        val button1 = findViewById<Button>(R.id.button_confirm_AAM_OCE)
        button1.setOnClickListener(buttonClick)
    }
    private val buttonClick = View.OnClickListener { view ->
        when (view.id) { // idに対応して処理を変える。
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

                // データの受け渡し
                val setter = findViewById<TextView>(R.id.button_AddActivityManually_record_OCE5) as TextView
                setter.setText(" 走行距離:" +Mileage+ "km" + "  日付:" +Day_month+ "/" +Day_day+ "\n" + "スタート:"
                        +StartTime_hour+ ":" +StartTime_minute+ "走行時間:" +exerciseTime_hour+":" +exerciseTime_minute+ ":" +exerciseTime_second)

                // 反映させた後は、記録確認へ飛ぶ(CheckRecord)
                val intent = Intent(this, CheckRecord::class.java)
                startActivity(intent)}
/* else -> { val intent = Intent(this, StartJogging::class.java) */
        }
    }
}