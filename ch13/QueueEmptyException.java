class QueueEmptyException extends Exception {

    QueueEmptyException() {

    }

    public String toString() {
        return "Queue is empty.";
    }
}
