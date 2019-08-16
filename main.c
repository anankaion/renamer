#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>

#define BUFSIZE 256

void
number (char* number_option, char* path) {

    int i = 0;
    int k = 0;
    int len;

	char* new_name;                 //new name of the file
	char* entry_path;               //complete path of the file entry
    char placeholder[2] = "\0";     //placeholder for append strings

	struct dirent* entry;
	DIR* dir = opendir(path);

	if (*number_option == 'f'){
	    while ((entry = readdir(dir))) {
            if ((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)) {      //skip . and .. directory
                new_name = calloc(strlen(entry->d_name) + strlen(path) + 2, sizeof(char));
                entry_path = calloc(strlen(entry->d_name) + strlen(path), sizeof(char));

                strcat(new_name, path);
                placeholder[0] = i + '0';
                placeholder[1] = '_';
                strcat(new_name, placeholder);
                strcat(new_name, entry->d_name);

                strcat(entry_path, path);
                strcat(entry_path, entry->d_name);

                rename(entry_path, new_name);

                i++;
            }
	    }
	} else if (*number_option == 'r') {
        while ((entry = readdir(dir))) {
            if ((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)) {      //skip . and .. directory
                new_name = calloc(strlen(path) + 2, sizeof(char));
                entry_path = calloc(strlen(entry->d_name) + strlen(path), sizeof(char));

                strcat(new_name, path);
                placeholder[0] = i + '0';
                strcat(new_name, placeholder);

                strcat(entry_path, path);
                strcat(entry_path, entry->d_name);

                rename(entry_path, new_name);

                i++;
            }
        }
	}
	/*else if (*number_option == 'b') {
        while ((entry = readdir(dir))) {
            if ((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)) {      //skip . and .. directory
                new_name = calloc(strlen(entry->d_name) + strlen(path) + 2, sizeof(char));
                entry_path = calloc(strlen(entry->d_name) + strlen(path), sizeof(char));

                strcat(new_name, path);
                strcat(new_name, entry->d_name);

                len = strlen(new_name);
                for (int j = 4; j > 0; --j) {
                    new_name[len + j] = new_name[len - k];
                    k++;
                }

                new_name[len - 4] = i + '0';
                new_name[len - 3] = '_';

                strcat(entry_path, path);
                strcat(entry_path, entry->d_name);

                rename(entry_path, new_name);

                i++;
            }
        }
	}*/
}

int
main (int argc, char** argv) {
	int c;

	char *path;
	char what;
	char *number_option;

	while ((c = getopt(argc, argv, "n:i:")) != -1) {
		switch (c) {
			case 'n':
				what = 'n';
				number_option = optarg;
				break;

            case 'i':
                path = optarg;
                break;

            default:
                printf("Unknown option.\n");
		}
	}

	if (what == 'n') {
	    number(number_option, path);
	}
}
