void psum1(float a[], float p[], long n)
{
    long i;
    float last, val;

    last = p[0] = a[0];

    for (i = 1; i < n; i++) {
        val  = last + a[i];
        p[i] = val;
        last = val;
    }
}
