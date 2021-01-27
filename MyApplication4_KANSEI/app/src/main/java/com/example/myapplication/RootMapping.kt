package com.example.myapplication

import android.Manifest
import android.content.pm.PackageManager
import android.graphics.Color
import android.location.Location
import android.location.LocationListener
import android.location.LocationManager
import android.net.wifi.WifiConfiguration.AuthAlgorithm.strings
import android.os.AsyncTask
import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import com.google.android.gms.maps.CameraUpdateFactory
import com.google.android.gms.maps.GoogleMap
import com.google.android.gms.maps.OnMapReadyCallback
import com.google.android.gms.maps.SupportMapFragment
import com.google.android.gms.maps.model.BitmapDescriptorFactory
import com.google.android.gms.maps.model.LatLng
import com.google.android.gms.maps.model.MarkerOptions
import com.google.android.gms.maps.model.PolylineOptions
import org.json.JSONException
import org.json.JSONObject
import java.io.BufferedReader
import java.io.IOException
import java.io.InputStream
import java.io.InputStreamReader
import java.net.HttpURLConnection
import java.net.URL
import java.util.*

class RootMapping : AppCompatActivity(), OnMapReadyCallback {
    private var mMap: GoogleMap? = null
    var listPoints: ArrayList<LatLng>? = null
    private var latLng: LatLng? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_root_mapping)
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        val mapFragment = supportFragmentManager
                .findFragmentById(R.id.maproot) as SupportMapFragment?
        Objects.requireNonNull(mapFragment)?.getMapAsync(this)
        ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.ACCESS_FINE_LOCATION), PackageManager.PERMISSION_GRANTED)
        ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.ACCESS_COARSE_LOCATION), PackageManager.PERMISSION_GRANTED)
        listPoints = ArrayList()
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

        //map on point route
        mMap!!.setOnMapLongClickListener { latLng ->
            if (listPoints!!.size == 2) {
                listPoints!!.clear()
                mMap!!.clear()
            }
            listPoints!!.add(latLng)
            //Create Marker
            val markerOptions = MarkerOptions()
            markerOptions.position(latLng)

            //1pointer
            if (listPoints!!.size == 1) {
                markerOptions.icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_BLUE))
            } else {
                //second
                markerOptions.icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_GREEN))
            }
            mMap!!.addMarker(markerOptions)
            if (listPoints!!.size == 2) {
                val url = getRequestURL(listPoints!![0], listPoints!![1])
                val taskRequestDirections = TaskRequestDirections()
                taskRequestDirections.execute(url)
            }
        }
    }

    private fun getRequestURL(origin: LatLng, dest: LatLng): String {
        val srt_org = "origin=" + origin.latitude + "," + origin.longitude
        val srt_dest = "destination=" + dest.latitude + "," + dest.longitude
        val sensor = "sensor=false"
        val mode = "mode=driving"
        val param = "$srt_org&$srt_dest&$sensor&$mode"
        val output = "json"
        return "https://maps.googleapis.com/maps/api/directions/$output?$param"
    }

    @Throws(IOException::class)
    private fun requestDirection(reqUrl: String): String {
        var responseString = ""
        var inputStream: InputStream? = null
        var httpURLConnection: HttpURLConnection? = null
        try {
            val url = URL(reqUrl)
            httpURLConnection = url.openConnection() as HttpURLConnection
            httpURLConnection.connect()

            //Get  the result
            inputStream = httpURLConnection!!.inputStream
            val inputStreamReader = InputStreamReader(inputStream)
            val bufferedReader = BufferedReader(inputStreamReader)
            val stringBuffer = StringBuffer()
            var line: String? = ""
            while (bufferedReader.readLine().also { line = it } != null) {
                stringBuffer.append(line)
            }
            responseString = stringBuffer.toString()
            bufferedReader.close()
            inputStreamReader.close()
        } catch (e: Exception) {
            e.printStackTrace()
        } finally {
            inputStream?.close()
            httpURLConnection!!.disconnect()
        }
        return responseString
    }

    inner class TaskRequestDirections : AsyncTask<String?, Void?, String>() {
        protected override fun doInBackground(vararg params: String?): String? {
            var responseString = ""
            try {
                responseString = requestDirection(strings[0])
            } catch (e: IOException) {
                e.printStackTrace()
            }
            return responseString
        }

        override fun onPostExecute(s: String) {
            super.onPostExecute(s)
            val taskParser = TaskParser()
            taskParser.execute(s)
        }
    }

    inner class TaskParser : AsyncTask<String?, Void?, List<List<HashMap<String, String>>>?>() {
        protected override fun doInBackground(vararg params: String?): List<List<HashMap<String, String>>>? {
            var jsonObject: JSONObject? = null
            var routes: List<List<HashMap<String, String>>>? = null
            try {
                jsonObject = JSONObject(strings[0])
                val directionsParser = DirectionsParser()
                routes = directionsParser.parse(jsonObject)
            } catch (e: JSONException) {
                e.printStackTrace()
            }
            return routes
        }

        override fun onPostExecute(lists: List<List<HashMap<String, String>>>?) {
            var points: ArrayList<*>? = null
            var polylineOptions: PolylineOptions? = null
            for (path in lists!!) {
                points = ArrayList<Any?>()
                polylineOptions = PolylineOptions()
                for (point in path) {
                    val lat = point["lat"]!!.toDouble()
                    val lon = point["lon"]!!.toDouble()
                    points.add(LatLng(lat, lon))
                }
                polylineOptions.addAll(points)
                polylineOptions.width(15f)
                polylineOptions.color(Color.BLUE)
                polylineOptions.geodesic(true)
            }
            if (polylineOptions != null) {
                mMap!!.addPolyline(polylineOptions)
            } else {
                Toast.makeText(applicationContext, "not found", Toast.LENGTH_SHORT).show()
            }
        }
    }
}

private fun PolylineOptions?.addAll(points: ArrayList<Any?>) {

}
