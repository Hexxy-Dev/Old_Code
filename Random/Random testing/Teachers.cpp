#include <iostream>
#include <vector>

struct teacher {
    teacher() = default;

    teacher(const std::string& name, uint32_t age)
        : name(name), age(age), nrOfStudents(0)
    {}

    void Display()
    {
        printf("Prof. %s's (age %d) students:", name.c_str(), age);
        for (size_t i = 0; i <= nrOfStudents; i++)
            printf("\n\t%s", students[i].c_str());
        puts("\n");
    }

    inline void AddStudent(const std::string& name) { students[nrOfStudents++] = name; }

private:
    std::string name;
    uint8_t age;
    std::string students[34];
    size_t nrOfStudents;
};

const char* names[] = {
    "Liam","Olivia","Noah","Emma","Oliver","Ava","Elijah",
    "Charlotte","William","Sophia","James","Amelia",
    "Benjamin","Isabella","Lucas","Mia","Henry","Evelyn",
    "Alexander","Harper"
};

#define NR_OF_TEACHERS 9
#define MAX_NR_OF_STUDENTS 12
#define MIN_NR_OF_STUDENTS 5
int main()
{
    srand(time(NULL));

    teacher teachers[NR_OF_TEACHERS];
    
    for (size_t i = 0; i < NR_OF_TEACHERS; i++) {
        teachers[i] = teacher(names[rand() % 20], rand() % 40 + 20);
        size_t nrOfStudents = rand() % MAX_NR_OF_STUDENTS + MIN_NR_OF_STUDENTS;
        for (size_t j = 0; j < nrOfStudents; j++)
            teachers[i].AddStudent(names[rand() % 20]);
    }

    for (size_t i = 0; i < NR_OF_TEACHERS; i++)
        teachers[i].Display();
}