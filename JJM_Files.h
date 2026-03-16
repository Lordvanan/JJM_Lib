#ifndef JJM_LIB_FILES
#define JJM_LIB_FILES 1

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;

enum class Mode {
	NONE,
	WRITE,
	APPEND,
	READ
};

class JJM_File
{
private:
	const char* filename;
	bool file_open;
	ofstream output_file;
	Mode current_mode;

public:
	// Constructor that defines the file name including the directory.
	JJM_File(const char* file);

	// Cleanly closes up the file before destruction.
	~JJM_File();

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

	void operator << (const char* stream);
	void operator << (string stream);
};

#endif