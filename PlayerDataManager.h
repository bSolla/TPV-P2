#pragma once
#include <vector>
#include <fstream>

using namespace std;

struct Time {
	unsigned int seconds;
	unsigned int minutes;

	bool operator=(const Time &other) {
		return (other.seconds == seconds) && (other.minutes == minutes);
	}

	bool operator<(const Time &other) {
		if (minutes = other.minutes) {
			return seconds < other.seconds;
		}
		else
			return minutes < other.minutes;
	}

	bool operator>(const Time &other) {
		return !(*this < other);
	}
};

const string TOP_10_FILENAME = "data\\top10.txt";


class PlayerDataManager {
// --------------------- variables------------------------------------------------------
	vector<Time> top10;

// ---------------------- methods ------------------------------------------------------
public:
	PlayerDataManager ();
	~PlayerDataManager ();

	// reads the top10 file and fills the top10 list
	void loadTop10 ();
	// checks if the given time enters in the top 10 and if so, inserts it
	void checkTime (unsigned int seconds, unsigned int minutes);
	// updates the top10 file if a new time makes it into the top10
	void writeTop10 ();
};

