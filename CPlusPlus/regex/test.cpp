// regex_match example
#include <iostream>
#include <string>
#include <regex>

#include <iomanip>

#include <memory>

#define splitLines "\n----------------------------------------------- "

struct myTimer {
	//myTimer(std::string str) :start(time(0)),name(str){ }
	myTimer(std::string str) :start(clock()), name(str) { }
	~myTimer() { 
		//std::cout << name << " using time " << (time(0) - start)<< " s"; 
		std::cout << name << " using " << (clock() - start) << " ms" << std::endl;
	}
	//time_t start;
	clock_t start;
	std::string name;
};
#define TIME_SCOPE_GLOBAL(str) std::shared_ptr<myTimer> pt = std::make_shared<myTimer>(str)

#define TIME_SCOPE_BEGIN(str) { std::cout << splitLines << str <<std::endl; \
std::shared_ptr<myTimer> pt = std::make_shared<myTimer>(str); 
#define TIME_SCOPE_END  std::cout << splitLines ;}

int main()
{
	//TIME_SCOPE_GLOBAL("test");

	TIME_SCOPE_BEGIN("code1")
	if (std::regex_match("subject", std::regex("(sub)(.*)")))
	{
		std::cout <<" string literal matched\n";
	}
	TIME_SCOPE_END

	const char cstr[] = "subject";
	std::string s("subject");
	std::regex e("(sub)(.*)");

	if (std::regex_match(s, e))
		std::cout << "string object matched\n";

	if (std::regex_match(s.begin(), s.end(), e))
		std::cout << "range matched\n";

	std::cmatch cm; 
	TIME_SCOPE_BEGIN("code1");
	  // same as std::match_results<const char*> cm;
	std::regex_match(cstr, cm, e);
	std::cout << "string literal with " << cm.size() << " matches\n";
	for (unsigned i = 0; i < cm.size(); ++i) {
		std::cout << "[" << cm[i] << "] ";
	}
	TIME_SCOPE_END;

	std::smatch sm; // same as std::match_results<string::const_iterator> sm;
	TIME_SCOPE_BEGIN("code2");
	std::regex_match(s, sm, e);
	std::cout << "string object with " << sm.size() << " matches\n";
	for (unsigned i = 0; i < sm.size(); ++i) {
		std::cout << "[" << sm[i] << "] ";
	}
	TIME_SCOPE_END;

	TIME_SCOPE_BEGIN("code3");
	std::regex_match(s.cbegin(), s.cend(), sm, e);
	std::cout << "range with " << sm.size() << " matches\n";
	for (unsigned i = 0; i < sm.size(); ++i) {
		std::cout << "[" << sm[i] << "] ";
	}
	TIME_SCOPE_END;

	TIME_SCOPE_BEGIN("code4");
	// using explicit flags:
	std::regex_match(cstr, cm, e, std::regex_constants::match_default);
	std::cout << "the matches were: ";
	for (unsigned i = 0; i < cm.size(); ++i) {
		std::cout << "[" << cm[i] << "] ";
	}
	TIME_SCOPE_END;

	std::cout << std::endl;

	{
		TIME_SCOPE_BEGIN("code5");

		//using std::string;
		std::string str = " 0\tabc123def456# \t\n";
		std::string::size_type i = 0;
		//for (i = 0; i < str.length(); i++) {
		for (i = (int32_t)str.length() - 1; i >= 0; i--)
		{
			if (str[i] != ' ' &&
				str[i] != '\t' &&
				str[i] != '\n' &&
				str[i] != '\r')
				break;
		}
		str = str.substr(0, i + 1);
		std::cout << str << std::endl;
		TIME_SCOPE_END;
	}

	{
		TIME_SCOPE_BEGIN("code6"); 

		using namespace std;

		cout << regex_match("123", regex("[0-9]+")) << endl;

		// regex搜索多次
		string str = "!!!123!!!12333!!!890!!!";
		auto re = regex("[0-9]{3}");
		while (regex_search(str, sm, re)) {
			//for (int i = 0; i < sm.size(); ++i)
			int i = 0;
				cout << "result: " << setw(10)<< sm.str(i) << ", pos = " << sm.position(i) << ", length = " << sm.length(i) << endl;
			str = sm.suffix().str();
		}
		TIME_SCOPE_END;
	}

	{
		TIME_SCOPE_BEGIN("code7");

		std::string s("this subject has a submarine as a subsequence");
		std::smatch m;
		std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

		std::cout << "Target sequence: " << s << std::endl;
		std::cout << "Regular expression: \\\\b(sub)([^ ]*)/" << std::endl;
		std::cout << "The following matches and submatches were found:" << std::endl;

		while (std::regex_search(s, m, e)) {
			//std::cout << m.str() << std::endl; // 只有匹配结果
			
			for (auto x : m)
				std::cout << x << " ";   // [0]位匹配结果，[1][2]分别为匹配的组
			std::cout << std::endl;
			
			s = m.suffix().str();
		}

		TIME_SCOPE_END;
	}

	{
		TIME_SCOPE_BEGIN("io");

		int result;
		char oldname[] = "regex.ilk";
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
				fprintf(pFile, "Name size = %d, name = %s\n", sizeof(buffer), buffer);
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


		TIME_SCOPE_END;
	}

	return 0;
}