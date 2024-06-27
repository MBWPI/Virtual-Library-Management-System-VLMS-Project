#include "libraryOperations.h"
#include "bookDatabase.h"
#include "bst.h"
#include "user.h"
#include "userManagement.h"
#include "utility.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

void searchBooks() {
  std::cout << "\nSearching for books...\n";

  // Load the book database
  BookDatabase bookDb;

  // Insert books into a Binary Search Tree for efficient searching
  BST bookTree;
  for (const auto &book : bookDb.getAllBooks()) {
    bookTree.insert(book);
  }

  // Get the search term from the user
  std::string searchTitle;
  std::cout << "\nEnter the title of the book to search: ";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n'); // Clear any previous input
  std::getline(std::cin, searchTitle);

  // Search for the book in the BST
  Book *foundBook = bookTree.search(searchTitle);
  if (foundBook) {
    std::cout << "\nBook found:\n";
    std::cout << "Title: " << foundBook->getTitle() << "\n";
    std::cout << "Author: " << foundBook->getAuthor() << "\n";
    std::cout << "ISBN: " << foundBook->getISBN() << "\n";
    std::cout << "Year: " << foundBook->getYear() << "\n";
  } else {
    std::cout << "Book not found.\n";
  }
}

void borrowBook(UserManagement &&userManager, BookDatabase &&findBookByTitle) {
  std::cout << "\nBorrowing a book...\n";
  // Load the book database
  BookDatabase bookDb;
  // Get the username from the user
  std::string username;
  std::cout << "\nEnter your username: ";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // Find the user in the user management system
  User *user = userManager.findUser(username);
  if (!user) {
    std::cout << "User not found.\n";
    return;
  } else {
    std::cout << "User found.\n";
  }
  // Get the book title from the user
  std::string Title;
  std::cout << "\nEnter the title of the book to borrow: ";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::getline(std::cin, Title);
  // Find the book in the book database
  Book *book = bookDb.findBookByTitle(Title);
  if (!book) {
    std::cout << "Book not found.\n";
    return;
  } else {
    std::cout << "Book found.\n";
    std::cout << "Title: " << book->getTitle() << "\n";
    std::cout << "Would you like to borrow this book? (y/n): ";
    char choice;
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y') {
      if (bookDb.borrowBook(book->getTitle(), username)) {
        std::cout << "Book borrowed successfully.\n";
      } else {
        std::cout << "Failed to borrow the book.\n";
      }
    } else if (choice == 'n' || choice == 'N') {
      std::cout << "Book not borrowed.\n";
    } else {
      std::cout << "Invalid choice.\n";
    }
  }
}

bool BookDatabase::returnBook(const std::string &isbn,
                              const std::string &username) {
  auto &userBooks = borrowedBooks[username];
  auto it = std::find_if(userBooks.begin(), userBooks.end(),
                         [&](const Book &b) { return b.getISBN() == isbn; });
  if (it != userBooks.end()) {
    books.push_back(*it); // Add the book back to the library's collection
    userBooks.erase(it);  // Remove the book from the user's borrowed books
    saveBooksToFile("book_database.txt"); // Save changes to file
    return true;
  }
  return false; // Book not found in user's borrowed books
}
void viewBorrowedBooks(const std::string &username) {
  std::cout << "\nViewing borrowed books for user: " << username << "\n";

  // Assuming borrowedBooks is a member variable of BookDatabase
  BookDatabase bookDb;

  // Get the borrowed books for the user
  std::vector<Book> borrowedBooks = bookDb.getBorrowedBooks(username);

  // Print borrowed books
  if (!borrowedBooks.empty()) {
    std::cout << "Borrowed Books:\n";
    for (const auto &book : borrowedBooks) {
      std::cout << "Title: " << book.getTitle() << "\n";
      std::cout << "Author: " << book.getAuthor() << "\n";
      std::cout << "ISBN: " << book.getISBN() << "\n";
      std::cout << "Year: " << book.getYear() << "\n\n";
    }
  } else {
    std::cout << "No books borrowed.\n";
  }
}

void updateProfile(UserManagement &userManager) {
  std::string username, oldPassword, newPassword;

  std::cout << "\nUpdating profile...\n";
  std::cout << "Enter your username: ";
  std::cin >> username;

  User *user = userManager.findUser(username);
  if (!user) {
    std::cout << "User not found.\n";
    return;
  }

  std::cout << "Enter your old password: ";
  std::cin >> oldPassword;

  if (user->getPassword() != oldPassword) {
    std::cout << "Incorrect password.\n";
    return;
  }

  std::cout << "Enter new password: ";
  std::cin >> newPassword;

  userManager.updateUserProfile(username, newPassword);
}

void addBook() {
  std::cout << "\nAdding a book...\n";
  // Implement add book logic
  std::string title, author, isbn;
  int year;

  std::cout << "Enter the title of the book: ";
  std::cin.ignore();
  std::getline(std::cin, title);
  std::cout << "Enter the author of the book: ";
  std::getline(std::cin, author);
  std::cout << "Enter the ISBN of the book: ";
  std::getline(std::cin, isbn);
  std::cout << "Enter the year of publication: ";
  std::cin >> year;

  Book book(title, author, isbn, year);
  BookDatabase bookDb;
  bookDb.addBook(book);
  std::cout << "Book added successfully.\n";
}

void removeBook() {
  std::string isbn;
  std::cout << "Enter the ISBN of the book to remove: ";
  std::cin.ignore();
  std::getline(std::cin, isbn);

  BookDatabase bookDb;
  bookDb.removeBook(isbn);
  std::cout << "Book removed successfully.\n";
}

void updateBookInfo() {
  std::cout << "\nUpdating book information...\n";
  // Implement update book info logic
  std::string title, author, isbn;
  int year;

  std::cout << "Enter the ISBN of the book to update: ";
  std::cin.ignore();
  std::getline(std::cin, isbn);
  std::cout << "Enter the new title of the book: ";
  std::getline(std::cin, title);
  std::cout << "Enter the new author of the book: ";
  std::getline(std::cin, author);
  std::cout << "Enter the new year of publication: ";
  std::cin >> year;

  Book book(title, author, isbn, year);
  BookDatabase bookDb;
  bookDb.updateBook(book);
  std::cout << "Book information updated successfully.\n";
}

void viewAllLoans() {
  std::cout << "\nViewing all loans...\n";
  // Implement view all loans logic
}

void LibraryOperations::borrowBook(const Book &book) {
  borrowedBooks.push(book);
}

void LibraryOperations::returnBook() {
  if (!borrowedBooks.empty()) {
    borrowedBooks.pop();
  }
}

Book *LibraryOperations::getNextBorrowedBook() {
  if (!borrowedBooks.empty()) {
    return &borrowedBooks.front();
  }
  return nullptr;
}

// Data Persistence in Book Management
void LibraryOperations::saveBooksToFile(const std::string &filename) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open file for writing: " << filename << std::endl;
    return;
  }
  // Serialize book data
  file.close();
}

void LibraryOperations::loadBooksFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open file for reading: " << filename << std::endl;
    return;
  }
  // Deserialize book data
  file.close();
}
