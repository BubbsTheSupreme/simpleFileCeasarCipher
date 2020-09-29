#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int encrypt(char *file_name, int file_size, int key) {
	char *buffer = (char*)malloc(file_size * sizeof(char));
	FILE *file = fopen(file_name, "r");
	
	if (file == NULL){ //check that file exists still
		printf("ERROR: file failed to open..\n");
		exit(1); // exit program
	}

	fread(buffer, sizeof(char), file_size, file); // read file contents into buffer
	fclose(file); // close file
	
	for (int i = 0; i < file_size; i++) {
		buffer[i] += key; // shift bytes that are in buffer
	}
	
	fopen(file_name, "w"); // open file in write mode
	fwrite(buffer, sizeof(char), file_size, file); // write new shifted bytes to file
	fclose(file); // close file
	free(buffer); // free memory!!!!
	return 0;
}

int decrypt(char *file_name, int file_size, int key) {
	char *buffer = (char*)malloc(file_size * sizeof(char));
	FILE *file = fopen(file_name, "r");
	
	if (file == NULL){ //check that file exists still
		printf("ERROR: file failed to open..\n");
		exit(1);
	}

	fread(buffer, sizeof(char), file_size, file); // read file contents into buffer
	fclose(file);
	
	for (int i = 0; i < file_size; i++) {
		buffer[i] -= key; // shift bytes that are in buffer
	}
	
	fopen(file_name, "w"); // open file in write mode
	fwrite(buffer, sizeof(char), file_size, file); // write new shifted bytes to file
	fclose(file); // close file
	free(buffer); // free memory!!!!
	return 0;
}

int get_size(char *file_name){ // counts each byte of the file it opens
	FILE *file = fopen(file_name, "r");
	if (file == NULL){
		printf("ERROR: file failed to open..\n");
		exit(1);
	}
	int count = 0;
	char c;
	if (file) {
		while(1) {
			c = fgetc(file); // read byte and store it in c
			if (c == EOF){ // if the byte is equal to the end of file byte 
				break; // then exit the loop and continue through the function
			}
			else{
				count++; // increment the count 
			}
		}
	}
	fclose(file);
	return count; // return count
}

int main(int argc, char *argv[]){
	if (argc < 4){
		printf("USAGE: cipher <filename> <key> <mode>\n");
		return 1; // return with a 1 signaling that there was an error
	}

	char *file_name = argv[1];
	int key = atoi(argv[2]); // convert string to int
	int file_size = get_size(file_name); // calls get_size() and stores it in variable

	if(strcmp(argv[3], "-e") == 0){
		int status = encrypt(file_name, file_size, key); 
		if (status == 0) { // check if encrypt() returns 0
			printf("ENCRYPTION SUCCESSFUL!\n");
		}
	}
	else if(strcmp(argv[3], "-d") == 0){
		int status = decrypt(file_name, file_size, key);
		if (status == 0) { // check if decrypt() returns 0
			printf("DECRYPTION SUCCESSFUL!\n");
		}
	}
	else { // if argv[3] <mode> does not match any of the required values 
		printf("ERROR: %s is not a valid argument for <mode>\n", argv[3]);
		printf("USAGE: -e: encrypt, -d: decrypt\n");
		return 1; // return with a 1 signaling that there was an error
	}
	
	return 0; // return with a 0 signaling everything executed correctly
}