class Vehicle {
    int passengers;
    int fuelcap;
    int mpg;

    Vehicle(int passengers, int fuelcap, int mpg) {
        this.passengers = passengers;
        this.fuelcap = fuelcap;
        this.mpg = mpg;
    }

    int range() {
        return this.fuelcap * this.mpg;
    }

    double fuelneeded(int miles) {
        return (double) miles / this.mpg;
    }
}

class VehicleConsDemo {
    public static void main(String args[]) {
        Vehicle minivan = new Vehicle(7, 16, 21);
        int range;
        int dist = 90;

        range = minivan.range();
        System.out.println("Minivan can carry " + minivan.passengers + " passengers with a range of " + range);
        System.out.println("To go " + dist + " miles, it needs " + minivan.fuelneeded(dist) + " gallons of fuel");
    }
}
