package com.holidaylightshow.holidaylightshow;

public class UDPServer {

    private byte frequency;
    private byte music;
    private byte shape;
    private byte[] color;
    private byte pattern;

    public UDPServer(byte frequency, byte music, byte shape, byte[] color, byte pattern) {
        this.frequency = frequency;
        this.music = music;
        this.shape = shape;
        this.color = color;
        this.pattern = pattern;
    }

    public void connect() {
        /*DatagramSocket serverSocket = new DatagramSocket(5005);
        byte[] sendData = new byte[1024];
        byte[] buffer = {10,23,12,31,43,32,24};
        byte [] IP={-64,-88,1,106};
        InetAddress address = InetAddress.getByAddress(IP);
        DatagramPacket packet = new DatagramPacket(
                buffer, buffer.length, address, 57
        );
        while(true)
        {
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
            serverSocket.receive(receivePacket);
            String sentence = new String( receivePacket.getData());
            System.out.println("RECEIVED: " + sentence);
            InetAddress IPAddress = receivePacket.getAddress();
            int port = receivePacket.getPort();
            String capitalizedSentence = sentence.toUpperCase();
            sendData = capitalizedSentence.getBytes();
            DatagramPacket sendPacket =
                    new DatagramPacket(sendData, sendData.length, IPAddress, port);
            serverSocket.send(sendPacket);
        }*/
    }

}
