// 必要に応じてサーバ上のDBからユーザ情報をリクエストし、表示する
package com.example.myapplication

// AppCompactActivityは、support library action barの機能を使ったactivityベースのクラス？
import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

// レイアウトファイルにあるレイアウトのidを指定して読み込み
//val linearLayout = findViewById(R.id.LinearLayout_UI_OCE) as LinearLayout

// CheckUserInfoクラスは、AppcompatActivityクラスを継承している
// AppCompatActivityクラスは、画面制御の基本的な機能を提供している
// その中のonCreateメソッドは、アクティビティが起動されたときに呼び出される
// そのメソッドのさらに中のsetContentViewは、画面に表示するビューの設定
class CheckUserInfo : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_user)  // レイアウトファイルの読み込み
        // テキストボックス内に表示させる内容
        val Sex: String = "male"
        val Shincho: String = "148.9"
        val num1 = Shincho.toDouble()
        val Taiju: String = "100.9"
        val num2 = Taiju.toDouble()
        val GoalWeight: String = "78.8"
        val num3 = GoalWeight.toDouble()
        val GoalMade: Double = num2 - num3
        val mokuhyoMade = GoalMade.toString()
        val GoalPeriod: String = "18"
        //
        val BMI = num2 / Math.pow(num1/100, 2.0)
        //
        val userSex = findViewById<TextView>(R.id.edit_UserSex_OCE) as TextView
        userSex.setText(Sex)
        val userHeight = findViewById<TextView>(R.id.edit_UserHeight_OCE) as TextView
        userHeight.setText(Shincho)
        val userWeight = findViewById<TextView>(R.id.edit_UserWeight_OCE) as TextView
        userWeight.setText(Taiju)
        val userBMI = findViewById<TextView>(R.id.edit_UserBMI_OCE) as TextView
        userBMI.setText(BMI.toString())
        //
        val userGoalWeight = findViewById<TextView>(R.id.edit_UserGoalWeight_OCE) as TextView
        userGoalWeight.setText(GoalWeight)
        val userGoalMade = findViewById<TextView>(R.id.edit_UserGoalMade_OCE) as TextView
        userGoalMade.setText(mokuhyoMade)
        val userGoalPeriod = findViewById<TextView>(R.id.edit_UserGoalPeriod_OCE) as TextView
        userGoalPeriod.setText(GoalPeriod)

        /*val textUI = TextView(this)
        textUI.setText("text", TextView.BufferType.NORMAL)
        setContentView(textUI)

        val editUI = TextView(this)
        editUI.setText("text", TextView.BufferType.NORMAL)
        setContentView(editUI)*/

        // button.setOnClickListenerでクリックイベントを取得
        val button1 = findViewById<Button>(R.id.button_CheckUserInfo_OCE)
        button1.setOnClickListener(buttonClick)
    }


    private val buttonClick = View.OnClickListener { view ->
        // whenはswichのこと

        when (view.id) { // idに対応して処理を変える。
            // MainActivityのところを変えると、そこに画面遷移をする。
            // Intent intent = new Intent(this, ::class.java)で画面指定
            // startActivity(intent)で、画面を開く
            R.id.button_CheckUserInfo_OCE -> {

                // ここに、結果を反映させる処理を書く。

                val intent = Intent(this, ChangeUserInfo::class.java)
                startActivity(intent)
            }
/* else -> { val intent = Intent(this, StartJogging::class.java) */
        }
    }
}