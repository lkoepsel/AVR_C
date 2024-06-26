# Notes on Working with git

## Turn this repository into your own (non-forking addition)
```bash
git clone git@github.com:lkoepsel/AVR_C.git
cd AVR_C
git status
rm -rf .git
git status
git init
git add -A
git commit "initial commit"
git remote add origin git@github.com:your_github_ID/AVR_C.git
git branch -M main
git push -u origin main
```

## Add your public key to GitHub (on Raspberry PI)
```bash
ssh-keygen -t ed25519 -C "youremail@yourdomain.com" && eval "$(ssh-agent -s)" && ssh-add ~/.ssh/id_ed25519 && cat ~/.ssh/id_ed25519.pub
# *** in Browser copy/paste public key into settings on GitHub ***
```
