package com.holidaylightshow.holidaylightshow;

import android.content.Intent;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    private SharedPreferences sharedPreferences;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        getSupportActionBar().setTitle("Holiday Light Show");
        PreferenceManager.setDefaultValues(this, R.xml.preferences, false);
        sharedPreferences = PreferenceManager.getDefaultSharedPreferences(getBaseContext());
        TextView description = (TextView) findViewById(R.id.text_description);
        description.setText("Immerse your holiday with a brilliant light show! Easily customizable light show that will dazzle your senses.\n");

        Button connect = (Button) findViewById(R.id.button_connect);
        connect.setOnClickListener(new View.OnClickListener() {
            @Override public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, SettingsActivity.class);
                startActivity(intent);
            }
        });

        Button userManual = (Button) findViewById(R.id.button_manual);
        userManual.setOnClickListener(new View.OnClickListener() {
            @Override public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, UserManualActivity.class);
                startActivity(intent);
            }
        });
    }

}
