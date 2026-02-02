#include "Library.h"
#include <iostream>

int main() {
    // Create a library
    Library myLibrary;
    
    // Add some books
    myLibrary.AddBook("1984", "George Orwell", 1949, 3);
    myLibrary.AddBook("To Kill a Mockingbird", "Harper Lee", 1960, 2);
    myLibrary.AddBook("The Great Gatsby", "F. Scott Fitzgerald", 1925, 5);
    
    // Display all books
    myLibrary.DisplayBooks();
    
    // Borrow a book
    myLibrary.BorrowBook("1984");
    myLibrary.BorrowBook("1984");
    
    // Display updated inventory
    myLibrary.DisplayBooks();
    
    // Try to borrow a book that doesn't exist
    myLibrary.BorrowBook("Nonexistent Book");
    
    // Remove a book
    myLibrary.RemoveBook("The Great Gatsby");
    
    // Display final inventory
    myLibrary.DisplayBooks();
    
    return 0;
}