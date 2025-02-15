public class TestLab1 {
    public static void main(String[] args) {

        // New player object
        Player p1 = new Player("Raymond", "defence", 99);

        // Print statements
        System.out.println("Name: " + p1.getName());
        System.out.println("Position: " + p1.getPosition());
        System.out.println("Jersey Number: " + p1.getJerseyNum());

        // Setter method test
        p1.setJerseyNum(77);
        p1.setPosition("forward");

        // Print statements
        System.out.println("Name: " + p1.getName());
        System.out.println("Position: " + p1.getPosition());
        System.out.println("Jersey Number: " + p1.getJerseyNum());

        System.out.println(p1);
    }
}