# Library Management System - Assignment

## Objective

Your task is to design and implement a C++ class that manages a library's book inventory using smart pointers (`std::unique_ptr`) and object-oriented programming principles. You will create a `Book` struct to store basic book information and a `Library` class that maintains an array of unique pointers to `Book` objects.

---

## Requirements

### Naming Conventions

Throughout this assignment, you must adhere to the requested naming convention:

* **Fields**: Use `mixedCamelCase` for naming your public data fields. 
  - Example: `title`, `author`
* **Private Fields**: Use `_mixedCamelCase` for naming your private data fields. 
  - Example: `_books`
* **Methods**: Use `UpperCamelCase` for naming your methods. 
  - Example: `GetTitle()`, `SetTitle()`

**⚠️ Failure to follow naming conventions will result in a loss of points.**

---

## `Book` Struct (Defined in `Library.h`)

Define a `Book` struct that contains the following public data fields:

* `title` (`std::string`) – The title of the book
* `author` (`std::string`) – The author of the book
* `publicationYear` (`int`) – The year the book was published
* `copiesAvailable` (`int`) – The number of copies available in the library
* `copiesCheckedOut` (`int`) – The number of copies that have been checked out

**This struct must have a constructor that initializes all fields when a `Book` object is created.**

---

## `Library` Class (Defined in `Library.h`, Implemented in `Library.cpp`)

Create a `Library` class that manages an inventory of books using `std::unique_ptr<Book>`.

### The class must:

* Store an array (or vector) of `std::unique_ptr<Book>` to manage dynamically allocated books
* Track the current number of books in the library
* Use smart pointers (`std::unique_ptr<Book>`) to manage memory automatically
* Encapsulate all data members (they must be private)

---

## Required Methods for Library

### Constructor

* A default constructor that initializes an empty library

### A method to add a book

* **Name**: `AddBook`
* **Return Type**: `void`
* **Parameters**:
  * `std::string title` – The book's title
  * `std::string author` – The book's author
  * `int publicationYear` – The year the book was published
  * `int copiesAvailable` – The number of copies available
* **Behavior**:
  * Creates a new `Book` object dynamically using `std::make_unique<Book>()` and adds it to the library's inventory
  * If the library is full, prints an error message

### A method to remove a book

* **Name**: `RemoveBook`
* **Return Type**: `void`
* **Parameters**:
  * `std::string title` – The title of the book to remove
* **Behavior**:
  * Searches for a book by title and removes it from the inventory
  * The `std::unique_ptr` should automatically handle memory deallocation

### A method to borrow a book from the library

* **Name**: `BorrowBook`
* **Return Type**: `void`
* **Parameters**:
  * `std::string title` – The title of the book to check out
* **Behavior**:
  * Searches for the book by title
  * If at least one copy is available, decreases `copiesAvailable` and increases `copiesCheckedOut`
  * Prints a message describing why a book can't be checked out (either not in library or no copies available)

### A method to display info about all the books in the library

* **Name**: `DisplayBooks`
* **Return Type**: `void`
* **Parameters**: None
* **Behavior**:
  * Prints details of all books currently in the library
  * If the library is empty, prints `"No books in the library."`

---

## Submission Guidelines

You must submit two separate files on Canvas:

1. **`Library.h`** – Contains the declaration of the `Book` struct and `Library` class
2. **`Library.cpp`** – Contains the implementation of the `Library` class methods

**Your program must use `std::unique_ptr<Book>` for memory management. Do not use raw pointers or `new`/`delete`.**

---

## Grading Breakdown (20 pts)

| Criteria | Points |
|----------|--------|
| Includes comment with name and assignment number/description | 2 pts |
| Adhere to the requested naming conventions | 3 pts |
| Proper `Book` struct definition in `Library.h` | 3 pts |
| Proper `Library` class implementation | 3 pts |
| Proper encapsulation of `Library` class data members | 3 pts |
| Correct implementation of `AddBook`, `RemoveBook`, `BorrowBook` methods | 4 pts |
| Proper separation of `Library.h` and `Library.cpp` | 2 pts |
| **Total** | **20 pts** |

---

## Notes

- Use modern C++ features (`std::unique_ptr`, `std::make_unique`)
- Follow proper object-oriented design principles
- Test your code thoroughly before submission
- Ensure proper memory management (no memory leaks)