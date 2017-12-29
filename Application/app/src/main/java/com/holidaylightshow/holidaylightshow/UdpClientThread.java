package com.holidaylightshow.holidaylightshow;

import android.os.Message;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.io.*;
import java.net.*;

public class UdpClientThread extends Thread {

    private static final String DST_ADDRESS = "192.168.0.1";
	private static final int DST_PORT = 5005;
    private String data;
    
    public UdpClientThread(String data) {
        super();
		this.data = data;
    }

    @Override public void run() {
        try {
            DatagramSocket socket = new DatagramSocket(DST_PORT);
            InetAddress address = InetAddress.getByName(DST_ADDRESS);

            byte[] sendData = new byte[64];
            sendData = data.getBytes();
            DatagramPacket packet = new DatagramPacket(sendData, sendData.length, DST_ADDRESS, DST_PORT);
            socket.send(packet);
        } catch (SocketException e) {
            e.printStackTrace();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (socket != null) {
                socket.close();
            }
        }
    }
	
}