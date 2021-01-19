package com.example.test

import android.content.Intent
import android.location.Location
import android.location.LocationListener
import android.location.LocationManager
import android.os.Bundle
import android.view.View
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import com.google.android.gms.maps.CameraUpdateFactory
import com.google.android.gms.maps.GoogleMap
import com.google.android.gms.maps.OnMapReadyCallback
import com.google.android.gms.maps.SupportMapFragment
import com.google.android.gms.maps.model.LatLng
import com.google.android.gms.maps.model.MarkerOptions

class HomeMap2 : AppCompatActivity(), OnMapReadyCallback {
    private var mMap: GoogleMap? = null
    private var latLng: LatLng? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_maps)
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        val mapFragment = (supportFragmentManager
                .findFragmentById(R.id.maproot) as SupportMapFragment?)!!
        mapFragment.getMapAsync(this)

        //button 画面遷移
        val sendButton = findViewById<Button>(R.id.RootSearchbutton1)
        sendButton.setOnClickListener { v: View? ->
            val intent = Intent(application, RootMapping::class.java)
            startActivity(intent)
        } //
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
    override fun onMapReady(googleMap: GoogleMap) {
        mMap = googleMap


        //現在地処理
        val locationListener: LocationListener = object : LocationListener {
            override fun onLocationChanged(location: Location) {
                try {
                    latLng = LatLng(location.latitude, location.longitude)
                    mMap!!.addMarker(MarkerOptions().position(latLng!!))
                    mMap!!.moveCamera(CameraUpdateFactory.newLatLngZoom(latLng, 14f))
                } catch (e: SecurityException) {
                    e.printStackTrace()
                }
            }

            override fun onStatusChanged(s: String, i: Int, bundle: Bundle) {}
            override fun onProviderEnabled(s: String) {}
            override fun onProviderDisabled(s: String) {}
        }
        val locationManager = getSystemService(LOCATION_SERVICE) as LocationManager
        try {
            val MIN_TIME: Long = 1000
            val MIN_DIST: Long = 5
            locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, MIN_TIME, MIN_DIST.toFloat(), locationListener)
        } catch (e: SecurityException) {
            e.printStackTrace()
        }
    }
}