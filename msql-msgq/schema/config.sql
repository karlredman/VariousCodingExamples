DROP DATABASE IF EXISTS configuration;
CREATE DATABASE configuration;
USE configuration;

DROP TABLE IF EXISTS Rack;
CREATE TABLE Rack (
       RackID            INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
       RackNumber        INT UNSIGNED NOT NULL
);

DROP TABLE IF EXISTS SubRack;
CREATE TABLE SubRack (
       SubRackID            INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
       RackID               INT UNSIGNED NOT NULL,
       SubRackNumber        INT UNSIGNED NOT NULL
);

DROP TABLE IF EXISTS TrunkGroup;
CREATE TABLE TrunkGroup (
       TrunkGroupID         INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
       CarrierID            INT UNSIGNED NOT NULL,
       TrunkGroupName       VARCHAR(65) NOT NULL,
       TrunkGroupType       INT UNSIGNED NOT NULL
);

DROP TABLE IF EXISTS TrunkGroupSpanAssignment;
CREATE TABLE TrunkGroupSpanAssignment (
       SpanID               INT UNSIGNED NOT NULL,
       TrunkGroupID         INT UNSIGNED NOT NULL
);

DROP TABLE IF EXISTS Carrier;
CREATE TABLE Carrier (
       CarrierID            INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
       CarrierName          VARCHAR(65) NOT NULL
);

DROP TABLE IF EXISTS MediaGateway;
CREATE TABLE MediaGateway (
       MediaGatewayID       INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
       SubRackID            INT UNSIGNED NOT NULL,
       MediaGatewayName     VARCHAR(65) NOT NULL,
       IPAddress            VARCHAR(100) NOT NULL,
       MACAddress           VARCHAR(12) NOT NULL,
       MediaGatewayNumber   INT UNSIGNED NOT NULL
);

DROP TABLE IF EXISTS LineCard;
CREATE TABLE LineCard (
       LineCardID           INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
       MediaGatewayID       INT UNSIGNED NOT NULL,
       LineCardName         VARCHAR(65) NOT NULL,
       IPAddress            VARCHAR(100) NOT NULL,
       MACAddress           VARCHAR(12) NOT NULL,
       LineCardNumber       INT UNSIGNED NOT NULL
);

DROP TABLE IF EXISTS LineCardAttribute;
CREATE TABLE LineCardAttribute (
       LineCardID           INT UNSIGNED NOT NULL PRIMARY KEY,
       CardType             INT NULL,
       StartRtpPort         INT UNSIGNED NULL
);

DROP TABLE IF EXISTS Span;
CREATE TABLE Span (
       SpanID               INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
       LineCardID           INT UNSIGNED NOT NULL,
       DChannelConfig       INT UNSIGNED NOT NULL,
       SpanName             VARCHAR(65) NOT NULL,
       SpanNumber           INT UNSIGNED NOT NULL
);

DROP TABLE IF EXISTS SpanAttribute;
CREATE TABLE SpanAttribute (
       SpanID               INT UNSIGNED NOT NULL,
       ProtocolType         INT NULL
);

DROP TABLE IF EXISTS CallDirector;
CREATE TABLE CallDirector (
       CallDirectorID       INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
       SubRackID            INT UNSIGNED NOT NULL,
       CallDirectorName     VARCHAR(65) NULL,
       IPAddress            VARCHAR(100) NULL,
       MACAddress           VARCHAR(12) NULL,
       IPAddress2           VARCHAR(100) NULL,
       MACAddress2          VARCHAR(12) NULL,
       CallDirectorNumber   INT UNSIGNED NOT NULL
);

DROP TABLE IF EXISTS SpeechServer;
CREATE TABLE SpeechServer (
       SpeechServerID       INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
       SubRackID            INT UNSIGNED NOT NULL,
       MaxRtpPorts          INT UNSIGNED NOT NULL,
       MaxASRs              INT UNSIGNED NOT NULL,
       SpeechServerName     VARCHAR(65) NOT NULL,
       IPAddress            VARCHAR(100) NOT NULL,
       MACAddress           VARCHAR(12) NOT NULL,
       SpeechServerNumber   INT UNSIGNED NOT NULL
);

DROP TABLE IF EXISTS SpeechServerAttributes;
CREATE TABLE SpeechServerAttributes (
       SpeechServerID       INT UNSIGNED NOT NULL,
       StartRtpPort         INT UNSIGNED
);

DROP TABLE IF EXISTS VSSApplication;
CREATE TABLE VSSApplication (
       VSSApplicationID     INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
       VSSApplicationName   VARCHAR(65) NOT NULL,
       VoiceXMLURL          VARCHAR(255) NOT NULL
);

DROP TABLE IF EXISTS DNIS;
CREATE TABLE DNIS (
       DNISID               INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
       VSSApplicationID     INT UNSIGNED NOT NULL,
       StartPhoneNumber     VARCHAR(25) NOT NULL,
       EndPhoneNumber       VARCHAR(25) NOT NULL
);

DROP TABLE IF EXISTS AppTrunkAssignment;
CREATE TABLE AppTrunkAssignment (
       AppTrunkAssignmentID INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
       VSSApplicationID     INT UNSIGNED NOT NULL,
       TrunkGroupID         INT UNSIGNED NOT NULL
);

LOAD DATA LOCAL INFILE "../data/Rack.txt"               INTO TABLE Rack;
LOAD DATA LOCAL INFILE "../data/SubRack.txt"            INTO TABLE SubRack;
LOAD DATA LOCAL INFILE "../data/CallDirector.txt"       INTO TABLE CallDirector;
LOAD DATA LOCAL INFILE "../data/SpeechServer.txt"       INTO TABLE SpeechServer;
LOAD DATA LOCAL INFILE "../data/MediaGateway.txt"       INTO TABLE MediaGateway;
LOAD DATA LOCAL INFILE "../data/LineCard.txt"           INTO TABLE LineCard;
LOAD DATA LOCAL INFILE "../data/Span.txt"               INTO TABLE Span;
LOAD DATA LOCAL INFILE "../data/TrunkGroup.txt"         INTO TABLE TrunkGroup;
LOAD DATA LOCAL INFILE "../data/TrunkGroupSpanAssignment.txt" INTO TABLE TrunkGroupSpanAssignment;
LOAD DATA LOCAL INFILE "../data/Carrier.txt"            INTO TABLE Carrier;
LOAD DATA LOCAL INFILE "../data/VSSApplication.txt"     INTO TABLE VSSApplication;
LOAD DATA LOCAL INFILE "../data/DNIS.txt"               INTO TABLE DNIS;
LOAD DATA LOCAL INFILE "../data/AppTrunkAssignment.txt" INTO TABLE AppTrunkAssignment;
