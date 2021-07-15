#include "vote.h"

using namespace std;

vote::vote(const std::vector<candidate>& prefs) : preferences(prefs) {}

bool vote::spent() const {
	return preferences.size() == 0;
}

candidate vote::first_preference() const {
	return preferences[0];
}

void vote::discard(candidate c) {
	for (int i = 0; i < preferences.size(); i++) {
		if (preferences[i] == c) {
			preferences.erase(preferences.begin() + i);
			break;
		}
	}
}
