#include "vote.h"
#include "election.h"
#include <fstream>

using namespace std;

int main() {
	ifstream in("votes.txt");
	election election = read_votes(in);
	int roundNumber = 1;
	candidate lastEliminated = 0;

	while (true) {
		cout << "Round " << roundNumber << ": " << election.vote_count() << " votes\n";
		cout << "First preferences:\n";
		vector<pair<candidate, int>> ranking = election.ranked_candidates();
		// stops a bug where sometimes on larger elections a candidate would be left with one vote after being eliminated
		if (ranking[ranking.size() - 1].first == lastEliminated) {
			election.eliminate(ranking[ranking.size() - 1].first);
			ranking = election.ranked_candidates();
		}
		// prints candidates in rank order along with number of votes received
		for (auto& i : ranking) {
			cout << "  Candidate " << i.first << ": " << i.second << "\n";
		}
		// checks to see if a candidate has received a majority vote and breaks from the loop if they have
		if (ranking[0].second >= election.vote_count() / 2.0f) {
			cout << "Candidate " << ranking[0].first << " is selected";
			break;
		}
		// eliminates the lowest ranking candidate
		cout << "Candidate " << ranking[ranking.size() - 1].first << " is eliminated.\n\n";
		lastEliminated = ranking[ranking.size() - 1].first;
		election.eliminate(ranking[ranking.size() - 1].first);
		roundNumber++;
	}
	return 0;
}
