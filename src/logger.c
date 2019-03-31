#include "logger.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BLUE    "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define NORMAL  "\033[39m\n"

static char     _logfile[256];
static FILE*    _logfile_p;

static void _timestamp(char str[]) {
    time_t t;
    struct tm* tmp;
    static char timestamp[420];
    time(&t);
    tmp = localtime(&t);
    strftime(timestamp, sizeof(timestamp), "%F %T", tmp);
    strcat(timestamp, str);
    strcpy(str, timestamp);
}

void logger_init(char logfile[]) {
    strcpy(_logfile, "");
    strcpy(_logfile, logfile);
    _logfile_p = fopen(_logfile, "a");
    if(!_logfile_p) {
        printf("%sFATAL - Could not open logfile: %s%s\n", RED, _logfile, NORMAL);
        exit(1);
    }
    log_info("Logger initialized!");
}

void logger_close(void) {
    int ret = fclose(_logfile_p);
    if(ret != 0) {
        printf("%sFATAL - Could not close logfile! Error code: %d%s\n", RED, ret, NORMAL);
        exit(1);
    }
}

void log_info(char msg[]) {
    char log_entry[400] = {" [INFO]: "};
    strcat(log_entry, msg);
    _timestamp(log_entry);
    fprintf(_logfile_p, "%s%s%s", BLUE, log_entry, NORMAL);
}

void log_error(char msg[]) {
    char log_entry[400] = {" [ERROR]: "};
    strcat(log_entry, msg);
    _timestamp(log_entry);
    fprintf(_logfile_p, "%s%s%s", YELLOW, log_entry, NORMAL);
}

void log_fatal(char msg[]) {
    char log_entry[400] = {" [FATAL]: "};
    strcat(log_entry , msg);
    _timestamp(log_entry);
    fprintf(_logfile_p, "%s%s%s", RED, log_entry, NORMAL);
}