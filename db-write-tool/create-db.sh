#!/bin/bash
DB=/home/spatel/work-repos/db-write-tool/test.db;
schema=/home/spatel/work-repos/db-write-tool/test.schema;
sqlite3 "file://$DB?mode=rwc" ".read $schema"