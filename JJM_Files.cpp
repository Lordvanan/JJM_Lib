#include "JJM_Files.h"
#include "JJM_App.h"

JJM_File::JJM_File(const char* file)
	: filename{ file }, file_open{ false }, current_mode{ Mode::NONE } 
{
	current = begin = SetBegin();
	SetEnd();
}

JJM_File::~JJM_File() {
	Close();
}

void JJM_File::Clear() {
	output_file.open(filename, ios::out | ios::trunc);
	output_file.close();
}

void JJM_File::Open() {
	Open(Mode::WRITE);
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
		input_file.open(filename, ios::in); 
		current_mode = Mode::READ;
		file_open = true;
		break;
	case Mode::NONE: return;
	}
}

void JJM_File::Close() {
	if (!file_open) return;
	if (output_file.is_open()) 
		output_file.close();
	if (input_file.is_open())
		input_file.close();
	file_open = false;
	current_mode = Mode::NONE;
}

void JJM_File::Write(const char* stream) {
	if (!file_open || current_mode != Mode::WRITE) 
		Open();
	output_file << stream;
	SetEnd();
}

void JJM_File::Write(string stream) {
	Write(stream.c_str());
}

void JJM_File::Append(const char* stream) {
	if (!file_open || current_mode != Mode::APPEND) 
		Open(Mode::APPEND);
	output_file << stream;
	SetEnd();
}

void JJM_File::Append(string stream) {
	Append(stream.c_str());
}

bool JJM_File::Read(string& out) {
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

bool JJM_File::ReadLine(string& out) {
	if (!file_open || current_mode != Mode::READ) 
		Open(Mode::READ);
	string temp;
	JJM_Debug("Current: %d\n", current);
	input_file.seekg(current);
	if (input_file >> temp)
	{
		out.append(temp + " ");
		current = input_file.tellg();
		return true;
	}
	return false;
}

int JJM_File::SetBegin() {
	if (!file_open || current_mode != Mode::READ)
		Open(Mode::READ);
	input_file.seekg(0, ios::beg);
	int set = input_file.tellg();
	return set;
}

int JJM_File::SetEnd() {
	if (!file_open || current_mode != Mode::READ)
		Open(Mode::READ);
	input_file.seekg(0, ios::end);
	int set = input_file.tellg();
	return set;
}

bool JJM_File::AtEnd() {
	return current == end;
}

void JJM_File::operator << (const char* stream) {
	Append(stream);
}

void JJM_File::operator << (string stream) {
	Append(stream);
}
