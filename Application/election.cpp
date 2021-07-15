#include "election.h"
#include <algorithm>
#include <sstream>

using namespace std;

vector<vote> voteCollection;

election::election() {}

void election::add_vote(const vote& v) {
	voteCollection.push_back(v);
}

int election::vote_count() const {
	return voteCollection.size();
}

void election::eliminate(candidate c) {
	for (auto& i : voteCollection) {
		i.discard(c);
		if (i.spent()) {
			remove_vote(i);
		}
	}
}

bool compareVoteCount(const pair<candidate, int>& p1, const pair<candidate, int>& p2) {
	return p1.second > p2.second;
}

bool voteAdded(const vote& vote, vector<pair<candidate, int>>& candidates) {
	for (auto& i : candidates) {
		if (i.first == vote.first_preference()) {
			i.second++;
			return true;
		}
	}
	return false;
}

vector<pair<candidate, int>> election::ranked_candidates() const {
	vector<pair<candidate, int>> candidates;
	// loops through all votes
	for (auto& i : voteCollection) {
		// checks to see if candidate has already been voted for
		if (!voteAdded(i, candidates)) {
			candidates.push_back(make_pair(i.first_preference(), 1));
		}
	}
	sort(candidates.begin(), candidates.end(), compareVoteCount);
	return candidates;
}

election read_votes(istream& in) {
	election elec = election();
	string line;
	// loops over text file extracting one line at a time as a string
	while (getline(in, line)) {
		vector<candidate> v;
		string cand;
		istringstream candidateStream(line);
		// loops over a line seperating votes into their preference ranking
		while (getline(candidateStream, cand, ' ')) {
			v.push_back(stoi(cand));
		}
		elec.add_vote(v);
	}
	return elec;
}

void election::remove_vote(vote v) {
	for (int i = 0; i < voteCollection.size(); i++) {
		if (voteCollection[i] == v) {
			voteCollection.erase(voteCollection.begin() + i);
		}
	}
}
