#include <fcntl.h>
#include <unistd.h>
#include <sqlite3.h>

#include <cstdio>
#include <cstdlib>
#include <thread>

#include <fstream>

#include <string>

static
void
push(const char* aDb, int aIndex)
{
    sqlite3 *db;

    const int rcOpen = sqlite3_open(aDb, &db);
    if ( rcOpen )
    {
        printf("push() can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    /*char *errMsg1 = NULL;
    const int jo = sqlite3_exec(db, "PRAGMA journal_size_limit=20000;", NULL, NULL, &errMsg1);
    if (jo != SQLITE_OK)
    {
        printf("SQL error: %s\n", errMsg1);
        sqlite3_free(errMsg1);
        sqlite3_close(db);
        sync();
        return;
    }*/

    int bt = sqlite3_busy_timeout(db, 1000);

    char *errMsg = NULL;
    for (;;)
    {
        const int rcExec = sqlite3_exec(db, "insert into test(message) VALUES('stuff')", NULL, NULL, &errMsg);


        if( rcExec != SQLITE_OK ){
            printf("SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
            sqlite3_close(db);
            sync();
            return;
        }
        sleep(0.01);
    }

    sqlite3_close(db);
}

int main(int aArgc, char **aArgs)
{
    const char* dbPath  = "/home/spatel/work-repos/db-write-tool/test.db";
    //int index = aArgs[1];
    push(dbPath, 1);

    return 0;
}

