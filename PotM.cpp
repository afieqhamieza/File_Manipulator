#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<iostream>
#include<string>
#include <fstream>
#include <stdlib.h>
#include <cstddef>//for getting the path of a file 

using namespace std;
void appendText();
void insertText();
void removeText();
void showText();
void RenameFile(void);
void MoveFile(void);
void createFile();
void deleteFile();
void copyFile();


//TO DO clean up text alteration functions to be clean functions (no input/output)
//TO DO add help (one big help funtions
int main()
{
	enum Functions {help, append, insert, show, remove, rename, move, create, del, copy, unknown, exit};
	Functions userCom;
	string command;
	string text;
	bool cont = true;

	while (cont)
	{
		cout << "Welcome to PotM \nEnter Command or enter -help for options\n";
		getline(std::cin, command);

		if (command == "help")
		{
			userCom = help;
		}
		else if (command == "append") userCom = append;
		else if (command == "insert") userCom = insert;
		else if (command == "show") userCom = show;
		else if (command == "rename") userCom = rename;
		else if (command == "remove") userCom = remove;
		else if (command == "move") userCom = move;
		else if (command == "create") userCom = create;
		else if (command == "delete") userCom = del;
		else if (command == "copy") userCom = copy;
		else userCom = unknown;

		switch (userCom)
		{
		case help:
			cout << "Here is a list of possible funcitons and their commands\n -help: get help information\n -append: add text to an existing text file\n -insert: inset text into a text file at a give position\n -show: show text file content\n -remove: remove all text from file\n -rename: rename a specified file \n -move: moves a file to a new location\n -create: creates a new file\n -delete: deletes a file\n -copy: creates a second copy of a file at a give location";
			break;

		case append:
			appendText();			
			break;

		case insert:
			insertText();
			break;

		case remove:
			removeText();
			break;

		case show:	
			showText();
			break;

		case rename: 
			RenameFile();
			break;

		case move:
			MoveFile();
			break;

		case create:
			createFile();
			break;

		case del:
			deleteFile();
			break;
			
		case copy:
			copyFile();
			break;

		case unknown:
			printf("unknown command, please re-enter or type 'help' for options\n");
			break;

		case exit:
			printf("exiting Program");
			cont = false;
			break;
		}

	}
	return 1;
}

//Steven Functions

void appendText()
{
	string fileLocation;
	string inputText;
	FILE *textFile;

	cout << "Enter the file location or /h for help\n"; //prompt user for file location
	cin >> fileLocation;
	
	if (strncmp(fileLocation.c_str(), "/h",2) == 0) //if /h was entered print help and continue
	{
		cout << "The append function adds text to the end of existing text file, file location refers to the full path of the file for which the text will be added. The enter text prompt will allow a user to enter a series of new lines to the text document, pressing enter without any text on the line will terminate the entry\n";
		getline(std::cin, inputText);
		appendText();
	}
	else {
		getline(std::cin, inputText); //if file path was entered ask for text to append
		cout << "Enter text to append \n";

		while (true) { //loop to read multiple lines of text
			getline(std::cin, inputText); 
			textFile = fopen(fileLocation.c_str(), "a");
			fprintf(textFile, inputText.c_str()); //added text to end of file
			fprintf(textFile, "\n");
			fclose(textFile);
			if (inputText.empty()) {
				break;
			}
		}
		cout << "Text Appened to file";
		
	}
}

void insertText()
{
	string fileLocation; 
	string inputText;
	int position;
	cout << "Enter file location or /h for help\n"; //prompt user for file path
	cin >> fileLocation;
	if (strcmp(fileLocation.c_str(), "/h") == 0)
	{
		cout << "The insert function adds text to a specified portion of an existing text file. File location refers to the full path of the file for which the text will be inserted. The enter text prompt will allow a user to enter a new line to the text document. The character postion prompt requires the character number where the insertion will occur (note this insertion does not create a new line)\n";
		getline(std::cin, inputText);
		insertText();
	}

	else {
		getline(std::cin, inputText);  //prompt user for for text to insert
		cout << "Enter text to add\n";
		getline(std::cin, inputText);

		cout << "Enter character postion\n";  //prompt user for location to add text
		cin >> position;
		cin.ignore(10000, '\n');

		std::ifstream inFile(fileLocation);
		std::string contents((std::istreambuf_iterator<char>(inFile)),
			std::istreambuf_iterator<char>());
		if (contents.empty() || position > contents.length())  //check if location is valid
		{
			cout << "position in text file does not exits";
		}
		else {
			string tempSt = contents.substr(0, position); //if valid location, make temp string to store text before location and one to store text after location
			string tempEn = contents.substr(position + 1);

			inFile.close();
			tempSt = tempSt + inputText + tempEn; //append the first half of text with with inserted text and the second half of the text

			ofstream outFile;  //write new contents to the text file
			outFile.open(fileLocation);
			outFile << tempSt << endl;
			outFile.close();
		}
	}
}


void removeText()
{
	string fileLocation;  
	cout << "Enter file location or /h for help\n";  //prompt for file location
	cin >> fileLocation;
	if (strcmp(fileLocation.c_str(), "/h") == 0)
	{
		cout << "The remove function removes all text from a provided text document. File location referes to the full path of the file for which the text will be removed\n";
		getline(std::cin, fileLocation);
		removeText();
	}
	else {
		string nl;
		FILE *textFile;
		textFile = fopen(fileLocation.c_str(), "w"); //open file with 'w' parameter, this will erase all contents in the file
		fclose(textFile);
		getline(std::cin, nl);
	}
}


void showText()
{
	string fileLocation;
	int pageSize; //number of lines per page
	char pause; //variable to capture pauses
	cout << "Enter file location or /h for help\n";
	cin >> fileLocation;
	if (strcmp(fileLocation.c_str(), "/h") == 0)
	{
		cout << "The show function shows all text from a provided text document, the text will be broken up into pages, with a specified line number. File location referes to the full path of the file for which the text will be shown. Page line number refers to the amount of lines that will be shown on each page. The pause prompt will pause on each page if enabled by entering a 'y' or 'Y' when prompted. If enabled each page will pause awaiting user input before the next page is displayed. In this mode, the display can be exited early by entering an 'x' or 'X' character at the concludion of a page\n";
		getline(std::cin, fileLocation);
		showText();
	}

	else {

		cout << "Enter Page Line Numbers\n"; //prompt for page numbers
		cin >> pageSize;

		cout << "Pause on each page? (Y/N)"; //prompt for pause condition
		cin >> pause;
		cin.ignore(256, '\n');
		std::ifstream inFile(fileLocation);
		std::string contents((std::istreambuf_iterator<char>(inFile)),
			std::istreambuf_iterator<char>());

		cout << "Text file contents, press enter to continue to next page, enter x to exit early \n\n\n";
		int lCount = 1; //line counter
		int pCount = 1; //page counter
		int i = 0; //global cusor for file 
		bool fileEnd = false; 
		string cont = "\0";
		int endChar = contents.length();

		while (!fileEnd && cont != "x" && cont != "X") //loop through all characters in the file
		{
			cout << "-----------Page " << pCount << " Start---------------\n";  //Page start seperator
			lCount = 1;
			while (lCount <= pageSize && !fileEnd) //internal loop to capture each new page
			{

				while (contents[i] != '\n') //second internal loop to represent each line
				{
					cout << contents[i];
					i++;
					if (i >= endChar)
					{
						fileEnd = true;
						break;
					}
				}
				i++;
				cout << "\n";
				lCount++;
				if (i >= endChar) //if the chracter = '\0' (null character) file end has been reached exit all loops
				{
					fileEnd = true;
					break;
				}

			}
			cout << "-----------Page " << pCount << "End----------------\n";
			if (pause == 'y' || pause == 'Y') //if pause is enabled, prompt user for continue after each page
			{
				cout << "ENTER to continue x to exit\n";
				getline(std::cin, cont);
			}
			pCount++;
		}
		cout << "------------File-End------------------\n";
		inFile.close();
	}
}

//Lucas section

void RenameFile(void)// the function that is called to rename the file 
{
	string OldPath, NewName, NewPath;//specifying the path and the new name 
	cout << "Please Enter the path of the file you would like to rename or /h for help \nEntry: ";//ask for the path of the file 

	getline(cin, OldPath);


	//cout << "\n" << OldPath << "\n";
	if (strcmp(OldPath.c_str(), "/h") == 0)// if the user asks for help print what it does and call the function to start over 
	{
		cout << "This is the Rename File Function it will allow you to rename a file existing on your computer\nTo change the name of a file you must fist specify the path of the file and what you would like the new name to be\n\n";
		RenameFile();// start over 
	}
	else {
		string OrgPath = OldPath;
		size_t split = OldPath.find_last_of("\\");//splits from the last / to find file name and path 
		string path = OldPath.substr(0, split);
		string OldName = OldPath.substr(split + 1);
		//cout << "Path: " << path<<"\nName: "<<OldName<<"\n";//print just for testing does not work with blank spaces 
		cout << "\nWhat Would you Like to rename the file?\nPlease Include File type for example test.txt";
		cout << "\nNew File Name: ";// get the new name of the file 


		getline(cin, NewName);



		NewName = path + "\\" + NewName;// add the path to the new name with the additional slash

		if (rename(OldPath.c_str(), NewName.c_str()) == 0)
		{
			cout << "\nFile Renamed Sucessfully\n";
			//maybe call main function to start over 
		}
		else// sometimes spaces do not work in that case have them enter a whole new path as intended 
		{
			cout << "\nError Unable to Change Name Please Try Again\n";
			RenameFile();

		}


	}
}



void MoveFile(void)
{
	FILE* source, *end;// specify the files 
	string StartDir, EndDir;// specify the directories 
	char move;
	cout << "What is the Directory including the file name and type of the file you want to move? or /h for help\nFile to be moved: ";
	getline(cin, StartDir);// get the directory
	if (strcmp(StartDir.c_str(), "/h") == 0)
	{
		cout << "\nThis is the move file function it will take the directory specified by you and move the file to the other directory you specify\nThe Inputs should be a start and end directory and an error message if something goes wrong\n";
		MoveFile();
	}
	else {
		fopen_s(&source, StartDir.c_str(), "r");
		if (source == NULL)// if the source file does not exist 
		{
			cout << "\nThe File " << StartDir << " you have specified does not exist\n";// print error message
			MoveFile(); //start the program over 
		}
		else {
			cout << "What is the directory that you would like the file to be moved to with the included file name and extension?\nAt this point you can also change the file name by specifying a new name in the directory\nLocation to be moved: ";
			getline(cin, EndDir);
			fopen_s(&end, EndDir.c_str(), "w");// open the end file for writing 

			// If needed I can seperate the directory from the file name again so it does not need to be included in the new type but that may make it more confusing

			while ((move = fgetc(source)) != EOF) // while the file is not empty 
			{
				fputc(move, end);//copy the contents 
			}
			fclose(source);//close the files 
			fclose(end);
			remove(StartDir.c_str());//delete the file it came from 
			// something about going back to the main function 
		}
	}
}


//Fie section

void createFile()
{
	string filename;    //filename store the name of the file that user wants to create

	cout << "enter a file path and name or '/h' for help: ";
	cin >> filename;

	if (strcmp(filename.c_str(), "/h") == 0)    //checking if user enter /h
	{
		cout << "create will create a new file. It will prompt for the name of the file you want to create together with its full path." << endl;
		createFile();

	}
	else {
		FILE *fp;
		fp = fopen(filename.c_str(), "w");  //creating the file
		fclose(fp); //close file
		getline(std::cin, filename);
	}
}

void deleteFile()
{
	string filename;    //filename store the name of the file that user wants to delete

	cout << "enter a file path and name or '/h' for help: ";
	cin >> filename;

	if (strcmp(filename.c_str(), "/h") == 0)    //checking if user enter /h
	{
		cout << "delete will delete an existing file. It will prompt for the name of the file you want to delete together with its full path." << endl;
		deleteFile();
	}

	else {

		int ret = remove(filename.c_str());     //deleting the file

		if (ret == 0)
			cout << "File deleted successfully." << endl;
		else
			cout << "Error: unable to delete the file" << endl;
		getline(std::cin, filename);
	}
}

void copyFile()
{
	string source_file, target_file;    //source_file store the name of the file to copy from and target_file store the name of file to copy to

	cout << "enter the name of the source file with its file path or '/h' for help: ";
	cin >> source_file;

	if (strcmp(source_file.c_str(), "/h") == 0)     //checking if user enter /h
	{
		cout << "copy will copy from one file to another. It will prompt for the name together with its full path of the file you are copying from and the name together with its full path of the file you are copying to." << endl;
		copyFile();
	}
	else {
		cout << "enter the name of the target file: ";
		cin >> target_file;

		char ch;
		FILE *source, *target;

		source = fopen(source_file.c_str(), "r");   //opening the source file

		if (source == NULL) //if fail to open source file
		{
			cout << "Press any key to exit..." << endl;
			exit(EXIT_FAILURE);
		}

		target = fopen(target_file.c_str(), "w");      //opening the target file or create a new one if none

		if (target == NULL)     //if fail to open target file
		{
			fclose(source);
			cout << "Press any key to exit..." << endl;
			exit(EXIT_FAILURE);
		}

		while ((ch = fgetc(source)) != EOF)     //copying from source file to target file
			fputc(ch, target);

		cout << "File copied successfully." << endl;

		fclose(source); //close source file
		fclose(target); //close target file
		getline(std::cin, source_file);
	}
}
