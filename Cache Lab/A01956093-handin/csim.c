// Shayan Taheri (A01956093)

# include "cachelab.h"
# include <stdio.h>
# include <stdlib.h>
# include <getopt.h>
# include <string.h>
# include <unistd.h>

/* Defining the structure of the lines in cache: 1) tag = TAG , 2) Accessess = It is the number of accessing to a particular
line , 3) occupied = It means thst a line has been occupied */ 

struct cache_line{

    unsigned long tag;

    int accesses;

    int occupied;
};

// "line" is a pointer to the lines in the cache ! "time" is the accessing number for each line.

struct cache_line *line;
int s = 0;
int E = 0;
int b = 0;
int time = 0;
int hit_count = 0;
int miss_count = 0;
int eviction_count = 0;
char trace_name[20];

// Defining the parse_command that will give the information of a command --> Analyzing a Command

void parse_command(int argc, char *argv[]){
    
  int option = 0;
  int convert = 0;
    
  while((option = getopt(argc, argv, "hvs:E:b:t:")) != -1){
        
      if (optarg != '\0')
            
	convert = atoi(optarg);
        
	switch (option) {
            
	  case 'v':
                break;
            
	  case 'h':
                break;
	  
	  case 's':
                s = convert;
                break;
            
	  case 'E':
                E = convert;
                break;
            
	  case 'b':
                b = convert;
                break;
           
	  case 't':
                strncpy(trace_name, optarg, 20);
                break;
           
	  default:
                break;
        }
    }
}

// Defining the LOAD function

void LOAD (unsigned long addr)
{

  // Calculating the TAG and set index bits according to the address
  
    unsigned long tag = (addr >> b) >> s;
    int set_index = (addr >> b) & ((1 << s) - 1);
    time++;
    int LRU = time;
    int replace_empty = 0;
    for (int i = 0; i < E; i++)
    {
	// if the line is occupied
        
        if (line[E * set_index + i].occupied == 1)
        {
	    // if the line has a tag that matches to "tbits" --> Hit
            if (line[E * set_index + i].tag == tag)
            {
                line[E * set_index + i].accesses = time;
                hit_count++;
                return;
            }
            
	    // For the occupied lines, Finding for the least recently used to evict a line !
            
            if (line[E * set_index + i].accesses < LRU)
            {
                LRU = line[E * set_index + i].accesses;
		replace_empty = i;
            }
        }

        else
        {
	  // Find an empty line !
	  
            replace_empty = i;
            LRU = time;
            break;
        }
    }
    
    miss_count++;


    if (LRU != time){
        eviction_count ++;

    }

    line[E * set_index + replace_empty].occupied = 1;
    line[E * set_index + replace_empty].accesses = time;
    line[E * set_index + replace_empty].tag = tag;
}


void STORE (unsigned long addr){
    LOAD (addr);
}


int main(int argc, char *argv[])
{
    FILE *fp;
    char trace_file[100];
    unsigned long address;
    parse_command(argc, argv);
    
    // Allocating a space in memory according to the size of each line !

    line = (struct cache_line*) malloc(sizeof(struct cache_line) * E * (1 << s));
    
    // For initializing each line with 0 !
    
    memset(line, 0, sizeof(struct cache_line) * E * (1 << s));
    
    fp = fopen(trace_name, "r");

    while (fgets(trace_file, 100, fp) != NULL) {

        sscanf(trace_file + 3, "%lx", &address);

        switch (trace_file[1]) {
            
	  case 'L':
                LOAD (address);
                break;
            
	  case 'S':
                STORE (address);
                break;
            
	  case 'M':
                LOAD (address);
                STORE (address);
                break;
            
	  default:
                break;
        }

    }

    printSummary(hit_count, miss_count, eviction_count);

    fclose(fp);
    free(line);
    return 0;
}