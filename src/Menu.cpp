#include "Menu.h"

#include <iostream>
#include <fstream>

ExitHandler Menu::exitHandler;

MenuResult ExitHandler::handle()
{
	return EXIT;
}

MenuResult Menu::handle()
{

	while (true)
	{
		unsigned int option;
		printMenu();

		cout << endl << "Choose an option: ";
		cin >> option;

		if (!cin.good())
		{
			string s;
			cin.clear();
			getline(cin, s);
			invalidOption(s);
			continue;
		}

		if (option >= entries.size())
		{
			invalidOption(option);
			continue;
		}

		MenuHandler &handler = entries[option].second;
		MenuResult res = handler.handle();

		if (res == EXIT)
		{
			break;
		}
	}

	return CONTINUE;
}

void Menu::invalidOption(int opt)
{
	cout << endl << "ERROR: The option \"" << opt << "\" is invalid." << endl << endl;
}

void Menu::invalidOption(string opt)
{
	cout << endl << "ERROR: The option \"" << opt << "\" is invalid." << endl << endl;
}

Menu::Menu(string name) {
	this->name = name;
}

void Menu::printMenu() const
{
	cout << name << endl;
	for (size_t i = 1; i < entries.size(); i++)
	{
		cout << i << ". " << entries[i].first << endl;
	}
	cout << endl << 0 << ". " << entries[0].first << endl;
}

/*OneDateProcessor::OneDateProcessor(string prompt, string error) :
	prompt1(prompt), error(error)
{

}

Date OneDateProcessor::readDate(string prompt, string error)
{
	while (true)
	{
		Date tmp;
		cout << prompt;
		cin >> tmp;
		if (tmp.valid())
		{
			return tmp;
		}
		else
		{
			cout << error;
		}
	}
}

MenuResult OneDateProcessor::handle()
{
	Date date = readDate(prompt1, error);

	return handle(date);
}

TwoDateProcessor::TwoDateProcessor(string prompt1, string prompt2, string error) :
	OneDateProcessor(prompt1, error), prompt2(prompt2)
{

}

MenuResult TwoDateProcessor::handle(Date date1) {

	Date date2 = readDate(prompt2, error);

	return handle(date1, date2);
}*/

Date readDate(string prompt)
{
	while (true)
	{
		Date date;
		cout << prompt;
		cin >> date;
		cin.clear();
		cin.ignore(INT64_MAX, '\n');
		if (date.valid())
		{
			return date;
		}
		cout << "ERROR: Invalid date." << endl;
	}
}

string readFileName(const string & prompt)
{
	while (true)
	{
		cout << prompt;
		string fileName;
		getline(cin, fileName);
		fstream test(fileName);
		if (test.is_open())
		{
			return fileName;
		}
		cout << "ERROR: File doesn't exist." << endl;
	}

}
