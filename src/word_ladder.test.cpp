#include "word_ladder.h"

#include <catch2/catch.hpp>
TEST_CASE("word_ladder::read_lexicon works as expected") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	const auto not_expected = std::unordered_set<std::string>{
		"balalala",
		"lol"
	};
	CHECK(english_lexicon != not_expected);
	const auto expected = std::unordered_set<std::string>{
		"zymotic",
		"zymurgies",
		"zymurgy",
		"zyzzyva",
		"zyzzyvas"
	};
	for (const auto &word : expected) {
		CHECK(english_lexicon.find(word) != english_lexicon.end());
	};
}

TEST_CASE("at -> it") {
	auto const lexicon = std::unordered_set<std::string>{
		"at",
		"it"
	};

	const auto expected = std::vector<std::vector<std::string>>{
		{"at", "it"}
	};

	auto const ladders = word_ladder::generate("at", "it", lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("already found cat -> cat") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");

	const auto expected = std::vector<std::vector<std::string>>{
		{"cat"}
	};

	auto const ladders = word_ladder::generate("cat", "cat", english_lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("multiple way") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");

	const auto expected = std::vector<std::vector<std::string>>{
		{"cat", "cap", "cop"},
		{"cat", "cot", "cop"},
	};

	auto const ladders = word_ladder::generate("cat", "cop", english_lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("longer multiple way") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	const auto expected = std::vector<std::vector<std::string>>{
		{"work", "fork", "form", "foam", "flam", "flay", "play"},
		{"work", "pork", "perk", "peak", "pean", "plan", "play"},
		{"work", "pork", "perk", "peak", "peat", "plat", "play"},
		{"work", "pork", "perk", "pert", "peat", "plat", "play"},
		{"work", "pork", "porn", "pirn", "pian", "plan", "play"},
		{"work", "pork", "port", "pert", "peat", "plat", "play"},
		{"work", "word", "wood", "pood", "plod", "ploy", "play"},
		{"work", "worm", "form", "foam", "flam", "flay", "play"},
		{"work", "worn", "porn", "pirn", "pian", "plan", "play"},
		{"work", "wort", "bort", "boat", "blat", "plat", "play"},
		{"work", "wort", "port", "pert", "peat", "plat", "play"},
		{"work", "wort", "wert", "pert", "peat", "plat", "play"}
	};
	auto const ladders = word_ladder::generate("work", "play", english_lexicon);
	CHECK(ladders == expected);
}

TEST_CASE("nonsense from word: kkk -> see") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");

	const auto expected = std::vector<std::vector<std::string>>{};

	auto const ladders = word_ladder::generate("kkk", "see", english_lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("nonsense to word: see -> kkk") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");

	const auto expected = std::vector<std::vector<std::string>>{};

	auto const ladders = word_ladder::generate("see", "kkk", english_lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("nonsense from and to word: vvv -> kkk") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");

	const auto expected = std::vector<std::vector<std::string>>{};

	auto const ladders = word_ladder::generate("vvv", "kkk", english_lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("from word shorter than to word leads to nowhere") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");

	auto const expected = std::vector<std::vector<std::string>>{};

	auto const ladders = word_ladder::generate("a", "abc", english_lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("from word longer than to word leads to nowhere") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");

	auto const expected = std::vector<std::vector<std::string>>{};

	auto const ladders = word_ladder::generate("abc", "a", english_lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("random, real words but no paths between words") {
	auto const english_lexicon1 = std::unordered_set<std::string>{"bye"};
	auto const english_lexicon2 = std::unordered_set<std::string>{};

	auto const expected1 = std::vector<std::vector<std::string>>{};

	auto const ladders1 = word_ladder::generate("hand", "tree", english_lexicon1);

	CHECK(ladders1 == expected1);

	auto const expected2 = std::vector<std::vector<std::string>>{};

	auto const ladders2 = word_ladder::generate("hand", "face", english_lexicon2);

	CHECK(ladders2 == expected2);
}