#include <iostream>
#include <fstream>
#include <string>
#include <variant>
#include <vector>
#include <algorithm>
#include <limits>
#include <compare>



// Struct representing a list of lists or ints
struct List: std::variant<std::vector<List>, int> {
	// Keep track of the list we are a part of (useful when parsing)
	List* parent = nullptr;
	// Variant constructor
	using std::variant<std::vector<List>, int>::variant;

	// Helper to extract the list
	std::vector<List>& list() { return std::get<std::vector<List>>(*this); }
	// Helper to extract the int
	int& Int() { return std::get<int>(*this); }

	// Print the list
	friend std::ostream& operator<<(std::ostream& s, List& l){
		// If we are a list
		if(l.index() == 0){
			// Get the list
			auto& v = l.list();
			// Print each element of the list
			s << '[';
			for(auto& elem: v)
				s << elem << ',';
			s << ']';
		// If we are an int... just print it
		} else s << l.Int();
		return s;
	}

	// Function which compares two lists together
	// NOTE: Overloading operator<=> seams to blow up std::variant...
	std::weak_ordering compare(List& other){
		// If both lists are singular ints... compare using the spaceship operator
		if(index() == 1 && other.index() == 1)
			return Int() <=> other.Int();

		// If only the left element is an int, convert it to a list
		std::vector<List> tL;
		if(index() == 1)
			tL.push_back(Int());
		else tL = list(); // Or extract its as list

		// If only the right element is an int, convert it to a list
		std::vector<List> oL;
		if(other.index() == 1)
			oL.push_back(other.Int());
		else oL = other.list(); // Or extract it as a list

		// Find the minimal size of the two lists
		int minSize = std::min(
			tL.size(),
			oL.size()
		);

		// Compare all of the elements within the same-sized portion
		for(int i = 0; i < minSize; i++)
			if(auto res = tL[i].compare(oL[i]); res != std::weak_ordering::equivalent)
				return res;

		// If the left list is shorter then it is less
		if(tL.size() < oL.size())
			return std::weak_ordering::less;
		// If the right list is shorter then the left is greater
		if(tL.size() > oL.size())
			return std::weak_ordering::greater;

		// If none of these conditions are met... the lists are equivalent
		return std::weak_ordering::equivalent;
	}
};



// Function which ignores a comma in the input stream
void ignoreComma(std::ifstream& fin){
	// Read a character
	char comma;
	fin >> comma;
	// If the character isn't a comma, put it back in the stream!
	if(comma != ',')
		fin.seekg(-1, std::ios::cur);
}

// Function which parses the next element of the list
void parseNext(std::ifstream& fin, List& list){
	// Extract the list from the input list
	auto& l = list.list();

	// Read in the first character
	char bracket;
	fin >> bracket;

	// If the first character is an open bracket...
	if(bracket == '[') {
		// Create a new list
		List _new = std::vector<List>{};
		_new.parent = &list;
		// Add it to the end of the current list
		l.emplace_back(_new);
		// Begin parsing within that list
		parseNext(fin, l.back());

	// If the first character is a close bracket...
	} else if(bracket == ']'){
		// If we aren't at the outmost list...
		if(list.parent) {
			// Ignore a comma after the ']' (if present)
			ignoreComma(fin);
			// Continue parsing the list one level up
			parseNext(fin, *list.parent);
		}
	// If it is not a control character is a number
	} else {
		// Put the first digit of the number back in the stream
		fin.seekg(-1, std::ios::cur);
		// Parse the number and add it to the list
		int value;
		fin >> value;
		l.push_back(value);

		// Ignore a comma after the number (if one is present)
		ignoreComma(fin);
		// Continue parsing the list
		parseNext(fin, list);
	}
}




int main() {
	// Connection to the input file
	std::ifstream fin("..Day13/day13_test.txt", std::ios::binary);
	// List of lists that we parse
	std::vector<List> lists;

	// While there is data in the file
	while(fin) {
		// Create a new list
		List list = std::vector<List>{};

		// Read in a bracket
		char bracket;
		fin >> bracket;
		if(!fin) break; // Break if out of data
		// If it is a bracket... parse the next element of the list
		if(bracket == '[')
			parseNext(fin, list);

		// Add the new list to the list of lists
		lists.emplace_back(list);
	}


	// // Part 1
	// // Merge the list of lists into a list of pairs of lists
	// std::vector<std::pair<List, List>> pairs;
	// for(int i = 0; i < lists.size(); i += 2)
	// 	pairs.emplace_back(lists[i], lists[i + 1]);

	// // Add the index of every pair listed in the correct order to a sum
	// int sum = 0;
	// for(int i = 0; i < pairs.size(); i++)
	//     if(pairs[i].first.compare(pairs[i].second)
	//       == std::weak_ordering::less)
	//         sum += i + 1; // Adding one since asking for 1 based index instead of 0 based

	// // Print the sum
	// std::cout << "Matching indices sum: "
	//     << sum << std::endl;


	// Part 2
	// Add extra dividers to the list of lists
	List divider1 = std::vector<List>{std::vector<List>{2}};
	lists.push_back(divider1);
	List divider2 = std::vector<List>{std::vector<List>{6}};
	lists.push_back(divider2);

	// Sort the list of lists
	std::sort(lists.begin(), lists.end(),
		[](List a, List b) {
			return a.compare(b) == std::weak_ordering::less;
	});

	// Find the indices of the two divider lists and multiply them together
	int decoderKey = 1;
	for(int i = 0; i < lists.size(); i++){
		auto& list = lists[i];
		if(list.compare(divider1) == std::weak_ordering::equivalent
		  || list.compare(divider2) == std::weak_ordering::equivalent)
			decoderKey *= (i + 1); // Adding one since asking for 1 based index instead of 0 based
	}

	// Print out the decoder key
	std::cout << "Decoder key: " << decoderKey
		<< std::endl;
}