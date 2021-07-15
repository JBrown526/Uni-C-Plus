#ifndef ELECTION_H
#define ELECTION_H

#include "vote.h"
#include <iostream>

class election {
	std::vector<vote> voteCollection;

public:
	election();

	void add_vote(const vote& v);

	int vote_count() const;

	void eliminate(candidate c);

	std::vector<std::pair<candidate, int>> ranked_candidates() const;

private:
	void remove_vote(vote v);

};

election read_votes(std::istream& in);

#endif
