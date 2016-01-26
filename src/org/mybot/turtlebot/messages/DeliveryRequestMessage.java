/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.mybot.turtlebot.messages;

public class DeliveryRequestMessage {
    private int message_code;
    private double source_x;
    private double source_y;
    private double destination_x;
    private double destination_y;
    private double depot_x;
    private double depot_y;


    public DeliveryRequestMessage() {
    }

    public DeliveryRequestMessage(int message_code, double source_x, double source_y, double destination_x, double destination_y, double depot_x, double depot_y) {
        this.message_code = message_code;
        this.source_x = source_x;
        this.source_y = source_y;
        this.destination_x = destination_x;
        this.destination_y = destination_y;
        this.depot_x = depot_x;
        this.depot_y = depot_y;
    }

    public int getMessage_code() {
        return message_code;
    }

    public void setMessage_code(int message_code) {
        this.message_code = message_code;
    }

    public double getSource_x() {
        return source_x;
    }

    public void setSource_x(double source_x) {
        this.source_x = source_x;
    }

    public double getSource_y() {
        return source_y;
    }

    public void setSource_y(double source_y) {
        this.source_y = source_y;
    }

    public double getDestination_x() {
        return destination_x;
    }

    public void setDestination_x(double destination_x) {
        this.destination_x = destination_x;
    }

    public double getDestination_y() {
        return destination_y;
    }

    public void setDestination_y(double destination_y) {
        this.destination_y = destination_y;
    }

    public double getDepot_x() {
        return depot_x;
    }

    public void setDepot_x(double depot_x) {
        this.depot_x = depot_x;
    }

    public double getDepot_y() {
        return depot_y;
    }

    public void setDepot_y(double depot_y) {
        this.depot_y = depot_y;
    }
}
