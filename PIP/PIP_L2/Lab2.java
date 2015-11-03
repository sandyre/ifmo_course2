// Вариант 1722

public class Lab2 {
  public static void main(String[] args) {
    Pidgeotto father = new Pidgeotto();
    Pidgeot daughter = new Pidgeot();
    Pidgeotto sister = new Pidgeot();

    daughter.gust(father);
    daughter.gust(sister);
    daughter.defenseCurl();
    father.workUp();
    daughter.keenEye();
    father.gust(sister);
    sister.batonPass();
    daughter.swordsDance();
    sister.workUp();
    daughter.lastChance();
    daughter.workUp();
    ((Pidgeot)sister).camouflage();
    father.gust(daughter);
    sister.lastChance();
    father.growth();
    father.lastChance();
  }
}

class Pidgeotto {
  public int surface;
  protected String poisonDark = "PoisonDark";
  protected String dark = "Dark";
  static int sky;
  protected String poison = "Poison";
  double length = 6.2;
  protected int juicer;

  public Pidgeotto() {
    sky = 89;
    juicer = 073;
  }

  {
    surface = 89;
    juicer = 39;
  }


  public void lastChance() {
    System.out.println("Pidgeotto casts Last Chance");
  }

  public void gust(Pidgeotto p) {
    System.out.println("Pidgeotto attacks Pidgeotto with Gust");
  }

  public void gust(Pidgeot p) {
    System.out.println("Pidgeotto attacks Pidgeot with Gust");
  }

  public static void workUp() {
    System.out.println("Pidgeotto casts Work Up");
  }

  public void growth() {
    double accuracy = 1.9;

    System.out.println((length - accuracy) == 4.3);
  }

  public void batonPass() {
    System.out.println(poisonDark == "Poison"+dark);
    System.out.println(poisonDark.equals(poison+"Dark"));
    System.out.println(poisonDark == "Poison"+"Dark");
    System.out.println(poisonDark.equals("Poison"+"Dark"));
    System.out.println(poisonDark.equals(poison+dark));
    System.out.println(poisonDark == poison+dark);
  }

  public void swordsDance() {
    System.out.println(surface - juicer);
    System.out.println(sky - surface);
    System.out.println(juicer + sky);
  }
}

class Pidgeot extends Pidgeotto {
  private String steel = "Steel";
  double depth = 5.4;
  private String steelDark = "SteelDark";
  private byte tracker = (byte) 0x89;

  public void gust(Pidgeot p) {
    System.out.println("Pidgeot attacks Pidgeot with Gust");
  }

  public static void workUp() {
    System.out.println("Pidgeot casts Work Up");
  }

  public void defenseCurl() {
    System.out.println(juicer - tracker);
    System.out.println(tracker - sky);
    System.out.println(tracker + surface);
  }

  public void gust(Pidgeotto p) {
    System.out.println("Pidgeot attacks Pidgeotto with Gust");
  }

  public void camouflage() {
    System.out.println(steelDark == new String("SteelDark"));
    System.out.println(steelDark == steel+dark);
    System.out.println(steelDark == (steel+dark).intern());
    System.out.println(steelDark == new String("Steel"+"Dark"));
  }

  public void lastChance() {
    System.out.println("Pidgeot casts Last Chance");
  }

  public void keenEye() {
    double evasion = 9.8;

    System.out.println((evasion + depth) == 4.4);
  }
}


