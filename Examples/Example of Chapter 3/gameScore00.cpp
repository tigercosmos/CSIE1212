#include <iostream>
#include <vector>
using namespace std;

// Exceptions
class RuntimeException {
	private:
		string errorMsg;
	public:
		RuntimeException(const string& err) { errorMsg = err; }
		string getMessage() const { return errorMsg; }
};

class IndexOutOfBounds: public RuntimeException {
	public:
		IndexOutOfBounds(const string& err = "Index out of bounds!"): RuntimeException(err) {}
};

// Class of game entry
class GameEntry {		// Stores the game scores
	public:
		GameEntry(const string& n="", int s=0);	// Constructor
		string getName() const;			// Get player name
		int getScore() const;			// Get player score
	private:
		string name;		// Player's name
		int score;			// Player's score
};
GameEntry::GameEntry(const string& n, int s): name(n), score(s) {}
string GameEntry::getName() const { return name; }
int GameEntry::getScore() const { return score; }

// Class of scores
class Scores {
	public:
		Scores(int maxEnt=10);	// Constructor
		~Scores(){};			// Destructor
		void add (const GameEntry& e); // add an entry
		GameEntry remove(int i)	throw (IndexOutOfBounds);	// Remove a single entry
		void print();	// For printing the scores
	private:
		int maxEntries;		// maximum number of entries
		int numEntries;		// actual number of entries
		vector<GameEntry> entries;		// array of game entries
};

Scores::Scores(int maxEnt) {	// Constructor
	maxEntries = maxEnt;
	entries = vector<GameEntry>(maxEnt);
	numEntries = 0;
}

void Scores::print() {
	cout << "numEntries=" << numEntries << ", maxEntries=" << maxEntries << endl;
	for (int i=0; i<numEntries; i++)
		cout << i << ": name=" << entries[i].getName().c_str() << ", score=" << entries[i].getScore() << endl;
	cout << endl;
}

void Scores::add(const GameEntry& e) {	// Add a game entry
	int newScore = e.getScore();		// Score to add
	if (numEntries == maxEntries){		// The array is full
		if (newScore <= entries[maxEntries-1].getScore())
			return;			// not high enough
	} else
		numEntries++;

	int i = numEntries - 2;	// Start with the next to last
	while (i>=0 && newScore>entries[i].getScore()) {
		entries[i+1] = entries[i];
		i--;
	}
	entries[i+1] = e;
}

GameEntry Scores::remove(int i) throw(IndexOutOfBounds) { // Remove
	try{	  // Exception for out of bounds
		if ( (i < 0) || (i >= numEntries) )
			throw IndexOutOfBounds("Invalid index");
	} catch (IndexOutOfBounds& iob) {
		cout << iob.getMessage().c_str() << endl;
		return GameEntry();
	}
	GameEntry e = entries[i];		// Save the removed object
	for (int j = i+1; j < numEntries; j++)
		entries[j-1] = entries[j];	// Shift entries left
	numEntries--;			// one fewer entry
	return e;			// return the removed object
}

int main() {
	Scores s(5);
	s.add(GameEntry("John", 9));
	s.add(GameEntry("Tim", 55));
	s.add(GameEntry("Alice", 19));
	s.add(GameEntry("Bob", 15));
	s.add(GameEntry("Sam", 1));
	s.add(GameEntry("Roger", 25));
	s.add(GameEntry("Annie", 85));
	s.print();

	s.remove(0);
	s.remove(3);
	s.print();

	s.remove(5);
	s.print();
	
	s.remove(0);
	s.remove(0);
	s.remove(0);
	s.remove(0);
	s.print();
}