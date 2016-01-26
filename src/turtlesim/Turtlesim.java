/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package turtlesim;

import java.util.Map;
import java.util.TreeMap;

/**
 *
 * @author akoubaa
 */
public class Turtlesim {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Map <String, Class> topicsMap = new TreeMap<String, Class>();
        
        
        topicsMap.put("c1", String.class);
        topicsMap.put("c2", Integer.class);
        
        System.out.println("c1: "+ topicsMap.get("c1").getName());
        System.out.println("c2: "+ topicsMap.get("c2").getName());
        
        for (Class c : topicsMap.values()){
            System.out.println(c.getName());
        }
        
    }
    
}
