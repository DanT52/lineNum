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
void trimbuff(char* buff, int buff_len);
int exiter(int fd, char *buffer, char *msg, int mid);

/**********************************************************************
Search for given word in dictionary using file descriptor fd.
Return the line number the word was found on, negative of the last line searched
if not found, or the error number if an error occurs.
**********************************************************************/
int lineNum(char *dictionaryName, char *word, int length) {

	char *buffer = malloc(length+1);										//malloc buffer
	if(!buffer) return exiter(-1, NULL,"Failed to allocate buffer.", 0);	//ensure allocation worked
	int dict_length, left = 0, right, mid;									//Create variables for the binary search

	trimbuff(word, length); 	//truncate the entered word.

	int fd = open(dictionaryName, O_RDONLY);						//open the dictionary
	if (fd< 0)return exiter(fd, buffer, "Failed to Open File.",0);	//ensure opened sucesfully

	dict_length = lseek(fd, 0, SEEK_END);											//seek to end of file to determine total length
	if (dict_length == -1)return exiter(fd, buffer, "Seeking in file Failed.", 0);	
	right = dict_length /length; 	//set right pointer for binary search to the last line

	while (left <= right){			//binary search is to run while left pointer is not equal to right

		mid = (left + right) / 2;	//set the current middle word

		//Seek too and read the middle word into buffer
		if (lseek(fd, mid*length, SEEK_SET) == -1)return exiter(fd, buffer, "Seeking in file Failed.", 0);
		if (read(fd, buffer, length)==-1)return exiter(fd, buffer, "Reading in file Failed", 0);
		trimbuff(buffer, length);			//truncate the word at the first space	
		int result = strcmp(word, buffer);	//compare entered word to word in buffer	

		if (result == 0)return exiter(fd, buffer, NULL, mid+1); //The word matches we found the line.
		if (result > 0 )left = mid +1;	//word is larger ignore left half
		if (result < 0)right = mid -1;	//word is smaller ignore right half
	}
	//we reached the end of the binary search without finding the word
	return exiter(fd, buffer, NULL, -(mid+1));
}


//trims buff by replacing replacing the first occurrence of a space, newline, 
//or the end of the buffer with a null terminator 
//buff: 		pointer to buffer for trimming
//buff_len: 	length of the buffer
void trimbuff(char* buff, int buff_len){
	int i = 0;

	while(1){	//loop until one of the conditions is met
		if (buff[i] == ' ' || buff[i] == '\n' || i == buff_len -1 || buff[i] == '\0'){
			buff[i]= '\0';
			return;
		}
		i++;	//move to the next character in the buffer
	}
}

//handles errors, cleans up, returns appropriate value
//fd:			file descripter to be closed, pass -1 if no file to close
//buffer:		pointer to buffer to be freed, pass null if no buffer to free
//msg:			custom error message, pass null if no error
//lineNumber:	line number to return if sucess, pass 0 otherwise.
//@return 		returns the provided lineNumber on success or errno on failure.
int exiter(int fd, char *buffer, char *msg, int lineNumber){
	 // display custom error message if provided
	if(msg)fprintf(stderr, "ERROR: %s Error#: '%d' Error Msg: '%s'\n", msg, errno, strerror(errno));
	
	if (fd != -1){	// close the file descriptor if valid
		if (close(fd) == -1)fprintf(stderr, "Error Closing File\n Error#: %d \n Message: %s  \n", errno, strerror(errno));
	}
	if(buffer)free(buffer);	// Free the buffer if it's not NULL

	// return the provided line number if non-zero, otherwise return the error number
	if(lineNumber != 0) return lineNumber;
	return errno;

}