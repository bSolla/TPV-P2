#include "PlayerDataManager.h"



PlayerDataManager::PlayerDataManager () {
	loadTop10 ();
}


PlayerDataManager::~PlayerDataManager () {
}


void PlayerDataManager::loadTop10 () {
	ifstream file;
	unsigned int fileMinutes, fileSeconds;

	file.open (TOP_10_FILENAME);
	if (!file.is_open ()) {
		throw ("couldn't open " + TOP_10_FILENAME);
	}
	else {
		for (unsigned int i = 0; i < 10; ++i) {
			file >> fileMinutes;
			file >> fileSeconds;

			top10.push_back ({ fileSeconds, fileMinutes });
		}

		file.close ();
	}
}


void PlayerDataManager::checkTime (unsigned int seconds, unsigned int minutes) {
	bool found = false;
	Time possibleTime { seconds, minutes };
	vector<Time>::iterator it = top10.begin();
	vector<Time>::iterator vEnd = top10.end ();

	while (it != vEnd && !found) {
		if (possibleTime < *it) {
			found = true;
			top10.insert (it, possibleTime);

			top10.pop_back ();

			writeTop10 ();
		}
		it++;
	}
}


void PlayerDataManager::writeTop10 () {
	ofstream file;

	file.open (TOP_10_FILENAME);
	if (!file.is_open ()) {
		throw ("couldn't open " + TOP_10_FILENAME);
	}
	else {
		for (unsigned int i = 0; i < top10.size (); ++i) {
			file << top10[i].minutes << " " << top10[i].seconds << "\n";
		}

		file.close ();
	}
}


