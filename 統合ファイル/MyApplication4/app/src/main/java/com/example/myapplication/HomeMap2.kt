package com.example.myapplication

import android.Manifest
import android.annotation.SuppressLint
import android.content.*
import android.content.pm.PackageManager
import android.graphics.Color
import android.location.Location
import android.os.*
import android.text.util.Linkify
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.localbroadcastmanager.content.LocalBroadcastManager
import com.example.myapplication.R.layout.activity_homemap2
import com.google.android.gms.maps.CameraUpdateFactory
import com.google.android.gms.maps.GoogleMap
import com.google.android.gms.maps.SupportMapFragment
import com.google.android.gms.maps.model.*
import kotlinx.android.synthetic.main.activity_homemap2.*
import permissions.dispatcher.NeedsPermission
import permissions.dispatcher.RuntimePermissions
import java.util.*


@RuntimePermissions
class HomeMap2 : AppCompatActivity() {
    private val TAG = "HomeMap2"

    private lateinit var map: GoogleMap

    var locationService: LocationService? = null

    private var userPositionMarker: Marker? = null
    private var locationAccuracyCircle: Circle? = null
    private var userPositionMarkerBitmapDescriptor: BitmapDescriptor? = null
    private var runningPathPolyline: Polyline? = null
    private val polylineOptions: PolylineOptions? = null
    private val polylineWidth = 30


    //boolean isZooming;
    //boolean isBlockingAutoZoom;

    internal var zoomable = true

    internal var zoomBlockingTimer: Timer? = null
    internal var didInitialZoom: Boolean = false
    private var handlerOnUIThread: Handler? = null


    private var locationUpdateReceiver: BroadcastReceiver? = null
    private var predictedLocationReceiver: BroadcastReceiver? = null

    private var startButton: Button? = null
    private var stopButton: Button? = null
    private var resetButton: Button? = null

    /* Filter */
    private var predictionRange: Circle? = null
    internal var oldLocationMarkerBitmapDescriptor: BitmapDescriptor? = null
    internal var noAccuracyLocationMarkerBitmapDescriptor: BitmapDescriptor? = null
    internal var inaccurateLocationMarkerBitmapDescriptor: BitmapDescriptor? = null
    internal var kalmanNGLocationMarkerBitmapDescriptor: BitmapDescriptor? = null
    internal var malMarkers = ArrayList<Marker>()
    internal val handler = Handler()



    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(activity_homemap2)
        val intent1: Intent = getIntent()
        //thread {
            // Obtain the SupportMapFragment and get notified when the map is ready to be used.
            val mapFragment = supportFragmentManager
                    .findFragmentById(R.id.map) as SupportMapFragment
            mapFragment.getMapAsync { googleMap ->

                /**
                 * Manipulates the map once available.
                 * This callback is triggered when the map is ready to be used.
                 * This is where we can add markers or lines, add listeners or move the camera. In this case,
                 * we just add a marker near Sydney, Australia.
                 * If Google Play services is not installed on the device, the user will be prompted to install
                 * it inside the SupportMapFragment. This method will only be triggered once the user has
                 * installed Google Play services and returned to the app.
                 */
                setupGoogleMapWithPermissionCheck(googleMap)

            }



            locationUpdateReceiver = object : BroadcastReceiver() {
                override fun onReceive(context: Context, intent: Intent) {
                    val newLocation = intent.getParcelableExtra<Location>("location")

                    if (newLocation != null) {
                        drawLocationAccuracyCircle(newLocation)
                    }
                    if (newLocation != null) {
                        drawUserPositionMarker(newLocation)
                    }

                    this@HomeMap2.locationService?.let {
                        if (it.isLogging) {
                            addPolyline()
                        }
                    }

                    if (newLocation != null) {
                        zoomMapTo(newLocation)
                    }

                    /* Filter Visualization */
                    drawMalLocations()

                }
            }

            predictedLocationReceiver = object : BroadcastReceiver() {
                override fun onReceive(context: Context, intent: Intent) {
                    val predictedLocation = intent.getParcelableExtra<Location>("location")

                    if (predictedLocation != null) {
                        drawPredictionRange(predictedLocation)
                    }

                }
            }

            locationUpdateReceiver?.let {
                LocalBroadcastManager.getInstance(this).registerReceiver(
                        it,
                        IntentFilter("LocationUpdated")
                )
            }

            predictedLocationReceiver?.let {
                LocalBroadcastManager.getInstance(this).registerReceiver(
                        it,
                        IntentFilter("PredictLocation")
                )
            }

            startButton = this.findViewById(R.id.start_button) as Button
            stopButton = this.findViewById(R.id.stop_button) as Button
            resetButton = this.findViewById(R.id.reset_button) as Button
            stopButton?.visibility = View.INVISIBLE

            //スタート処理&再開
            var stoptime: Long = 0
            startButton?.setOnClickListener {
                startButton?.visibility = View.INVISIBLE
                stopButton?.visibility = View.VISIBLE

               // clearPolyline()
                //clearMalMarkers()
                chronometer.base = SystemClock.elapsedRealtime() + stoptime
                chronometer.start()
                this@HomeMap2.locationService?.startLogging()
            }

            //ストップ処理
            stopButton?.setOnClickListener {
                startButton?.visibility = View.VISIBLE
                stopButton?.visibility = View.INVISIBLE

                stoptime = chronometer.base - SystemClock.elapsedRealtime()
                chronometer.stop()
                this@HomeMap2.locationService?.stopLogging()
            }

        //リセット処理
        resetButton?.setOnClickListener {
            startButton?.visibility = View.VISIBLE
            stopButton?.visibility = View.INVISIBLE

            chronometer.base = SystemClock.elapsedRealtime()
            stoptime = 0
            chronometer.stop()
            clearPolyline()
            clearMalMarkers()
            this@HomeMap2.locationService?.stopLogging()
            val intent = Intent(this.application, Result::class.java)
        }


            oldLocationMarkerBitmapDescriptor = BitmapDescriptorFactory.fromResource(R.drawable.old_location_marker)
            noAccuracyLocationMarkerBitmapDescriptor =
                    BitmapDescriptorFactory.fromResource(R.drawable.no_accuracy_location_marker)
            inaccurateLocationMarkerBitmapDescriptor =
                    BitmapDescriptorFactory.fromResource(R.drawable.inaccurate_location_marker)
            kalmanNGLocationMarkerBitmapDescriptor =
                    BitmapDescriptorFactory.fromResource(R.drawable.kalman_ng_location_marker)

        }


        override fun onCreateOptionsMenu(menu: Menu): Boolean {
            val inflater = menuInflater
            inflater.inflate(R.menu.main, menu)
            return super.onCreateOptionsMenu(menu)
        }

        // オプションメニューのアイテムが選択されたときに呼び出されるメソッド
        override fun onOptionsItemSelected(item: MenuItem): Boolean {
            val intent1: Intent = getIntent()
            val id1: String = intent1.extras?.getString("ID", "a") ?:""

            when (item.itemId) {
                R.id.item1 -> {
                    val intent = Intent(this.application, CheckUserInfo::class.java)
                    //ID受け渡し
                    intent.putExtra("ID", id1)
                    startActivity(intent)
                    return true
                }
                R.id.item2 -> {
                    val intent = Intent(this.application, ResultActivity::class.java)
                    //ID受け渡し
                    intent.putExtra("ID", id1)
                    startActivity(intent)
                    return true
                }
                R.id.item3 -> {
                    val textInquiry = findViewById<TextView>(R.id.item3)
                    textInquiry.setText("https://docs.google.com/forms/d/e/1FAIpQLSc4HJYQdx2DEvIIF3_GXxixvbdbQ3UKCS_YjPP3PVjP59F_5A/viewform")
                    Linkify.addLinks(textInquiry, Linkify.ALL)
                }
            }
            return super.onOptionsItemSelected(item)
        }

        @NeedsPermission(Manifest.permission.ACCESS_FINE_LOCATION)
        fun setupGoogleMap(googleMap: GoogleMap) {
            map = googleMap
            map.uiSettings.isZoomControlsEnabled = false
            if (ActivityCompat.checkSelfPermission(
                            this,
                            Manifest.permission.ACCESS_FINE_LOCATION
                    ) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(
                            this,
                            Manifest.permission.ACCESS_COARSE_LOCATION
                    ) != PackageManager.PERMISSION_GRANTED
            ) {
                // TODO: Consider calling
                //    ActivityCompat#requestPermissions
                // here to request the missing permissions, and then overriding
                //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                //                                          int[] grantResults)
                // to handle the case where the user grants the permission. See the documentation
                // for ActivityCompat#requestPermissions for more details.
                return
            }
            map.isMyLocationEnabled = false //TODO: RuntimePermissionを後で入れる
            map.uiSettings.isCompassEnabled = true
            map.uiSettings.isMyLocationButtonEnabled = true

            //10秒ごとに追跡
            map.setOnCameraMoveStartedListener { reason ->
                if (reason == GoogleMap.OnCameraMoveStartedListener.REASON_GESTURE) {
                    Log.d(TAG, "onCameraMoveStarted after user's zoom action")

                    zoomable = false

                    zoomBlockingTimer?.cancel()


                    handlerOnUIThread = Handler()

                    val task = object : TimerTask() {
                        override fun run() {
                            handlerOnUIThread?.post {
                                zoomBlockingTimer = null
                                zoomable = true
                            }
                        }
                    }
                    zoomBlockingTimer = Timer()
                    zoomBlockingTimer?.schedule(task, (10 * 1000).toLong())
                    Log.d(TAG, "start blocking auto zoom for 10 seconds")
                }
            }

            val locationService = Intent(this.application, LocationService::class.java)

            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                this.application.startForegroundService(locationService)
            } else {
                this.application.startService(locationService)
            }
            this.application.bindService(locationService, serviceConnection, Context.BIND_AUTO_CREATE)

        }

        private val serviceConnection = object : ServiceConnection {
            override fun onServiceConnected(className: ComponentName, service: IBinder) {
                // This is called when the connection with the service has been
                // established, giving us the service object we can use to
                // interact with the service.  Because we have bound to a explicit
                // service that we know is running in our own process, we can
                // cast its IBinder to a concrete class and directly access it.
                val name = className.className

                if (name.endsWith("LocationService")) {
                    locationService = (service as LocationService.LocationServiceBinder).service

                    this@HomeMap2.locationService?.startUpdatingLocation()
                }
            }

            override fun onServiceDisconnected(className: ComponentName) {
                // This is called when the connection with the service has been
                // unexpectedly disconnected -- that is, its process crashed.
                // Because it is running in our same process, we should never
                // see this happen.
                if (className.className == "LocationService") {
                    this@HomeMap2.locationService?.stopUpdatingLocation()
                    locationService = null
                }
            }
        }


        public override fun onDestroy() {

            try {
                if (locationUpdateReceiver != null) {
                    unregisterReceiver(locationUpdateReceiver)
                }

                if (predictedLocationReceiver != null) {
                    unregisterReceiver(predictedLocationReceiver)
                }
            } catch (ex: IllegalArgumentException) {
                ex.printStackTrace()
            }


            super.onDestroy()

        }


        private fun zoomMapTo(location: Location) {
            val latLng = LatLng(location.latitude, location.longitude)

            if (this.didInitialZoom == false) {
                try {
                    map.moveCamera(CameraUpdateFactory.newLatLngZoom(latLng, 17.5f))
                    this.didInitialZoom = true
                    return
                } catch (e: Exception) {
                    e.printStackTrace()
                }

                //Toast.makeText(this.getActivity(), "Inital zoom in process", Toast.LENGTH_LONG).show();
            }

            if (zoomable) {
                try {
                    zoomable = false
                    map.animateCamera(CameraUpdateFactory.newLatLng(latLng),
                            object : GoogleMap.CancelableCallback {
                                override fun onFinish() {
                                    zoomable = true
                                }

                                override fun onCancel() {
                                    zoomable = true
                                }
                            })
                } catch (e: Exception) {
                    e.printStackTrace()
                }

            }
        }


        private fun drawUserPositionMarker(location: Location) {
            val latLng = LatLng(location.latitude, location.longitude)

            if (this.userPositionMarkerBitmapDescriptor == null) {
                userPositionMarkerBitmapDescriptor = BitmapDescriptorFactory.fromResource(R.drawable.user_position_point)
            }

            userPositionMarker?.let {
                it.setPosition(latLng)
            } ?: run {
                userPositionMarker = map.addMarker(
                        MarkerOptions()
                                .position(latLng)
                                .flat(true)
                                .anchor(0.5f, 0.5f)
                                .icon(this.userPositionMarkerBitmapDescriptor)
                )
            }
        }


        private fun drawLocationAccuracyCircle(location: Location) {
            if (location.accuracy < 0) {
                return
            }

            val latLng = LatLng(location.latitude, location.longitude)

            locationAccuracyCircle?.let {
                it.center = latLng
            } ?: run {
                this.locationAccuracyCircle = map.addCircle(
                        CircleOptions()
                                .center(latLng)
                                .fillColor(Color.argb(64, 0, 0, 0))
                                .strokeColor(Color.argb(64, 0, 0, 0))
                                .strokeWidth(0.0f)
                                .radius(location.accuracy.toDouble())
                ) //set readius to horizonal accuracy in meter.
            }
        }


        private fun addPolyline() {
            locationService?.locationList?.let { locationList ->

                runningPathPolyline?.let {
                    val toLocation = locationList[locationList.size - 1]
                    val to = LatLng(
                            toLocation.latitude,
                            toLocation.longitude
                    )
                    val points = it.points
                    points.add(to)
                    it.points = points
                } ?: run {
                    if (locationList.size > 1) {
                        val fromLocation = locationList[locationList.size - 2]
                        val toLocation = locationList[locationList.size - 1]

                        val from = LatLng(
                                fromLocation.latitude,
                                fromLocation.longitude
                        )

                        val to = LatLng(
                                toLocation.latitude,
                                toLocation.longitude
                        )

                        this.runningPathPolyline = map.addPolyline(
                                PolylineOptions()
                                        .add(from, to)
                                        .width(polylineWidth.toFloat()).color(Color.parseColor("#801B60FE")).geodesic(true)
                        )
                    }
                }
            }

        }

        private fun clearPolyline() {
            runningPathPolyline?.remove()
            runningPathPolyline = null
        }


        /* Filter Visualization */
        private fun drawMalLocations() {
            locationService?.let {
                drawMalMarkers(it.oldLocationList, oldLocationMarkerBitmapDescriptor!!)
                drawMalMarkers(it.noAccuracyLocationList, noAccuracyLocationMarkerBitmapDescriptor!!)
                drawMalMarkers(it.inaccurateLocationList, inaccurateLocationMarkerBitmapDescriptor!!)
                drawMalMarkers(it.kalmanNGLocationList, kalmanNGLocationMarkerBitmapDescriptor!!)
            }
        }

        private fun drawMalMarkers(locationList: ArrayList<Location>, descriptor: BitmapDescriptor) {
            for (location in locationList) {
                val latLng = LatLng(location.latitude, location.longitude)

                val marker = map.addMarker(
                        MarkerOptions()
                                .position(latLng)
                                .flat(true)
                                .anchor(0.5f, 0.5f)
                                .icon(descriptor)
                )

                malMarkers.add(marker)
            }
        }

        private fun drawPredictionRange(location: Location) {
            val latLng = LatLng(location.latitude, location.longitude)

            predictionRange?.let {
                it.center = latLng
            } ?: run {
                predictionRange = map.addCircle(
                        CircleOptions()
                                .center(latLng)
                                .fillColor(Color.argb(50, 30, 207, 0))
                                .strokeColor(Color.argb(128, 30, 207, 0))
                                .strokeWidth(1.0f)
                                .radius(30.0)
                ) //30 meters of the prediction range
            }


            this.predictionRange?.isVisible = true

            handler.postDelayed({ this@HomeMap2.predictionRange?.isVisible = false }, 2000)
        }

        private fun clearMalMarkers() {
            for (marker in malMarkers) {
                marker.remove()
            }
        }

        @SuppressLint("NeedOnRequestPermissionsResult")
        override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<String>, grantResults: IntArray) {
            super.onRequestPermissionsResult(requestCode, permissions, grantResults)
            // NOTE: delegate the permission handling to generated function
            onRequestPermissionsResult(requestCode, grantResults)
        }

}
