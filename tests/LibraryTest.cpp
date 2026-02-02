#include "Library.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

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

void TestRemoveBook() {
    Library lib;
    lib.AddBook("Book1", "Author1", 2000, 1);
    lib.RemoveBook("Book1");
    assert(lib.GetBookCount() == 0);
    assert(lib.FindBookByTitle("Book1") == nullptr);
    lib.RemoveBook("Book1"); // Should not crash
    std::cout << "TestRemoveBook passed.\n";
}

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
