package com.example.myapplication

import android.Manifest
import android.content.Intent
import android.content.pm.PackageManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.util.Log
import android.widget.Button
import android.widget.TextView
import androidx.core.app.ActivityCompat
import com.google.android.gms.maps.GoogleMap
import com.google.android.gms.maps.OnMapReadyCallback
import com.google.android.gms.maps.SupportMapFragment
//map
import android.location.LocationManager
import android.content.Context
import android.provider.Settings
import android.widget.Toast
import androidx.core.content.ContextCompat

class RunningActivity : AppCompatActivity(), OnMapReadyCallback {
    val handler = Handler()                      //
    var timeValue = 0                              // 秒カウンタ
    private lateinit var mMap: GoogleMap
    private lateinit var locationManager: LocationManager

    companion object {
        //        const val EXTRA_MESSAGE = "com.example.Kotlintestactivitydatatrans.MESSAGE"
        val Key_Running = "key"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_maps)


        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        val mapFragment = supportFragmentManager
                .findFragmentById(R.id.map) as SupportMapFragment
        mapFragment.getMapAsync(this)

        //permissioncheck
        if (ContextCompat.checkSelfPermission(this,
                        Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this,
                    arrayOf(Manifest.permission.ACCESS_FINE_LOCATION),
                    1000)
        } else {
            locationStart()

            if (::locationManager.isInitialized) {
                locationManager.requestLocationUpdates(
                        LocationManager.GPS_PROVIDER,
                        1000,
                        50f,
                        this)
            }

        }
    }



    //位置測定スタート
    private fun locationStart() {
        Log.d("debug", "locationStart()")

        // Instances of LocationManager class must be obtained using Context.getSystemService(Class)
        locationManager = getSystemService(Context.LOCATION_SERVICE) as LocationManager

        val locationManager = getSystemService(Context.LOCATION_SERVICE) as LocationManager

        if (locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER)) {
            Log.d("debug", "location manager Enabled")
        } else {
            // to prompt setting up GPS
            val settingsIntent = Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS)
            startActivity(settingsIntent)
            Log.d("debug", "not gpsEnable, startActivity")
        }

        if (ContextCompat.checkSelfPermission(this,
                        Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this,
                    arrayOf(Manifest.permission.ACCESS_FINE_LOCATION), 1000)

            Log.d("debug", "checkSelfPermission false")
            return
        }

        locationManager.requestLocationUpdates(
                LocationManager.GPS_PROVIDER,
                1000,
                50f,
                this)

    }

    override fun onRequestPermissionsResult(
            requestCode: Int, permissions: Array<String>, grantResults: IntArray) {
        if (requestCode == 1000) {
            // 使用が許可された
            if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                Log.d("debug", "checkSelfPermission true")

                locationStart()

            } else {
                // それでも拒否された時の対応
                val toast = Toast.makeText(this,
                        "これ以上なにもできません", Toast.LENGTH_SHORT)
                toast.show()
            }
        }
    }


    //実際の動き
    override fun onStart() {
        super.onStart()
        //画面遷移用のボタンの取得
        val button1 = findViewById<Button>(R.id.stopButton)
        val button2 = findViewById<Button>(R.id.startButton)
        //serializableから値取得
        val state_running = intent.getSerializableExtra(Key_Running)

        //画面遷移
//        button1.setOnClickListener {
//            val intent = Intent(this@MapsActivity, SubActivity::class.java)
//            startActivity(intent)
//        }
//        //時間の初期化の有無
//        if (state_running is dataState) {
//            if (state_running.key == 1) {
//                val oma = state_running.time
//            }
//        }

        val runnable = object : Runnable {
            // メッセージ受信が有った時かな?
            override fun run() {
                timeValue++                      // 秒カウンタ+1
                timeToText(timeValue)?.let {        // timeToText()で表示データを作り
                    val timeText = findViewById<TextView>(R.id.timeText)
                    timeText.text = it            // timeText.textへ代入(表示)

                }
                handler.postDelayed(this, 1000)  // 1000ｍｓ後に自分にpost
            }
        }
        handler.post(runnable)
        // startボタン押された時(setOnClickListener)の処理
//
//        button2.setOnClickListener {
//                          // 最初のキュー登録
//        }
        // stopボタン押された時の処理
        button1.setOnClickListener {
            handler.removeCallbacks(runnable)      // キューキャンセル
            //画面遷移
            val intent = Intent(this@RunningActivity, PauseRunningActivity::class.java)
            //値移行
            val timeText = findViewById<TextView>(R.id.timeText)
            val state_pause = dataState(timeText.text.toString(),timeValue)
            intent.putExtra(PauseRunningActivity.Key_Pause, state_pause);

            startActivity(intent)
        }
        // resetボタン押された時の処理
//            reset.setOnClickListener {
//                handler.removeCallbacks(runnable)      // キューキャンセル
//                timeValue = 0                          // 秒カウンタークリア
//                timeToText()?.let {                  // timeToText()で表示データを作り
//                    timeText.text = it                // timeText.textに表示
//                }


    }


    // 時間表示メソッド
    private fun timeToText(time: Int = 0): String? {
        return if (time < 0) {
            null                                    // 時刻が0未満の場合 null
        } else if (time == 0) {
            "00:00:00"                            // ０なら
        } else {
            val h = time / 3600
            val m = time % 3600 / 60
            val s = time % 60
            "%1$02d:%2$02d:%3$02d".format(h, m, s)  // 表示に整形


        }
    }
    /**
     * Manipulates the map once available.
     * This callback is triggered when the map is ready to be used.
     * This is where we can add markers or lines, add listeners or move the camera. In this case,
     * we just add a marker near Sydney, Australia.
     * If Google Play services is not installed on the device, the user will be prompted to install
     * it inside the SupportMapFragment. This method will only be triggered once the user has
     * installed Google Play services and returned to the app.
     */
    @NeedsPermission(Manifest.permission.ACCESS_FINE_LOCATION)
    override fun onMapReady(googleMap: GoogleMap) {
        mMap = googleMap
        googleMap.uiSettings.isScrollGesturesEnabled = true
//        googleMap.isMyLocationEnabled = true
        mMap.uiSettings.isZoomControlsEnabled = false
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            // TODO: Consider calling
            //    ActivityCompat#requestPermissions
            // here to request the missing permissions, and then overriding
            //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
            //                                          int[] grantResults)
            // to handle the case where the user grants the permission. See the documentation
            // for ActivityCompat#requestPermissions for more details.
            return
        }
        //現在地表示
        mMap.isMyLocationEnabled = true //TODO: RuntimePermissionを後で入れる
       
        //コンパス表示
        mMap.uiSettings.isCompassEnabled = true
        //現在地ボタン
        mMap.uiSettings.isMyLocationButtonEnabled = true
        //ズームボタン
        mMap.uiSettings.isZoomGesturesEnabled = true
        //ピンチインアウトズーム


        }
        // Add a marker in Sydney and move the
//        // camera
//        val sydney = LatLng(-34.0, 151.0)

    }

private fun LocationManager.requestLocationUpdates(gpsProvider: String, i: Int, fl: Float, runningActivity: RunningActivity) {

}

annotation class NeedsPermission(val value: String)

