DROP DATABASE IF EXISTS Cdr;
CREATE DATABASE Cdr;
USE Cdr;
DROP TABLE IF EXISTS CallDetailRecord ;
CREATE TABLE CallDetailRecord  (
     cseq    BIGINT UNSIGNED NOT NULL,
     event  SMALLINT UNSIGNED NOT NULL,
     fromPort    INT UNSIGNED NOT NULL,
     fromHost    VARCHAR(65) NOT NULL,
     fromUserName    VARCHAR(100) NOT NULL,
     toPort    INT UNSIGNED NOT NULL,
     toHost    VARCHAR(65) NOT NULL,
     toUserName    VARCHAR(100) NOT NULL,
     timeStamp    TIMESTAMP NOT NULL,
     callId    VARCHAR(100) NOT NULL,
     appName    VARCHAR(100) NOT NULL,
     status    SMALLINT UNSIGNED NULL
);
DROP TABLE IF EXISTS CallEvent;
CREATE TABLE CallEvent  (
     event    INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
     value    VARCHAR(20) NOT NULL
);
DROP TABLE IF EXISTS CallStatus;
CREATE TABLE CallStatus  (
     id    INT UNSIGNED NOT NULL PRIMARY KEY,
     status    VARCHAR(20) NOT NULL
);
#
LOAD DATA LOCAL INFILE "../data/cdr.txt"               INTO TABLE CallDetailRecord;
LOAD DATA LOCAL INFILE "../data/call_event.txt"        INTO TABLE CallEvent;
LOAD DATA LOCAL INFILE "../data/call_status.txt"       INTO TABLE CallStatus;
