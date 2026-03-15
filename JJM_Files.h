#ifndef JJM_LIB_FILES
#define JJM_LIB_FILES 1

#include <fstream>
#include <string>

using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;

struct JJM_File
{
	// JJM_File constructor that defines the file name to read and write to.
	JJM_File(const char* file);

	// Overwrites the contents of the file with a new stream.
	void Write(const char* stream);

	// Overwrites the contents of the file with a new stream.
	void Write(string stream);

	// Adds the given stream to the end of the existing file contents.
	void Append(const char* stream);

	// Adds the given stream to the end of the existing file contents.
	void Append(string stream);

	// Overwrites the contents of a file specified at the time of the function call.
	static void Write(const char* file, const char* stream);

	// Overwrites the contents of a file specified at the time of the function call.
	static void Write(const char* file, string stream);

	// Overwrites the contents of a file specified at the time of the function call.
	static void Write(string file, const char* stream);

	// Overwrites the contents of a file specified at the time of the function call.
	static void Write(string file, string stream);

	// Adds the given stream to the end of a file specified at the time of the function call.
	static void Append(const char* file, const char* stream);

	// Adds the given stream to the end of a file specified at the time of the function call.
	static void Append(const char* file, string stream);

	// Adds the given stream to the end of a file specified at the time of the function call.
	static void Append(string file, const char* stream);

	// Adds the given stream to the end of a file specified at the time of the function call.
	static void Append(string file, string stream);

private:
	const char* filename;
};

#endif