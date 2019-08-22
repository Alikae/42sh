# 21sh
---
Made by: Ede-Ram Tcillard Tmeyer Thdelmas
---
	
- sh  [-abCefhimnuvx]  [-o option]...  [+abCefhimnuvx]  [+o option]...  [script [arg...]]
- sh  [-abCefhimnuvx]  [-o option]...  [+abCefhimnuvx]  [+o option]...  -c [command_name [arg...]]
- sh  [-abCefhimnuvx]  [-o option]...  [+abCefhimnuvx]  [+o option]...  -s [arg...]

# MAN
- http://pubs.opengroup.org/onlinepubs/9699919799/

### UNIT TESTS
- Placed here: './yourproject/unit_tests'
- 'make test' to run unit test ( then select 6 to be speed )
- Or run with: './unit_tests/utester.sh'
- Find your result in: './unit_tests/logs/unit_tests.report'

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
