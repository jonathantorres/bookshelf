class Vehicle {
    int passengers;
    int fuelcap;
    int mpg;

    int range() {
        return fuelcap * mpg;
    }

    double fuelneeded(int miles) {
        return (double) miles / mpg;
    }
}

class VehicleDemo {
    public static void main(String args[]) {
        Vehicle minivan = new Vehicle();
        int range;
        int dist = 90;

        minivan.passengers = 7;
        minivan.fuelcap = 16;
        minivan.mpg = 21;

        range = minivan.range();
        System.out.println("Minivan can carry " + minivan.passengers + " passengers with a range of " + range);
        System.out.println("To go " + dist + " miles, it needs " + minivan.fuelneeded(dist) + " gallons of fuel");
    }
}
