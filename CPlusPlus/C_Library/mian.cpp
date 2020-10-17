
#include <cstdlib>

#include <iostream>
#include <string>
#include <iomanip>

#include <memory>
#include <ctime>

#define splitLines "\n----------------------------------------------- "

struct myTimer {
	//myTimer(std::string str) :start(time(0)),name(str){ }
	myTimer(std::string str) :start(clock()), name(str) {
		std::cout << splitLines << str << std::endl;
	}
	~myTimer() {
		//std::cout << name << " using time " << (time(0) - start)<< " s"; 
		std::cout << splitLines << name << " using " << (clock() - start) << " ms" << std::endl;
	}
	//time_t start;
	clock_t start;
	std::string name;
};
#define TIME_SCOPE_GLOBAL(str) std::shared_ptr<myTimer> pt = std::make_shared<myTimer>(str)    // 可以用#不展开，直接作为字符

#define TIME_SCOPE_BEGIN(str) { std::cout << splitLines << str <<std::endl; \
std::shared_ptr<myTimer> pt = std::make_shared<myTimer>(str); 
#define TIME_SCOPE_END  std::cout << splitLines ;}

int main()
{
	{
		TIME_SCOPE_GLOBAL("file control");

		int result;
		char oldname[] = "C_Library.ilk";
		char newname[] = "newname.txt";
		result = rename(oldname, newname);
		if (result == 0)
			puts("File successfully renamed");
		else
			perror("Error renaming file");

		//getchar();

		if (remove("newname.txt") != 0)
			perror("Error deleting file");
		else
			puts("File successfully deleted");
	}

	{
		puts("...... temp file ......");

		char buffer[256];
		FILE * pFile;
		pFile = tmpfile();

		do {
			if (!fgets(buffer, 256, stdin)) break;
			fputs(buffer, pFile);
		} while (strlen(buffer) > 1);

		rewind(pFile);

		while (!feof(pFile)) {
			if (fgets(buffer, 256, pFile) == NULL) break;
			fputs(buffer, stdout);
		}


		{
			puts("...... save temp file ......");

			rewind(pFile);

			char buffer[L_tmpnam];
			char * pointer;
			tmpnam(buffer);

			puts(buffer);

			FILE *tmp = fopen(buffer, "w");
			setbuf(tmp, buffer);
			fprintf(pFile, "Name size = %zd, name = %s\n", sizeof(buffer), buffer);
			fflush(pFile);
			fclose(tmp);


			//getchar();

			if (remove(buffer) != 0)
				perror("Error deleting tmp file");
			else
				puts("Tmp File successfully deleted");
		}


		fclose(pFile);
	}

	{
		TIME_SCOPE_GLOBAL("stdlib");

		puts("...... environment ......");
		char* pPath;
		pPath = getenv("PATH");
		if (pPath != NULL)
			printf("The current path is: %s", pPath);

		puts("...... system ......");

		printf("Checking if processor is available...");
		if (system(NULL)) puts("Ok");
		else exit(EXIT_FAILURE);
		printf("Executing command DIR...\n");
		int i = system("dir");
		printf("The value returned was: %d.\n", i);

	}
	{
		TIME_SCOPE_GLOBAL("string");

		{
			puts("...... strtok ......");
			char str[] = "- This, a sample string.";
			char * pch;
			printf("Splitting string \"%s\" into tokens:\n", str);
			pch = strtok(str, " ,.-");
			while (pch != NULL)
			{
				printf("%s\n", pch);
				pch = strtok(NULL, " ,.-");
			}
		}
		{
			puts("...... strchr ......");
			char str[] = "This is a sample string";
			char * pch;
			printf("Looking for the 's' character in \"%s\"...\n", str);
			pch = strchr(str, 's');
			while (pch != NULL)
			{
				printf("found at %d\n", pch - str + 1);
				pch = strchr(pch + 1, 's');
			}
		}
		{
			puts("...... strerror ......");
			FILE * pFile;
			pFile = fopen("unexist.ent", "r");
			if (pFile == NULL)
				//printf("Error opening file unexist.ent: %s\n", strerror(errno));
				perror("Error opening file unexist.ent"); //效果同上
		}
	}

	return 0;
}