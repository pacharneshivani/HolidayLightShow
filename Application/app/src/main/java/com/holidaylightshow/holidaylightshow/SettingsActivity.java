package com.holidaylightshow.holidaylightshow;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.preference.PreferenceFragment;
import android.preference.PreferenceManager;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class SettingsActivity extends AppCompatActivity {

    private static final String STOP_SIGNAL = "e";
    private SharedPreferences sharedPreferences;
    private UdpClientHandler udpClientHandler;
    private UdpClientThread udpClientThread;
    TextView textViewRx;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ActionBar actionBar = getSupportActionBar();
        actionBar.setTitle("Settings");
        actionBar.setDisplayHomeAsUpEnabled(true);
        getFragmentManager().beginTransaction().replace(android.R.id.content, new SettingsFragment()).commit();
        textViewRx = (TextView)findViewById(R.id.received);
        sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getBaseContext());

        udpClientHandler = new UdpClientHandler(this);
    }

    private String getSharedPrefStatusString(boolean status, String key) {
        String result = "0";

        if (status) {
            if (key.contains("color")) {
                result = sharedPreferences.getString(key, "");//result = Integer.toHexString(sharedPreferences.getInt(key, 0));
            } else {
                result = sharedPreferences.getString(key, "");
            }
        }


        return result;
    }

    public void playLightShow(View v) {
        String frequency = String.valueOf(sharedPreferences.getInt("frequency", 0));
        float int_frequency = Integer.parseInt(frequency);
        /*if ((int_frequency % 2) == 0){
            int_frequency -= 1;
        }
        frequency = String.valueOf(int_frequency);*/
        String music1 = sharedPreferences.getString("music", "");
        float float_music = Float.parseFloat(music1) + 10;
        int int_music = (int) float_music;
        String music = String.valueOf(int_music);
        boolean status1 = sharedPreferences.getBoolean("status1", false);
        boolean status2 = sharedPreferences.getBoolean("status2", false);
        boolean status3 = sharedPreferences.getBoolean("status3", false);
        boolean status4 = sharedPreferences.getBoolean("status4", false);


        String shape1 = getSharedPrefStatusString(status1, "shape1");
        String color1 = getSharedPrefStatusString(status1, "color1");
        String pattern1 = getSharedPrefStatusString(status1, "pattern1");

        String shape2 = getSharedPrefStatusString(status2, "shape2");
        String color2 = getSharedPrefStatusString(status2, "color2");
        String pattern2 = getSharedPrefStatusString(status2, "pattern2");

        String shape3 = getSharedPrefStatusString(status3, "shape3");
        String color3 = getSharedPrefStatusString(status3, "color3");
        String pattern3 = getSharedPrefStatusString(status3, "pattern3");

        String shape4 = getSharedPrefStatusString(status4, "shape4");
        String color4 = getSharedPrefStatusString(status4, "color4");
        String pattern4 = getSharedPrefStatusString(status4, "pattern4");

        String data = frequency + music
                + shape1 + color1 + pattern1
                + shape2 + color2 + pattern2
                + shape3 + color3 + pattern3
                + shape4 + color4 + pattern4;

        String send_test = "Frequency is " + frequency + " Song is " + music + "\nStrand 0 is: "  + '0' +
                " Color 1 is " + color1  + " Pattern 1 is " + pattern1  + "\nStrand 1 is: " + '1' +
                " Color 2 is " + color2 + " Pattern 2 is " + pattern2 + "\nStrand 2 is: " + '2' +
                " Color 3 is " + color3 + " Pattern 3 is " + pattern3 + "\nStrand 3 is: " + '3'+
                " Color 4 is " + color4 + " Pattern 4 is " + pattern4 + "\nStrand 4 is: " + '4';

        udpClientThread = new UdpClientThread(udpClientHandler, data);
        udpClientThread.start();

        Button play = (Button) findViewById(R.id.button_play);
        //textViewRx.setText(send_test);
        play.setEnabled(false);
        updateState("Configuring Light Show");
        updateState(data);

    }

    public void stopLightShow(View v) {
        udpClientThread = new UdpClientThread(udpClientHandler, STOP_SIGNAL);
        udpClientThread.start();

        updateState("Stopping Light Show");
    }

    public void updateState(String state) {
        Toast.makeText(getApplicationContext(), state, Toast.LENGTH_SHORT).show();
    }

    public void clientEnd() {
        udpClientThread = null;

        Button play = (Button) findViewById(R.id.button_play);
        play.setEnabled(true);
        updateState("Send successful");
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            this.finish();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    public static class SettingsFragment extends PreferenceFragment {
        @Override
        public void onCreate(final Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            addPreferencesFromResource(R.xml.preferences);
        }

        @Override
        public void onActivityCreated(Bundle savedInstanceState) {
            super.onActivityCreated(savedInstanceState);
            View rootView = getView();
            ListView list = (ListView) rootView.findViewById(android.R.id.list);
            list.setDivider(null);
        }
    }

    public static class UdpClientHandler extends Handler {

        private SettingsActivity parent;
        private static final int UPDATE_STATE = 0;
        private static final int UPDATE_END = 1;

        public UdpClientHandler(SettingsActivity parent) {
            super();
            this.parent = parent;
        }

        public void sendState(String state){
            sendMessage(Message.obtain(this, UPDATE_STATE, state));
        }

        public void sendEndSignal() {
            sendEmptyMessage(UPDATE_END);
        }

        @Override public void handleMessage(Message message) {
            switch (message.what){
                case UPDATE_STATE:
                    parent.updateState((String) message.obj);
                    break;
                case UPDATE_END:
                    parent.clientEnd();
                    break;
                default:
                    super.handleMessage(message);
            }
        }

    }

}
