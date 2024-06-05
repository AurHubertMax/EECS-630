#ifndef _MY_EDIT_DISTANCE_H_
#define _MY_EDIT_DISTANCE_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>



/*------------------------------------------------------------------------------
    EditDistance: find the minimum number of edits that converts one string to another
    
        str1: the first input string, has an alphabet of [A, C, G, T]
        str2: the second input string, has an alphabet of [A, C, G, T]
        operations: the list of edit operations as string: 
            [M] for match, [C] for convert, [I] for insert, [D] for delete
        
        returns the number of edit distance
------------------------------------------------------------------------------*/
unsigned int EditDistance
(
    const std::string & str1,
    const std::string & str2,
    std::string & operations
)
{
    unsigned int len1 = str1.length();
    unsigned int len2 = str2.length();

    std::vector<std::vector<unsigned int>> dp(len1 + 1, std::vector<unsigned int>(len2 + 1));

    // Initialize matrix
    for (unsigned int i = 0; i <= len1; i++) {
        dp[i][0] = i;
    }
    for (unsigned int j = 0; j <= len2; j++) {
        dp[0][j] = j;
    }
    
    // Count edit distance
    for (unsigned int i = 1; i <= len1; i++) {
        for (unsigned int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = std::min({dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]}) + 1;
            }
        }
    }
    

    // Backtracking
    unsigned int i = len1;
    unsigned int j = len2;
    // create operation strings
    while (i > 0 && j > 0) {
        if (dp[i - 1][j] <= dp[i - 1][j - 1] && dp[i - 1][j] <= dp[i][j - 1] && dp[i - 1][j] < dp[i][j]) {
            operations = "D" + operations;
            i--;
        } else if (dp[i][j - 1] <= dp[i - 1][j - 1] && dp[i][j - 1] <= dp[i - 1][j] && dp[i][j - 1] < dp[i][j]) {
            operations = "I" + operations;
            j--;
        } else {
            if (dp[i - 1][j - 1] == dp[i][j]) {
                operations = "M" + operations;
            } else {
                operations = "C" + operations;
            }
            i--;
            j--;
        }
    }
    while (i > 0) {
        operations = "D" + operations;
        i--;
    }
    while (j > 0) {
        if (i > 0 && str1[i - 1] != str2[j - 1]) {
            operations = "C" + operations;
            i--;
        } else {
            operations = "I" + operations;
        }
        j--;
    }
    
    // Return the edit distance
    return dp[len1][len2];
}



/*------------------------------------------------------------------------------
    PrintAlgnment: prints the two aligned sequences and the corresponding operations
        in the alignment form to stdout
    
        str1: the first input string, has an alphabet of [A, C, G, T]
        str2: the second input string, has an alphabet of [A, C, G, T]
        operations: the list of edit operations as string: 
            [M] for match, [C] for convert, [I] for insert, [D] for delete

    The alignment output should contain three rows:
        The first row corresponds to the first sequence with gaps
        The second row corresponds to the list of operations
        The third row corresponds to the second sequence with gaps
        A match [M] operation should be represented using '|'
        A convert [C] operation should be represented using '*'
        Insert and delete operations should be represented using ' ' (empty space)

    Example:
        str1: "ACAACC"
        str2: "CAAAAC"
        operations: "DMMMICM"

        output alignment:
        ACAA-CC
         ||| *|
        -CAAAAC
------------------------------------------------------------------------------*/
void PrintAlignment
(
    const std::string & str1,
    const std::string & str2,
    const std::string & operations
)
{
    // Initialize variables for the aligned sequences
    std::string alignedStr1 = "";
    std::string alignedStr2 = "";
    std::string alignmentOps = "";

    unsigned int index1 = 0;
    unsigned int index2 = 0;

    // Iterate through the operations string
    for (unsigned int i = 0; i < operations.size(); i++) {
        // Check the type of operation
        switch (operations[i]) {
            case 'M':
                // Match operation
                alignedStr1 += str1[index1++];
                alignedStr2 += str2[index2++];
                alignmentOps += "|";
                break;
            case 'C':
                // Convert operation
                alignedStr1 += str1[index1++];
                alignedStr2 += str2[index2++];
                alignmentOps += "*";
                break;
            case 'I':
                // Insert operation
                alignedStr1 += "-";
                alignedStr2 += str2[index2++];
                alignmentOps += " ";
                break;
            case 'D':
                // Delete operation
                alignedStr1 += str1[index1++];
                alignedStr2 += "-";
                alignmentOps += " ";
                break;
        }
    }

    // Print the aligned sequences and operations
    std::cout << alignedStr1 << std::endl;
    std::cout << alignmentOps << std::endl;
    std::cout << alignedStr2 << std::endl;
}



#endif
