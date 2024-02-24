#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

struct Folder;

struct File {
	File(const std::string& Name, std::shared_ptr<Folder> parent = nullptr)
		: parent(parent)
	{
		for (size_t i = Name.size(); i > 0; i--)
			if (Name[i] == '.') {
				name = Name.substr(0, i);
				extension = Name.substr(i);
				return;
			}
		name = Name;
		extension = "";
	}
	std::string name;
	std::string extension;
	std::shared_ptr<Folder> parent;
};

struct Folder {
	Folder(const std::string& name, std::shared_ptr<Folder> parent = nullptr)
		: name(name), parent(parent)
	{}
	std::string name;
	std::shared_ptr<Folder> parent;
	std::vector<std::shared_ptr<Folder>> folders;
	std::vector<std::shared_ptr<File>> files;
};

std::shared_ptr<Folder> CreateFolderStructure(const std::string& path, const std::string& name = "",
											std::shared_ptr<Folder> parent = nullptr) {
	std::ifstream entry;
	entry.open(path + ".entry.txt");
	if (entry.fail())
		throw "CANNOT FIND FOLDER ENTRY FILE";

	auto RootFolder = std::make_shared<Folder>(name, parent);

	std::string line;
	while (std::getline(entry, line)) {
		if (line[line.size() - 1] == '/') {
			RootFolder->folders.push_back(CreateFolderStructure(path+line,line,RootFolder));
		}
		else
			RootFolder->files.push_back(std::make_shared<File>(line, RootFolder));
	}
	entry.close();

	return RootFolder;
}

std::string GetPath(std::shared_ptr<Folder> currentFolder)
{
	if (!currentFolder)
		return "";
	std::string path = currentFolder->name;
	while (currentFolder->parent) {
		currentFolder = currentFolder->parent;
		path = currentFolder->name + path;
	}
	return path;
}
std::string GetPath(std::shared_ptr<File> file)
{
	if (!file)
		return "";
	std::string path = GetPath(file->parent);
	return path;
}

void AddEntry(std::shared_ptr<Folder> currentFolder, std::string Name, bool isFolder = false)
{
	std::string path = GetPath(currentFolder);
	std::ofstream entry;
	entry.open(path + ".entry.txt", std::ios_base::app);
	if (entry.fail())
		throw "CANNOT FIND FOLDER ENTRY FILE";

	if (isFolder) {
		system(("mkdir \"" + path + Name + '"').c_str());

		Name += '/';
		currentFolder->folders.push_back(std::make_shared<Folder>(Name, currentFolder));
		std::ofstream newEntry(path + Name + ".entry.txt");
		newEntry.close();
	}
	else
		currentFolder->files.push_back(std::make_shared<File>(Name, currentFolder));
	entry << Name + '\n';
	entry.close();
}

void RemoveEntry(std::shared_ptr<Folder> currentFolder, std::string Name, bool isFolder = false)
{
	std::string path = GetPath(currentFolder);
	std::ifstream entry;
	entry.open(path + ".entry.txt");
	if (entry.fail())
		throw "CANNOT FIND FOLDER ENTRY FILE";

	std::ofstream tmp("tmp.txt");

	std::string line;
	while (std::getline(entry, line)) {
		if (line != Name)
			tmp << line << '\n';
	}
	entry.close();
	tmp.close();

	remove((path + ".entry.txt").c_str());
	rename("tmp.txt", (path + ".entry.txt").c_str());

	if (isFolder) {
		for (size_t i = 0; i < currentFolder->folders.size(); i++)
			if (currentFolder->folders[i]->name == Name) {
				currentFolder->folders.erase(currentFolder->folders.begin() + i);
				system(("rmdir /s \"" + path + Name + '"').c_str());
				break;
			}
	} else {
		for (size_t i = 0; i < currentFolder->files.size(); i++)
			if ((currentFolder->files[i]->name + currentFolder->files[i]->extension) == Name) {
				currentFolder->files.erase(currentFolder->files.begin() + i);
				remove((path + Name).c_str());
				break;
			}
	}
}

void PrintFolderStructure(std::shared_ptr<Folder> Root, bool recursive = false, std::string indentation = "") {
	printf("%s|-%s\n", indentation.c_str(), Root->name.c_str());
	indentation += "   ";
	for (const auto& file : Root->files)
		printf("%s|-%s%s\n", indentation.c_str(),
			file->name.c_str(),
			file->extension.c_str());
	if(recursive)
		for (const auto& folder : Root->folders)
			PrintFolderStructure(folder, true, indentation);
	else
		for (const auto& folder : Root->folders)
			printf("%s|-%s\n", indentation.c_str(), folder->name.c_str());
}

std::vector<std::string> SeparateArguments(std::string argumentsConcatenated)
{
	std::vector<std::string> arguments;
	size_t last = 0;

	uint8_t escaped = 0;
	uint8_t string = 0;

	for (size_t i = 0; i < argumentsConcatenated.size(); i++) {
		switch (argumentsConcatenated[i]) {
		case '\\':
			escaped = 2;
			break;
		case '\"':
			if (!escaped)
				string = string ? 0 : 1;
			break;
		case ' ':
			if (!string) {
				arguments.push_back(argumentsConcatenated.substr(last, i - last));
				last = i + 1;
			}
			break;
		}
		if (escaped > 0)
			escaped--;
	}
	arguments.push_back(argumentsConcatenated.substr(last));
	argumentsConcatenated.clear();

	return arguments;
}

enum Argument {
	TEXT,
	RECURSIVE
};

struct commandArg {
	Argument type;
	std::string data;
};

commandArg GetArgument(const std::string& argument)
{
	if (argument == "-r")
		return commandArg{ RECURSIVE, "" };
	return commandArg{ TEXT, argument };
}

std::vector<commandArg> GetArguments(const std::string& argumentsConcatenated)
{
	std::vector<commandArg> args;

	std::vector<std::string> argumentStrings = SeparateArguments(argumentsConcatenated);
	for (const auto& argStr : argumentStrings)
		args.push_back(GetArgument(argStr));

	return args;
}

enum Command {
	LS,
	CD,
	MKDIR,
	TOUCH,
	RM,
	FIND,
	CLEAR,
	ERROR
};

Command GetCommand(const std::string& command)
{
	if (command == "ls")
		return LS;
	if (command == "cd")
		return CD;
	if (command == "mkdir")
		return MKDIR;
	if (command == "touch")
		return TOUCH;
	if (command == "rm")
		return RM;
	if (command == "clear")
		return CLEAR;
	if (command == "find")
		return FIND;
	return ERROR;
}

std::shared_ptr<File> FindFileRecursive(const File& file, std::shared_ptr<Folder> currentFolder)
{
	std::shared_ptr<File> File = nullptr;
	for (const auto& folderFile : currentFolder->files)
		if (!File)
			if(folderFile->name == file.name)
				if (file.extension != "") {
					if (folderFile->extension == file.extension)
						File = folderFile;
				} else
					File = folderFile;

	for (const auto& folder : currentFolder->folders)
		if(!File)
			File = FindFileRecursive(file, folder);

	return File;
}

void ExecuteCommand(std::shared_ptr<Folder> Root, std::shared_ptr<Folder>& CurrentFolder,
	const Command& command, const std::vector<commandArg>& arguments)
{
	switch (command) {
	case LS: {
		bool recursive = false;
		if (arguments.size())
			if (arguments[0].type == RECURSIVE)
				recursive = true;
			else if (arguments.size() == 2) {
				if (arguments[1].type == RECURSIVE)
					recursive = true;
				// USER SPECIFIED A PATH TO FOLDER
			}
		PrintFolderStructure(CurrentFolder, recursive);
	}
		   break;
	case CD:
		if (arguments[0].type == TEXT) {
			if (arguments[0].data == "/") {
				CurrentFolder = Root;
				break;
			}
			if (arguments[0].data == "..") {
				if (CurrentFolder->parent)
					CurrentFolder = CurrentFolder->parent;
				else
					puts("NO PARENT FOLDER");
				break;
			}
			for (const auto& folder : CurrentFolder->folders)
				if (folder->name == arguments[0].data) {
					CurrentFolder = folder;
					break;
				}
		}
		break;
	case MKDIR:
		if (arguments[0].type == TEXT)
			if (arguments[0].data.find("..") == std::string::npos)
				AddEntry(CurrentFolder, arguments[0].data, true);
		break;
	case TOUCH:
		if (arguments[0].type == TEXT)
			if (arguments[0].data.find("..") == std::string::npos)
				AddEntry(CurrentFolder, arguments[0].data);
		break;
	case RM: {
		bool recursive = false;
		if (arguments[0].type == RECURSIVE) {
			recursive = true;
			if (arguments[0].data.find("..") == std::string::npos)
				RemoveEntry(CurrentFolder, arguments[1].data, true);
			break;
		}
		if (arguments[0].type == TEXT)
			if (arguments[0].data.find("..") == std::string::npos)
				RemoveEntry(CurrentFolder, arguments[0].data, false);
	}
		   break;
	case FIND:
		if (arguments[0].type == TEXT) {
			File file(arguments[0].data);
			std::string path = GetPath(FindFileRecursive(file, CurrentFolder));
			if (path != "")
				printf("Path: %s%s\n", path.c_str(), arguments[0].data.c_str());
			else
				puts("File not found!");
		}
		break;
	case CLEAR:
		system("CLS");
		break;
	default:
		puts("Command not found");
		puts("Commands availabe:"
			"\n\tls        -r - Recursive"
			"\n\tcd"
			"\n\tmkdir"
			"\n\ttouch"
			"\n\trm        -r - for folders"
			"\n\tfind"
			"\n\tclear");
		break;
	}
}

std::string FindCompletion(const std::shared_ptr<Folder>& CurrentFolder, const std::string& buffer)
{
	std::string Completion = "";
	std::string toBeCompleted = "";
	for (size_t i = buffer.size(); i > 0; i--)
		if (buffer[i] == ' ') {
			toBeCompleted = buffer.substr(i + 1);
			break;
		}
	for (size_t i = 0; i < CurrentFolder->files.size(); i++)
		if (CurrentFolder->files[i]->name.find(toBeCompleted) != std::string::npos) {
			Completion = CurrentFolder->files[i]->name.substr(
				CurrentFolder->files[i]->name.find(toBeCompleted) + toBeCompleted.size())
				+ CurrentFolder->files[i]->extension;
			break;
		}
	if (Completion == "")
		for (size_t i = 0; i < CurrentFolder->folders.size(); i++)
			if (CurrentFolder->folders[i]->name.find(toBeCompleted) != std::string::npos) {
				Completion = CurrentFolder->folders[i]->name.substr(
					CurrentFolder->folders[i]->name.find(toBeCompleted) + toBeCompleted.size());
				break;
			}

	return Completion;
}

int main()
{
	auto Root = CreateFolderStructure("root/","root/");
	std::shared_ptr<Folder> CurrentFolder = Root;

	printf("root/\n> ");

	std::string lastBuffer = "";
	std::string buffer = "";
	while (true) {
		char c = getch();
		switch (c) {
		case '\r':
			{
				puts("");
				std::string command;
				std::string argumentsConcatenated;

				lastBuffer = buffer;

				for (size_t i = 0; i < buffer.size(); i++)
					if (buffer[i] == ' ') {
						command = buffer.substr(0, i);
						argumentsConcatenated = buffer.substr(i + 1);
						break;
					} else
						if(i == buffer.size() - 1)
							command = buffer;
				buffer.clear();

				ExecuteCommand(Root, CurrentFolder, GetCommand(command), GetArguments(argumentsConcatenated));

				printf("\n%s\n> ", GetPath(CurrentFolder).c_str());
			}
			break;
		case '\b':
			if (buffer.size()) {
				buffer.pop_back();
				printf("\b \b");
			}
			break;
		case '\t': {
				std::string Completion = FindCompletion(CurrentFolder, buffer);

				if (Completion != "") {
					printf("%s", Completion.c_str());
					buffer += Completion;
				}
			}
			break;
		case char(0xe0): {
				char c2 = getch();
				switch (c2) { //arrow keys
					case 'H': //up
						buffer = lastBuffer;
						printf("%s", lastBuffer.c_str());
						break;
					case 'M': //right
						break;
					case 'P': //down
						break;
					case 'K': //left
						break;
				}
			}
			break;
		case char(0x16):
			// ctrl + V
			break;
		default:
			printf("%c", c);
			buffer += c;
			break;
		}
	}
	return 0;
}