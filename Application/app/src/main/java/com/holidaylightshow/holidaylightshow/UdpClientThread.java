package com.holidaylightshow.holidaylightshow;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

public class UdpClientThread extends Thread {

    private static final String DST_ADDRESS = "192.168.0.1";
    private static final int DST_PORT = 5005;
    private SettingsActivity.UdpClientHandler udpClientHandler;
    private String data;
    private DatagramSocket socket;
    private InetAddress address;

    public UdpClientThread(SettingsActivity.UdpClientHandler udpClientHandler, String data) {
        super();
        this.udpClientHandler = udpClientHandler;
        this.data = data;
    }

    @Override public void run() {
        udpClientHandler.sendState("Connecting...");

        try {
            socket = new DatagramSocket(DST_PORT);
            address = InetAddress.getByName(DST_ADDRESS);

            byte[] sendData = new byte[64];
            sendData = data.getBytes();
            DatagramPacket packet = new DatagramPacket(sendData, sendData.length, address, DST_PORT);
            socket.send(packet);

            udpClientHandler.sendState("Connected");
        } catch (SocketException e) {
            e.printStackTrace();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            socket.close();
            udpClientHandler.sendEndSignal();
        }
    }

}
