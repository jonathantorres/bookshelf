int bis(int x, int m);
int bic(int x, int m);

int bool_or(int x, int y)
{
    int result = bis(x, y);
    return result;
}

int bool_xor(int x, int y)
{
    int result = bis(bic(x, y), bic(y, x));
    return result;
}

int main(void)
{
    return 0;
}
