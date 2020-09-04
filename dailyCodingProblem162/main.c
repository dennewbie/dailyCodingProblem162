//
//  main.c
//  dailyCodingProblem162
//
//  Created by Denny Caruso on 04/09/2020.
//  Copyright © 2020 Denny Caruso. All rights reserved.
//

/*
    Daily Coding Problem 162 - Level: Medium
    This problem was asked by Square.

    Given a list of words, return the shortest unique prefix of each word. For example, given the list:

    - dog
    - cat
    - apple
    - apricot
    - fish
    - duck
 
    Return the list:

    - do
    - c
    - app
    - apr
    - f
    - du
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **getShortestUniquePrefixArray(char **, int);
void generateError(char *);
void printArray(char **, int, char *);

int main(int argc, const char * argv[]) {
    char *wordsArray[] = { "Dog" , "Cat", "Apple", "Apricot", "Fish", "Duck" };
    int size = (sizeof(wordsArray) / sizeof(wordsArray[0]));
    
    printArray(wordsArray, size, "\nWord List:\n");
    char **finalArray = getShortestUniquePrefixArray(wordsArray, size);
    printArray(finalArray, size, "\nFinal Word List:\n");
    
    return 0;
}

char **getShortestUniquePrefixArray(char **wordList, int size) {
    char **finalList = (char **) malloc(sizeof(char *) * size);
    if(!finalList) generateError("final List");
    unsigned short int nChar = 1;
    
/*
      Number of char that will be at least inside the new array for each word.
      This nChar is going to increase each time that we found an equal character inside the array,
      in this way we are going to reserve more space in memory for its place in the array.
      Furthermore when we found an equal char it means that prefix isn't unique, so we decrease the
      counter j (internal one) and check again if also the following letters are equal in order to get
      the shortest unique prefix array.
 */
    
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != j) {
                if (strncmp(wordList[i], wordList[j], nChar) == 0) {
                    nChar += 1;
                    if (nChar == strlen(wordList[i])) break;
                    j--;
                }
            }
        }
        
        finalList[i] = (char *) malloc(nChar + 1);
        if (!finalList[i]) generateError("finalList[i]");
        
        strncpy(finalList[i], wordList[i], nChar);
        finalList[i][nChar + 1] = '\0';
        
        if (nChar == strlen(wordList[i])) printf("\nAlert: There are two equal words. It's impossible to make an array with shortest unique prefixes...\n");
        nChar = 1;
    }
    
    return finalList;
}

void generateError(char *errorMessage) {
    printf("\nError allocating memory for %s...\n", errorMessage);
    exit(EXIT_FAILURE);
}

void printArray(char **finalList, int size, char *message) {
    printf("\n%s\n", message);
    for (int i = 0; i < size; i++) printf("-> %s\n", finalList[i]);
}
