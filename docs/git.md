# Notes on Working with git in the Terminal
 
Here are some common tasks to use when working with git and GitHub. Be sure you are executing these commands on your Raspberry Pi in the Terminal (CLI). And you are using the SSH forms of github, **NOT https://** as in:

* ssh form: `git@github.com:lkoepsel/AVR_C.git`
* https: form: `https://github.com/lkoepsel/AVR_C.git`

## Turn this repository into your own (non-forking addition)
```bash
# copy repo to your system
git clone git@github.com:lkoepsel/AVR_C.git

# change to the repo folder
cd AVR_C

# confirm and everything has checked in
git status

# remove git tracking, be sure you want to do this!
rm -rf .git

# this will now be a fatal error
git status

# initialize the folder as a git directory
git init

# stage the contents
git add -A

# commit them with the usual message
git commit -m "initial commit"

## In browser open your github instance 
# and add a new repo, AVR_C using the browser

# per Github, execute the following three commands to
# connect your remote repo to the local hub
git remote add origin git@github.com:your_github_ID/AVR_C.git
git branch -M main
git push -u origin main
```

## Add your public key to GitHub (on Raspberry PI)
Use this command to create a key on your Raspberry Pi then save it via your browser to your *Settings -> SSH and GPG keys -> New SSH key*. Just save the last line printed below which will start with "ssh-...." and end with your email address.

```bash
ssh-keygen -t ed25519 -C "youremail@yourdomain.com" && eval "$(ssh-agent -s)" && ssh-add ~/.ssh/id_ed25519 && cat ~/.ssh/id_ed25519.pub
# *** in Browser copy/paste public key into settings on GitHub ***
```

## Three Commands to Add Changes
Use these three commands periodically to save your changes and push them to your remote repository. 
```bash
# 1. stage your changes
git add -A

# 2. commit your staged changes
git commit -m "message is appropriate to changes"

# 3. push to remote repository
git push
```

## Fix a HTTPS form back to SSH form
Confirm the form of the url for your remote, if it has *https* in the name, it is in the wrong form, to use with *SSH authentication*.
```bash
# confirm the form of the url for your remote
git remote -v

# change it to be the desired SSH
git remote set-url origin git@github.com:lkoepsel/AVR_C.git

# confirm the form is now the correct *ssh* URL
git remote -v

# now you may push to your heart's content
```
