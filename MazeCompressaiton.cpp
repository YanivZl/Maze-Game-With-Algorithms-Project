#include "MazeCompressation.h"


void MazeCompressaiton::Compress()
{
	int answer = IsMazeExistNew(maze_Name, file_Name);
	if (answer == 1)
	{
		cout << BOLDRED << "The Maze " << BOLDCYAN << maze_Name << BOLDRED << " already exist" << BOLDWHITE << endl;
		UpdateCompressedArray();
		return;
	}
	std::size_t found = file_Name.find(".txt");
	if (found)
		myfile_write.open(file_Name, std::ios_base::app);
	else
	{
		string fname = file_Name + ".txt";
		myfile_write.open(fname, std::ios_base::app);
	}
	int counter = 1;
	int index = 0;
	myfile_write << maze_Name << endl;
	int size = maze.getHeight() * maze.getWidth() - 2;
	for (int i = 0; i < size; i++)
	{
		compressionarray.push_back(BigArray[i]);
		myfile_write << BigArray[i];
		while (BigArray[i] == BigArray[i + 1] && i < size)
		{
			counter++;
			i++;
		}
		myfile_write << " " << counter << endl;
		compressionarray.push_back(counter);
		counter = 1;
	}
	compressionarray.push_back(BigArray[size]);
	compressionarray.push_back(counter);
	myfile_write << BigArray[size] << " " << counter << endl;
	myfile_write << "End" << endl;

	cout << BOLDGREEN << "compression of " << BOLDCYAN << maze_Name << BOLDGREEN << " - Succeeded" << BOLDWHITE << endl;
	cout << endl << endl;
	BigArray.clear();
	myfile_write.close();
}
void MazeCompressaiton::Expansion()
{
	std::size_t found = file_Name.find(".txt");
	if (found)
		myfile_read.open(file_Name);
	else
	{
		string fname = file_Name + ".txt";
		myfile_read.open(fname);
	}
	string line;
	int one, two, countIteration = 1;
	int answer = 1;

	while (myfile_read && answer)
	{
		getline(myfile_read, line);
		if (line == maze_Name)
			answer = 0;
	}
	answer = 1;
	while (myfile_read && answer)
	{
		getline(myfile_read, line);
		if (line == "End")
		{
			answer = 0;
		}
		else if (int(line.length()) == 3)
		{
			one = int(line[0]) - 48;
			two = int(line[2]) - 48;
		}
		else if (int(line.length()) == 4 && line[0] == '-')
		{
			one = (int(line[1]) - 48) * -1;
			two = int(line[3]) - 48;
		}
		else if (int(line.length()) == 4 && line[0] != '-')
		{
			one = int(line[0]) - 48;
			two = ((int(line[2]) - 48) * 10) + (int(line[3]) - 48);
		}
		else if (int(line.length()) == 5 && line[0] != '-')
		{
			one = int(line[0]) - 48;
			two = ((int(line[2]) - 48) * 100) + ((int(line[3]) - 48) * 10) + (int(line[4]) - 48);
		}
		else
		{
			break;
		}

		while (countIteration <= two)
		{
			expansionarray.push_back(one);
			countIteration++;
		}
		countIteration = 1;
	}

	int counterArray = 0;
	for (int i = 0; i < maze.getHeight(); i++)
		for (int j = 0; j < maze.getWidth(); j++, counterArray++)
			expansionMaze[i][j] = expansionarray[counterArray];

	cout << endl << endl;
	cout << BOLDYELLOW << "Expansion Array 2D" << BOLDWHITE << endl;
	for (int i = 0; i < maze.getHeight(); i++)
	{
		for (int j = 0; j < maze.getWidth(); j++, counterArray++)
		{
			cout << expansionMaze[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << BOLDGREEN << "Expansion of " << BOLDCYAN << maze_Name << BOLDGREEN << " - Succeeded" << BOLDWHITE << endl;
	myfile_read.close();
}
int MazeCompressaiton::getCompressedSize()
{
	UpdateCompressedArray();
	cout << BOLDYELLOW << "Compressed Size: " << BOLDCYAN << int(compressionarray.size()) * sizeof(char) << BOLDWHITE << endl;
	return int(compressionarray.size()) * sizeof(char);
}
int MazeCompressaiton::getExpansionSize()
{
	cout << BOLDYELLOW << "Expansion Size: " << BOLDCYAN << sizeof(charMaze[0][0]) * maze.getHeight() * maze.getWidth() << BOLDWHITE << endl;
	return sizeof(charMaze[0][0]) * maze.getHeight() * maze.getWidth();
}

int MazeCompressaiton::IsMazeExistNew(string name, string FileName)
{
	int answer = -1;
	std::size_t found = FileName.find(".txt");
	if (found)
		myfile_read.open(FileName);
	else
	{
		string fname = FileName + ".txt";
		myfile_read.open(fname);
	}

	string line;
	while (myfile_read)
	{
		getline(myfile_read, line);
		if (line == name)
		{
			myfile_read.close();
			return 1;
		}
	}
	myfile_read.close();
	return 0;
}
void MazeCompressaiton::UpdateCompressedArray()
{
	int counter = 1;
	int index = 0;
	int size = maze.getHeight() * maze.getWidth() - 2;
	for (int i = 0; i < size; i++)
	{
		compressionarray.push_back(BigArray[i]);
		while (BigArray[i] == BigArray[i + 1] && i < size)
		{
			counter++;
			i++;
		}
		compressionarray.push_back(counter);
		counter = 1;
	}
	compressionarray.push_back(BigArray[size]);
	compressionarray.push_back(counter);
}