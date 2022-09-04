#include <stdio.h>

void half(void *val, char type);

int main(int argc, char const *argv[])
{
    int i = 20;
    long l = 100000;
    float f = 12.456;
    double d = 123.044444;

    printf("%d\n", i);
    printf("%ld\n", l);
    printf("%f\n", f);
    printf("%lf\n", d);

    half(&i, 'i');
    half(&l, 'l');
    half(&f, 'f');
    half(&d, 'd');

    puts("");
    printf("%d\n", i);
    printf("%ld\n", l);
    printf("%f\n", f);
    printf("%lf\n", d);
    return 0;
}

void half(void *val, char type)
{
    switch (type) {
        case 'i':
        {
            *((int *)val) /= 2;
            break;
        }
        case 'l':
        {
            *((long *)val) /= 2;
            break;
        }
        case 'f':
        {
            *((float *)val) /= 2;
            break;
        }
        case 'd':
        {
            *((double *)val) /= 2;
            break;
        }
    }
}
