/*
 * The third project of the course "C language programming" for YSU
 *
 * AUTHOR: Platohykj
 * DATE: 2023-11-16
 * EMAIL: "abc39757785aa@outlook.com"
 *
 * platform: Windows 11 or Linux
 * Programming language: C
 * TOOLS: CLion Nova for Windows 11 or gcc for Linux
 * Project name: Book manage system
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux__
#include <unistd.h>
#endif
#include <time.h>

#define USERNAME_LEN 10
#define PASSWORD_LEN 20
#define BOOK_NAME_LEN 20
#define BOOK_AUTHOR_LEN 20
#define BOOK_ISBN_LEN 14
#define BOOK_LIBRARY_LEN 20
#define BOOK_TIME_LEN 20
#define BOOK_TAG_LEN 20
#define VERSION "1.0.0"
#define AUTHOR "Platohykj"
#define EMAIL "abc39757785aa@outlook.com"

#define PRINT_HEAD printf("-------------------------------------------------------------------------------------------------------------------------------\n");\
                   printf("%-20s|%-20s|%-20s|%-20s|%-20s|%-20s\n","Name","Author","ISBN","Tag","Add time","Update time");\
                   printf("-------------------------------------------------------------------------------------------------------------------------------\n");
#define PRINT_TAIL printf("===============================================================================================================================\n");

// Book structure
typedef struct Book_info {
    char name[BOOK_NAME_LEN];
    char author[BOOK_AUTHOR_LEN];
    char ISBN[BOOK_ISBN_LEN];
    char tag;
    long long int add_time;
    long long int update_time;
} Book_info;

// Book node
typedef struct Book_node {
    Book_info book;
    struct Book_node* next;
} Book_node;

// Book list
typedef struct Book_list {
    Book_node* head;
} Book_list;

// Library structure
typedef struct Library {
    char name[BOOK_LIBRARY_LEN];
    Book_list* book_list;
} Library;

//Function declarations

//Users manage functions
void sleep_s(int time); // Sleep for a while
void clear_screen(); // Clear the screen
void flush_s(); // Flush the stdin
char* stdin_readline(char* str, int n); // Read a line from stdin
char* getUsername(); // Get the username
char* getPassword(); // Get the password
unsigned long long simpleHash(const char* input); // Encrypt the password
int createAccount(char* username, char* password); // Create an account
bool checkPassword(const char* username, const char* input_password); // Check the password
int login_info(); // Login
int signup_check(); // Sign up check
int signup_info(); // Sign up
int main_info(); // The main interface
int first_info(); // The first interface

//Library manage functions
Library* createLibrary(char* name); // Create a library
int addBook(Library* library, Book_info book); // Add a book
int push_info_to_book(Book_info* book); // Push the info to the book
bool check_ISBN(const char* isbnCode); // Check the ISBN
long long int get_time(); // Get the time
void switch_time(long long int time, char* format_time, char* format, int size_of_string); // Switch the time format
void printBook(Book_info* book); // Print the book
void print_library(Library* library); // Print the library
int save_to_file(Library* library); // Save the library to the file
int load_from_file(Library* library); // Load the library from the file
bool check_ID(int id, Library* library); // Check the ID
void freelibrary(Library* library); // Free the library
void PressAnyKeyToExit(); // Press any key to exit
int deleteBook(Library* library, unsigned int index); // Delete a book
int changeBook(Library* library, Book_info* book, int id); // Change a book
Book_info* getBookByISBN(Library* library, char* isbn); // Get the book by ISBN
Book_info* getBookByName(Library* library, char* name); // Get the book by name
void printBookByTag(Library* library, char tag); // Get the book list by tag
int manage_info(Library* library); // Manage the library

// Main function
int main() {
    while (1) {
        if (first_info() == 0) {
            break;
        }
    }
    while (1) {
        const int choice = main_info();
        if (choice == 1) {
            char temp[BOOK_NAME_LEN];
            char library_name[BOOK_LIBRARY_LEN];
            printf("==========Welcome to create a library==========\n");
            printf("Please enter the name of the library: ");
            stdin_readline(temp, BOOK_LIBRARY_LEN);
            strcpy(library_name, temp);
            strcat(library_name, ".lib");
            FILE* fp = fopen(library_name, "r");
            if (fp != NULL) {
                fclose(fp);
                printf("The library has been created!\n");
                printf("================================================\n");
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
                continue;
            }
            FILE* fp_create = fopen(library_name, "wb+");
            if (fp_create == NULL) {
                printf("Failed to create the library!\n");
                printf("================================================\n");
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
                continue;
            }
            fclose(fp_create);
            printf("Create a library success!\n");
            printf("The name of the library is %s\n", temp);
            printf("================================================\n");
            for (int m = 0; m < 3; ++m) {
                printf("system will return to the first interface after %d seconds\n", 3 - m);
                sleep_s(1000);
            }
            clear_screen();
            continue;
        }
        if (choice == 2) {
            printf("================================================\n");
            printf("Please enter the name of the library: ");
            char library_name[BOOK_LIBRARY_LEN];
            stdin_readline(library_name, BOOK_LIBRARY_LEN);
            char temp[BOOK_LIBRARY_LEN];
            strcpy(temp, library_name);
            strcat(temp, ".lib");
            FILE* fp = fopen(temp, "r");
            if (fp == NULL) {
                printf("The library does not exist!\n");
                printf("================================================\n");
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
                continue;
            }
            fclose(fp);
            Library* library = createLibrary(library_name);
            if (load_from_file(library) == -1) {
                printf("Failed to load the library!\n");
                printf("================================================\n");
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
                continue;
            }
            clear_screen();
            manage_info(library);
        }
        if (choice == -1) {
            break;
        }
    }
    return 0;
}

// Function definitions
/*
 * void sleep_s(int time)
 * - Sleep for a while
 * - This function is used to sleep for a while
 * - time: The time to sleep
 */

void sleep_s(int time) {
#ifdef _WIN32
    Sleep(time);
#endif
#ifdef __linux__
    usleep(time * 1000);
#endif
}

/*
 * void clear_screen()
 * - Clear the screen
 * - This function is used to clear the screen
 */

void clear_screen() {
#ifdef _WIN32
    system("cls");
#endif
#ifdef __linux__
    system("clear");
#endif
}

/*
 * void flush_s()
 * - Flush the stdin
 * - This function is used to flush the stdin
 */

void flush_s() {
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n');
    // Flush remaining characters including '\n'
    clearerr(stdin);
}

/*
 * char *stdin_readline(char *str, int n)
 * - Read a line from stdin
 * - This function is used to read a line from stdin
 * - str: The string to store the line
 * - n: The max length of the string
 * - return: The string
 */

char* stdin_readline(char* str, const int n) {
    if (fgets(str, n, stdin) != NULL) {
        const size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            // Remove the trailing newline
            str[len - 1] = '\0';
        }
        else {
            // Flush the input buffer if no newline is found
            flush_s();
        }
    }
    else {
        str[0] = '\0';
    }
    return str;
}

/*
 * char *getUsername()
 * - Get the username
 * - This function is used to get the username
 * - return: The username
 */

char* getUsername() {
    char* username = calloc(USERNAME_LEN, sizeof(char));
    printf("Username: ");
    stdin_readline(username, USERNAME_LEN);
    return username;
}

/*
 * char *getPassword()
 * - Get the password
 * - This function is used to get the password
 * - return: The password
 * - Note: The password will not be displayed on the screen
 */

char* getPassword() {
    char* password = calloc(PASSWORD_LEN, sizeof(char));
    printf("Password: ");
#ifdef _WIN32
    // Shut down the echo
    const HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & ~ENABLE_ECHO_INPUT);
    // Get the password
    stdin_readline(password, PASSWORD_LEN);
    // Turn on the echo
    SetConsoleMode(hStdin, mode);
#endif
#ifdef __linux__
    // Shut down the echo
    system("stty -echo");
    // Get the password
    stdin_readline(password, PASSWORD_LEN);
    // Turn on the echo
    system("stty echo");
#endif
    return password;
}

/*
 * unsigned long long simpleHash(const char *input)
 * - Encrypt the password
 * - This function is used to encrypt the password with a simple hash algorithm
 * - input: The password
 * - return: The encrypted password
 */

unsigned long long simpleHash(const char* input) {
    unsigned long long hash = 0;
    const size_t len = strlen(input);
    for (size_t i = 0; i < len; i++) {
        hash = (hash << 5) + input[i];
    }
    return hash;
}

/*
 * int checkPassword(const char *username, const char *password)
 * - Check the password
 * - This function is used to check the password
 * - username: The username
 * - password: The password
 * - return: 1 if the password is correct, 0 if the password is incorrect
 * - Note: The password will not be displayed on the screen
 */

bool checkPassword(const char* username, const char* input_password) {
    FILE* fp = fopen(username, "rb");
    if (fp == NULL) {
        return false;
    }
    unsigned long long stored_hash;
    const size_t read_count = fread(&stored_hash, sizeof(unsigned long long), 1, fp);
    fclose(fp);
    if (read_count != 1) {
        return false;
    }
    const unsigned long long input_hash = simpleHash(input_password);
    return input_hash == stored_hash;
}

/*
 * int createAccount(char *username, char *password)
 * - Create an account
 * - This function is used to create an account
 * - username: The username
 * - password: The password
 * - return: 0 if success, -1 if failed
 * - Note: The password will not be displayed on the screen
 */

int createAccount(char* username, char* password) {
    FILE* fp = fopen(username, "wb+");
    if (fp == NULL) {
        return -1;
    }
    const unsigned long long hash = simpleHash(password);
    fwrite(&hash, sizeof(unsigned long long), 1, fp);
    fclose(fp);
    return 0;
}

/*
 * int login_info()
 * - Login
 * - This function is used to log in
 * - return: 0 if success, -1 if failed
 * - Note: The password will not be displayed on the screen
 * - Note: The user can try 3 times at most
 * - Note: The user can try again after 3 seconds
 * - Note: The user can return to the first interface after 3 seconds
 * - Note: The user can return to the first interface if the username does not exist
 * - Note: The user can return to the first interface if the password is incorrect
 */

int login_info() {
    printf("==========Welcome to login==========\n");
    char* username = getUsername();
    //check if the username exists
    const FILE* fp = fopen(username, "r");
    if (fp == NULL) {
        printf("The username does not exist!\n");
        free(username);
        for (int i = 0; i < 3; ++i) {
            printf("system will return to the first interface after %d seconds\n", 3 - i);
            sleep_s(1000);
        }
        clear_screen();
        return -1;
    }
    char* password = NULL;
    int i = 0;
    while (i < 3) {
        password = getPassword();
        if (checkPassword(username, password)) {
            printf("Login success!\n");
            username = NULL;
            password = NULL;
            free(username);
            free(password);
            //sleep for 1 seconds
            sleep_s(1000);
            clear_screen();
            return 0;
        }
        printf("Login failed!\n");
        free(password);
        password = NULL;
        i++;
    }
    free(username);
    username = NULL;
    printf("You have tried 3 times, please try again later!\n");
    //sleep for 3 seconds
    for (int m = 0; m < 3; ++m) {
        printf("system will return to the first interface after %d seconds\n", 3 - m);
        sleep_s(1000);
    }
    clear_screen();
    return -1;
}

/*
 * int signup_check()
 * - Sign up check
 * - This function is used to check if the user is the admin
 * - return: 0 if success, -1 if failed
 * - Note: The password will not be displayed on the screen
 */

int signup_check() {
    printf("Please enter the admin password\n");
    //check if the username exists
    const FILE* fp = fopen("admin", "r");
    if (fp == NULL) {
        printf("The username does not exist!\n");
        for (int i = 0; i < 3; ++i) {
            printf("system will return to the first interface after %d seconds\n", 3 - i);
            sleep_s(1000);
        }
        clear_screen();
        return -1;
    }
    char* password = NULL;
    int i = 0;
    while (i < 3) {
        password = getPassword();
        if (checkPassword("admin", password)) {
            printf("Login success!\n");
            password = NULL;
            free(password);
            //sleep for 1 seconds
            sleep_s(1000);
            clear_screen();
            return 0;
        }
        printf("Login failed!\n");
        free(password);
        password = NULL;
        i++;
    }
    printf("You have tried 3 times, please try again later!\n");
    //sleep for 3 seconds
    for (int q = 0; q < 3; ++q) {
        printf("system will return to the first interface after %d seconds\n", 3 - q);
        sleep_s(1000);
    }
    clear_screen();
    return -1;
}

/*
 * int signup_info()
 * - Sign up
 * - This function is used to sign up
 * - return: 0 if success, -1 if failed
 * - Note: The password will not be displayed on the screen
 */

int signup_info() {
    if (signup_check() == -1) {
        return first_info();
    }
    clear_screen();
    printf("==========Welcome to sign up==========\n");
    char* username = getUsername();
    FILE* fp = fopen(username, "r");
    if (fp != NULL) {
        printf("The username has been used!\n");
        free(username);
        fclose(fp);
        clear_screen();
        return -1;
    }
    char* password = getPassword();
    if (createAccount(username, password) == -1) {
        printf("Failed to create account!\n");
        free(username);
        free(password);
        fclose(fp);
        return -1;
    }
    printf("\nSign up success!\n");
    for (int i = 0; i < 3; ++i) {
        printf("system will return to the first interface after %d seconds\n", 3 - i);
        sleep_s(1000);
    }
    clear_screen();
    return first_info();
}

/*
 * int first_info()
 * - The first interface
 * - This function is used to show the first interface
 * - return: 0 if success, -1 if failed
 * - Note: The password will not be displayed on the screen
 */

int first_info() {
    FILE* fp_admin = fopen("admin", "r+");
    if (fp_admin == NULL) {
        printf("This is the first time you use this system!\n");
        printf("Please sign up to create an admin account!\n");
        fp_admin = fopen("admin", "wb+");
        if (fp_admin == NULL) {
            printf("Failed to create admin account!\n");
            return -1;
        }
        char* password = getPassword();
        const unsigned long long hash = simpleHash(password);
        printf("Please enter the password again: ");
        fwrite(&hash, sizeof(unsigned long long), 1, fp_admin);
        free(password);
        password = NULL;
        fflush(fp_admin);
        clear_screen();
        fclose(fp_admin);
        printf("\nSign up success!\n");
        for (int i = 0; i < 3; ++i) {
            printf("system will return to the first interface after %d seconds\n", 3 - i);
            sleep_s(1000);
        }
        clear_screen();
    }
    else {
        fclose(fp_admin);
    }

    printf("==========Welcome to the book manage system==========\n");
    printf("- [l] Login\n");
    printf("- [s] Sign up\n");
    printf("- [q] Quit\n");
    printf("=====================================================\n");
    printf("Please enter your choice: ");
    const char choice = getchar();
    flush_s();
    clear_screen();
    switch (choice) {
        case 'l':
            return login_info();
        case 'L':
            return login_info();
        case 's':
            return signup_info();
        case 'S':
            return signup_info();
        case 'q':
            exit(0);
        case 'Q':
            exit(0);
        default:
            printf("Invalid input!\n");
            printf("Please try again!\n");
            return -1;
    }
}

/*
 * int main_info()
 * - The main interface
 * - This function is used to show the main interface
 * - return: 0 if success, -1 if failed
 * - Note: After the user logs in, the user can choose to create a library, or choose to manage the library
 */

int main_info() {
    printf("==========Welcome to the book manage system==========\n");
    printf("- [c] Create a library\n");
    printf("- [m] Manage the library\n");
    printf("- [q] Quit\n");
    printf("=====================================================\n");
    printf("Please enter your choice: ");
    const char choice = getchar();
    clear_screen();
    flush_s();
    switch (choice) {
        case 'c':
            return 1;
        case 'C':
            return 1;
        case 'm':
            return 2;
        case 'M':
            return 2;
        case 'q':
            exit(0);
        case 'Q':
            exit(0);
        default:
            printf("Invalid input!\n");
            printf("Please try again!\n");
            return -1;
    }
}

/*
 * Library *createLibrary(char *name)
 * - Create a library
 * - This function is used to create a library
 * - name: The name of the library
 * - return: The library
 */

Library* createLibrary(char* name) {
    Library* library = (Library *)calloc(1, sizeof(Library));
    strcpy(library->name, name);
    library->book_list = calloc(1, sizeof(Book_list));
    library->book_list->head = NULL;
    return library;
}

/*
 * int addBook(Library *library, Book_info book)
 * - Add a book
 * - This function is used to add a book
 * - library: The library
 * - book: The book
 * - return: 0 if success, -1 if failed
 */

int addBook(Library* library, Book_info book) {
    Book_node* new_node = (Book_node *)calloc(1, sizeof(Book_node));
    if (new_node == NULL) {
        fprintf(stdout, "Error: Memory allocation failed.\n");
        return -1;
    }
    new_node->book = book;
    new_node->next = NULL;
    if (library->book_list->head == NULL) {
        library->book_list->head = new_node;
    }
    else {
        Book_node* p = library->book_list->head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = new_node;
    }
    return 0;
}

/*
 * bool check_ISBN(char* ISBN)
 * - Check the ISBN
 * - This function is used to check the ISBN
 * - ISBN: The ISBN
 * - return: true if success, false if failed
 * - Note: The ISBN must be 13 digits
 * - Note: The ISBN must be numbers
 * - Note: Use the ISBN_13 algorithm to check the ISBN
 */

bool check_ISBN(const char* isbnCode) {
    if (strlen(isbnCode) < 13) return 0;
    int sum = 0, len = strlen(isbnCode);
    char c;
    for (int i = 0, j = 1; i < len - 1; i++) {
        if (isbnCode[i] >= '0' && isbnCode[i] <= '9') {
            if (j % 2 == 1) {
                sum += isbnCode[i] - '0';
            }
            else {
                sum += 3 * (isbnCode[i] - '0');
            }
            j++;
        }
    }
    c = isbnCode[len - 1];
    sum = 10 - sum % 10;
    if (sum == 10)
        return c == 'X' || c == 'x';
    return sum == c - '0';
}

/*
 * long long int get_time()
 * - Get the time
 * - This function is used to get the time
 * - return: The time
 * - Note: The time is the number of seconds since 1970-01-01 00:00:00
 */

long long int get_time() {
    time_t t;
    time(&t);
    return t;
}

/*
 * void switch_time(long long int time,char* format_time,char* format,int size_of_string)
 * - Switch the time format
 * - This function is used to switch the time format
 * - time: The time
 * - format_time: The time in the new format
 * - format: The format of the time
 * - size_of_string: The size of the string
 * - Note: The time is the number of seconds since 1970-01-01 00:00:00
 * - Note: The format of the time is like "2021-01-01 00:00:00"
 * - Note: The size of the string is 20
 * - Note: The format of the time must be like "YYYY-MM-DD hh:mm:ss"
 */

void switch_time(long long int time, char* format_time, char* format, int size_of_string) {
    struct tm* p = localtime((time_t *)&time);
    strftime(format_time, size_of_string, format, p);
}

/*
 * int push_info_to_book(Book_info *book)
 * - Push the info to the book
 * - This function is used to push the info to the book
 * - book: The book
 * - return: true if success, false if failed
 */

int push_info_to_book(Book_info* book) {
    printf("Please enter the name of the book: ");
    stdin_readline(book->name, BOOK_NAME_LEN);
    printf("Please enter the author of the book: ");
    stdin_readline(book->author, BOOK_AUTHOR_LEN);
    while (1) {
        printf("Please enter the ISBN of the book: ");
        stdin_readline(book->ISBN, BOOK_ISBN_LEN);
        if (book->ISBN[0] == 'q' || book->ISBN[0] == 'Q') {
            strcpy(book->ISBN, "NULL");
            break;
        }
        if (!check_ISBN(book->ISBN)) {
            printf("The ISBN is invalid!\n");
            for (int m = 0; m < 3; ++m) {
                printf("system will return to the first interface after %d seconds\n", 3 - m);
                sleep_s(1000);
            }
            clear_screen();
            continue;
        }
        break;
    }
    printf("\n");
    printf("================================================\n");
    printf("- [1] Textbook\n");
    printf("- [2] Reference book\n");
    printf("- [3] Monograph\n");
    printf("- [4] Novel\n");
    printf("- [5] Others\n");
    printf("Please enter the tag of the book: ");
    char tag = getchar();
    flush_s();
    switch (tag) {
        case '1':
            book->tag = '1';
            break;
        case '2':
            book->tag = '2';
            break;
        case '3':
            book->tag = '3';
            break;
        case '4':
            book->tag = '4';
            break;
        case '5':
            book->tag = '5';
            break;
        default:
            printf("Invalid input!\n");
            printf("Please try again!\n");
            printf("Please wait for 1 seconds\n");
            sleep_s(1000);
            clear_screen();
            return 0;
    }
    return 1;
}

/*
 * void printBook(Book_info *book)
 * - Print the book
 * - This function is used to print the book
 * - book: The book
 * - Note: The time is the number of seconds since 1970-01-01 00:00:00
 * - Note: The format of the time is like "2021-01-01 00:00:00"
 * - Note: The size of the string is 20
 * - Note: The format of the time must be like "YYYY-MM-DD hh:mm:ss"
 * - Note: The tag of the book is like "1" for textbook, "2" for reference book, "3" for monograph, "4" for novel, "5" for others
 */

void printBook(Book_info* book) {
    char add_time[BOOK_TIME_LEN];
    char update_time[BOOK_TIME_LEN];
    char tag[BOOK_TAG_LEN];
    switch (book->tag) {
        case '1':
            strcpy(tag, "Textbook\0");
            break;
        case '2':
            strcpy(tag, "Reference book\0");
            break;
        case '3':
            strcpy(tag, "Monograph\0");
            break;
        case '4':
            strcpy(tag, "Novel\0");
            break;
        case '5':
            strcpy(tag, "Others\0");
            break;
        default:
            strcpy(tag, "Unknown\0");
            break;
    }
    switch_time(book->add_time, add_time, "%Y-%m-%d %H:%M:%S",BOOK_TIME_LEN);
    switch_time(book->update_time, update_time, "%Y-%m-%d %H:%M:%S",BOOK_TIME_LEN);
    printf("%-20s|%-20s|%-20s|%-20s|%-20s|%-20s\n", book->name, book->author, book->ISBN, tag, add_time, update_time);
    printf(
        "-------------------------------------------------------------------------------------------------------------------------------\n");
}

/*
 * void print_library(Library *library)
 * - Print the library
 * - This function is used to print the library
 * - library: The library
 * - Note: The time is the number of seconds since 1970-01-01 00:00:00
 * - Note: The format of the time is like "2021-01-01 00:00:00"
 * - Note: The size of the string is 20
 */

void print_library(Library* library) {
    int id = 1;
    printf("The name of the library is %s\n", library->name);
    PRINT_HEAD
    Book_node* p = library->book_list->head;
    while (p != NULL) {
        printf("%-4d|", id);
        printBook(&p->book);
        p = p->next;
        id++;
    }
    PRINT_TAIL
}

/*
 * int save_to_file(Library *library)
 * - Save the library to the file
 * - This function is used to save the library to the file
 * - library: The library
 * - return: 0 if success, -1 if failed
 */

int save_to_file(Library* library) {
    char temp[BOOK_LIBRARY_LEN];
    strcpy(temp, library->name);
    strcat(temp, ".lib");
    FILE* fp = fopen(temp, "wb+");
    if (fp == NULL) {
        return -1;
    }
    int id = 1;
    Book_node* p = library->book_list->head;
    while (p != NULL) {
        fwrite(&id, sizeof(int), 1, fp);
        fwrite(&p->book, sizeof(Book_info), 1, fp);
        p = p->next;
        id++;
    }
    fclose(fp);
    return 0;
}

/*
 * int load_from_file(Library *library)
 * - Load the library from the file
 * - This function is used to load the library from the file
 * - library: The library
 * - return: 0 if success, -1 if failed
 */

int load_from_file(Library* library) {
    char temp[BOOK_LIBRARY_LEN];
    strcpy(temp, library->name);
    strcat(temp, ".lib");
    FILE* fp = fopen(temp, "rb+");
    if (fp == NULL) {
        return -1;
    }
    int id = 1;
    Book_info book;
    while (fread(&id, sizeof(int), 1, fp) == 1) {
        fread(&book, sizeof(Book_info), 1, fp);
        addBook(library, book);
    }
    fclose(fp);
    return 0;
}

/*
 * bool check_ID(int id,Library *library)
 * - Check the ID
 * - This function is used to check the ID
 * - id: The ID
 * - library: The library
 * - return: true if success, false if failed
 */

bool check_ID(int id, Library* library) {
    if (id < 1) {
        return false;
    }
    Book_node* p = library->book_list->head;
    int i = 1;
    while (p != NULL) {
        if (i == id) {
            return true;
        }
        p = p->next;
        i++;
    }
    return false;
}

/*
 * void freelibrary(Library *library)
 * - Free the library
 * - This function is used to free the library
 * - library: The library
 */

void freelibrary(Library* library) {
    Book_node* p = library->book_list->head;
    while (p != NULL) {
        Book_node* q = p;
        p = p->next;
        free(q);
    }
    free(library->book_list);
    free(library);
}

/*
 * void PressAnyKeyToExit()
 * - Press any key to exit
 * - This function is used to press any key to exit?
 */

void PressAnyKeyToExit() {
    printf("Press any key to exit\n");
    getchar();
}

/*
 * int deleteBook(Library* library, unsigned int index)
 * - Delete a book
 * - This function is used to delete a book
 * - library: The library
 * - index: The index of the book
 * - return: 0 if success, -1 if failed
 */

int deleteBook(Library* library, unsigned int index) {
    if (index < 1) {
        return -1;
    }
    Book_node* p = library->book_list->head;
    Book_node* q = NULL;
    int i = 1;
    while (p != NULL) {
        if (i == index) {
            if (q == NULL) {
                library->book_list->head = p->next;
            }
            else {
                q->next = p->next;
            }
            free(p);
            return 0;
        }
        q = p;
        p = p->next;
        i++;
    }
    return -1;
}

/*
 * int changeBook(Library* library, Book_info* book, int id)
 * - Change a book
 * - This function is used to change a book
 * - library: The library
 * - book: The book
 * - id: The ID of the book
 * - return: 0 if success, -1 if failed
 */

int changeBook(Library* library, Book_info* book, int id) {
    if (id < 1) {
        return -1;
    }
    Book_node* p = library->book_list->head;
    int i = 1;
    while (p != NULL) {
        if (i == id) {
            const long long int add_time_i = p->book.add_time;
            p->book = *book;
            p->book.add_time = add_time_i;
            p->book.update_time = get_time();
            return 0;
        }
        p = p->next;
        i++;
    }
    return -1;
}

/*
 * Book_info* getBookByISBN(Library* library, char* isbn)
 * - Get the book by ISBN
 * - This function is used to get the book by ISBN
 * - library: The library
 * - isbn: The ISBN of the book
 * - return: The book
 */

Book_info* getBookByISBN(Library* library, char* isbn) {
    Book_node* p = library->book_list->head;
    while (p != NULL) {
        if (strcmp(p->book.ISBN, isbn) == 0) {
            return &p->book;
        }
        p = p->next;
    }
    return NULL;
}

/*
 * Book_info* getBookByName(Library* library, char* name)
 * - Get the book by name
 * - This function is used to get the book by name
 * - library: The library
 * - name: The name of the book
 * - return: The book
 */

Book_info* getBookByName(Library* library, char* name) {
    Book_node* p = library->book_list->head;
    while (p != NULL) {
        if (strcmp(p->book.name, name) == 0) {
            return &p->book;
        }
        p = p->next;
    }
    return NULL;
}

/*
 * Book_info* getBookByTag(Library* library, char tag)
 * - Get the book list by tag
 * - This function is used to get the book list by tag
 * - library: The library
 * - tag: The tag of the book
 * - return: The book list
 */

void printBookByTag(Library* library, char tag) {
    Book_node* p = library->book_list->head;
    PRINT_HEAD
    while (p != NULL) {
        if (p->book.tag == tag) {
            printBook(&p->book);
        }
        p = p->next;
    }
    PRINT_TAIL
}

/*
 * int manage_info(Library* library)
 * - Manage the library
 * - This function is used to manage the library
 * - library: The library
 * - return: 0 if success, -1 if failed
 * - Note: The time is the number of seconds since 1970-01-01 00:00:00
 */

int manage_info(Library* library) {
    printf("==========Welcome to manage the library %s==========\n", library->name);
    printf("- [a] Add a book\n");
    printf("- [b] Delete a book\n");
    printf("- [c] Change a book\n");
    printf("- [d] Search a book by ISBN\n");
    printf("- [e] Search a book by name\n");
    printf("- [f] List the books by tag\n");
    printf("- [g] List all the books\n");
    printf("- [h] Save the library\n");
    printf("- [i] Delete the library\n");
    printf("=====================================================\n");
    printf("- [j] Show the version of the library\n");
    printf("- [k] Show the information of the manage systhem\n");
    printf("- [l] Quit\n");
    printf("=====================================================\n");
    printf("Please enter your choice: ");
    const char choice = getchar();
    flush_s();
    clear_screen();
    switch (choice) {
        case 'a':
        case 'A':
            printf("==========Welcome to add a book==========\n");
            printf("Please enter the information of the book\n");
            Book_info book;
            if (push_info_to_book(&book) == 0) {
                printf("================================================\n");
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
                return manage_info(library);
            }
            book.add_time = get_time();
            book.update_time = get_time();
            if (addBook(library, book) == -1) {
                printf("Failed to add the book!\n");
                printf("================================================\n");
                PressAnyKeyToExit();
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
                return manage_info(library);
            }
            printf("Add the book success!\n");
            printf("================================================\n");
            PressAnyKeyToExit();
            for (int m = 0; m < 3; ++m) {
                printf("system will return to the first interface after %d seconds\n", 3 - m);
                sleep_s(1000);
            }
            clear_screen();
            return manage_info(library);

        case 'b':
        case 'B':
            printf("==========Welcome to delete a book==========\n");
            printf("Please enter the ID of the book: ");
            int id;
            scanf("%d", &id);
            flush_s();
            if (!check_ID(id, library)) {
                printf("The ID is invalid!\n");
                printf("================================================\n");
                PressAnyKeyToExit();
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
                return manage_info(library);
            }
            if (deleteBook(library, id) == -1) {
                printf("Failed to delete the book!\n");
                printf("================================================\n");
                PressAnyKeyToExit();
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
                return manage_info(library);
            }
            printf("Delete the book success!\n");
            printf("================================================\n");
            for (int m = 0; m < 3; ++m) {
                printf("system will return to the first interface after %d seconds\n", 3 - m);
                sleep_s(1000);
            }
            clear_screen();
            return manage_info(library);

        case 'c':
        case 'C':
            printf("==========Welcome to change a book==========\n");
            printf("Please enter the ID of the book: ");
            int id_change;
            scanf("%d", &id_change);
            flush_s();
            if (!check_ID(id_change, library)) {
                printf("The ID is invalid!\n");
                printf("================================================\n");
                PressAnyKeyToExit();
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
                return manage_info(library);
            }
            printf("Please enter the information of the book\n");
            Book_info book_change;
            if (push_info_to_book(&book_change) == 0) {
                printf("================================================\n");
                PressAnyKeyToExit();
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
                return manage_info(library);
            }
            if (changeBook(library, &book_change, id_change) == -1) {
                printf("Failed to change the book!\n");
                printf("================================================\n");
                PressAnyKeyToExit();
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
                return manage_info(library);
            }
            printf("Change the book success!\n");
            printf("================================================\n");
            PressAnyKeyToExit();
            for (int m = 0; m < 3; ++m) {
                printf("system will return to the first interface after %d seconds\n", 3 - m);
                sleep_s(1000);
            }
            clear_screen();
            return manage_info(library);

        case 'd':
        case 'D':
            printf("==========Welcome to search a book by ISBN==========\n");
            printf("Please enter the ISBN of the book: ");
            char ISBN[BOOK_ISBN_LEN];
            stdin_readline(ISBN, BOOK_ISBN_LEN);
            Book_info* book_ISBN = getBookByISBN(library, ISBN);
            if (book_ISBN == NULL) {
                printf("The ISBN is invalid!\n");
                printf("================================================\n");
                PressAnyKeyToExit();
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
            }
            else {
                printf("The book is found!\n");
                PRINT_HEAD
                printBook(book_ISBN);
                PRINT_TAIL
                printf("================================================\n");
                PressAnyKeyToExit();
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
            }
            return manage_info(library);

        case 'e':
        case 'E':
            printf("==========Welcome to search a book by name==========\n");
            printf("Please enter the name of the book: ");
            char name[BOOK_NAME_LEN];
            stdin_readline(name, BOOK_NAME_LEN);
            Book_info* book_name = getBookByName(library, name);
            if (book_name == NULL) {
                printf("The name is invalid!\n");
                printf("================================================\n");
                PressAnyKeyToExit();
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
            }
            else {
                printf("The book is found!\n");
                PRINT_HEAD
                printBook(book_name);
                PRINT_TAIL
                printf("================================================\n");
                PressAnyKeyToExit();
                printf("system will return to the last interface after 3 seconds\n");
                sleep_s(3000);
                clear_screen();
            }
            return manage_info(library);

        case 'f':
        case 'F':
            printf("==========Welcome to list the books by tag==========\n");
            printf("================================================\n");
            printf("- [1] Textbook\n");
            printf("- [2] Reference book\n");
            printf("- [3] Monograph\n");
            printf("- [4] Novel\n");
            printf("- [5] Others\n");
            printf("Please enter the tag of the book: ");
            char tag = getchar();
            flush_s();
            switch (tag) {
                case '1':
                    printBookByTag(library, '1');
                    break;
                case '2':
                    printBookByTag(library, '2');
                    break;
                case '3':
                    printBookByTag(library, '3');
                    break;
                case '4':
                    printBookByTag(library, '4');
                    break;
                case '5':
                    printBookByTag(library, '5');
                    break;
                default:
                    printf("Invalid input!\n");
                    printf("Please try again!\n");
                    printf("Please wait for 1 seconds\n");
                    sleep_s(1000);
                    clear_screen();
                    return manage_info(library);
            }
            printf("================================================\n");
            PressAnyKeyToExit();
            for (int m = 0; m < 3; ++m) {
                printf("system will return to the first interface after %d seconds\n", 3 - m);
                sleep_s(1000);
            }
            clear_screen();
            return manage_info(library);

        case 'g':
        case 'G':
            printf("==========Welcome to list all the books==========\n");
            print_library(library);
            printf("\n================================================\n");
            PressAnyKeyToExit();
            for (int m = 0; m < 3; ++m) {
                printf("system will return to the first interface after %d seconds\n", 3 - m);
                sleep_s(1000);
            }
            clear_screen();
            return manage_info(library);

        case 'h':
        case 'H':
            printf("==========Welcome to save the library==========\n");
            if (save_to_file(library) == -1) {
                printf("Failed to save the library!\n");
                printf("================================================\n");
                PressAnyKeyToExit();
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
            }
            else {
                printf("Save the library success!\n");
                printf("================================================\n");
                PressAnyKeyToExit();
                for (int m = 0; m < 3; ++m) {
                    printf("system will return to the first interface after %d seconds\n", 3 - m);
                    sleep_s(1000);
                }
                clear_screen();
            }
            return manage_info(library);

        case 'i':
        case 'I':
            printf("==========Welcome to delete the library==========\n");
            printf("Are you sure to delete the library?\n");
            printf("- [y] Yes\n");
            printf("- [n] No\n");
            printf("Please enter your choice: ");
            char choice_delete = getchar();
            flush_s();
            switch (choice_delete) {
                case 'y':
                case 'Y':
                    printf("Please enter the admin password\n");
                    char* password = getPassword();
                    if (checkPassword("admin", password)) {
                        char temp[BOOK_LIBRARY_LEN];
                        strcpy(temp, library->name);
                        strcat(temp, ".lib");
                        remove(temp);
                        freelibrary(library);
                        printf("Delete the library success!\n");
                        printf("================================================\n");
                        PressAnyKeyToExit();
                        for (int m = 0; m < 3; ++m) {
                            printf("system will return to the first interface after %d seconds\n", 3 - m);
                            sleep_s(1000);
                        }
                        clear_screen();
                        return main_info();
                    }
                    printf("The password is incorrect!\n");
                    printf("================================================\n");
                    PressAnyKeyToExit();
                    for (int m = 0; m < 3; ++m) {
                        printf("system will return to the first interface after %d seconds\n", 3 - m);
                        sleep_s(1000);
                    }
                    clear_screen();
                    return manage_info(library);
                case 'n':
                case 'N':
                    printf("================================================\n");
                    PressAnyKeyToExit();
                    for (int m = 0; m < 3; ++m) {
                        printf("system will return to the first interface after %d seconds\n", 3 - m);
                        sleep_s(1000);
                    }
                    clear_screen();
                    return manage_info(library);
                default:
                    printf("Invalid input!\n");
                    printf("Please try again!\n");
                    printf("Please wait for 1 seconds\n");
                    sleep_s(1000);
                    clear_screen();
                    return manage_info(library);
            }

        case 'j':
        case 'J':
            printf("The version of the library is %s\n", VERSION);
            printf("================================================\n");
            PressAnyKeyToExit();
            for (int m = 0; m < 3; ++m) {
                printf("system will return to the first interface after %d seconds\n", 3 - m);
                sleep_s(1000);
            }
            clear_screen();
            return manage_info(library);

        case 'k':
        case 'K':
            printf("The information of the manage systhem is as follows:\n");
            printf("================================================\n");
            printf("The version of the manage systhem is %s\n", VERSION);
            printf("The author of the manage systhem is %s\n", AUTHOR);
            printf("The email of the author is %s\n", EMAIL);
            printf("================================================\n");
            PressAnyKeyToExit();
            for (int m = 0; m < 3; ++m) {
                printf("system will return to the first interface after %d seconds\n", 3 - m);
                sleep_s(1000);
            }
            clear_screen();
            return manage_info(library);

        case 'l':
        case 'L':
            printf("Do you want to save the library?\n");
            printf(" - [y] Yes\n");
            printf(" - [n] No\n");
            printf("Please enter your choice: ");
            char choice_save = getchar();
            flush_s();
            switch (choice_save) {
                case 'y':
                case 'Y':
                    if (save_to_file(library) == -1) {
                        printf("Failed to save the library!\n");
                        printf("================================================\n");
                        PressAnyKeyToExit();
                        for (int m = 0; m < 3; ++m) {
                            printf("system will return to the first interface after %d seconds\n", 3 - m);
                            sleep_s(1000);
                        }
                        clear_screen();
                    }
                    else {
                        freelibrary(library);
                        printf("Save the library success!\n");
                        printf("================================================\n");
                        PressAnyKeyToExit();
                        for (int m = 0; m < 3; ++m) {
                            printf("system will return to the first interface after %d seconds\n", 3 - m);
                            sleep_s(1000);
                        }
                        clear_screen();
                        return main_info();
                    }

                case 'n':
                case 'N':
                    printf("================================================\n");
                    PressAnyKeyToExit();
                    for (int m = 0; m < 3; ++m) {
                        printf("system will return to the first interface after %d seconds\n", 3 - m);
                        sleep_s(1000);
                    }
                    clear_screen();
                    return main_info();
                default:
                    printf("Invalid input!\n");
                    printf("Please try again!\n");
                    printf("Please wait for 1 seconds\n");
                    sleep_s(1000);
                    clear_screen();
                    return manage_info(library);
            }

        default:
            printf("Invalid input!\n");
            printf("Please try again!\n");
            printf("Please wait for 1 seconds\n");
            sleep_s(1000);
            clear_screen();
            return manage_info(library);
    }
}
