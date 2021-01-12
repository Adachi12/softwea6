// 必要に応じてサーバ上のDBからユーザ情報をリクエストし、表示する
package com.example.sample1

// AppCompactActivityは、support library action barの機能を使ったactivityベースのクラス？
import android.app.Activity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import android.widget.LinearLayout
import androidx.appcompat.app.AppCompatActivity
import android.view.View

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

        // button.setOnClickListenerでクリックイベントを取得
        /*    val button1 = findViewById<Button>(R.id.button_UserInfo_OCE)
             button1.setOnClickListener(buttonClick) */
    }
}