package com.example.myapplication

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import com.google.android.gms.maps.GoogleMap
import com.google.android.gms.maps.OnMapReadyCallback
import com.google.android.gms.maps.SupportMapFragment
import com.google.android.gms.maps.model.LatLng


class EndRunningActivity : AppCompatActivity() ,OnMapReadyCallback {

    private lateinit var mMap: GoogleMap

    companion object {
        //場所指定
        val Key_End = "key_state"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_maps_sub)

        //値を持ってくる
        val state_end = intent.getSerializableExtra(Key_End)
        if (state_end is dataState) { //よくわからんけど書いて損はなさそう
        //テキスト更新
            val timeText2 = findViewById<TextView>(R.id.timeText2)
            timeText2.text = state_end.id

        }

        //画面遷移用のボタンの取得
        val button2 = findViewById<Button>(R.id.endButton)
        //画面遷移
        button2.setOnClickListener {
            //画面遷移だけの部分
            val intent = Intent(this@EndRunningActivity, RunningActivity::class.java)
            startActivity(intent)
        }
        val mapFragment = supportFragmentManager
                .findFragmentById(R.id.map) as SupportMapFragment
        mapFragment.getMapAsync(this)

    }

    override fun onMapReady(googleMap: GoogleMap) {
        mMap = googleMap
        googleMap.uiSettings.isScrollGesturesEnabled = true

        // Add a marker in Sydney and move the
        // camera
        val sydney = LatLng(-34.0, 151.0)

    }
}