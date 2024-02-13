#include <iostream>
#include <vector>

struct employee {
    std::string name;
    uint8_t age;
    uint32_t salary;
    employee* coworker = nullptr;

    employee(std::string name, uint32_t age, uint32_t salary)
        : name(name), age(age), salary(salary)
    {}

    void Display()
    {
        printf("\n%s's stats:"
                "\n\tAge:%d"
                "\n\tSalary:%d",
                name.c_str(), age, salary);
        if (coworker)
            printf("\n\tCo-worker: %s", coworker->name.c_str());
        else
            puts("\n\tDoes not have a co-worker!");
        puts("\n");
    }
};

const char* names[] = {
    "Liam","Olivia","Noah","Emma","Oliver","Ava","Elijah",
    "Charlotte","William","Sophia","James","Amelia",
    "Benjamin","Isabella","Lucas","Mia","Henry","Evelyn",
    "Alexander","Harper"
};

#define NR_OF_EMPOYEES 9
int main()
{
    srand(time(NULL));
    std::vector<employee> employees;
    employees.reserve(NR_OF_EMPOYEES);
    for (size_t i = 0; i < NR_OF_EMPOYEES; i++)
        employees.emplace_back(employee(
            names[rand() % 20],
            rand() % 30 + 20,
            rand() % 5000 + 2000));

    for (size_t i = 0; i < NR_OF_EMPOYEES - NR_OF_EMPOYEES % 2; i++)
        employees[i].coworker = &(employees[((i % 2) ? i - 1 : i + 1)]);

    for (size_t i = 0; i < NR_OF_EMPOYEES; i++)
        employees[i].Display();
}