#!/bin/bash

DB=/home/spatel/work-repos/db-write-tool/test.db;
i=$1;
while true; do
	sqlite3 "file://$DB?mode=rw" "insert into test values($i, 'stuff')";
	i=$(($i+1));
	sleep 0.5
done
