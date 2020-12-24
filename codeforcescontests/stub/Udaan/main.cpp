#include <bits/stdc++.h>

using namespace std;

class flight {
public:
	// static int total_fl;
	string name;
	int flightNo;
	string source, dest;
	int stTime, endTime;		// format 1200 hours and so on
	vector<int> weekdayActive;	// (0,sunday),(1,monday), ... (6,saturday)
	int seatsleft;
	flight(string _name, int _flightNo, string _src, string _dest, int _stTime, int _endTime, vector<int> _act, int s) {
		name = _name;
		flightNo = _flightNo;
		source = _src;
		dest = _dest;
		stTime = _stTime;
		endTime = _endTime;
		weekdayActive = _act;
		seatsleft = s;
	}
	flight() {
	}
};

class Booking {
public:
	flight* fl;
	string date;
	int seats_reserved;
	Booking(flight* _fl, string _date, int sr) {
		fl = _fl;
		date = _date;
		seats_reserved = sr;
	}
};

class User {
public:
	int userId;
	vector<Booking> bookings;
	User(int u) {
		userId = u;
	}

	void viewBookings() {
		cout << "The user has booked flights as follows" << endl;
		for (auto& booking : bookings) {
			cout << booking.fl->flightNo << ' ' << booking.date << ' ' << booking.seats_reserved << endl;
		}
		cout << "Booking Listings Complete" << endl;
	}
};

int getDayofWeek(int d, int m, int y) {
	vector<int> t = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}
unordered_map<string, unordered_map<string, vector<flight*>>> flightsMap;
map<int, flight> vfl;

void findFlights(string src, string dest, int d, int m, int y) {
	int day = getDayofWeek(d, m, y);
	vector<flight*>& flights = flightsMap[src][dest];
	for (auto& fl : flights) {
		if (fl->weekdayActive[day])
			cout << fl->flightNo << ' ' << fl->name << ' ' << fl->stTime << ' ' << fl->endTime << endl;
	}
	cout << endl;
}

void reserve(int flno, int d, int m, int y, int ts, User& user) {
	if (vfl.count(flno) == 0) {
		cout << "Flight does not exist" << endl;
		return;
	}
	flight& fl = vfl[flno];
	int dw = getDayofWeek(d, m, y);
	if (fl.weekdayActive[dw] == 0) {
		cout << "Flight does not operate on this day" << endl;
		return;
	}
	if (fl.seatsleft < ts) {
		cout << "Insufficents seats left on flight" << endl;
		return;
	}
	fl.seatsleft -= ts;
	user.bookings.push_back(Booking(&fl, to_string(d) + '/' + to_string(m) + '/' + to_string(y), ts));
}

int main() {
	// map<pair<string, string>, flight> flightsMap;
	// insert a few flights for reference

	// vector<flight> vfl;
	vfl[1] = flight("flight1",
					1,
					"dest1",
					"dest2",
					1200,
					1430,
					{1, 1, 1, 1, 0, 1, 1},
					100);
	vfl[2] = flight("flight2",
					2,
					"dest1",
					"dest2",
					1300,
					1530,
					{1, 1, 1, 0, 0, 1, 0},
					100);

	for (auto& it : vfl) {
		flightsMap[it.second.source][it.second.dest].push_back(&it.second);
	}

	cout << "Please Enter your user Id (Int)";
	int userId;
	cin >> userId;

	User user(userId);

	while (1) {
		cout << "Choose and option : " << endl;
		cout << "OPTION 1)Search for flights based on source, destination and date" << endl;
		cout << "OPTION 2)Reserve n seats on a flight on particluar date" << endl;
		cout << "Option 3)View your Reservations" << endl;
		cout << "Option 4)Exit" << endl;

		int option;
		cin >> option;

		switch (option) {
		case 1: {
			string src, dest;
			int d, m, y;
			cout << "Enter source of flight" << endl;
			cin >> src;
			cout << "Enter destination of flight" << endl;
			cin >> dest;
			cout << "Enter date in the form of an array ie 24 March 2020 as \"24 3 2020\"" << endl;
			cin >> d >> m >> y;
			findFlights(src, dest, d, m, y);
			// flights
		} break;
		case 2: {
			int n, d, m, y, ns;

			cout << "Enter flightNo" << endl;
			cin >> n;
			cout << "Enter date in the form of an array ie 24 March 2020 as \"24 3 2020\"" << endl;
			cin >> d >> m >> y;
			cout << "Enter number of seats" << endl;
			cin >> ns;
			reserve(n, d, m, y, ns, user);

		} break;
		case 3:
			user.viewBookings();

			break;

		default:
			return 0;
		}
	}
}