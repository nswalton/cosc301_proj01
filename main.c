/* Neil Walton
 * September 26, 2014
 * COSC301
 * Project 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "list.h"





void process_data(FILE *input_file) {

    struct node **head = malloc(sizeof(struct node));
    

    size_t size = 0;
    char *line = NULL;
    while (getline(&line, &size, input_file) != -1) {
	for (int i = 0; i < strlen(line); i++) {
	    char curr = line[i];
	    if (curr == '#') {
		line[i] = '\0';
		break;
	    }
	}

	//Tokenize here

	char *copy = strdup(line);
        char *token = malloc(sizeof(char)*strlen(line));

        token = strtok(copy, " \n\t");

        while (token != NULL) {
	    int isint = 0;
	    for (int i = 0; i < strlen(token); i++) {
		if ((token[i] < 48) || (token[i] > 57)) {
		    isint = 1;
		    break;
		}
	    }
	    if (isint == 0) {
		int inttoken = atoi(token);
		list_append(inttoken, head);

	    }
	    token = strtok(NULL, " \n\t");
        }
    }

    list_sort(head);
    printf("***List contents begins here***\n");
    list_print(*head);
    printf("***List contents ends here***\n");
    list_destroy(head);

    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
	printf("User time: %ld.%06ld\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
        printf("System time: %ld.%06ld\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
    } 
    if (getrusage(RUSAGE_SELF, &usage) == -1) {
	fprintf(stderr, "Did not retrieve usage information.\n");
	exit(1);
    } 

}




void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}

#ifndef AUTOTEST
int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    process_data(datafile);
    fclose(datafile);
    return 0;
}
#endif
