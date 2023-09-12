# `lineNum` (assigment2)

## Description
The `lineNum` function is designed to determine if a word exists in an online dictionary. It utilizes a binary search to efficiently locate the word in the dictionary and returns the line number of the word if found.

## Features
- Efficient binary search to determine word existence.
- Memory allocation and deallocation for buffers.
- File handling to open, seek, read, and close dictionary files.
- Error handling with custom error messages.

## Functions

### `int lineNum(char *dictionaryName, char *entered_word, int length)`
- **Inputs**:
  - `dictionaryName`: Name of the dictionary file to be searched.
  - `entered_word`: Word to be searched in the dictionary.
  - `length`: Length of the word.
- **Output**:
  - Returns the line number if the word is found.
  - Returns the negative of the last line searched if not found.
  - Returns the error number if an error occurs.

### `void cpy_word(char *entered_word, char *word, int buff_len)`
- **Inputs**:
  - `entered_word`: Word to be copied.
  - `word`: Buffer where the copied word will be stored.
  - `buff_len`: Length of the buffer.
- **Functionality**:
  - Copies the `entered_word` into `word` and fills any remaining space with spaces until the length matches `buff_len`.
  - The new word is null terminated.

### `int exiter(int fd, char *buffer, char *word, char *msg, int lineNumber)`
- **Inputs**:
  - `fd`: File descriptor to be closed. Pass -1 if no file to close.
  - `buffer`: Buffer to be freed.
  - `word`: Word buffer to be freed.
  - `msg`: Custom error message. Pass null if no error.
  - `lineNumber`: Line number to return if successful, pass 0 otherwise.
- **Output**:
  - Returns the provided line number on success or errno on failure.
- **Functionality**:
  - Handles errors, cleanup, and returns the appropriate value.

## Usage
To utilize the `lineNum` function:
1. Include the necessary headers and definitions.
2. Call the `lineNum` function with the appropriate arguments.
3. Handle the returned value as desired.
