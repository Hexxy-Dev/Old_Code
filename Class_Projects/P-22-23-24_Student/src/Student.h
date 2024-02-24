#pragma once
#include <string>
#include <vector>
#include <random>
#include "Names.h"

struct Student {
	Student(const std::string& name, std::string surname, uint8_t age)
		: name(name), age(age), surname(surname)
	{}
	std::string name;
	std::string surname;
	uint8_t age;
	std::vector<Student*> friends;
};


bool IsFriend(const std::vector<Student*>& friends, const Student& s)
{
	for (size_t k = 0; k < friends.size(); k++)
		if (friends[k] == &s)
			return 1;
	return 0;
}

std::vector<Student> CreateStudentGraph()
{
	constexpr size_t PERSONS = 100;
	constexpr size_t MinimumNumberOfFriends = 2;

	std::vector<Student> studentGraph;
	studentGraph.reserve(PERSONS);

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<> uniform_AGE_distribution(17, 24);
	std::uniform_int_distribution<> uniform_NAME_distribution(0, 99);
	std::uniform_int_distribution<> uniform_GENDER_distribution(0, 1);
	std::uniform_int_distribution<> uniform_FRIENDS_distribution(0, PERSONS - 1);

	for (size_t i = 0; i < PERSONS; i++)
		studentGraph.emplace_back(Names[uniform_GENDER_distribution(generator)]
										[uniform_NAME_distribution(generator)],
									Names[2][uniform_NAME_distribution(generator)],
									uniform_AGE_distribution(generator));
	for (size_t i = 0; i < PERSONS; i++) {
		studentGraph.reserve(MinimumNumberOfFriends);
		for (int j = 0; j < MinimumNumberOfFriends; j++) {
			uint8_t newFriendIndex = uniform_FRIENDS_distribution(generator);
			if (newFriendIndex != i) {
				if (!IsFriend(studentGraph[i].friends, studentGraph[newFriendIndex])) {
					studentGraph[i].friends.emplace_back(&studentGraph[newFriendIndex]);
					studentGraph[newFriendIndex].friends.push_back(&studentGraph[i]);
				}
			}
			else
				j--;
		}
	}

	return studentGraph;
}

void GetStudentGraphStats(const std::vector<Student>& studentGraph)
{
	size_t min = -1;
	size_t max = 0;
	size_t accumulator = 0;
	for (const Student& student : studentGraph) {
		accumulator += student.friends.size();
		if (min > student.friends.size())
			min = student.friends.size();
		if (max < student.friends.size())
			max = student.friends.size();
	}
	printf("Student graph stats:"
			"\n\tMin: %u"
			"\n\tMax: %u"
			"\n\tAverage: %u\n\n\n"
		, min, max, accumulator / studentGraph.size());
}