abstract class TwoDShape {
    private String name;
    private double width;
    private double height;

    TwoDShape() {
        width = 0;
        height = 0;
        name = "none";
    }

    TwoDShape(double w, double h, String n) {
        width = w;
        height = h;
        name = n;
    }

    TwoDShape(double x, String n) {
        width = x;
        height = x;
        name = n;
    }

    TwoDShape(TwoDShape ob) {
        width = ob.width;
        height = ob.height;
        name = ob.name;
    }

    void showDim() {
        System.out.println("Width and height are " + width + " and " + height);
    }

    abstract double area();

    double getWidth() { return width; }
    double getHeight() { return height; }
    String getName() { return name; }
    void setWidth(double w) { width = w; }
    void setHeight(double h) { height = h; }
}

class Triangle extends TwoDShape {
    private String style;

    Triangle() {
        super();
        style = "none";
    }

    Triangle(String s, double w, double h) {
        super(w, h, "triangle");
        style = s;
    }

    Triangle(double x) {
        super(x, "triangle");
        style = "filled";
    }

    Triangle(Triangle ob) {
        super(ob);
        style = ob.style;
    }

    public double area() {
        return getWidth() * getHeight() / 2;
    }

    void showStyle() {
        System.out.println("Triangle is " + style);
    }
}

class Rectangle extends TwoDShape {
    Rectangle() {
        super();
    }

    Rectangle(double w, double h) {
        super(w, h, "rectangle");
    }

    Rectangle(double x) {
        super(x, "rectangle");
    }

    Rectangle(Rectangle ob) {
        super(ob);
    }

    public boolean isSquare() {
        if (getWidth() == getHeight()) {
            return true;
        }
        return false;
    }

    public double area() {
        return getWidth() * getHeight();
    }
}

class AbsShape {
    public static void main(String[] args) {
        TwoDShape shapes[] = new TwoDShape[4];
        shapes[0] = new Triangle("outlined", 8.0, 12.0);
        shapes[1] = new Rectangle(10);
        shapes[2] = new Rectangle(10, 4);
        shapes[3] = new Triangle(7.0);

        for (TwoDShape shape: shapes) {
            System.out.println("Object is " + shape.getName());
            System.out.println("Area is " + shape.area());
            System.out.println();
        }
    }
}
