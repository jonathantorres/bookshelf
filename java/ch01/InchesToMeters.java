class InchesToMeters {
    public static void main(String args[]) {
        int inches;
        int totalInches = 0;
        int feet;
        int meters;
        int counter = 0;

        for (feet = 0; feet <= 12; feet++) {
            for (inches = 1; inches <= 12; inches++) {
                totalInches++;
                System.out.println(feet + " feet and " + inches + " inches is " + totalInches / 39.370 + " meters");
                counter++;

                if (counter == 12) {
                    System.out.println();
                    counter = 0;
                }
            }
        }
    }
}
