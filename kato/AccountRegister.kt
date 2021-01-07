package com.example.myapplication

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.RadioButton
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.app.AlertDialog as AlertDialog

//入力項目ごとに字数制限とかをつけんと、害悪利用者によって破壊されるかも
class AccountRegister : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_accountregister)
        val button1 = findViewById<Button>(R.id.button_accountregister)
        button1.setOnClickListener(buttonClick)
        val radioButton1 = findViewById<RadioButton>(R.id.sex_man)
        radioButton1.setOnClickListener(buttonClick)
        val radioButton2 = findViewById<RadioButton>(R.id.sex_woman)
        radioButton2.setOnClickListener(buttonClick)

    }

    private val buttonClick = View.OnClickListener { view ->
        when (view.id) {
            R.id.sex_man -> {
                val radioButton1 = findViewById<RadioButton>(R.id.sex_man)
                val checked = radioButton1.isChecked
                if (checked) {
                    // 1つ目のRadioButtonが選択された時の処理
                    val radioButton2 = findViewById<RadioButton>(R.id.sex_woman)
                    radioButton2.isChecked = false  //2つ目のボタンの選択解除
                }
            }
            R.id.sex_woman -> {
                val radioButton1 = findViewById<RadioButton>(R.id.sex_woman)
                val checked = radioButton1.isChecked
                if (checked) {
                    // 2つ目のRadioButtonが選択された時の処理
                    val radioButton2 = findViewById<RadioButton>(R.id.sex_man)
                    radioButton2.isChecked = false //1つ目のボタンの選択解除
                }
            }
            R.id.button_accountregister -> {
                try{
                val editText1 = findViewById<View>(R.id.editTextNumber_weight) as EditText  //体重
                val editText2 = findViewById<View>(R.id.editTextNumber_height) as EditText  //身長
                val editText3 = findViewById<View>(R.id.editTextNumber_year) as EditText    //生年月日
                val editText4 = findViewById<View>(R.id.editTextID) as EditText             //ID
                val editText5 = findViewById<View>(R.id.editTextPassword) as EditText       //Password
                val editText6 = findViewById<View>(R.id.editTextEmailAddress) as EditText   //メアド
                val str1 = editText1.text.toString()
                val str2 = editText2.text.toString()
                val str3 = editText3.text.toString()
                val str4 = editText4.text.toString()
                val str5 = editText5.text.toString()
                val str6 = editText6.text.toString()
                val num1 = str1.toFloat()
                val num2 = str2.toFloat()
                //val num3 = str3.toInt()
                val radioButton1 = findViewById<RadioButton>(R.id.sex_woman)
                val radioButton2 = findViewById<RadioButton>(R.id.sex_man)
                val flag :Boolean = isCheckInput(num1, num2, str3, str4, str5, str6)

                if(flag == true && (radioButton1.isChecked == true || radioButton2.isChecked == true)) {
                    //DataBaseへ送信してから(年齢について...生年月日は必要なく年齢だけでいいのか→年、月、日を送るそう)

                    //「登録が完了しました」のダイアログを出して
                    AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                        .setTitle("登録完了")
                        .setMessage("登録が完了しました。")
                        .setPositiveButton("OK", { dialog, which ->
                            // OKが押されたら
                            //ログインしてジョギング開始モジュールに進む(現在は仮でLoginに飛ばす)
                            val intent = Intent(this, Login::class.java)
                            startActivity(intent)
                        })
                        .show()
                } else if(flag == false || (radioButton1.isChecked == false && radioButton2.isChecked == false)) {
                    //エラーを表示する(入力項目に不備有)
                    AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                            .setTitle("Error")
                            .setMessage("入力項目に不備があります。")
                            .setPositiveButton("OK", { dialog, which ->
                                // OKが押された時の挙動
                            })
                            .show()
                } else {
                    //error(詳細不明)
                    //エラーを表示する(入力項目に不備有)
                    AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                            .setTitle("Error")
                            .setMessage("予期せぬエラーが発生しました。製造元にお問い合わせしてください。")
                            .setPositiveButton("OK", { dialog, which ->
                                // OKが押された時の挙動
                            })
                            .show()
                        }
                    } catch(e: Exception){
                    //エラーを表示する(入力項目に不備有)
                    AlertDialog.Builder(this) // FragmentではActivityを取得して生成
                        .setTitle("Error")
                        .setMessage("入力項目に不備があります。")
                        .setPositiveButton("OK", { dialog, which ->
                            // OKが押された時の挙動
                        })
                        .show()
                }
            }
        }
    }

    //入力項目が適切かチェックする関数
    private fun isCheckInput(weight: Float, height: Float, year: String, id: String, pass: String, mail: String): Boolean {
        try {
            if (
                    0 < weight && weight < 1000                                                     //体重
                    && 50 < height && height < 300                                                  //身長
                    && 1900 < year.substring(0, 4).toInt() && year.substring(0, 4).toInt() < 2100   //年
                    && 0 < year.substring(4, 6).toInt() && year.substring(4, 6).toInt() < 13        //月
                    && 0 < year.substring(6, 8).toInt() && year.substring(6, 8).toInt() < 32        //日
                    && 0 < id.length && id.length < 9                                               //id
                    && 0 < pass.length && pass.length < 33                                          //password
                    && 0 < mail.length && mail.length < 31                                          //mailaddres
            ) {
                return true
            } else {
                return false
            }
        } catch(e: Exception) {
        return false
    }
    }
}