#ifndef VOTE_H
#define VOTE_H

#include <vector>

typedef unsigned int candidate;

class vote {
	std::vector<candidate> preferences;

public:
	vote(const std::vector<candidate>& prefs);

	bool operator==(const vote& lhs) {
		return this->preferences == lhs.preferences;
	}

	bool spent() const;

	candidate first_preference() const;

	void discard(candidate c);

};

#endif
