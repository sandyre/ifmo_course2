import java.util.Iterator;
import java.util.Map;

// var. 277
public class Lab4 {
    public static void main(String[] args) {
        B a = new B();
        B b = new H();
        H c = new H();
        c.f11();
        c.f12();
        b.f25();
        b.f17();
        b.f30();x
        c.f29();
        b.f18();
        a.f4();
        a.f37();
        c.f39();
        c.f9(a);
        b.f9(b);
        c.f9(c);
        c.f24();
        c.f50();
        c.f42();
        Thread t = new Thread(new Runnable() {
            public void run() {
                while(true) {
                    try {
                        H d = new H();
                        d.f32();
                        Thread.sleep(7);
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
}
class B {
    int f3;
    int f16;
    int f2;
    int f13;
    int f7;
    long f38;
    long f40;
    long f6;
    java.io.ObjectOutputStream stringsWriter;
    java.io.ObjectOutputStream printOut;
    java.io.ObjectOutputStream sampleWriter;
    int[] f22 = {0, 1, 0, 3, -2};
    int[] f5 = {3, -2, -2, 0, 0};
    int[] f26 = {3, 2, -3, -3, 2};
    java.util.Map<java.net.URL,byte[]> cache = new java.util.HashMap<java.net.URL,byte[]>();
    static int f48;
    static int f47;
    static int f45;
    static int f14;
    static int f44;
    java.util.List<String> f31 = new java.util.ArrayList<String>();
    java.util.List<String> f43 = new java.util.ArrayList<String>();
    java.util.List<String> f49 = new java.util.ArrayList<String>();
    public B() {
        f3 = 2;
        f16 = 0;
        f2 = 5;
        f13 = 9;
        f7 = 6;
        f38 = 9L;
        f40 = 8L;
        f6 = 0L;
        try {
            stringsWriter = new java.io.ObjectOutputStream(new java.io.FileOutputStream("stringsWriter.txt"));
            printOut = new java.io.ObjectOutputStream(new java.io.FileOutputStream("printOut.txt"));
            sampleWriter = new java.io.ObjectOutputStream(new java.io.FileOutputStream("sampleWriter.txt"));
        } catch (java.lang.Exception e) {
            // Do nothing
        }
    }
    public void init() {
        try {
            if (stringsWriter == null) stringsWriter = new java.io.ObjectOutputStream(new java.io.FileOutputStream("stringsWriter.txt"));
            System.out.println("Thread : " + Thread.currentThread() + ", stringsWriter = " + stringsWriter);
        } catch(Exception e) {
            // Ignore it
        }
        try {
            if (printOut == null) printOut = new java.io.ObjectOutputStream(new java.io.FileOutputStream("printOut.txt"));
            System.out.println("Thread : " + Thread.currentThread() + ", printOut = " + printOut);
        } catch(Exception e) {
            // Ignore it
        }
        try {
            if (sampleWriter == null) sampleWriter = new java.io.ObjectOutputStream(new java.io.FileOutputStream("sampleWriter.txt"));
            System.out.println("Thread : " + Thread.currentThread() + ", sampleWriter = " + sampleWriter);
        } catch(Exception e) {
            // Ignore it
        }
    }
    public byte[] getValueFromCache(String s) {
        try {
            java.net.URL url = new java.net.URL(s); // vo vremya initiatilaztion tam address luboi mojet stat
            Iterator it = cache.entrySet().iterator();
            while(it.hasNext())
            {
                Map.Entry pair = (Map.Entry)it.next();
                java.net.URL tmp = (java.net.URL)pair.getKey();
                if(tmp.getAuthority().equals(url.getAuthority()))
                {
                    return cache.get(it);
                }
            }
            cache.put(url, new byte[786432]);
            return cache.get(url);
        } catch (Exception e) {
            System.out.println("Error: invalid URL!");
            return null;
        }
    }

    public void f11() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(sampleWriter) {
                            sampleWriter.writeObject("метод f11 в классе B (#" + String.valueOf(i) + ")");
                            Thread.sleep(6);
                            sampleWriter.flush();
                            sampleWriter.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void f12() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(printOut) {
                            printOut.writeObject("метод f12 в классе B (#" + String.valueOf(i) + ")");
                            Thread.sleep(6);
                            printOut.flush();
                            printOut.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void f25() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(stringsWriter) {
                            stringsWriter.writeObject("метод f25 в классе B (#" + String.valueOf(i) + ")");
                            Thread.sleep(6);
                            stringsWriter.flush();
                            stringsWriter.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void f17() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(printOut) {
                            printOut.writeObject("метод f17 в классе B (#" + String.valueOf(i) + ")");
                            Thread.sleep(6);
                            printOut.flush();
                            printOut.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void f30() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(printOut) {
                            printOut.writeObject("метод f30 в классе B (#" + String.valueOf(i) + ")");
                            Thread.sleep(6);
                            printOut.flush();
                            printOut.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void f29() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                init();
                int i = 0;
                while(true) {
                    i++;
                    try {
                        synchronized(printOut) {
                            printOut.writeObject("метод f29 в классе B (#" + String.valueOf(i) + ")");
                            Thread.sleep(6);
                            printOut.flush();
                            printOut.reset();
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public static void f18() {
        System.out.println("метод f18 в классе B");
        System.out.println(f48);
    }
    public static void f4() {
        System.out.println("метод f4 в классе B");
        System.out.println((f48 + 5));
    }
    public static void f37() {
        System.out.println("метод f37 в классе B");
        System.out.println(f47);
    }
    public static void f39() {
        System.out.println("метод f39 в классе B");
        System.out.println((f47 - 3));
    }
    public void f9(B r) {
        r.f11();
    }
    public void f9(H r) {
        r.f12();
    }
}
class H extends B {
    public H() {
        f13 = 9;
        f6 = 8L;
    }
    public void f24() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                while(true) {
                    try {
                        synchronized(cache) {
                            getValueFromCache("https://www.google.com");
                            Thread.sleep(6);
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void f50() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                while(true) {
                    try {
                        synchronized(cache) {
                            getValueFromCache("https://www.google.com");
                            Thread.sleep(5);
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public void f42() {
        Thread t = new Thread(new Runnable() {
            public void run() {
                while(true) {
                    try {
                        synchronized(cache) {
                            getValueFromCache("https://www.google.com");
                            Thread.sleep(11);
                        }
                    } catch(Exception e) {
                        // Do nothing
                    }
                }
            }
        });
        t.start();
    }
    public static void f18() {
        System.out.println("метод f18 в классе H");
        System.out.println(++f48);
    }
    public static void f4() {
        System.out.println("метод f4 в классе H");
        System.out.println(f47);
    }
    public static void f37() {
        System.out.println("метод f37 в классе H");
        System.out.println((f47 - 4));
    }
    public static void f39() {
        System.out.println("метод f39 в классе H");
        System.out.println(f47);
    }
    public void f32() {
        for(int i = 0; i < 6; i++) {
            this.f43.add(String.valueOf(System.nanoTime()));
            // System.out.println(this.f43.size());
        }
    }
    public void f27() {
        for(int i = 0; i < 5; i++) {
            this.f43.add(String.valueOf(System.nanoTime()));
            // System.out.println(this.f43.size());
        }
    }
    public void f20() {
        for(int i = 0; i < 8; i++) {
            this.f31.add(String.valueOf(System.nanoTime()));
            // System.out.println(this.f31.size());
        }
    }
    public void f36() {
        for(int i = 0; i < 8; i++) {
            this.f31.add(String.valueOf(System.nanoTime()));
            // System.out.println(this.f31.size());
        }
    }
    public void f9(B r) {
        r.f25();
    }
    public void f9(H r) {
        r.f17();
    }
}