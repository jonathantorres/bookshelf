void fix_set_diag_opt(fix_matrix A, int val)
{
    int *a   = &A[0][0];
    long i   = 0;
    long end = N * (N + 1);

    do {
        a[i] = val;
        i += (N + 1);
    } while (i != end);
}
