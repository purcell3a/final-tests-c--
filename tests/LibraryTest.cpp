#include "Library.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

// TestLibraryFull()
// - Library correctly enforces MAX_BOOKS capacity
// - Adding beyond capacity doesn't increase count
// - Overflow book is NOT added (search returns nullptr)
// What it catches: Buffer overflows, capacity enforcement bugs, vector growth issues

void TestLibraryFull() {
    Library lib;
    const int cap = lib.GetCapacity();
    for (int i = 0; i < cap; i++) {
        lib.AddBook("B" + std::to_string(i), "A", 2000, 1);
    }
    assert(lib.GetBookCount() == cap);
    lib.AddBook("Overflow", "A", 2000, 1);
    assert(lib.GetBookCount() == cap); // must NOT increase
    assert(lib.FindBookByTitle("Overflow") == nullptr);
    std::cout << "TestLibraryFull passed.\n";
}

struct CoutRedirect {
    std::streambuf* old;
    CoutRedirect(std::ostringstream& o) : old(std::cout.rdbuf(o.rdbuf())) {}
    ~CoutRedirect() { std::cout.rdbuf(old); }
};

// TestDisplayBooksEmptyOutput()
// - Empty library displays "No books in the library."
// - Uses output redirection to capture and verify console output
// What it catches: Missing empty-state handling, incorrect output messages

void TestDisplayBooksEmptyOutput() {
    Library lib;
    std::ostringstream out;
    {
        CoutRedirect guard(out);
        lib.DisplayBooks();
    } // cout restored here
    assert(out.str().find("No books in the library.") != std::string::npos);
    std::cout << "TestDisplayBooksEmptyOutput passed.\n";
}

// TestAddBook()
// -  Book count increases after adding
// -  Book can be found by title after adding
// - All Book fields are stored correctly (title, author, year, copies)
// -  copiesCheckedOut initializes to 0
// - What it catches: Broken constructor, incorrect field assignment, search failures

void TestAddBook() {
    Library lib;
    lib.AddBook("Test Book", "Test Author", 2020, 2);
    assert(lib.GetBookCount() == 1);
    const Book* b = lib.FindBookByTitle("Test Book");
    assert(b != nullptr);
    assert(b->title == "Test Book");
    assert(b->author == "Test Author");
    assert(b->publicationYear == 2020);
    assert(b->copiesAvailable == 2);
    assert(b->copiesCheckedOut == 0);
    std::cout << "TestAddBook passed.\n";
}

// TestRemoveBook()
// - Book count decreases after removal
// - Removed book is actually gone (can't be found)
// - Removing non-existent book doesn't crash the program
// What it catches: Memory leaks, dangling pointers, removal logic errors, crash on edge cases

void TestRemoveBook() {
    Library lib;
    lib.AddBook("Book1", "Author1", 2000, 1);
    lib.RemoveBook("Book1");
    assert(lib.GetBookCount() == 0);
    assert(lib.FindBookByTitle("Book1") == nullptr);
    lib.RemoveBook("Book1"); // Should not crash
    std::cout << "TestRemoveBook passed.\n";
}

// TestBorrowBook()
// - Available copies decrease when borrowed
// - Checked-out copies increase when borrowed
// - Can't borrow when no copies available (counts stay the same)
// - Borrowing non-existent book doesn't crash
// What it catches: Off-by-one errors, counter logic, edge case handling

void TestBorrowBook() {
    Library lib;
    lib.AddBook("Book2", "Author2", 2010, 1);
    lib.BorrowBook("Book2");
    const Book* b = lib.FindBookByTitle("Book2");
    assert(b && b->copiesAvailable == 0 && b->copiesCheckedOut == 1);
    lib.BorrowBook("Book2");
    b = lib.FindBookByTitle("Book2");
    assert(b && b->copiesAvailable == 0 && b->copiesCheckedOut == 1);
    lib.BorrowBook("Nonexistent");
    std::cout << "TestBorrowBook passed.\n";
}

// TestDisplayBooks()
// - Empty library has count of 0
// - After adding, count is correct
// - Added book exists and is findable
// What it catches: Basic state consistency

void TestDisplayBooks() {
    Library lib;
    assert(lib.GetBookCount() == 0);
    // You could redirect std::cout to test output, but here we just check state
    lib.AddBook("Book3", "Author3", 2022, 3);
    assert(lib.GetBookCount() == 1);
    const Book* b = lib.FindBookByTitle("Book3");
    assert(b != nullptr);
    std::cout << "TestDisplayBooks passed.\n";
}

int main() {
    TestAddBook();
    TestRemoveBook();
    TestBorrowBook();
    TestDisplayBooks();
    TestLibraryFull();
    TestDisplayBooksEmptyOutput();
    std::cout << "All tests completed.\n";
    return 0;
}
