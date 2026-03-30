#include "JJM_Files.h"

JJM::File::File(const char* file)
	: filename{ file }, file_open{ false }, current_mode{ Mode::NONE } 
{
	current = SetBegin();
	SetEnd();
}

JJM::File::~File() {
	Close();
}

void JJM::File::Clear() {
	output_file.open(filename, ios::out | ios::trunc);
	output_file.close();
}

void JJM::File::Open() {
	Open(Mode::WRITE);
}

void JJM::File::Open(Mode open_mode) {
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
		input_file.open(filename, ios::in); 
		current_mode = Mode::READ;
		file_open = true;
		break;
	case Mode::NONE: return;
	}
}

void JJM::File::Close() {
	if (!file_open) return;
	if (output_file.is_open()) 
		output_file.close();
	if (input_file.is_open())
		input_file.close();
	file_open = false;
	current_mode = Mode::NONE;
}

void JJM::File::Write(const char* stream) {
	if (!file_open || current_mode != Mode::WRITE) 
		Open();
	output_file << stream;
	SetEnd();
}

void JJM::File::Write(string stream) {
	Write(stream.c_str());
}

void JJM::File::Append(const char* stream) {
	if (!file_open || current_mode != Mode::APPEND) 
		Open(Mode::APPEND);
	output_file << stream;
	SetEnd();
}

void JJM::File::Append(string stream) {
	Append(stream.c_str());
}

bool JJM::File::Read(string& out) {
	if (!file_open || current_mode != Mode::READ) 
		Open(Mode::READ);
	input_file.seekg(current);
	if (input_file >> out)
	{
		current = input_file.tellg();
		return true;
	}
	return false;
}

int JJM::File::SetBegin() {
	if (!file_open || current_mode != Mode::READ)
		Open(Mode::READ);
	input_file.seekg(0, ios::beg);
	begin = input_file.tellg();
	return begin;
}

int JJM::File::SetEnd() {
	if (!file_open || current_mode != Mode::READ)
		Open(Mode::READ);
	input_file.seekg(0, ios::end);
	end = input_file.tellg();
	return end;
}

bool JJM::File::AtEnd() {
	return current == end;
}

void JJM::File::operator << (const char* stream) {
	Append(stream);
}

void JJM::File::operator << (string stream) {
	Append(stream);
}
