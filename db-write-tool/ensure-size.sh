#!/bin/bash

# This script is intended to be invoked periodically by a cronjob to check for
# sqlite oversized wal file .

DB=/home/spatel/work-repos/db-write-tool/test.db;
FILENAME=/home/spatel/work-repos/db-write-tool/test.db-wal;
FILESIZE=$(stat -c%s "$FILENAME");
MAX_FILE_SIZE=2000000;
TIMEOUT=60000; # 10 seconds


if [ $FILESIZE -gt $MAX_FILE_SIZE ];then
    sqlite3 "file://$DB?mode=rw" "PRAGMA busy_timeout=$TIMEOUT;" "PRAGMA wal_checkpoint(TRUNCATE);" # wait for 10 seconds before timeout
fi;
echo $?;
