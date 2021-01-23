package com.example.myapplication

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import androidx.appcompat.app.AppCompatActivity


class ChangeUserInfo : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_change_user)  // レイアウトファイルの読み込み

        // テキストボックス内に表示させる内容
        val Sex: String = "male"
        val Shincho: String = "148.9"
        val Taiju: String = "100.9"
        val GoalWeight: String = "78.8"
        val GoalPeriod: String = "18"
        //
        val userSex = findViewById<EditText>(R.id.edit_UserSex_Change_OCE) as EditText
        userSex.setText(Sex)
        val userHeight = findViewById<EditText>(R.id.edit_UserHeight_Change_OCE) as EditText
        userHeight.setText(Shincho)
        val userWeight = findViewById<EditText>(R.id.edit_UserWeight_Change_OCE) as EditText
        userWeight.setText(Taiju)
        //
        val userGoalWeight = findViewById<EditText>(R.id.edit_UserGoalWeight_Change_OCE) as EditText
        userGoalWeight.setText(GoalWeight)
        val userGoalPeriod = findViewById<EditText>(R.id.edit_UserGoalPeriod_Change_OCE) as EditText
        userGoalPeriod.setText(GoalPeriod)

        // button.setOnClickListenerでクリックイベントを取得
        val button1 = findViewById<Button>(R.id.button_Determine_ChangeUserInfo_OCE)
        button1.setOnClickListener(buttonClick)
    }

    private val buttonClick = View.OnClickListener { view ->
         when (view.id) { // idに対応して処理を変える。
            // MainActivityのところを変えると、そこに画面遷移をする。
            // Intent intent = new Intent(this, ::class.java)で画面指定
            // startActivity(intent)で、画面を開く
             R.id.button_Determine_ChangeUserInfo_OCE -> {

                 // ここに、結果を反映させる処理を書く
                 val userSex = findViewById<EditText>(R.id.edit_UserSex_Change_OCE) as EditText
                 val Sex = userSex.getText()
                 val userHeight = findViewById<EditText>(R.id.edit_UserHeight_Change_OCE) as EditText
                 val Height = userHeight.getText()
                 val userWeight = findViewById<EditText>(R.id.edit_UserWeight_Change_OCE) as EditText
                 val Weight = userWeight.getText()
                 //
                 val userGoalWeight = findViewById<EditText>(R.id.edit_UserGoalWeight_Change_OCE) as EditText
                 val GoalWeight = userGoalWeight.getText()
                 val userGoalPeriod = findViewById<EditText>(R.id.edit_UserGoalPeriod_Change_OCE) as EditText
                 val GoalPeriod = userGoalPeriod.getText()

                 // ユーザ情報確認へ飛ぶ(CheckUserInfo)
                 val intent = Intent(this, CheckUserInfo::class.java)
                 startActivity(intent)
             }
/* else -> { val intent = Intent(this, StartJogging::class.java) */
        }
    }
}
