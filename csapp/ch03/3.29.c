/* A: The loop never terminates once we reach the first odd number (number 1) */
/* B: See code below */
long sum = 0;
long i   = 0;

while (i < 10) {
    if (i & 1) {
        goto iter;
    }

    sum += i;

iter:
    i++;
}
