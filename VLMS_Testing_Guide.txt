
## How to Test the Virtual Library Management System (VLMS) Program

### 1. Pre-Test Setup
- Ensure the development environment is correctly set up (C++ compiler, IDE, etc.).
- Verify that the main.cpp file is error-free and compiles successfully.
- Prepopulate the `users` map with test users for login testing:
  ```cpp
  users["admin"] = User("admin", "admin", "admin");
  users["user1"] = User("user1", "password", "user");
  ```

### 2. PreLoginMenu Testing
#### Objective:
Test the user registration, login, and navigation functionalities before logging in.

#### Steps:
1. Start the Program:
   - Run the compiled program.
   - Ensure the pre-login menu displays correctly.

2. Register a New User:
   - Select the "Register" option.
   - Enter a new username and password.
   - Verify that a success message is displayed and the user is added to the `users` map.

3. Login with Existing User:
   - Select the "Login" option.
   - Enter valid credentials for both admin and regular user roles.
   - Verify that the correct menu (admin or user) is displayed based on the user role.

4. Login with Invalid Credentials:
   - Attempt to log in with incorrect usernames and/or passwords.
   - Verify that an error message is displayed.

5. Exit the Program:
   - Select the "Exit" option.
   - Ensure the program terminates correctly.

### 3. User Menu Testing
#### Objective:
Test the functionalities available to regular users after logging in.

#### Steps:
1. Login as a Regular User:
   - Use credentials for a user (e.g., `user1`).
   - Ensure the user menu is displayed correctly.

2. Test Each User Menu Option:
   - Search for Books: Verify that the placeholder message "Searching for books..." is displayed.
   - Borrow a Book: Verify that the placeholder message "Borrowing a book..." is displayed.
   - Return a Book: Verify that the placeholder message "Returning a book..." is displayed.
   - View Borrowed Books: Verify that the placeholder message "Viewing borrowed books..." is displayed.
   - Update Profile: Verify that the placeholder message "Updating profile..." is displayed.
   - Logout: Ensure the user is logged out and returned to the pre-login menu.

3. Invalid Choices:
   - Enter invalid menu choices (e.g., numbers outside the provided options).
   - Verify that an error message is displayed.

### 4. Admin Menu Testing
#### Objective:
Test the functionalities available to admin users.

#### Steps:
1. Login as Admin:
   - Use admin credentials (e.g., `admin`).
   - Ensure the admin menu is displayed correctly.

2. Test Each Admin Menu Option:
   - Add a Book: Verify that the placeholder message "Adding a book..." is displayed.
   - Remove a Book: Verify that the placeholder message "Removing a book..." is displayed.
   - Update Book Information: Verify that the placeholder message "Updating book information..." is displayed.
   - View All Loans: Verify that the placeholder message "Viewing all loans..." is displayed.
   - Add/Remove User (Admins): Verify that the placeholder message "Managing users..." is displayed.
   - Logout: Ensure the admin is logged out and returned to the pre-login menu.

3. Invalid Choices:
   - Enter invalid menu choices (e.g., numbers outside the provided options).
   - Verify that an error message is displayed.

### 5. General Considerations
- Error Handling: Test how the program handles incorrect inputs at various stages.
- Input Validation: Ensure all inputs (e.g., usernames, passwords) are validated correctly.
- User Experience: Verify the clarity and usability of messages and prompts displayed to users.

### Questions for the Tester
1. Are there any specific edge cases or scenarios you want to ensure are tested (e.g., maximum username/password length)?
2. Do you have a specific list of book-related functionalities that need to be tested beyond the placeholders?
3. Should any additional user roles or permissions be tested?
4. Are there any known issues or limitations in the current implementation that should be documented during testing?

### Conclusion
This guide outlines a comprehensive approach to testing the VLMS program, ensuring that all major functionalities and user interactions are verified. By following these steps, you can ensure the program works as intended and provides a smooth user experience.
