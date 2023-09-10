/***********************************************************************
name:
	lineNum -- see if a word is in the online dictionary
description:	
	See CS 360 IO lecture for details.
***********************************************************************/

/* Includes and definitions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int lineNum(char *dictionaryName, char *word, int length);
int exiter(int fd, char *msg, int lineNumber);
void cpy_word(char *entered_word, char *word, int buff_len);

/**********************************************************************
Search for given word in dictionary using file descriptor fd.
Return the line number the word was found on, negative of the last line searched
if not found, or the error number if an error occurs.
**********************************************************************/
int lineNum(char *dictionaryName, char *entered_word, int length){

	int dict_length, right, left=0, mid;
	char buffer[length], word[length];
	cpy_word(entered_word, word, length);

	int fd = open(dictionaryName, O_RDONLY);						//open the dictionary
	if (fd == -1)return exiter(fd, "Failed to open file.", 0);
	
	dict_length = lseek(fd, 0, SEEK_END);							//seek to end of file to determine total length
	if (dict_length == -1)return exiter(fd, "Failed to seek", 0);
	right = dict_length /length; 	//set right pointer for binary search to the last line

	while (left <= right){			//binary search is to run while left pointer is not equal to right

		mid = (left + right) / 2;	//set the current middle word
		
		//Seek too and read the middle word into buffer
		if (lseek(fd, mid*length, SEEK_SET)==-1)return exiter(fd, "Failed to seek", 0);
		if (read(fd, buffer, length) != length)return exiter(fd, "Failed to read word from dictionary.", 0);
		buffer[length-1] = '\0'; // null terminate buffer.
		
		int result = strcmp(word, buffer);	//compare entered word to word in buffer	
		if (result == 0)return  exiter(fd, NULL, (mid+1)); 	//The word matches we found the line.
		if (result > 0 )left = mid +1;						//word is larger ignore left half
		if (result < 0)right = mid -1;						//word is smaller ignore right half
	}

	//we reached the end of the binary search without finding the word
	return exiter(fd, NULL, -(mid+1));
	
}
//Copies entered word into word
//leaves spaces after entered word untill word is same length as buff_len
//the new word is null terminated
void cpy_word(char *entered_word, char *word, int buff_len){
	int i = 0;
	while (entered_word[i] != '\0' && entered_word[i] != '\n' && i < buff_len){
		word[i]=entered_word[i];			//copy chars too word while there are chars to copy
		i++;
	}
	while(i<buff_len){		//add spaces untill length matches buff/dictionary length.
		word[i] = ' ';
		i++;
	}
	word[i-1] = '\0';
}

//handles errors, cleans up, returns appropriate value
//fd:			file descripter to be closed, pass -1 if no file to close
//msg:			custom error message, pass null if no error
//lineNumber:	line number to return if sucess, pass 0 otherwise.
//@return 		returns the provided lineNumber on success or errno on failure.
int exiter(int fd, char *msg, int lineNumber){
	 // display custom error message if provided
	if(msg)fprintf(stderr, "ERROR: %s Error#: '%d' Error Msg: '%s'\n", msg, errno, strerror(errno));
	
	if (fd != -1){	// close the file descriptor if valid
		if (close(fd) == -1)fprintf(stderr, "Error Closing File\n Error#: %d \n Message: %s  \n", errno, strerror(errno));
	}
	// return the provided line number if non-zero, otherwise return the error number
	if(lineNumber != 0) return lineNumber;
	return errno;
}