class DynQueue implements ICharQ {
    private char q[];
    private int putloc, getloc;

    DynQueue(int size) {
        q = new char[size];
        putloc = getloc = 0;
    }

    // put a character into the queue
    public void put(char ch) {
        if (putloc == q.length) {
            char t[] = new char[q.length*2];
            for (int i = 0; i< q.length; i++) {
                t[i] = q[i];
            }
            q = t;
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
