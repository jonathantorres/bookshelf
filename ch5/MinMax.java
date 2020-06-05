class ArrayDemo2 {
    public static void main(String[] args) {
        int nums[] = {
            4,5,6,
            98,10,22,
            71,11,5,6,
        };
        int min = nums[0];
        int max = nums[0];
        for (int i = 0; i < 10; i++) {
            if (nums[i] < min) {
                min = nums[i];
            }
            if (nums[i] > max) {
                max = nums[i];
            }
        }
        System.out.println("Max num is " + max + " and Min num is " + min);
    }
}
