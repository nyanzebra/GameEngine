#include "file.h"
#include "console.h"

#include <assert.h>
#include <stdio.h>
#include <FreeImage.h>
#ifdef _WIN32
#include <direct.h>
#define CWD _getcwd
#else
#include <unistd.h>
#define CWD getcwd
#endif

using namespace cppe::io;

void file::append(const std::string& data) {
	assert(file_name != "" || !file_name.empty());

	FILE* file = fopen(file_name.c_str(), "a");

	if (!file) {
		console::output_line("ERROR: failed to open file...");
		return;
	}

	fputs(data.c_str(), file);

	fclose(file);
}

void file::print_current_working_directory() {
	char path[FILENAME_MAX];
	CWD(path, sizeof(path));
	path[sizeof(path) - 1] = NULL;

	console::output_line("Current working directory is: ", path);
}

const std::string& file::data() const {
	return file_data;
}

const std::string& file::read() {
	assert(file_name != "" || !file_name.empty());

	FILE* file = fopen(file_name.c_str(), "r");

	if (!file) {
		console::output_line("ERROR: failed to open file...");
	}

	fseek(file, 0, SEEK_END);
	unsigned long length = ftell(file);

	char* data = new char[length + 1];
	memset(data, 0, length + 1);
	fseek(file, 0, SEEK_SET);

	fread(data, 1, length, file);
	fclose(file);

	file_data = data;
	delete[] data;

	return file_data;
}

void file::write(const std::string& data) {
	assert(file_name != "");

	FILE* file = fopen(file_name.c_str(), "w");

	if (!file) {
		console::output_line("ERROR: failed to open file...");
		return;
	}

	fwrite(data.c_str(), sizeof(char), sizeof(data), file);
	fclose(file);
}
