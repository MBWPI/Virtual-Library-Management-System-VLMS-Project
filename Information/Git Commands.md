# Git Commands

// Creates a new Git repository
git init

// Clones a repository with a git clone
git remote add origin https://github.com/MBWPI/Virtual-Library-Management-System-VLMS-Project.git

// Removes remotes
git remote rm origin

// Combined local unpublished changes with the latest remote published changes
// Resolves any conflicts if prompted and continue the rebase 
git pull --rebase origin main

// Integrates the changes to from the local repositories to remote repositories
git push -u origin main

// Deletes Credentials (Deletes stored user/logs out)
git config --local credential.helper ""
git config --global --unset credential.helper

// Enables credential storage on Git, next time push/pull asks for user and pass it will store to auto login following push/pull
git config --global credential.helper store



// IF CONFLICT WITH PUSH OR SYNCING TO LOCAL
git add .
git commit -m 'message'
git pull --rebase origin main
git push -u origin main

// Checks status?
git status -v

// Git remote status
git remote -v

// Sets email
git config --global user.email "temp@temp.com"

// Sets name
git config --global user.name "temp"

// Git reset
git reset --hard

// Git pull (potential (windows) git command fix)
git pull origin main
