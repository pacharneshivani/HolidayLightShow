package com.holidaylightshow.holidaylightshow;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.Preference;
import android.preference.PreferenceFragment;
import android.preference.PreferenceManager;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.ListView;
import android.widget.SeekBar;
import android.widget.TextView;

import java.nio.ByteBuffer;

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
        byte frequency = 0;
        /*float f = sharedPreferences.getFloat("frequency_", 0.0f);
        int frequencyScaled = (int) ((f / 1.0f) * 100.0f);
        byte frequency = (byte) frequencyScaled;*/
        int musicInt = Integer.valueOf(sharedPreferences.getString("music", ""));
        byte music = (byte) musicInt;
        int shapeInt = Integer.valueOf(sharedPreferences.getString("shapes", ""));
        byte shape = (byte) shapeInt;
        int colorInt = Integer.valueOf(sharedPreferences.getInt("colors", 0));
        Log.d("color", String.valueOf(colorInt));
        byte[] color = ByteBuffer.allocate(4).putInt(colorInt).array();
        int patternInt = Integer.valueOf(sharedPreferences.getString("pattern", ""));
        byte pattern = (byte) patternInt;
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
