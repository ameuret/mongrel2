#undef NDEBUG
#ifndef _minunit_h
#define _minunit_h

#include <stdio.h>
#include <dbg.h>
#include <stdlib.h>

#define mu_suite_start() char *message = NULL

#define mu_suite_shutdown()\
   fclose(mu_lf)

/* file: minunit.h */
#define LOG_FILE "tests/tests.log"
#define MAX_LOG_LENGTH 1024

FILE *mu_lf;
char mu_log_line[MAX_LOG_LENGTH];
char *mu_log_found=NULL;
  
#define mu_assert(test, message) if (!(test)) { log_err(message); return message; }
#define mu_run_test(test) debug("\n-----%s", " " #test); message = test(); tests_run++; if (message) return message;
#define mu_assert_log(target, message)\
     while(fgets( mu_log_line, MAX_LOG_LENGTH, mu_lf ) != NULL )\
       if(mu_log_found=strstr(mu_log_line,target)) break;\
     if(!mu_log_found) return message;

#define RUN_TESTS(name) void taskmain(int argc, char *argv[]) {\
     if(argc > 1) printf("TESTS DON'T TAKE ARGS\n");\
     FILE *log_file = fopen(LOG_FILE, "a+");\
     if(!log_file) { printf("CAN'T OPEN TEST LOG\n"); exit(1); } \
     mu_lf=fopen(LOG_FILE,"r");\
     setbuf(log_file, NULL);\
     dbg_set_log(log_file);\
     debug("----- RUNNING: %s", argv[0]);\
     printf("----\nRUNNING: %s\n", argv[0]);\
     char *result = name();\
     if (result != 0) {\
         printf("FAILED: %s\n", result);\
     }\
     else {\
         printf("ALL TESTS PASSED\n");\
     }\
     printf("Tests run: %d\n", tests_run);\
     exit(result != 0);\
 }


int tests_run;

#endif
