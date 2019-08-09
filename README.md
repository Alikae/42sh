# 42sh
___
	
- sh  [-abCefhimnuvx]  [-o option]...  [+abCefhimnuvx]  [+o option]...  [script [arg...]]
- sh  [-abCefhimnuvx]  [-o option]...  [+abCefhimnuvx]  [+o option]...  -c [command_name [arg...]]
- sh  [-abCefhimnuvx]  [-o option]...  [+abCefhimnuvx]  [+o option]...  -s [arg...]

# MAN
- http://pubs.opengroup.org/onlinepubs/9699919799/

### COMMIT CONVENTION
- ADD | MAJ | FIX | EDT | RMV
- (ex: "FIX file_name your_stuff")
- (you can add more in githistory.txt)

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

|		STATUS     		| NAME |
|-----------------------|----------|
|		:cyclone:		|	a	|
|		:cyclone:		|	b	|
|		:cyclone:		|	c	|
|		:cyclone:		|	C	|
|		:cyclone:		|	e	|
|		:cyclone:		|	f	|
|		:cyclone:		|	h	|
|		:cyclone:		|	i	|
|		:cyclone:		|	m	|
|		:cyclone:		|	n	|
|		:cyclone:		|	o	|
|		:cyclone:		|	s	|
|		:cyclone:		|	u	|
|		:cyclone:		|	v	|
|		:cyclone:		|	x	|
|		:cyclone:		|	noediting	|
|		:cyclone:		|	poisx	|

#### - Built-in
|		STATUS     		| NAME |
|-----------------------|----------|
|		:cyclone:		|	admin	|
|		:cyclone:		|	alias	|
|		:cyclone:		|	ar	|
|		:cyclone:		|	asa	|
|		:cyclone:		|	at	|
|		:cyclone:		|	awk	|
|		:cyclone:		|	basename	|
|		:cyclone:		|	batch	|
|		:cyclone:		|	bc	|
|		:cyclone:		|	bg	|
|		:cyclone:		|	break	|
|		:cyclone:		|	c99	|
|		:cyclone:		|	cal	|
|		:cyclone:		|	cat	|
|		:zap:			|	cd	|
|		:cyclone:		|	cflowi |
|		:cyclone:		|	chgrp	|
|		:cyclone:		|	chmod	|
|		:cyclone:		|	chown	|
|		:cyclone:		|	cksum	|
|		:cyclone:		|	cmp		|
|		:cyclone:		|	colon	|
|		:cyclone:		|	comm	|
|		:cyclone:		|	command	|
|		:cyclone:		|	compress	|
|		:cyclone:		|	continue	|
|		:cyclone:		|	cp	|
|		:cyclone:		|	crontab	|
|		:cyclone:		|	csplit	|
|		:cyclone:		|	ctags	|
|		:cyclone:		|	cut	|
|		:cyclone:		|	cxref	|
|		:cyclone:		|	date	|
|		:cyclone:		|	dd	|
|		:cyclone:		|	delta	|
|		:cyclone:		|	df	|
|		:cyclone:		|	diff	|
|		:cyclone:		|	dirname	|
|		:cyclone:		|	dot	|
|		:cyclone:		|	du	|
|		:cyclone:		|	echo	|
|		:cyclone:		|	ed	|
|		:zap:			|	env	|
|		:cyclone:		|	eval	|
|		:cyclone:		|	ex	|
|		:cyclone:		|	exec	|
|	:heavy_check_mark:	|	exit	|
|		:cyclone:		|	expand	|
|			:zap:		|	export	|
|		:cyclone:		|	expr	|
|	:heavy_check_mark:	|	false	|
|		:cyclone:		|	fc	|
|		:cyclone:		|	fg	|
|		:cyclone:		|	file	|
|		:cyclone:		|	find	|
|		:cyclone:		|	fold	|
|		:cyclone:		|	fort77	|
|		:cyclone:		|	fuser	|
|		:cyclone:		|	gencat	|
|		:cyclone:		|	get	|
|		:cyclone:		|	getconf	|
|		:cyclone:		|	getopts	|
|		:cyclone:		|	grep	|
|		:cyclone:		|	hash	|
|		:cyclone:		|	head	|
|		:cyclone:		|	iconv	|
|		:cyclone:		|	id	|
|		:cyclone:		|	ipcrm	|
|		:cyclone:		|	ipcs	|
|		:cyclone:		|	jobs	|
|		:cyclone:		|	join	|
|		:cyclone:		|	kill	|
|		:cyclone:		|	lex	|
|		:cyclone:		|	link	|
|		:cyclone:		|	ln	|
|		:cyclone:		|	locale	|
|		:cyclone:		|	localedef	|
|		:cyclone:		|	logger	|
|		:cyclone:		|	logname	|
|		:cyclone:		|	lp	|
|		:cyclone:		|	ls 	|
|		:cyclone:		|	m4	|
|		:cyclone:		|	mailx |
|		:cyclone:		|	make |
|		:cyclone:		|	man	|
|		:cyclone:		|	mesg	|
|		:cyclone:		|	mkdir	|
|		:cyclone:		|	mkfifo	|
|		:cyclone:		|	more	|
|		:cyclone:		|	mv	|
|		:cyclone:		|	newgrp	|
|		:cyclone:		|	nice	|
|		:cyclone:		|	nl	|
|		:cyclone:		|	nm	|
|		:cyclone:		|	nohup	|
|		:cyclone:		|	od	|
|		:cyclone:		|	paste	|
|		:cyclone:		|	patch	|
|		:cyclone:		|	pathchk	|
|		:cyclone:		|	pax	|
|		:cyclone:		|	pr	|
|		:cyclone:		|	printf	|
|		:cyclone:		|	prs	|
|		:cyclone:		|	ps	|
|		:cyclone:		|	pwd	|
|		:cyclone:		|	qalter	|
|		:cyclone:		|	qdel	|
|		:cyclone:		|	qhold	|
|		:cyclone:		|	qmove	|
|		:cyclone:		|	qmsg	|
|		:cyclone:		|	qrerun	|
|		:cyclone:		|	qrls	|
|		:cyclone:		|	qselect	|
|		:cyclone:		|	qsig	|
|		:cyclone:		|	qstat	|
|		:cyclone:		|	qsub	|
|		:cyclone:		|	read	|
|		:zap:			|	readonly	|
|		:cyclone:		|	renice	|
|		:cyclone:		|	return	|
|		:cyclone:		|	rm	|
|		:cyclone:		|	rmdel	|
|		:cyclone:		|	rmdir	|
|		:cyclone:		|	sact	|
|		:cyclone:		|	sccs	|
|		:cyclone:		|	sed	|
|		:zap:			|	set	|
|		:zap:			|	sh	|
|		:cyclone:		|	shift	|
|		:cyclone:		|	sleep	|
|		:cyclone:		|	sort	|
|		:cyclone:		|	split	|
|		:cyclone:		|	strings	|
|		:cyclone:		|	strip	|
|		:cyclone:		|	stty	|
|		:cyclone:		|	tabs	|
|		:cyclone:		|	tail	|
|		:cyclone:		|	talk	|
|		:cyclone:		|	tee	|
|		:cyclone:		|	test	|
|		:cyclone:		|	time	|
|		:cyclone:		|	times	|
|		:cyclone:		|	touch	|
|		:cyclone:		|	tput	|
|		:cyclone:		|	tr	|
|		:cyclone:		|	trap	|
|	:heavy_check_mark:	|	true	|
|		:cyclone:		|	tsort	|
|		:cyclone:		|	tty	|
|		:cyclone:		|	type	|
|		:cyclone:		|	ulimit	|
|		:cyclone:		|	umask	|
|		:cyclone:		|	unalias	|
|		:cyclone:		|	uname	|
|		:cyclone:		|	uncompress	|
|		:cyclone:		|	unexpand	|
|		:cyclone:		|	unget	|
|		:cyclone:		|	uniq	|
|		:cyclone:		|	unlink	|
|		:cyclone:		|	unset	|
|		:cyclone:		|	uucp	|
|		:cyclone:		|	uudecode	|
|		:cyclone:		|	uuencode	|
|		:cyclone:		|	uustat	|
|		:cyclone:		|	uux	|
|		:cyclone:		|	val	|
|		:cyclone:		|	vi	|
|		:cyclone:		|	wait	|
|		:cyclone:		|	wc	|
|		:cyclone:		|	what	|
|		:cyclone:		|	who	|
|		:cyclone:		|	write	|
|		:cyclone:		|	xargs	|
|		:cyclone:		|	yacc	|
|		:cyclone:		|	zcat	|

---
Made by: Ede-Ram Tcillard Tmeyer Thdelmas
---

### **GIT BRANCHING TUTO:**
- Good tuto: https://learngitbranching.js.org/
- Create new branch						:	git branch MyBranch
- go to a branch							:	git checkout MyBranch
- Do your ~~shit~~ commits
- merge BranchX to the branch where i am	:	git merge BranchX
