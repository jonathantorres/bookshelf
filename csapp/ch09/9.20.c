#include "csapp.h"

/* Basic constants and macros */
#define WSIZE     4         /* Word and header/footer size (bytes) */
#define DSIZE     8         /* Double word size (bytes) */
#define CHUNKSIZE (1 << 12) /* Extend heap by this amount (bytes) */

#define MAX(x, y) ((x) > (y) ? (x) : (y))

// 20 MB
#define MAX_HEAP (20 * (1 << 20))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p)      (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp) ((char *)(bp)-WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp)-WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp)-GET_SIZE(((char *)(bp)-DSIZE)))

/* Global variables */
static char *heap_listp = 0; /* Pointer to first block */
static char *next_fitp;
static char *mem_heap;     /* Points to first byte of heap */
static char *mem_brk;      /* Points to last byte of heap plus 1 */
static char *mem_max_addr; /* Max legal heap addr plus 1*/

/* Function prototypes for internal helper routines */
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);

static void mem_init(void);
static void *mem_sbrk(int incr);
static int mm_init(void);
static void *mm_malloc(size_t size);
static void mm_free(void *ptr);

void test_malloc()
{
    // test malloc from libc
    clock_t time_start = clock();

    for (int i = 0; i < 1000000; i++) {
        char *b = malloc(i + 1);

        if (!b) {
            printf("No memory!\n");
            exit(EXIT_FAILURE);
        }

        free(b);
    }

    clock_t time_end = clock();

    printf("malloc \t\t total run time: %lf\n", difftime(time_end, time_start) / CLOCKS_PER_SEC);
}

void test_custom_malloc()
{
    // test custom allocator
    clock_t time_start = clock();

    for (int i = 0; i < 1000000; i++) {
        char *b = mm_malloc(i + 1);

        if (!b) {
            printf("No memory!\n");
            exit(EXIT_FAILURE);
        }

        mm_free(b);
    }

    clock_t time_end = clock();

    printf("mm_malloc \t total run time: %lf\n", difftime(time_end, time_start) / CLOCKS_PER_SEC);
}

// measure the allocations
int main(void)
{
    test_custom_malloc();
    test_malloc();

    return 0;
}

int mm_init(void)
{
    mem_init();

    /* Create the initial empty heap */
    if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void *)-1) {
        return -1;
    }

    PUT(heap_listp, 0);                            /* Alignment padding */
    PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1)); /* Prologue header */
    PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1)); /* Prologue footer */
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1));     /* Epilogue header */
    heap_listp += (2 * WSIZE);
    next_fitp = heap_listp;

    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if (extend_heap(CHUNKSIZE / WSIZE) == NULL) {
        return -1;
    }

    return 0;
}

static void *extend_heap(size_t words)
{
    char *bp;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;

    if ((long)(bp = mem_sbrk(size)) == -1) {
        return NULL;
    }

    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));         /* Free block header */
    PUT(FTRP(bp), PACK(size, 0));         /* Free block footer */
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */

    /* Coalesce if the previous block was free */
    return coalesce(bp);
}

void mm_free(void *bp)
{
    if (bp == 0) {
        return;
    }

    size_t size = GET_SIZE(HDRP(bp));

    if (heap_listp == 0) {
        mm_init();
    }

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
}

static void *coalesce(void *bp)
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size       = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) { /* Case 1 */
        return bp;
    } else if (prev_alloc && !next_alloc) { /* Case 2 */
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    } else if (!prev_alloc && next_alloc) { /* Case 3 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    } else { /* Case 4 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    /* Make sure the rover isn't pointing into the free block */
    /* that we just coalesced */
    if ((next_fitp > (char *)bp) && (next_fitp < NEXT_BLKP(bp))) {
        next_fitp = bp;
    }

    return bp;
}

void *mm_malloc(size_t size)
{
    size_t asize;      /* Adjusted block size */
    size_t extendsize; /* Amount to extend heap if no fit */
    char *bp;

    if (heap_listp == 0) {
        mm_init();
    }

    /* Ignore spurious requests */
    if (size == 0) {
        return NULL;
    }

    /* Adjust block size to include overhead and alignment reqs. */
    if (size <= DSIZE) {
        asize = 2 * DSIZE;
    } else {
        asize = DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE);
    }

    /* Search the free list for a fit */
    if ((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    /* No fit found. Get more memory and place the block */
    extendsize = MAX(asize, CHUNKSIZE);

    if ((bp = extend_heap(extendsize / WSIZE)) == NULL) {
        return NULL;
    }

    place(bp, asize);

    return bp;
}

static void place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));

    if ((csize - asize) >= (2 * DSIZE)) {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize - asize, 0));
        PUT(FTRP(bp), PACK(csize - asize, 0));
    } else {
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
}

static void *find_fit(size_t asize)
{
    char *temp = next_fitp;

    for (; GET_SIZE(HDRP(next_fitp)) > 0; next_fitp = NEXT_BLKP(next_fitp)) {
        if (!GET_ALLOC(HDRP(next_fitp)) && (asize <= GET_SIZE(HDRP(next_fitp)))) {
            return next_fitp;
        }
    }

    for (next_fitp = heap_listp; next_fitp < temp; next_fitp = NEXT_BLKP(next_fitp)) {
        if (!GET_ALLOC(HDRP(next_fitp)) && (asize <= GET_SIZE(HDRP(next_fitp)))) {
            return next_fitp;
        }
    }

    return NULL;
}

void mem_init(void)
{
    mem_heap     = (char *)Malloc(MAX_HEAP);
    mem_brk      = (char *)mem_heap;
    mem_max_addr = (char *)(mem_heap + MAX_HEAP);
}

void *mem_sbrk(int incr)
{
    char *old_brk = mem_brk;

    if ((incr < 0) || ((mem_brk + incr) > mem_max_addr)) {
        errno = ENOMEM;
        fprintf(stderr, "ERROR: mem_sbrk failed. Ran out of memory...\n");
        return (void *)-1;
    }

    mem_brk += incr;

    return (void *)old_brk;
}
