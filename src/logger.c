#include <logger.h>
#include <string.h>
#include <stdio.h>

#define BLUE    "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define NORMAL  "\033[39m\n"

static void _timestamp(char* str) {
    time_t t;
    struct tm* tmp;
    static char timestamp[19];
    time(&t);
    tmp = localtime(&t);
    strftime(timestamp, sizeof(timestamp), "%F %T", tmp);
    str = strcat(timestamp, str);
}

void logger_init(char* logfile) {
    if(strcmp(_logfile, "")) {
        _logfile = logfile;
    }
    _logfile_p = fopen(_logfile, "a");
    if(!_logfile_p) {
        printf("FATAL - Could not open logfile!\n");
    }
    log_info("Logger initialized!");
}

void logger_close(void) {
    if(!fclose(_logfile_p)) {
        printf("FATAL - Could not close logfile!\n");
    }
}

void log_info(char* msg) {
    char* log_entry = strcat("[INFO]: ", msg);
    _timestamp(log_entry);
    fprintf(_logfile_p, "%s",BLUE, log_entry, NORMAL);
}

void log_error(char* msg) {
    char* log_entry = strcat("[ERROR]: ", msg);
    _timestamp(log_entry);
    fprintf(_logfile_p, "%s", YELLOW, log_entry, NORMAL);
}

void log_fatal(char* msg) {
    char* log_entry = strcat("[FATAL]: ", msg);
    _timestamp(log_entry);
    fprintf(_logfile_p, "%s%s%s", RED, log_entry, NORMAL);
}