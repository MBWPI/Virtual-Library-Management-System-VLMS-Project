
# Project Report: Git Commands and Version Control

## Setting Up a GitHub Repository from a Local Repository

1. **`git init`**
   - This command we used to initialize a new Git repository in the current directory. We used this to set up the repository in the group project folder on our local hard drive.

2. **`git remote add origin https://github.com/MBWPI/Virtual-Library-Management-System-VLMS-Project.git`**
   - This command is used to add a remote repository URL to your local Git repository. We used this to sync the GitHub repository to our local group project folder.

3. **`git pull origin main`**
   - This command is used to fetch and integrate changes from the remote repository to the local repository. We used this to sync the latest changes from the GitHub repository to our local group project folder.

4. **`git checkout Version-4`**
   - This command is used to switch to the specified branch. We used this to switch to the current group project branch in our local repository.

5. **`git add .`**
   - This command is used to stage all the changes in the working directory for the next commit. We used this to stage all the files in the group project folder for the initial commit.

6. **`git commit -m 'Initial commit'`**
   - This command is used to commit the staged changes with a descriptive message. We used this to make the initial commit of all the files in the  group project folder.

7. **`git push origin Version-4`**
   - This command is used to push the committed changes to the specified branch on the remote repository. We used this to push the initial commit to the  current group project branch on the GitHub repository.

## Git Commit Messages

**Used Meaningful Commit Messages**

1. **`git commit -m 'Initial commit'`**
   - This command is used to commit the staged changes with a descriptive message. We used this to make the initial commit of all the files in the  group project folder.
   
2. **`git commit -m 'Git Documentation commit'`**
   - We used this to commit all of the Git commands documentation for commands used in this project.
   
3. **`git commit -m 'Git README commit'`**
   - We used this to commit the README which contains information about this project.

## Technical Requirements

**Version Control with Git:**

1. **Initialize a Git Repository:**
   - To start version control for the project, initialize a Git repository in the project directory.
   - Command: `git init`
   
2. **Clone a Repository:**
   - To clone an existing repository from a platform like GitHub to your local machine.
   - Command: `git clone <repository_url>`
   
3. **Add Remote Repository:**
   - To link the local repository to a remote repository on GitHub.
   - Command: `git remote add origin <repository_url>`

4. **Check Repository Status:**
   - To check the status of files in the working directory and staging area.
   - Command: `git status`

5. **Stage Changes:**
   - To stage changes (files that have been modified or newly added) for the next commit.
   - Command: `git add <file_name>` or `git add .` (to stage all changes)

6. **Commit Changes:**
   - To commit the staged changes with a meaningful message.
   - Command: `git commit -m "Your commit message"`

7. **Push Changes:**
   - To push the committed changes to the remote repository on GitHub.
   - Command: `git push origin <branch_name>`

8. **Pull Changes:**
   - To pull the latest changes from the remote repository to your local repository.
   - Command: `git pull origin <branch_name>`

9. **Branching:**
   - To create a new branch for development or features.
   - Command: `git branch <branch_name>`
   - To switch to a specific branch.
   - Command: `git checkout <branch_name>`
   - To create and switch to a new branch in one step.
   - Command: `git checkout -b <branch_name>`

10. **Merge Branches:**
    - To merge changes from one branch into another (typically merging a feature branch into the main branch).
    - Command: `git merge <branch_name>`

11. **View Commit History:**
    - To view the commit history for the repository.
    - Command: `git log`

12. **Tagging:**
    - To create a tag for marking specific points in the repository’s history, such as releases.
    - Command: `git tag <tag_name>`

## Deliverables

**Source Code Management:**

1. **Regular Commits:**
   - Ensure that commits are made frequently to capture incremental changes.
   - Each commit should have a meaningful message that accurately describes the changes made.
   
2. **Meaningful Commit Messages:**
   - Commit messages should follow a consistent format and convention, such as using present tense and being concise yet descriptive.

**Example Commit Message Format:**
```
Add feature for user login
Fix bug in user registration
Update documentation for installation process
```

**Steps for Managing Source Code:**

1. **Initialize Repository:**
   - `git init`
   - Set up the initial repository and add a remote.
   - `git remote add origin <repository_url>`

2. **Initial Commit:**
   - Stage and commit initial project files.
   - `git add .`
   - `git commit -m "Initial commit - add project structure"`

3. **Regular Development Workflow:**
   - **Create a Feature Branch:**
     - `git checkout -b feature/add-login`
   - **Make Changes and Stage Them:**
     - `git add <modified_files>`
   - **Commit Changes:**
     - `git commit -m "Add login functionality"`
   - **Push Feature Branch to Remote:**
     - `git push origin feature/add-login`

4. **Collaborate and Merge:**
   - **Pull Latest Changes from Main Branch:**
     - `git pull origin main`
   - **Resolve Conflicts (if any) and Commit:**
     - `git add .`
     - `git commit -m "Resolve merge conflicts"`
   - **Merge Feature Branch into Main Branch:**
     - `git checkout main`
     - `git merge feature/add-login`
   - **Push Merged Changes to Remote:**
     - `git push origin main`

5. **Tagging Releases:**
   - `git tag v1.0.0`
   - `git push origin v1.0.0`

## Conclusion

Utilizing Git for version control ensures that the project's source code is managed efficiently, facilitating collaboration, version tracking, and ensuring a robust history of changes. Regular commits with meaningful messages and proper branch management are crucial for maintaining a clear and organized development workflow. Hosting the repository on a platform like GitHub enhances accessibility and collaboration among team members.
