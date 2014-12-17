package fi.kajakgames.uth;

import java.util.Vector;

import android.content.Context;
import android.content.Intent;
import android.location.Location;


import android.media.AudioManager;
import android.os.Bundle;
import android.os.Vibrator;
import android.util.Log;
import android.view.*;
import fi.kajakgames.uth.R;

import com.google.android.gms.ads.*;
import com.google.android.gms.games.Games;
import com.google.android.gms.plus.Plus;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesClient;
import com.google.android.gms.common.GooglePlayServicesUtil;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.drive.internal.OnResourceIdSetResponse;
import com.google.android.gms.analytics.*;
import com.google.android.gms.location.*;

import fi.kajakgames.uth.BaseGameUtils;

public class GameActivity extends android.app.NativeActivity
implements LocationListener, 
GoogleApiClient.ConnectionCallbacks, 
GoogleApiClient.OnConnectionFailedListener
{
	private boolean useGoogleAnalytics = false;
	private boolean usePlayServices = false;
	private boolean useGPS = false;
	private static final long INTERVAL = 1000 * 15;
    private static final long FASTEST_INTERVAL = 1000 * 5;
	
	Advertisement initialAd = null;
	Vector<Advertisement> adList = new Vector<Advertisement>(32);
	
	GameActivity gameActivity;
	GoogleApiClient mClient;
	GoogleApiClient lClient;
	Location mCurLocation;
	LocationRequest locationRequest;
	
	//Test Only
	private InterstitialAd interstitial;
	private InterstitialAd interstitial2;
	AdRequest adRequest;
	static
	{
		System.loadLibrary("sndfile");
		System.loadLibrary("openal");
		System.loadLibrary("uthengine");
	}
	

	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		// Make your custom init here
		setVolumeControlStream(AudioManager.STREAM_MUSIC);
		
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
		
		if(gameActivity == null)
			gameActivity = this;
	
		int dpi = getResources().getDisplayMetrics().densityDpi;
		float padding = ((dpi / 100.0f) * getResources().getDisplayMetrics().density);
		initialAd = new Advertisement(this, (int)padding);
		
		//Test
		interstitial = new InterstitialAd(this);
		final String adID = this.getString(R.string.AdMobPublisherID) + "/" + "9257920890";
		interstitial.setAdUnitId(adID);
	    adRequest = new AdRequest.Builder()
									    .addTestDevice("E69C2A8B1675A10447583C0049DC0D26")
									    .build();
	    
	    interstitial.loadAd(adRequest);

		if(usePlayServices){
		mClient = new GoogleApiClient.Builder(this)
		.addApi(Games.API).addScope(Games.SCOPE_GAMES)
		.addApi(Plus.API).addScope(Plus.SCOPE_PLUS_LOGIN)
		.addApi(LocationServices.API)
		.addOnConnectionFailedListener(this)
		.addConnectionCallbacks(this)
		.build(); }
		
		if(useGoogleAnalytics){	GoogleAnalytics.getInstance(this).newTracker(R.xml.app_tracker); }
		
		if(useGPS){
		lClient = new GoogleApiClient.Builder(this)
		.addApi(LocationServices.API)
		.addConnectionCallbacks(this)
		.addConnectionCallbacks(this)
		.build(); 
	
		
		locationRequest = LocationRequest.create();
		locationRequest.setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY);
		locationRequest.setInterval(INTERVAL);
		locationRequest.setFastestInterval(FASTEST_INTERVAL);
		
		}
	}
	
	public void onResume()
	{
		super.onResume();
		
		gameActivity.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				interstitial.loadAd(adRequest);
			}
		});
	}
	
	boolean IsGPGSAvailable()
	{
		int result = GooglePlayServicesUtil.isGooglePlayServicesAvailable(this);
		
		if (result == ConnectionResult.SERVICE_VERSION_UPDATE_REQUIRED)
		{
			Log.d("GooglePlayServices", "" + GooglePlayServicesUtil.getErrorString(result));
			return false;
		}
		if (result == ConnectionResult.SERVICE_MISSING)
		{
			Log.d("GooglePlayServices", "" + GooglePlayServicesUtil.getErrorString(result));
			return false;
		}
		if (result == ConnectionResult.SERVICE_DISABLED)
		{
			Log.d("GooglePlayServices", "" + GooglePlayServicesUtil.getErrorString(result));
			return false;
		}
		if (result == ConnectionResult.SUCCESS)
		{
			Log.d("GooglePlayServices", "" + GooglePlayServicesUtil.getErrorString(result));
			return true;
		}
		return false;
	}
	
	public void onStart()
	 {
	 	super.onStart();
	 	if(usePlayServices){ mClient.connect(); }
	 	
	 	if(useGoogleAnalytics){ GoogleAnalytics.getInstance(this).reportActivityStart(this); }
	 	
	 	if(useGPS){ lClient.connect(); }
	 }
	  
	 public void onStop()
	 {
		if(usePlayServices){ mClient.disconnect(); }
			
		if(useGoogleAnalytics){ GoogleAnalytics.getInstance(this).reportActivityStop(this); }
		
		if(useGPS){ lClient.disconnect(); }
		
		super.onStop();	
	}
	
	public boolean MoveTaskToBack(boolean value)
	{
		boolean returnable = moveTaskToBack(value);
		
		return returnable;
	}
	
	public void Vibrate(final int time)
	{
		Vibrator vibra = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
		
		if(vibra == null)
			Log.i("uth-engine", "vibra is null");
			
		Log.d("Vibra", "Has Vibrator: " + vibra.hasVibrator());
		vibra.vibrate(time);
	}
	
	public void ShowAd(final int offsetX, final int offsetY, final int origin, final String name)
	{
		final String publisher = this.getString(R.string.AdMobPublisherID);
		
		gameActivity.runOnUiThread(new Runnable() 
		{
			@Override
			public void run()
			{
				boolean exists = false;
				int index = 0;
				
				for(int i = 0; i < adList.size(); i++)
				{
					if(adList.get(i).name.equals(name))
					{
						exists = true;
						index = i;
						break;
					}
				}
				
				if(exists == false)
				{
					String adID  = publisher + "/" + name;
					int[] offset = {offsetX, offsetY};
					Advertisement lol = new Advertisement(adID, initialAd, AdSize.BANNER, offset, origin);
					lol.name = name;
					
					adList.add(lol);
					index = adList.indexOf(lol);
				}
				adList.get(index).Show();
			}
		});
	}
	
	public void ShowAdFull(final String adID)
	{
		gameActivity.runOnUiThread(new Runnable() 
		{
			@Override
			public void run()
			{				
				if (interstitial != null && interstitial.isLoaded())
				{
					interstitial.show();
				}
			}
		});
	}
	
	public void HideAd(final String name)
	{
		final String publisherID = this.getString(R.string.AdMobPublisherID);
		gameActivity.runOnUiThread(new Runnable() 
		{
			@Override
			public void run()
			{
				for(int i = 0; i < adList.size(); i++)
				{
					if(adList.get(i).name.equals(name))
					{
						adList.get(i).Hide();
						break;
					}
				}
			}
		});
	}
	public void UnlockAchievement(String achievement_id)
	{	
		if(!IsGPGSAvailable())
			return;
		
		if(usePlayServices)
		{
			if(!mClient.isConnected())
				mClient.connect();	
			
			Games.Achievements.unlock(mClient, achievement_id);
		}
		else
		{
			Log.d("uth-engine", "GooglePlayGameServices is disabled.");
		}
	}
	public void IncrementAchievement(String achievement_id, int steps)
	{	
		if(!IsGPGSAvailable())
			return;
		
		if(usePlayServices)
		{
			if(!mClient.isConnected())
				mClient.connect();	
			
			Games.Achievements.increment(mClient, achievement_id, steps);
		}
		else
		{
			Log.d("uth-engine", "GooglePlayGameServices is disabled.");
		}
	}
	
	public void ShowAchievements()
	{	
		if(!IsGPGSAvailable())
			return;
		
		if(usePlayServices)
		{
			if(!mClient.isConnected())
				mClient.connect();
			
			startActivityForResult(Games.Achievements.getAchievementsIntent(mClient), 5001);
		}
		else
		{
			Log.d("uth-engine", "GooglePlayGameServices is disabled.");
		}
	}
	
	public void SubmitHighScore(String leaderboard_id, int score)
	{	
		if(!IsGPGSAvailable())
			return;
		
		if(usePlayServices)
		{
			if(!mClient.isConnected())
				mClient.connect();
			
			Games.Leaderboards.submitScore(mClient, leaderboard_id, score);
		}
		else
		{
			Log.d("uth-engine", "GooglePlayGameServices is disabled.");
		}
	}
	
	public void ShowLeaderboard(String leaderboard_id)
	{	
		if(!IsGPGSAvailable())
			return;
		
		if(usePlayServices)
		{
			if(!mClient.isConnected())
				mClient.connect();
			
			startActivityForResult(Games.Leaderboards.getLeaderboardIntent(mClient, leaderboard_id), 5002);
		}
		else
		{
			Log.d("uth-engine", "GooglePlayGameServices is disabled.");
		}
	}
	

	public String GetCurrentLocation()
	{
		Log.d("getloc", "doh");
		if(!IsGPGSAvailable())
			return "";
		Log.d("getloc", "doh2");
		if(useGPS){
		mCurLocation = LocationServices.FusedLocationApi.getLastLocation(lClient);
		
		//Log.d("location test", "" + mCurLocation); 
		
		//Log.d("location string", "" + mCurLocation.toString());
	
		return mCurLocation.toString();
		}
		else
		{
			return "GPS is disabled!";
		}
	}
	public float DistanceTo(double endLatitude, double endLongitude)
	{
		if(!IsGPGSAvailable())
			return 0;
		
		if(useGPS){
		float[] result = {0, 0, 0};
		
		//GetCurrentLocation();
		//double startLatitude = mCurLocation.getLatitude();
		//double startLongitude = mCurLocation.getLongitude();
		double startLatitude = GetLatitude();
		double startLongitude = GetLongitude();
		
		Location.distanceBetween(startLatitude, startLongitude, endLatitude, endLongitude, result);
		
		return result[0];
		}
		else
		{
			Log.d("uth-engine", "GPS is disabled!");
			return 0;
		}
	}
	public float DistanceBetween(double startLatitude, double startLongitude, double endLatitude, double endLongitude)
	{
		if(!IsGPGSAvailable())
			return 0;
		
		if(useGPS){
		float[] result = {0, 0, 0 };
		
		Location.distanceBetween(startLatitude, startLongitude, endLatitude, endLongitude, result);
		
		return result[0];
		}
		else
		{
			Log.d("uth-engine", "GPS is disabled!");
			return 0;
		}
	}
	public double GetLatitude()
	{
		if(!IsGPGSAvailable())
			return 0;
		
		if(useGPS){
		double result = 0;

		//GetCurrentLocation();
		result = LocationServices.FusedLocationApi.getLastLocation(lClient).getLatitude();
		
		return result;
		}
		else
		{
			Log.d("uth-engine", "GPS is disabled!");
			return 0;
		}
	}
	public double GetLongitude()
	{
		if(!IsGPGSAvailable())
			return 0;
		
		if(useGPS){
		double result = 0;
		
		//GetCurrentLocation();
		result = LocationServices.FusedLocationApi.getLastLocation(lClient).getLongitude();
		
		return result;
		}
		else
		{
			Log.d("uth-engine", "GPS is disabled!");
			return 0;
		}
	}
	public float GetAccuracy()
	{
		if(!IsGPGSAvailable())
			return 0;
		
		if(useGPS){
		float result = 0;
		
		//GetCurrentLocation();
		result = LocationServices.FusedLocationApi.getLastLocation(lClient).getAccuracy();
		
		return result;
		}
		else
		{
			Log.d("uth-engine", "GPS is disabled");
			return 0;
		}
	}
	
	private static int RC_SIGN_IN = 9001;
	private boolean mResolvingConnectionFailure = false;
	private boolean mAutoStartSignInFlow = true;
	private boolean mSignInClicked = false;

	@Override
	public void onConnectionFailed(ConnectionResult arg0) 
	{
		Log.d("uth-engine", "Connection failed, result: " + arg0);
		
		if (mResolvingConnectionFailure)
		{
			return;
		}
		
		if(mSignInClicked || mAutoStartSignInFlow)
		{
			mAutoStartSignInFlow = false;
			mSignInClicked = false;
			mResolvingConnectionFailure = true;		
			
			
			if(!BaseGameUtils.resolveConnectionFailure(this, mClient, arg0, RC_SIGN_IN, "Error message"))
			{
				mResolvingConnectionFailure = false;
			}
		}
	}

	@Override
	public void onConnected(Bundle arg0) 
	{
		Log.d("uth-engine", "OnConnected, bundle: " + arg0);
		//Toast.makeText(this, "Connected", Toast.LENGTH_SHORT).show();
		if(useGPS){
		LocationServices.FusedLocationApi.requestLocationUpdates(lClient, locationRequest, gameActivity);
		}
	}
	@Override
	public void onConnectionSuspended(int arg0) 
	{
		Log.d("uth-engine", "onConnectionSuspended, arg: " + arg0);
	}
	@Override
	protected void onActivityResult(int requestCode, int responseCode, Intent intent)
	 {
		 if(requestCode == RC_SIGN_IN)
		 {
			 mSignInClicked = false;
			 Log.d("uth-engine", "onActivityResult with requestCode == 9001, responseCode=" + responseCode + ", intent=" + intent);
		 
			 if(responseCode == RESULT_OK)
			 {
				 mClient.connect();
			 }
			 else
			 {
				 BaseGameUtils.showActivityResultError(this, requestCode, responseCode, R.string.signin_failure, R.string.signin_other_error);
			 }
		 }
	 }

	@Override
	public void onLocationChanged(Location arg0) {
		// TODO Auto-generated method stub
		Log.d("location", "changed");
	}

	
	public void onDisconnected() 
	{
		//Toast.makeText(this, "Disconnected.", Toast.LENGTH_SHORT).show();
		Log.d("uth-engine", "Disconnected");
		
	}
	
	
}
