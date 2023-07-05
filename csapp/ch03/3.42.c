/* A: See code below */
/* B: It's a linked list and "fun" computes the sum of the elements on the list */

struct ELE {
    long v;
    struct ELE *p;
}

long fun(struct ELE *ptr)
{
    long res = 0;

    while (ptr) {
        res += ptr->v;
        ptr = ptr->p;
    }

    return res;
}
