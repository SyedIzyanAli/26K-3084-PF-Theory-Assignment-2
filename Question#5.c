#include <stdio.h>
#include <string.h>

// Function Prototypes
void displayMenu(void);
void registerMember(char name[], int *studentID, int *memberType);
void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks);
void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType);
float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine);
void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver);

int main(void) {
    // Initializing book inventory data
    int totalBooks = 4;
    int bookIDs[4] = {101, 102, 103, 104};
    char bookTitles[4][50] = {
        "Programming in C",
        "Data Structures",
        "Database Systems",
        "Computer Networks"
    };
    int availableCopies[4] = {5, 3, 0, 4};

    // Member and borrowing record variables
    char name[100] = "";
    int studentID = 0;
    int memberType = 0; // 1 for Student, 2 for Faculty
    int borrowedBookIDs[3] = {0};
    int borrowedCount = 0;
    float totalFine = 0.0;
    float fineAfterWaiver = 0.0;

    int choice = 0;
    int registered = 0;

    do {
        displayMenu();
        printf("Enter your choice: ");
        
        // Safely check scanf input to prevent infinite loops on wrong inputs
        if (scanf("%d", &choice) != 1) {
            printf("\n[!] Invalid input! Please enter a valid number.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // Clear invalid input safely
            choice = 0; // Reset choice to keep loop running
            continue;
        }
        
        // Clear trailing newline left by choice input
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choice) {
            case 1:
                registerMember(name, &studentID, &memberType);
                registered = 1;
                break;

            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
                break;

            case 3:
                if (!registered) {
                    printf("\n[!] Please register a member first (Option 1).\n");
                    break;
                }
                borrowBook(bookIDs, bookTitles, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType);
                break;

            case 4:
                if (!registered) {
                    printf("\n[!] Please register a member first (Option 1).\n");
                    break;
                }
                if (borrowedCount == 0) {
                    printf("\n[!] You have not borrowed any books to return.\n");
                    break;
                }
                fineAfterWaiver = returnBook(bookIDs, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType, &totalFine);
                break;

            case 5:
                if (!registered) {
                    printf("\n[!] Please register a member first (Option 1).\n");
                    break;
                }
                displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFine, fineAfterWaiver);
                break;

            case 6:
                printf("\nExiting University Library Management System. Goodbye!\n");
                break;

            default:
                printf("\n[!] Invalid choice! Please select between 1 and 6.\n");
        }

    } while (choice != 6);

    return 0;
}

// 1. Display Menu Function
void displayMenu(void) {
    printf("\n\n");
    printf("     UNIVERSITY LIBRARY MANAGEMENT SYSTEM\n");
    printf("\n");
    printf("1. Register Member\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("\n");
}

// 2. Register Member Function
void registerMember(char name[], int *studentID, int *memberType) {
    printf("\n--- Member Registration ---\n");
    printf("Enter Member Name: ");
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = 0; // remove trailing newline

    printf("Enter Student/Member ID: ");
    while (scanf("%d", studentID) != 1) {
        printf("[!] Invalid ID. Enter a numeric Student/Member ID: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    do {
        printf("Enter Membership Type (1 for Student, 2 for Faculty): ");
        if (scanf("%d", memberType) != 1) {
            printf("[!] Invalid input. Please enter 1 or 2.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            *memberType = 0;
            continue;
        }
        if (*memberType != 1 && *memberType != 2) {
            printf("[!] Invalid membership type. Please enter 1 or 2.\n");
        }
    } while (*memberType != 1 && *memberType != 2);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("-> Registration Successful!\n");
}

// 3. Display Books Function
void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks) {
    printf("\n\n");
    printf("|  ID   |          Title          | Copies |\n");
    printf("\n");
    for (int i = 0; i < totalBooks; i++) {
        printf("| %-5d | %-23s | %-6d |\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
    printf("\n");
}

// 4. Borrow Book Function
void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType) {
    if (*borrowedCount >= 3) {
        printf("\n[!] Borrowing limit reached! You can borrow a maximum of 3 books at a time.\n");
        return;
    }

    int targetID, days, foundIndex = -1;
    printf("\nEnter Book ID to borrow: ");
    while (scanf("%d", &targetID) != 1) {
        printf("[!] Invalid input. Enter a valid Book ID: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    for (int i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == targetID) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("[!] Invalid Book ID.\n");
        return;
    }

    if (availableCopies[foundIndex] <= 0) {
        printf("[!] Sorry, '%s' is currently out of stock.\n", bookTitles[foundIndex]);
        return;
    }

    do {
        printf("Enter number of days you intend to keep the book: ");
        if (scanf("%d", &days) != 1) {
            printf("[!] Invalid input. Please enter a positive number.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            days = 0;
            continue;
        }
        if (days <= 0) {
            printf("[!] Number of days must be positive.\n");
        }
    } while (days <= 0);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Record the borrowing
    borrowedBookIDs[*borrowedCount] = targetID;
    (*borrowedCount)++;
    availableCopies[foundIndex]--;

    printf("-> Book '%s' successfully borrowed for %d days!\n", bookTitles[foundIndex], days);
}

// 5. Return Book Function
float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine) {
    int targetID, actualDays, foundPos = -1;
    printf("\nEnter Book ID to return: ");
    while (scanf("%d", &targetID) != 1) {
        printf("[!] Invalid input. Enter a valid Book ID: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // Verify if member borrowed this book
    for (int i = 0; i < *borrowedCount; i++) {
        if (borrowedBookIDs[i] == targetID) {
            foundPos = i;
            break;
        }
    }

    if (foundPos == -1) {
        printf("[!] You have not borrowed a book with ID %d.\n", targetID);
        return *totalFine;
    }

    do {
        printf("Enter actual number of days the book was kept: ");
        if (scanf("%d", &actualDays) != 1) {
            printf("[!] Invalid input. Please enter a positive number.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            actualDays = 0;
            continue;
        }
        if (actualDays <= 0) {
            printf("[!] Days must be positive.\n");
        }
    } while (actualDays <= 0);

    // Find allowed limit (Student: 14 days, Faculty: 30 days)
    int allowedDays = (memberType == 1) ? 14 : 30;
    float currentFine = 0.0;

    if (actualDays > allowedDays) {
        int extraDays = actualDays - allowedDays;
        float rate = (memberType == 1) ? 20.0 : 10.0;
        currentFine = extraDays * rate;
        printf("-> Late return! %d extra days recorded. Fine: Rs. %.2f\n", extraDays, currentFine);
    } else {
        printf("-> Book returned on time. No late fine.\n");
    }

    *totalFine += currentFine;
    float fineAfterWaiver = *totalFine;

    // Membership code waiver check
    char code[20];
    printf("Enter membership code for waiver (or type 'NONE'): ");
    scanf("%19s", code);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if (strcmp(code, "LIB2026") == 0) {
        fineAfterWaiver *= 0.5; // 50% waiver
        printf("-> Valid code 'LIB2026' entered! 50%% waiver applied.\n");
    } else {
        printf("-> Invalid or no code entered. No waiver applied.\n");
    }

    // Update book inventory (increase available copies)
    for (int i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == targetID) {
            availableCopies[i]++;
            break;
        }
    }

    // Remove book from borrowed list by shifting elements
    for (int i = foundPos; i < *borrowedCount - 1; i++) {
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    }
    borrowedBookIDs[*borrowedCount - 1] = 0;
    (*borrowedCount)--;

    return fineAfterWaiver;
}

// 6. Display Member Record Function
void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver) {
    printf("\n\n");
    printf("           MEMBER RECORD REPORT          \n");
    printf("\n");
    printf("Name           : %s\n", name);
    printf("Student/ID     : %d\n", studentID);
    printf("Membership Type: %s\n", (memberType == 1) ? "Student" : "Faculty");
    printf("Currently Borr.: ");
    if (borrowedCount == 0) {
        printf("None\n");
    } else {
        for (int i = 0; i < borrowedCount; i++) {
            printf("[%d] ", borrowedBookIDs[i]);
        }
        printf("\n");
    }
    printf("Total Fine Before Waiver: Rs. %.2f\n", totalFine);
    printf("Final Payable Fine      : Rs. %.2f\n", fineAfterWaiver);
    printf("\n");
}