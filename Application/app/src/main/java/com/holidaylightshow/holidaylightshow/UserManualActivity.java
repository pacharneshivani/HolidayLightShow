package com.holidaylightshow.holidaylightshow;

import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MenuItem;
import android.widget.TextView;

public class UserManualActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_user_manual);
        ActionBar actionBar = getSupportActionBar();
        actionBar.setTitle("User Manual");
        actionBar.setDisplayHomeAsUpEnabled(true);

        TextView description = (TextView) findViewById(R.id.text_manual);
        description.setText("The purpose of the Holiday Light Show is to create an affordable and user-friendly light show that anyone can set up, program, and enjoy. In the past several years, extravagant holiday light shows have grown in popularity because of the increasing availability and decreasing price of single-board computers and microcontrollers. Currently these light shows are much too difficult for most consumers to create on their own. There are not any user-friendly ways of setting up these light shows currently on the market.\n\nWith the world being technology driven and the enormous popularity of smart handheld devices, we have decided to use a tablet or phone as the means of programming the controller of the light show. This allows the user to open his/her favorite device and customize the light show through an application with a few simple steps. A wireless connection will be used to send commands from the application to the light show controller. Consumers will not have many wires strewn across their yard making for a clean yard. The only wires will be power for our controller boxes and lights. With easy setup, easily programmable light shows, pre-built shapes, and energy-efficient lights our Holiday Light Show simply cannot be beat.\n\nThe following is a brief description regarding the various controls that can be used to navigate through the app and customize the light show:\n- Customize the Light Show button: Launches the configuration screen that is used to set up the light show. This screen automatically loads (stores) the last used configuration.\n- Frequency seekbar: Customize the frequency of the light show between 88.1 MHz and 108.1 MHz.\n- Music listbox: Choose the music to use for the light show.\n- Active switch: Control how many shapes to use for the light show.\n- Shape listbox: Choose between four different shapes to use for the light show.\n- Color listbox: Choose between seven different colors to use for the light show.\n- Pattern listbox: Choose between three different patterns to use for the light show.\n- Play button: Start the light show.\n- Stop button: Stop the light show.")
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
