//
//  TreeBreeder.c
//  BFAIClean
//
//  Created by Daniel Tan on 28/5/18


#include "TreeBreeder.h"
#include <stdlib.h>
#include <string.h>

extern Breeder breeders[];
extern Breeder breeder;
extern int numBreeders;

extern GeneticAlgorithm algorithm;
extern int arity[256];

char* getTree(char* root, const char* const arity);

void initTreeBreeder(void){
    breeders[numBreeders] = (Breeder){
        .name = "TreeBreeder",
        .scan = scanTreeBreeder,
        .save = saveTreeBreeder,
        .breed = treeBreed
    };
    numBreeders++;
}

/* TODO: get the arity array from somewhere */

void treeBreed(Genome *p1, Genome *p2, Genome *child){
	// Copy one of the parents to the child, then mutate the child with the second parent
    int genLen = algorithm.genomeLength;    
    memmove(child->dna, p1->dna, genLen);

    int i1 = rand() % genLen;
    int i2 = rand() % genLen;
    char* start1 = &child->dna[i1];
    char* start2 = &p2->dna[i2];
    char* end1 = getTree(start1, arity)+1;
    char* end2 = getTree(start2, arity)+1; 
   
    int len1 = end1 - start1;
    int len2 = end2 - start2;

    // copy a segment of length (len2) from start2 into start1
    // accomodate for differences in segment lengths
    int diff = len1 - len2;
    int rem1 = genLen - i1 - len1; //remaining length in the buffer
    if (diff >= 0) memmove(end1-diff, end1, rem1);
    else memmove(end1-diff, end1, rem1-diff);
    memmove(start1, start2, len2);
}


// Given a pointer to a character in an expression program's DNA, returns a pointer to the last char in the tree
// Works because trees are contiguous in memory
char* getTree(char* root, const char* const arity) {
    char c = *root;
    if (arity[c] == 0) {
    	return root;
    } else if (arity[c] == 1) {
        return getTree(root+1, arity);
    } else if (arity[c] == 2) {
        root = getTree(root+1, arity);
        return getTree(root+1, arity);
    } else {
        // WARNING: this code was not designed with 3-ary functions in mind
        return NULL;
    }
}

/* TODO: implement the scan and save functions */

void scanTreeBreeder(FILE *file){
    //fscanf(file, "Segment Size: %d\n", &breeder.segmentSize);
}

void saveTreeBreeder(FILE *file){
    //fprintf(file, "Segment Size: %d\n", breeder.segmentSize);
}
