#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/semaphore.h>
#include <sys/shm.h>

/* we don't want sizeof(Mesg) > 4096 */
#define MAXMESGDATA (4096-16)

typedef struct {
  int   mesg_len;   /* #bytes in mesg_data, can be 0 or > 0 */
  long  mesg_type;  /* message type, must be > 0 */
  char  mesg_data[MAXMESGDATA];
} Mesg;

/* length of mesg_len and mesg_type */
#define MESGHDRSIZE (sizeof(Mesg) - MAXMESGDATA)

/* number of buffers in shared memory */
#define NBUFF 4

#define SHMKEY  ((key_t) 7890) /* base value for shmem key */
#define SEMNAME1 "/cli"        /* client semaphore name */
#define SEMKEY1 ((key_t) 7891) /* client semaphore key */
#define SEMKEY2 ((key_t) 7892) /* server semaphore key */
#define SEMNAME2 "/srv"        /* server semaphore name */

#define PERMS   0666
