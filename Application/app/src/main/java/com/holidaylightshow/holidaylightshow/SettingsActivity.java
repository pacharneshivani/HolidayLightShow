package com.holidaylightshow.holidaylightshow;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceFragment;
import android.preference.PreferenceManager;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.ListView;

public class SettingsActivity extends AppCompatActivity {

    private SharedPreferences sharedPreferences;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ActionBar actionBar = getSupportActionBar();
        actionBar.setTitle("Settings");
        actionBar.setDisplayHomeAsUpEnabled(true);
        getFragmentManager().beginTransaction().replace(android.R.id.content, new SettingsFragment()).commit();
        sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getBaseContext());
    }

    public void playLightShow(View v) {
        String frequency = String.valueOf(sharedPreferences.getFloat("frequency_", 0.0f));
        String music = sharedPreferences.getString("music", "");
        String shape = sharedPreferences.getString("shapes", "");
        String color = String.valueOf(sharedPreferences.getInt("colors", 0));
        String pattern = sharedPreferences.getString("pattern", "");
        String data = String.join(",", frequency, music, shape, color, pattern);
        
        UdpClientThread udpClientThread = new UdpClientThread(data);
        udpClientThread.start();
        Toast.makeText(getActivity(), "Starting Holiday Light Show", Toast.LENGTH_LONG).show();
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

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            this.finish();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

}
