//this works best in a browser!

import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class DrawImageApplet extends Applet
                             implements ActionListener, Runnable {
   private Thread drawImageThread = null;
   private Button interruptButton;

   public void init(){
      setLayout(new BorderLayout());
      interruptButton = new Button("Interrupt");
      interruptButton.addActionListener(this);
      add(interruptButton, BorderLayout.SOUTH);
   }

   public void actionPerformed(ActionEvent e){
      drawImageThread.interrupt();
   }

   public void start() {
      if (drawImageThread == null) {
         drawImageThread = new Thread(this);
         drawImageThread.start();
       }
   }

   public void stop() {
      drawImageThread = null;
   }

   public void run() {
      Thread currentThread = Thread.currentThread();
      while(currentThread == drawImageThread){
         for (int i = 0; i < 255; i++){
            for (int j = 0; j < 255; j++){
               if (drawImageThread.isInterrupted() == false){
                  Graphics g = getGraphics();
                  g.setColor(new Color(i, j, (i+j)/2));
                  g.drawLine(i, j, 1, 1);
                  Thread.yield();
               }
            }
         }
      }
   }

}
