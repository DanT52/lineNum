/***********************************************************************
name:
	lineNum -- see if a word is in the online dictionary
description:	
	See CS 360 IO lecture for details.
***********************************************************************/

/* Includes and definitions */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int lineNum(char *dictionaryName, char *word, int length);
void trimbuff(char* buff, int buff_len);

/**********************************************************************
Search for given word in dictionary using file descriptor fd.
Return the line number the word was found on, negative of the last line searched
if not found, or the error number if an error occurs.
**********************************************************************/
int lineNum(char *dictionaryName, char *word, int length) {

	

	char buffer[32];
	
	int dict_length;
	
	
	int prev_middle;
	int left = 0;
	
	int right;
	int mid;


	trimbuff(word, length); //trim word


	//open the dictionary file
	int fd = open(dictionaryName, O_RDONLY);
	if (fd< 0){
		fprintf(stderr, "ERROR: #%d : %s  \n", errno, strerror(errno));
		return 1;
	}

	dict_length = lseek(fd, 0, SEEK_END);

	right = dict_length /length;

	printf("dict num of words: %d \n", right);

	

	

	while (left <= right){

		mid = (left + right) / 2;

		printf("current middle: %d \n", mid);

		lseek(fd, mid*length, SEEK_SET);
		read(fd, buffer, length);


		//trim dict word

		trimbuff(buffer, length);

		//str cmp

		int result = strcmp(word, buffer);

		if (result == 0){
			return mid +1;
			//word matches

		}

		if (result > 0 ){
			// word is larger ignore left half
			left = mid +1;

		} else {
			//word is smaller ignore right half

			right = mid -1;

		}


		
	}

	return -(mid +1);

	
}

void trimbuff(char* buff, int buff_len){
	int i =0;



	while(1){
		
		if (buff[i] == ' ' || buff[i] == '\n' || i == buff_len -1 || buff[i] == '\0'){
			buff[i]= '\0';
			return;
		}

		i++;
	}


}


int main(int argc, char const *argv[])
{
	// char testString[] = "cat";

	// trimbuff(testString, 9);

	// printf("testtrim: %s \n", testString);

	char file[] = "tiny_9";
	char word[] = "cow";
	

	int result = lineNum(file, word, 9);
	printf("line num: %d \n", result);

	return 0;
}

