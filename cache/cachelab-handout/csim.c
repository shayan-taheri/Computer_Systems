/* Shayan Taheri (A01956093) */

# include "cachelab.h"
# include <stdio.h>
# include <getopt.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/* Defining Global Variables */
int h = 0;
int v = 0;
int s = 0;
int E = 0;
int b = 0;
int t = 0;
const int length = 100;
int hit_count = 0;
int miss_count = 0;
int eviction_count = 0;
char tracefile[length];
struct cache_struct *cache;

/* Defining The Arguments */
const char argument[] = "s:E:b:t:hv";

/* Parse Command-Line Options by Using getopt Function */
void get_input(int argc, char *argv[]){
  
    int option = 0;
    int k;
    
    while((option = getopt(argc, argv, argument)) != -1){
      
        if (optarg != NULL) {
            k = atoi(optarg);}
	
        switch (option) {
		
            case 'h':
                h = 1;
                break;
		
	    case 'v':
                v = 1;
                break;
		
	    case 's':
                s = k;
                break;
		
            case 'E':
                E = k;
                break;
		
            case 'b':
                b = k;
                break;
		
            case 't':
                strncpy(tracefile, optarg, length);
                break;
		
            default:
                break;
        }
    }
}

/* Making Cache Structure */
struct cache_struct {

  /* Tag of Cache Lines */
    unsigned long long tag;
    
/* Last Access */
    int last_access;
    
/* Indicating Non-Availability */
    char non_available;
};

/* Simulating of Cache Load Operation */
void load (unsigned long long address) {

    /* Defining Tag */
    unsigned long long tag = (address >> b);
    
    /* Index of first cache line in set */
    int idx = E * (tag & ((1 << s) - 1));
    
    int lru = t + 1;
    int empty = -1;
    
    for (int i = 0; i < E; i++)
    {
        /* for a occupied cache line */
        if (cache[idx + i].non_available)
        {
            /* check if tags match */
            if (cache[idx + i].tag == tag)
            {
                cache[idx + i].last_access = t;
                hit_count++;
                if (v)
                    printf(" hit_count");
                return;
            }
            /* otherwise, find least recently updated line */
            if (cache[idx + i].last_access < lru)
            {
                lru = cache[idx + i].last_access;
                empty = i;
            }
        }
        /* for an empty line, just use it */
        else
        {
            empty = i;
            lru = t;
            break;
        }
    }
    miss_count++;
    if (v)
        printf(" miss_count");
    /* eviction_count occurs on non-empty lines */
    if (lru != t){
        eviction_count ++;
        if (v)
            printf(" eviction_count");
    }
    /* update */
    cache[idx + empty].non_available = 1;
    cache[idx + empty].last_access = t;
    cache[idx + empty].tag = tag;
}

/* simulate cache store. simply calls load (this is ok in this application)*/
void store(unsigned long long address){
    load(address);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    char tracebuf[length];
    unsigned long add;
    get_input(argc, argv);
    if (v)
        printf("s:%d(%d), E:%d, b:%d(%d)\n", s, 1<<s, E, b, 1<<b);
    /* initialize cache */
    cache = (struct cache_struct*)malloc(sizeof(struct cache_struct) * E * (1<<s));
    memset(cache, 0, sizeof(struct cache_struct) * E * (1<<s));
    
    fp = fopen(tracefile, "r");
    /* read one line from file */
    while (fgets(tracebuf, length, fp) != NULL) {
        /* do nothing on instruction load */
        if (tracebuf[0] == 'I'){
            //if (v)
                //printf("-----\n");
            continue;
        }
        /* extract the addressess */
        sscanf(tracebuf + 2, "%lx", &add);
        if (v)
            printf("%c at 0x%lx", tracebuf[1], add);
        /* three types of operations (actually, nothing but load)*/
        switch (tracebuf[1]) {
            case 'L':
                load(add);
                break;
            case 'S':
                store(add);
                break;
            case 'M':
                load(add);
                store(add);
                break;
            default:
                break;
        }
        if (v)
            putchar('\n');
    }
    /* report the results */
    printSummary(hit_count, miss_count, eviction_count);
    /* cleaning up */
    fclose(fp);
    free(cache);
    return 0;
}

