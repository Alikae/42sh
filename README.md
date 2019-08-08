# 42sh
___

- sh  [-abCefhimnuvx]  [-o option]...  [+abCefhimnuvx]  [+o option]...  [script [arg...]]
- sh  [-abCefhimnuvx]  [-o option]...  [+abCefhimnuvx]  [+o option]...  -c [command_name [arg...]]
- sh  [-abCefhimnuvx]  [-o option]...  [+abCefhimnuvx]  [+o option]...  -s [arg...]

# MAN
- http://pubs.opengroup.org/onlinepubs/9699919799/

## GIT
### USE MAKE TO PUSH
- make gitsave GITCOM="ADD/FIX/RMV file commit"
- make savegit GITCOM="ADD/FIX/RMV file commit"
### COMMIT CONVENTION
- ADD | MAJ | FIX | EDT | RMV
- (ex: "FIX file_name your_stuff")
- (you can add more in githistory.txt)
### **GIT BRANCHING TUTO:**
- Good tuto: https://learngitbranching.js.org/
- Create new branch						:	git branch MyBranch
- go to a branch							:	git checkout MyBranch
- Do your ~~shit~~ commits
- merge BranchX to the branch where i am	:	git merge BranchX

___
#### - [ ] Env / Var 
- [ ] $SHELL 
- [ ] $SHLVL 
- [x] $PATH 
- [x] $PWD 
- [X] $OLDPWD
- [ ] $HOME
- [ ] $USER
- [ ] $PPID
- [ ] $
- [ ] $_
- [ ] $*
- [ ] $-
- [ ] $0
- [ ] $n
- [ ] $# 
- [ ] $@
- [ ] $? 
- [ ] $!
- [ ] $$
- [ ] ${}
- [ ] ${#}
- [ ] /dev/random

#### - [ ] Options
___
- [ ] -a
- [ ] -b
- [ ] -c
- [ ] -C
- [ ] -e
- [ ] -f
- [ ] -h
- [ ] -i
- [ ] -m
- [ ] -n
- [ ] -o
- [ ] -s
- [ ] -u
- [ ] -v
- [ ] -x
- [x] --noediting 
- [x] --posix 

#### - Built-in

|		STATUS     		| NAME |
|-----------------------|----------|
|	:heavy_check_mark:	| True |
|	:heavy_check_mark:	| False |
|	:zap:				| Cd |

#### - [ ] Fd
___
- [x] Stdin
- [ ] Stderr
- [ ] Stdout
- [ ] Pipe - Blocked
- [ ] Pipe - non-Blocked
- [ ] Pipe - Blocked
- [ ] Pipe - Broken
- [ ] /dev/null
---
Made by: Ede-Ram Tcillard Tmeyer Thdelmas
---
