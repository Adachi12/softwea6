package com.example.myapplication

import android.os.Bundle
import android.view.View
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import android.content.Intent


class TopActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_top)
        val button1 = findViewById<Button>(R.id.button1_top)
        button1.setOnClickListener(buttonClick)
        val button2 = findViewById<Button>(R.id.button2_top)
        button2.setOnClickListener(buttonClick)
    }

    private val buttonClick = View.OnClickListener { view ->
        when (view.id) {
            R.id.button1_top ->{ val intent = Intent(this, AccountRegister::class.java)
                startActivity(intent)}
            R.id.button2_top -> {val intent = Intent(this, Login::class.java)
                startActivity(intent)}
        }
    }
}