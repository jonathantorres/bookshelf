class MoonGravity {
    public static void main(String[] args) {
        double gravity = 0.17;
        for (int i = 10; i <= 250; i += 10) {
            System.out.println("Weight: " + i + " Moon Weight: " + i * gravity);
        }
    }
}
