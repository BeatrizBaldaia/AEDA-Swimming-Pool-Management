#include "Utilities.h"
#include "Exceptions.h"

void getInputInt(int &answer, int min, int max, string msg) {
	while (true) { ///sai do ciclo quando o input é aceite; passa o input válido por referência a partir de "answer"
		try {
			cout << endl << msg << ": ";
			int tmp;
			cin >> tmp;
			if (cin.eof()) {
				cin.clear();
				throw(InvalidInputInt(answer, min, max));
			}

			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');

				throw(InvalidInputInt(answer, min, max));
			} else if (min <= tmp && tmp <= max) {
				answer = tmp;
				cin.ignore(10000, '\n');
				return;
			} else {
				throw(InvalidInputInt(answer, min, max));
			}
		} catch (InvalidInputInt &e) {
			e.printError();
		}
	}
}

Date getInputDate(string msg) {
	while (true) {
		try {
			string date;
			cout << endl << msg << ": ";
			getline(cin, date);
			if (date[2] != '/' || date[5] != '/' || date.length() < 10) {
				throw(InvalidInputDate()); /// se não escreveu na forma DD/MM/YYY
			}
			stringstream ss(date);
			unsigned int day, month, year;
			ss >> day;
			ss.ignore();
			ss >> month;
			ss.ignore();
			ss >> year;
			if (ss.fail()) {
				throw(InvalidInputDate());
			}
			Date d(day, month, year);
			return d;
		} catch (InvalidInputDate &e) {
			e.printError();
		} catch (...) { ///apanha qualquer uma das exceções do construtor Date
			cout << endl << "Invalid date." << endl;
		}
	}
}

Time getInputTime(string msg) {
	while (true) {
		try {
			string time;
			cout << endl << msg << ": ";
			getline(cin, time);
			if (time[2] != ':' && time.length() != 5) {
				throw(InvalidInputTime()); /// se não escreveu na forma 08:30
			}
			stringstream ss(time);
			unsigned int hour, minute;
			ss >> hour;
			ss.ignore();
			ss >> minute;
			if (ss.fail()) {
				throw(InvalidInputTime());
			}
			Time t(hour, minute);
			return t;
		} catch (InvalidInputTime &e) {
			e.printError();
		} catch (...) { ///apanha qualquer uma das exceções do construtor Date
			cout << endl << "Invalid time." << endl;
		}
	}
}

DayOfWeek getInputDayOfWeek(string msg) {
	while (true) {
		try {
			string day;
			cout << endl << msg << ": ";
			getline(cin, day);
			for (auto & elem : day) {
				elem = tolower(elem);
			}
			if (day != "monday" && day != "tuesday" && day != "wednesday"
					&& day != "thursday" && day != "friday" && day != "saturday"
					&& day != "sunday") {
				throw(InvalidInputDayOfWeek()); /// se não escreveu um dia da semana válido
			}
			DayOfWeek d;
			if (day == "Monday") {
				d = MON;
			} else {
				if (day == "Tuesday") {
					d = TUE;
				} else {
					if (day == "Wednesday") {
						d = WED;
					} else {
						if (day == "Thursday") {
							d = THU;
						} else {
							if (day == "Friday") {
								d = FRI;
							} else {
								if (day == "Saturday") {
									d = SAT;
								} else {
									if (day == "Sunday") {
										d = SUN;
									}
								}
							}
						}
					}
				}
			}

			return d;
		} catch (InvalidInputDayOfWeek &e) {
			e.printError();
		}

	}
}
