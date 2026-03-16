#include "JJM_Files.h"

JJM_File::JJM_File(const char* file)
	: filename{ file }, file_open{ false }, current_mode{ Mode::NONE } {
}

JJM_File::~JJM_File() {
	Close();
}

void JJM_File::Clear() {
	output_file.open(filename, ios::out | ios::trunc);
	output_file.close();
}

void JJM_File::Open() {
	if (file_open) Close();
	output_file.open(filename, ios::out);
	current_mode = Mode::WRITE;
	file_open = true;
}

void JJM_File::Open(Mode open_mode) {
	if (file_open) Close();
	switch (open_mode) {
	case Mode::WRITE: 
		output_file.open(filename, ios::out); 
		current_mode = Mode::WRITE;
		file_open = true;
		break;
	case Mode::APPEND: 
		output_file.open(filename, ios::app); 
		current_mode = Mode::APPEND;
		file_open = true;
		break;
	case Mode::READ: 
		output_file.open(filename, ios::in); 
		current_mode = Mode::READ;
		file_open = true;
		break;
	case Mode::NONE: return;
	}
}

void JJM_File::Close() {
	if (!file_open) return;
	output_file.close();
	file_open = false;
	current_mode = Mode::NONE;
}

void JJM_File::Write(const char* stream) {
	if (!file_open || current_mode != Mode::WRITE) 
		Open();
	output_file << stream;
}

void JJM_File::Write(string stream) {
	if (!file_open || current_mode != Mode::WRITE) 
		Open();
	output_file << stream;
}

void JJM_File::Append(const char* stream) {
	if (!file_open || current_mode != Mode::APPEND) 
		Open(Mode::APPEND);
	output_file << stream;
}

void JJM_File::Append(string stream) {
	if (!file_open || current_mode != Mode::APPEND) 
		Open(Mode::APPEND);
	output_file << stream;
}

void JJM_File::operator << (const char* stream) {
	Append(stream);
}

void JJM_File::operator << (string stream) {
	Append(stream);
}
