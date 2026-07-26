#include "apue.h"
#include "apue_db.h"
#include <fcntl.h>

int main(void)
{
    DBHANDLE db;

    if ((db = db_open("db1", O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) == NULL) {
        err_sys("db_open error");
    }

    if (db_store(db, "Foo", "data for foo", DB_INSERT) != 0) {
        err_quit("db_store error for foo");
    }

    if (db_store(db, "Bar", "data for bar", DB_INSERT) != 0) {
        err_quit("db_store error for bar");
    }

    if (db_store(db, "Baz", "data for baz", DB_INSERT) != 0) {
        err_quit("db_store error for baz");
    }

    db_close(db);

    return 0;
}
