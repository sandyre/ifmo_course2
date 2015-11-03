import java.io.*;
import java.util.*;

public class Task3
{
        public static void main(String[] args)
        {
                float r;
                try
                {
                        if(args.length != 0)
                        {
                                r = Float.parseFloat(args[0]);
                                if(r < 0)
                                {
                                        System.out.println("Radius have to be positive or 0. R = 3 (by default).");
                                        r = 3.0f;
                                } 
                        }
                        else
                        {
                                System.out.println("No arguments passed through command-line. R = 3 (by default).");
                                r = 3.0f;
                        }
                } catch(NumberFormatException e)
                {
                        System.out.println("First command-line argument is NaN. Radius will be default (R = 3).");
                        r = 3.0f;
                }

                ArrayList<Punto> puntos = new ArrayList<Punto>();
                puntos.add(new Punto(-1,1));
                puntos.add(new Punto(-2,3));
                puntos.add(new Punto(4,-5));
                puntos.add(new Punto(-3,0));
                puntos.add(new Punto(-3,4));
                puntos.add(new Punto(5,5));
                puntos.add(new Punto(-5,-5));
                puntos.add(new Punto(0,0));

                System.out.println("Kontur includes these puntos: ");

                Kontur kontur = new Kontur(r);
                Iterator<Punto> iter = puntos.iterator();
                do
                {
                        Punto punto = iter.next();
                        if(kontur.includesPunto(punto) == 1)
                        {
                                System.out.println("{" + punto.getX() + ","
                                        + punto.getY() + "}");
                        }
                } while(iter.hasNext());
        }
}