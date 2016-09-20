//
//  main.c
//  project1
//
//  Created by Kovalcik, Michael on 9/18/16.
//  Copyright © 2016 Kovalcik, Michael. All rights reserved.
//

/* Assembler code fragment for LC-2K */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINELENGTH 1000

int readAndParse(FILE *, char *, char *, char *, char *, char *);
int isNumber(char *);



int
main(int argc, char *argv[])
{
    char *inFileString, *outFileString;
    FILE *inFilePtr, *outFilePtr;
    char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH],
    arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];
    
    if (argc != 3) {
        printf("error: usage: %s <assembly-code-file> <machine-code-file>\n",
               argv[0]);
        exit(1);
    }
    
    inFileString = argv[1];
    outFileString = argv[2];
    
    inFilePtr = fopen(inFileString, "r");
    if (inFilePtr == NULL) {
        printf("error in opening %s\n", inFileString);
        exit(1);
    }
    outFilePtr = fopen(outFileString, "w");
    if (outFilePtr == NULL) {
        printf("error in opening %s\n", outFileString);
        exit(1);
    }
    
    static char strArr[65536][MAXLINELENGTH];
    int idx = 0;
    int loc = -1;
    while (readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)) {
        if(strcmp(label,"\0")){
            for(int i = 0; i < idx; i++){
                if(!strcmp(label,strArr[i])) exit(1);
            }
            strcpy(strArr[idx], label);
        }
        idx = idx + 1;
    }
    
    /* here is an example for how to use readAndParse to read a line from
     inFilePtr */
    //    if (! readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2) ) {
    //        /* reached end of file */
    //    }
    
    /* this is how to rewind the file ptr so that you start reading from the
     beginning of the file */
    rewind(inFilePtr);
    
    int bn = 0;
    int temp = 0;
    int mask = 65535;
    int pc = 0;
    int nextPos;
    
    while(readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)){
        loc = -1;
        if (!strcmp(opcode, "add")){
            bn = 0 << 22;
            if(atoi(arg0) > -1 && atoi(arg0) < 8){
                temp = atoi(arg0) << 19;
                bn = bn + temp;
            }
            else{
                exit(1);
            }
            if(atoi(arg1) > -1 && atoi(arg1) < 8){
                temp = atoi(arg1) << 16;
                bn = bn + temp;
            }
            else{
                exit(1);
            }
            if(atoi(arg2) > -1 && atoi(arg2) < 8){
                bn = bn + atoi(arg2);
            }
            else{
                exit(1);
            }
        }
        else if(!strcmp(opcode, "nor")){
            bn = 1 << 22;
            if(atoi(arg0) > -1 && atoi(arg0) < 8){
                temp = atoi(arg0) << 19;
                bn = bn + temp;
            }
            else{
                exit(1);
            }
            if(atoi(arg1) > -1 && atoi(arg1) < 8){
                temp = atoi(arg1) << 16;
                bn = bn + temp;
            }
            else{
                exit(1);
            }
            if(atoi(arg2) > -1 && atoi(arg2) < 8){
                bn = bn + atoi(arg2);
            }
            else{
                exit(1);
            }
        }
        else if(!strcmp(opcode, "lw")){
            bn = 2 << 22;
            if(atoi(arg0) > -1 && atoi(arg0) < 8){
                temp = atoi(arg0) << 19;
                bn = bn + temp;
            }
            else{
                exit(1);
            }
            if(atoi(arg1) > -1 && atoi(arg1) < 8){
                temp = atoi(arg1) << 16;
                bn = bn + temp;
            }
            else{
                exit(1);
            }
            if(isNumber(arg2) == 1){
                if(atoi(arg2) > -32768 && atoi(arg2) < 32767){
                    if(atoi(arg2) < 0){
                        bn = bn + (atoi(arg2) & mask);
                    }
                    else{
                        bn = bn + atoi(arg2);
                    }
                }
                else{
                    exit(1);
                }
            }
            else{
                for(int i = 0; i < idx; i++){
                    if(!strcmp(arg2,strArr[i])){
                        loc = i;
                        break;
                    }
                }
                if(loc != -1){
                    bn = bn + loc;
                }
                else{
                    exit(1);
                }
            }
        }
        else if(!strcmp(opcode, "sw")){
            bn = 3 << 22;
            if(atoi(arg0) > -1 && atoi(arg0) < 8){
                temp = atoi(arg0) << 19;
                bn = bn + temp;
            }
            else{
                exit(1);
            }
            if(atoi(arg1) > -1 && atoi(arg1) < 8){
                temp = atoi(arg1) << 16;
                bn = bn + temp;
            }
            else{
                exit(1);
            }
            if(isNumber(arg2) == 1){
                if(atoi(arg2) > -32768 && atoi(arg2) < 32767){
                        bn = bn + (atoi(arg2) & mask);
                }
                else{
                    exit(1);
                }
            }
            else{
                for(int i = 0; i < idx; i++){
                    if(!strcmp(arg2,strArr[i])){
                        loc = i;
                        break;
                    }
                }
                if(loc != -1){
                    bn = bn + loc;
                }
                else{
                    exit(1);
                }
            }

        }
        else if(!strcmp(opcode, "beq")){
            bn = 4 << 22;
            if(atoi(arg0) > -1 && atoi(arg0) < 8){
                temp = atoi(arg0) << 19;
                bn = bn + temp;
            }
            else{
                exit(1);
            }
            if(atoi(arg1) > -1 && atoi(arg1) < 8){
                temp = atoi(arg1) << 16;
                bn = bn + temp;
            }
            else{
                exit(1);
            }
            if(isNumber(arg2) == 1){
                if(atoi(arg2) > -32768 && atoi(arg2) < 32767){
                        bn = bn + (atoi(arg2) & mask);
                }
                else{
                    exit(1);
                }

            }
            else{
                for(int i = 0; i < idx; i++){
                    if(!strcmp(arg2,strArr[i])){
                        loc = i;
                        break;
                    }
                }
                if(loc != -1){
                    nextPos = loc - 1 - pc;
                    nextPos = nextPos & mask;
                    bn = bn + nextPos;
                }
                else{
                    exit(1);
                }
            }
        }
        else if(!strcmp(opcode, "jalr")){
            bn = 5 << 22;
            if(atoi(arg0) > -1 && atoi(arg0) < 8){
                temp = atoi(arg0) << 19;
            }
            else{
                exit(1);
            }
            if(atoi(arg1) > -1 && atoi(arg1) < 8){
                temp = atoi(arg1) << 16;
                bn = bn + temp;
            }
            else{
                exit(1);
            }
            
        }
        else if(!strcmp(opcode, "halt")){
            bn = 6 << 22;
        }
        else if(!strcmp(opcode, "noop")){
            bn = 7 << 22;
        }
        else if(!strcmp(opcode, ".fill")){
            if(isNumber(arg0)){
                bn = atoi(arg0);
            }
            else{
                for(int i = 0; i < idx; i++){
                    if(!strcmp(arg0,strArr[i])){
                        loc = i;
                        break;
                    }
                }
                if(loc != -1){
                    bn = loc;
                }
                else{
                    exit(1);
                }
            }
        }
        else{
            exit(1);
        }
        fprintf(outFilePtr, "%d", bn);
        fprintf(outFilePtr, "\n");
        pc = pc + 1;
    }
    
    
    return(0);
}

/*
 * Read and parse a line of the assembly-language file.  Fields are returned
 * in label, opcode, arg0, arg1, arg2 (these strings must have memory already
 * allocated to them).
 *
 * Return values:
 *     0 if reached end of file
 *     1 if all went well
 *
 * exit(1) if line is too long.
 */
int
readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0,
             char *arg1, char *arg2)
{
    char line[MAXLINELENGTH];
    char *ptr = line;
    
    /* delete prior values */
    label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';
    
    /* read the line from the assembly-language file */
    if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL) {
        /* reached end of file */
        return(0);
    }
    
    /* check for line too long (by looking for a \n) */
    if (strchr(line, '\n') == NULL) {
        /* line too long */
        printf("error: line too long\n");
        exit(1);
    }
    
    /* is there a label? */
    ptr = line;
    if (sscanf(ptr, "%[^\t\n\r ]", label)) {
        /* successfully read label; advance pointer over the label */
        ptr += strlen(label);
    }
    
    /*
     * Parse the rest of the line.  Would be nice to have real regular
     * expressions, but scanf will suffice.
     */
    sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]",
           opcode, arg0, arg1, arg2);
    return(1);
}

int
isNumber(char *string)
{
    /* return 1 if string is a number */
    int i;
    return( (sscanf(string, "%d", &i)) == 1);
}



