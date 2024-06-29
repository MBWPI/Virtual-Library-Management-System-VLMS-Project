
# VLMS User Manual

## Introduction

The Virtual Library Management System (VLMS) allows users to manage books and user accounts within a virtual library. Users can search for books, borrow and return them, and view their borrowed books. Administrators have additional privileges to manage the book catalog and user accounts.

## Table of Contents

1. [Getting Started](#getting-started)
2. [User Operations](#user-operations)
    - [Login](#login)
    - [Register](#register)
    - [Search for Books](#search-for-books)
    - [Borrow a Book](#borrow-a-book)
    - [Return a Book](#return-a-book)
    - [View Borrowed Books](#view-borrowed-books)
    - [Update Profile](#update-profile)
3. [Admin Operations](#admin-operations)
    - [Add a Book](#add-a-book)
    - [Remove a Book](#remove-a-book)
    - [Update Book Information](#update-book-information)
    - [View All Loans](#view-all-loans)
    - [Manage Users](#manage-users)
4. [Technical Details](#technical-details)
    - [Transaction Logs](#transaction-logs)
5. [Troubleshooting](#troubleshooting)

## Getting Started

To use the VLMS, you will need to compile the source code and run the executable. Ensure you have all necessary dependencies installed, including the bcrypt library for password hashing.

### Compilation Instructions

1. **Install Dependencies:**
    - On Debian-based systems: `sudo apt-get install libbcrypt-dev`
    - On other systems, follow respective instructions to install bcrypt.

2. **Compile the Program:**
    ```sh
    make
    ```

3. **Run the Program:**
    ```sh
    ./vlms
    ```

## User Operations

### Login

1. Run the program and select the **Login** option.
2. Enter your username and password.
3. If the credentials are correct, you will be logged in. Otherwise, an error message will be displayed.

### Register

1. Run the program and select the **Register** option.
2. Enter a new username and password.
3. If the username does not already exist, your account will be created.

### Search for Books

1. After logging in, select the **Search for Books** option.
2. Enter the title of the book to search for.
3. A list of books matching the search query will be displayed, showing the title, author, ISBN, year, and quantity.

### Borrow a Book

1. After logging in, select the **Borrow a Book** option.
2. Enter the title of the book to borrow.
3. If the book is available, it will be borrowed and added to your borrowed books list.

### Return a Book

1. After logging in, select the **Return a Book** option.
2. Enter the title of the book to return.
3. If the last transaction for the book was a borrow transaction by you, the book will be returned and removed from your borrowed books list.

### View Borrowed Books

1. After logging in, select the **View Borrowed Books** option.
2. A list of books you have currently borrowed will be displayed.

### Update Profile

1. After logging in, select the **Update Profile** option.
2. Enter your new username and password.
3. Your profile will be updated, and any transactions associated with your old username will be updated to reflect the new username.

## Admin Operations

### Add a Book

1. Log in as an admin and select the **Add a Book** option.
2. Enter the book's title, author, ISBN, year, and quantity.
3. The book will be added to the library's catalog.

### Remove a Book

1. Log in as an admin and select the **Remove a Book** option.
2. Enter the ISBN of the book to remove.
3. The book will be removed from the library's catalog.

### Update Book Information

1. Log in as an admin and select the **Update Book Information** option.
2. Enter the ISBN of the book to update.
3. Enter the new title, author, year, and quantity for the book.
4. The book's information will be updated.

### View All Loans

1. Log in as an admin and select the **View All Loans** option.
2. A list of all borrowed books will be displayed.

### Manage Users

1. Log in as an admin and select the **Manage Users** option.
2. You can add or remove users by following the prompts.

### Transaction Logs

All transactions (borrow and return) are logged in the `transactions.txt` file. This file is used to determine the availability of books and to track borrowed books.

## Troubleshooting

1. **Invalid Username or Password:**
    - Ensure you are entering the correct username and password.
    - If you forgot your password, contact the admin to reset it.

2. **Book Not Available:**
    - If a book is not available, check if it is already borrowed by you or another user.

3. **Compilation Errors:**
    - Ensure all dependencies are installed.
    - Ensure your `Makefile` is correctly configured.

4. **Profile Update Issues:**
    - Ensure you are entering a valid new username and password.

If you encounter any issues not listed here, please contact one of the contributors for further assistance.

---

This user manual provides the basic steps to get started with the VLMS. For more advanced operations or further assistance, please refer to the source code documentation or contact the contributors.
