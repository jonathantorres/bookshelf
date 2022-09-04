int main(int argc, char const *argv[])
{
    char names[20];
    char key[16] = "This is the key";

    bsearch(key, names, 20, 16, cmpfunc);

    return 0;
}
