# Notes on Working with git

Here are some common tasks to use when working with git and GitHub.

## Turn this repository into your own (non-forking addition)
```bash
git clone git@github.com:lkoepsel/AVR_C.git
cd AVR_C
git status
rm -rf .git
git status
git init
git add -A
git commit -m "initial commit"
## In browser open github and add a new repo via browser
git remote add origin git@github.com:your_github_ID/AVR_C.git
git branch -M main
git push -u origin main
```

## Add your public key to GitHub (on Raspberry PI)
```bash
ssh-keygen -t ed25519 -C "youremail@yourdomain.com" && eval "$(ssh-agent -s)" && ssh-add ~/.ssh/id_ed25519 && cat ~/.ssh/id_ed25519.pub
# *** in Browser copy/paste public key into settings on GitHub ***
```

## Three Commands to Add Changes
```bash
# stage your changes
git add -A

# commit your staged changes
git commit -m "message is appropriate to changes"

# push to repository
git push
```
