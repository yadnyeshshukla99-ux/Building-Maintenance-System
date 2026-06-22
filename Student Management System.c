#include<stdio.h>
#include<string.h>
#define max 100

struct Student
{
    int roll;
    char name[50];
    float marks;
};

struct Student s[max];
int count = 0;

/* Function to Add Student */
void addStudent()
{
    if (count >= max)
    {
        printf("Student list is full.\n");
        return;
    }

    printf("Enter student roll no: ");
    scanf("%d", &s[count].roll);

    getchar();  // clear newline from buffer

    printf("Enter student name: ");
    fgets(s[count].name, sizeof(s[count].name), stdin);
    s[count].name[strcspn(s[count].name, "\n")] = 0; // remove newline

    printf("Enter student marks: ");
    scanf("%f", &s[count].marks);

    count++;

    printf("Student added successfully!\n");
}

/* Function to Display Students */
void displayStudents()
{
    if (count == 0)
    {
        printf("No students available.\n");
        return;
    }

    printf("\n----- Student List -----\n");
    for (int i = 0; i < count; i++)
    {
        printf("Roll: %d | Name: %s | Marks: %.2f\n",
               s[i].roll, s[i].name, s[i].marks);
    }
}

/* Function to Search Student */
void searchStudent()
{
    int roll, found = 0;

    printf("Enter roll no to search: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++)
    {
        if (s[i].roll == roll)
        {
            printf("Student Found!\n");
            printf("Roll: %d | Name: %s | Marks: %.2f\n",
                   s[i].roll, s[i].name, s[i].marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");
}

/* Function to Sort Students by Marks (Descending) */
void sortStudents()
{
    struct Student temp;

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (s[j].marks < s[j + 1].marks)
            {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }

    printf("Students sorted by marks (Descending).\n");
}

/* Function to Delete Student */
void deleteStudent()
{
    int roll, found = 0;

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++)
    {
        if (s[i].roll == roll)
        {
            for (int j = i; j < count - 1; j++)
            {
                s[j] = s[j + 1];
            }
            count--;
            found = 1;
            printf("Student deleted successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Student not found!\n");
}

/* Main Function */
int main()
{
    int choice;

    do
    {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Sort by Marks\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: sortStudents(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}