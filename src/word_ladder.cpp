#include "word_ladder.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <unordered_map>

// Read the txt file, push every word into an unordered list then return that list
auto word_ladder::read_lexicon(const std::string &path) -> std::unordered_set<std::string> {
    std::unordered_set<std::string> lexicon;
    std::ifstream file(path);

	if (not file.is_open()) {
		std::cout << "Error opening file";
		return lexicon;
	}

	std::string word;
	while (file >> word) {
		lexicon.insert(word);
	};

	file.close();
	return lexicon;
}

void constructingPath(std::vector<std::vector<std::string>> &results, std::vector<std::string> &current_path, std::string current_word, 
std::unordered_map<std::string, std::vector<std::string>> &predecessors, const std::string &destination_word) {
	current_path.push_back(current_word);
	

	// Base case
	if (current_word == destination_word) {
		results.push_back(current_path);
	} else {
		for (size_t i = 0; i < predecessors[current_word].size(); ++i) {
			auto new_path = current_path;
			constructingPath(results, new_path, predecessors[current_word][i], predecessors, destination_word);
		}

	}
}

auto word_ladder::generate(
	const std::string &from,
	const std::string &to,
	const std::unordered_set<std::string> &lexicon
) -> std::vector<std::vector<std::string>> {
	// Initialize queue for BFS
	std::queue<std::string> queue;

	// Create a temporary vector (copy of from) then push a copy of word into paths
	queue.push({from});

	// Initialise visited map
	std::unordered_map<std::string, int> visited;
	visited[from] = 0;
	
	std::unordered_set<std::string> current_level_visited;
	
	// Initialise predecessor map
	std::unordered_map<std::string, std::vector<std::string>> predecessors;

	while (not queue.empty()) {
		std::string lastest_word = queue.front();
		queue.pop();
		for (size_t i = 0; i < lastest_word.length(); i++) {
			// a to z for every character of the last word
			for (char c = 'a'; c <= 'z'; ++c) {
				auto new_word = lastest_word;
				new_word[i] = c;

				if (new_word == to) {
					if (visited.find(new_word) == visited.end() or visited[lastest_word] + 1 < visited[new_word]) {
						visited[new_word] = visited[lastest_word] + 1;
						predecessors[new_word].push_back(lastest_word);

					} else if (visited[lastest_word] + 1 == visited[new_word]) {
						predecessors[new_word].push_back(lastest_word);
					}

				} else if (lexicon.find(new_word) != lexicon.end()) {
					if (visited.find(new_word) == visited.end() or visited[lastest_word] + 1 < visited[new_word]) {
						queue.push(new_word);
						visited[new_word] = visited[lastest_word] + 1;
						predecessors[new_word].push_back(lastest_word);
					} else if (visited[lastest_word] + 1 == visited[new_word]) {
						predecessors[new_word].push_back(lastest_word);
					}
				}
			}
		}
	}

	// Constructing paths
	// Store final result
	auto results = std::vector<std::vector<std::string>>{};
	auto result = std::vector<std::string>{};
	constructingPath(results, result, to, predecessors, from);
	for (auto & path : results) {
    	std::reverse(path.begin(), path.end());
	}
	auto sorted = results;
	std::sort(sorted.begin(), sorted.end());
	return sorted;
}