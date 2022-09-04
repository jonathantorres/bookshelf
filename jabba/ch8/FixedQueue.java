class FixedQueue implements ICharQ {
    private char q[];
    private int putloc, getloc;

    FixedQueue(int size) {
        q = new char[size];
        putloc = getloc = 0;
    }

    // put a character into the queue
    public void put(char ch) {
        if (putloc == q.length) {
            System.out.println(" Queue is full!");
            return;
        }
        q[putloc++] = ch;
    }

    // get a character from the queue
    public char get() {
        if (getloc == putloc) {
            System.out.println(" Queue is empty");
            return (char) 0;
        }

        return q[getloc++];
    }
}
