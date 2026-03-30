#ifndef JJM_LIB_FILES
#define JJM_LIB_FILES 1

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using std::ofstream;
using std::ifstream;
using std::streampos;
using std::ios;
using std::string;

namespace JJM
{
	enum class Mode {
		NONE,
		WRITE,
		APPEND,
		READ
	};

	class File
	{
	private:
		const char* filename;
		bool file_open;
		ofstream output_file;
		ifstream input_file;
		Mode current_mode;
		streampos begin;
		streampos current;
		streampos end;

		int SetBegin();

		int SetEnd();
	public:
		// Constructor that defines the file name including the directory.
		File(const char* file);

		// Cleanly closes up the file before destruction.
		~File();

		// Clears all contents of the file.
		void Clear();

		// Opens the file in write mode to override the current contents.
		void Open();

		// Opens the file in the mode specified.
		void Open(Mode open_mode);

		// Cleanly closes up the file.
		void Close();

		// Overwrites the contents of the file with a new stream.
		void Write(const char* stream);

		// Overwrites the contents of the file with a new stream.
		void Write(string stream);

		// Adds to the contents of the file with a new stream.
		void Append(const char* stream);

		// Adds to the contents of the file with a new stream.
		void Append(string stream);

		bool Read(string& out);

		bool AtEnd();

		void operator << (const char* stream);
		void operator << (string stream);
	};
}
#endif