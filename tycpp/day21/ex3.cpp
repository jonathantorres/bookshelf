#ifndef DEBUG
#define DPRINT(string)
#else
#define DPRINT(STRING) cout << #STRING;
#endif

int main(int argc, char const *argv[])
{
    return 0;
}
