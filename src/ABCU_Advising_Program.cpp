//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Christopher Mooers
// Version     : 1.0
// Course      : CS-300: Data Structures and Algorithms
// Description : ABCU Advising Program
//               Command-line program to load, sort, and display course
//               information for academic advising use.
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>

using namespace std;

// Structure to represent a course with its number, title, and prerequisites
struct Course {
	string number;							// Course code
	string title;							// Course name
	vector<std::string> prereqs;			// List of prerequisite course numbers
};

// Trim leading and trailing whitespace from a string
static inline string trim(string s) {
	auto is_space = [](unsigned char c) { return std::isspace(c); };
	while (!s.empty() && is_space(s.front())) s.erase(s.begin());
	while (!s.empty() && is_space(s.back())) s.pop_back();
	return s;
}

// Split a string into tokens using a delimiter (e.g., comma)
static vector<string> split(const string& line, char delim) {
	vector<string> out;
	string cur;
	stringstream ss(line);
	while (getline(ss, cur, delim)) {
		cur = trim(cur);
		if (!cur.empty()) out.push_back(cur);
	}
	return out;
}

// Loads courses from a CSV file into a hash table (unordered_map) and stores
// the course numbers in a vector for sorting and printing later.
static bool loadCourses(const string& filename, unordered_map<string, Course>& table, vector<string>& order) {
	table.clear();
	order.clear();

	ifstream in(filename);
	if (!in.is_open()) {
		cerr << "Error: could not open file '" << filename << "'.\n";
		return false;
	}

	string line;
	while (getline(in, line)) {
		if (trim(line).empty()) continue;

		// Split line by commas
		auto fields = split(line, ',');
		if (fields.size() < 2) continue;	// Skip invalid rows

		Course c;
		c.number = trim(fields[0]);
		c.title = trim(fields[1]);

		// Add any remaining comma-separated values as prerequisties
		for (size_t i = 2; i < fields.size(); ++i)
			c.prereqs.push_back(fields[i]);

		// Add course to hash table and record order
		table[c.number] = c;
		order.push_back(c.number);
	}

	in.close();
	return true;
}


// Comparison function for sorting course numbers alphanumerically
static bool alnumless(const string& a, const string& b) {
	return a < b;
}

// Display all courses in alphanumeric order
static void printCourseList(const unordered_map<string, Course>& table, vector<string> order) {
	if (table.empty()) {
		cout << "No data loaded. Choose option 1 first.\n\n";
		return;
	}

	// Sort course numbers
	sort(order.begin(), order.end(), alnumless);

	cout << "Here is a sample schedule:\n\n";
	for (const auto& num : order) {
		const auto& c = table.at(num);
		cout << c.number << "," << c.title << '\n';
	}

	cout << '\n';
}

// Display information about a specific course
static void printCourseInfo(const unordered_map<string, Course>& table) {
	if (table.empty()) {
		cout << "No data loaded. Choose option 1 first.\n\n";
		return;
	}

	cout << "What course do you want to know about?";
	string input;
	getline(cin, input);

	// Convert user input to uppercase for consistent matching
	transform(input.begin(), input.end(), input.begin(), ::toupper);

	// Find the course in the hash table
	auto it = table.find(input);
	if (it == table.end()) {
		cout << "Course not found.\n\n";
		return;
	}

	// Print course details
	const Course& c = it->second;
	cout << c.number << "," << c.title << '\n';
	cout << "Prerequisites: ";

	// Display reprequisites or "None"
	if (c.prereqs.empty()) cout << "None\n\n";
	else {
		for (size_t i = 0; i < c.prereqs.size(); ++i) {
			cout << c.prereqs[i];
			if (i + 1 < c.prereqs.size()) cout << ",";
		}

		cout << "\n\n";
	}
}

// Main Program

int main() {
	unordered_map<string, Course> table;	// Hash table for fast lookup
	vector<string> order;					// List of course numbers for sorting
	string choice;

	cout << "Welcome to the course planner.\n\n";

	bool running = true;
	while (running) {
		// Display main menu
		cout << "  1. Load Data Structure.\n";
		cout << "  2. Print Course List.\n";
		cout << "  3. Print Course.\n";
		cout << "  9. Exit\n\n";
		cout << "What would you like to do? ";
		getline(cin, choice);
		cout << '\n';

		// Menu options
		if (choice == "1") {
			cout << "Enter the file name to load: ";
			string fname;
			getline(cin, fname);

			// Attempt to load the data file
			if (loadCourses(trim(fname), table, order)) {
				cout << "Courses loaded successfully.\n\n";
			}
			else {
				cout << "Load failed. Please check the file name.\n\n";
			}
		}
		else if (choice == "2") {
			printCourseList(table, order);
		}
		else if (choice == "3") {
			printCourseInfo(table);
		}
		else if (choice == "9") {
			running = false;
		}
		else {
			// Handle invalid menu selection
			cout << choice << " is not a valid option.\n\n";
		}
	}

	cout << "Thank you for using the course planner!\n";
	return 0;
}
