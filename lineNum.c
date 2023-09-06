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
	int current_middle;
	int prev_middle;

	int left =0;
	int right;
	int mid;

	trimbuff(word, length); //trim word

	//open the dictionary file
	int fd = open("test.txt", O_RDONLY);
	if (fd< 0){
		fprintf(stderr, "ERROR: #%d : %s  \n", errno, strerror(errno));
		return 1;
	}

	dict_length = lseek(fd, 0, SEEK_END) / length;
	right = dict_length;

	lseek(fd, 0, SEEK_SET);

	current_middle = dict_length / 2;

	while (left <= right){
		mid = (left + right) / 2;


		//trim dict word

		trimbuff(buffer, length);

		//str cmp


		//word matches

		

		// word is larger ignore left half
		left = mid +1;


		//word is smaller ignore right half

		right = mid -1;

		//if current middle is past middle then not found.



		
		
	}

	return -mid;


	
	//insert your code here
	return 0;
}

void trimbuff(char* buff, int buff_len){
	int i =0;

	while(1){
		
		if (buff[i] == ' ' || buff[i] == '/n' || i == buff_len -1 || buff[i] == '\0'){
			buff[i]= '\0';
		}

		i++;
	}


}


int main(int argc, char const *argv[])
{
	char buff[9];
	int width = 9;
	int middle = 0;

	int fd = open("tiny_9", O_RDONLY);
	if (fd< 0){
		fprintf(stderr, "ERROR: #%d : %s  \n", errno, strerror(errno));
		return 1;
	}

	int dict_length = lseek(fd, 0, SEEK_END);
	printf("seeked curr: %d \n", dict_length);

	middle = (dict_length/width)/2;

	dict_length = lseek(fd, middle*width, SEEK_SET);
	printf("seeked curr: %d \n", dict_length);

	int reader = read(fd, buff, 9);
	dict_length = lseek(fd, 0, SEEK_CUR);
	printf("seeked curr: %d \n", dict_length);

	printf("letters %s \n",buff);

	return 0;
}

