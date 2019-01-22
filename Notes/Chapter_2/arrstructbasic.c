#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    enum {female, male} gender;
    union {
        bool children;
        bool beard;
    } u;
} Info;

typedef struct {
    char name[30];
    int age;
    int salary;
    Info genderinfo;
} Person;

int main()
{
    // Arrays
    int list[5];
    int *plist;
    int i;
    for (i = 0; i < 5; i++) list[i] = rand() % 100 + 1;
    for (i = 0; i < 5; i++) printf("%d ", list[i]);
    printf("\n");
    plist = list;
    int n = 5;
    while (n--) printf("%p %d\n", plist + n, *(plist + n));
    printf("\n");

    // Unions
    Person person;
    static const char *genderstr[] = {"female", "male"};
    strcpy(person.name, "Joyce Chin");
    person.age = 19;
    person.salary = 0;
    person.genderinfo.gender = female;
    person.genderinfo.u.children = false;
    printf("Info:\n");
    const char *gender[10] = {genderstr[person.genderinfo.gender]};
    printf("%s\n%d\n%s\n%d\n", person.name, person.age, *gender, person.genderinfo.u.children);
    return 0;
}