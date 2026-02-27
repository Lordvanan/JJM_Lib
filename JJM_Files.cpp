#include "JJM_Files.h"

JJM_File::JJM_File(const char* file)
	: filename{ file } {
}

void JJM_File::Write(const char* stream)
{
	ofstream output_file;
	output_file.open(filename, ios::out);

	output_file << stream;
	output_file.close();
}

void JJM_File::Write(string stream)
{
	ofstream output_file;
	output_file.open(filename, ios::out);

	output_file << stream;
	output_file.close();
}

void JJM_File::Append(const char* stream)
{
	ofstream output_file;
	output_file.open(filename, ios::app);

	output_file << stream;
	output_file.close();
}

void JJM_File::Append(string stream)
{
	ofstream output_file;
	output_file.open(filename, ios::app);

	output_file << stream;
	output_file.close();
}

void JJM_File::Write(const char* file, const char* stream)
{
	ofstream output_file;
	output_file.open(file, ios::out);

	output_file << stream;
	output_file.close();
}

void JJM_File::Write(const char* file, string stream)
{
	ofstream output_file;
	output_file.open(file, ios::out);

	output_file << stream;
	output_file.close();
}

void JJM_File::Write(string file, const char* stream)
{
	ofstream output_file;
	output_file.open(file, ios::out);

	output_file << stream;
	output_file.close();
}

void JJM_File::Write(string file, string stream)
{
	ofstream output_file;
	output_file.open(file, ios::out);

	output_file << stream;
	output_file.close();
}

void JJM_File::Append(const char* file, const char* stream)
{
	ofstream output_file;
	output_file.open(file, ios::app);

	output_file << stream;
	output_file.close();
}

void JJM_File::Append(const char* file, string stream)
{
	ofstream output_file;
	output_file.open(file, ios::app);

	output_file << stream;
	output_file.close();
}

void JJM_File::Append(string file, const char* stream)
{
	ofstream output_file;
	output_file.open(file, ios::app);

	output_file << stream;
	output_file.close();
}

void JJM_File::Append(string file, string stream)
{
	ofstream output_file;
	output_file.open(file, ios::app);

	output_file << stream;
	output_file.close();
}
