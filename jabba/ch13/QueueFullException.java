class QueueFullException extends Exception {
    int size;

    QueueFullException(int s) {
        size = s;
    }

    public String toString() {
        return "Queue is full. Maximum size is " + size;
    }
}
