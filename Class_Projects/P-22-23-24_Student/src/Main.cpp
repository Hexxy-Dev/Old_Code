#include <iostream>
#include "Student.h"

void SuggestFriends(const Student& student)
{
	uint8_t suggestions = 0;
	std::vector<Student*> suggested;
	for(const Student* Friend : student.friends)
		for (Student* friendOfFriend : Friend->friends) {
			if (IsFriend(student.friends, *friendOfFriend) || &student == friendOfFriend
				|| IsFriend(suggested, *friendOfFriend))
				continue;
			suggested.push_back(friendOfFriend);
			puts((friendOfFriend->name + ' ' + friendOfFriend->surname).c_str());
			suggestions++;
			if (suggestions == 10)
				return;
		}
}

void AverageFriendsAge(const Student& student)
{
	if (rand() % 20 == 7) {
		puts("I DO NOT WANT TO TELL YOU THAT!!");
		return;
	}

	uint16_t accumulator = 0;
	for (const Student* Friend : student.friends)
		accumulator += Friend->age;
	printf("%u", accumulator / student.friends.size());
}

int main()
{
	srand(time(NULL));
	std::vector<Student> studentGraph = CreateStudentGraph();
	GetStudentGraphStats(studentGraph);
	for (size_t i = 0; i < 10; i++) {
		uint8_t studentIndex = rand() % 100;
		printf("%s's Friends Suggestions:\n",
			(studentGraph[studentIndex].name + ' ' + studentGraph[studentIndex].surname).c_str());
		SuggestFriends(studentGraph[studentIndex]);
		printf("%s's Average firends age: ", studentGraph[studentIndex].name.c_str());
		AverageFriendsAge(studentGraph[studentIndex]);
		puts("\n\n");
	}
}