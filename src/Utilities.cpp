#include "Utilities.h"
#include "Exceptions.h"


void ValidInputInt(int &answer, int min, int max, string msg){
	while(true) { ///sai do ciclo quando o input é aceite; passa o input válido por referência a partir de "answer"
			try {
				cout << endl << msg << ": ";
				cin >> answer;
				cin.ignore();

				if (cin.fail()) {
					cin.clear();
					cin.ignore(10000, '\n');

					throw(InvalidInput(answer, min, max));
				} else if (min <= answer && answer <= max)
					return;
				else
					throw(InvalidInput(answer, min, max));
			} catch (InvalidInput &e) {
				e.what();
			}
		}
}

Date ValidDate(string msg){
	while(true){
		try{
			string date;
			cout << endl << msg << ": ";
			getline(cin, date);
			if(date[2] != ' ' || date[4] != ' ' || date[7] != ' ' || date[9] != ' '){
			throw(InvalidInputDate()); /// se não escreveu na forma 01 / 01 / 1999
	}
	stringstream ss;
	ss.str(date);
	unsigned int day, month, year;
	string trash; /// vai apanhar a barra '/'
	ss >> day >> trash >> month >> trash >> year;
	Date d(day, month, year);
	return d;
	}catch(InvalidInputDate &e){
		e.what();
	}
	catch(...){ ///apanha qualquer uma das exceções do construtor Date
		cout << "Values out of range." << endl;
	}
	}
}

