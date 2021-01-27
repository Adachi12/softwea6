package com.example.myapplication

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity


class TopActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_top)
        val button1 = findViewById<Button>(R.id.button1)
        button1.setOnClickListener(buttonClick)
        val button2 = findViewById<Button>(R.id.button2)
        button2.setOnClickListener(buttonClick)
    }

    private val buttonClick = View.OnClickListener { view ->
        when (view.id) {
            R.id.button1 ->{ val intent = Intent(this, AccountRegister::class.java)
                startActivity(intent)}
            R.id.button2 -> {val intent = Intent(this, Login::class.java)
                startActivity(intent)}
        }
    }
}