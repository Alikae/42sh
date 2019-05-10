/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 15:48:58 by thdelmas          #+#    #+#             */
/*   Updated: 2019/04/23 16:00:53 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_FLAGS_H
# define SH21_FLAGS_H

/* Possible values for the `flags' field of a WORD_DESC. */
#define W_HASDOLLAR     0x000001        /* Dollar sign present. */
#define W_QUOTED        0x000002        /* Some form of quote character is present. */
#define W_ASSIGNMENT    0x000004        /* This word is a variable assignment. */
#define W_SPLITSPACE    0x000008        /* Split this word on " " regardless of IFS */
#define W_NOSPLIT       0x000010        /* Do not perform word splitting on this word because ifs is empty string. */
#define W_NOGLOB        0x000020        /* Do not perform globbing on this word. */
#define W_NOSPLIT2      0x000040        /* Don't split word except for $@ expansion (using spaces) because context does not allow it. */
#define W_TILDEEXP      0x000080        /* Tilde expand this assignment word */
#define W_DOLLARAT      0x000100        /* $@ and its special handling */
#define W_DOLLARSTAR    0x000200        /* $* and its special handling */
#define W_NOCOMSUB      0x000400        /* Don't perform command substitution on this word */
#define W_ASSIGNRHS     0x000800        /* Word is rhs of an assignment statement */
#define W_NOTILDE       0x001000        /* Don't perform tilde expansion on this word */
#define W_ITILDE        0x002000        /* Internal flag for word expansion */
#define W_NOEXPAND      0x004000        /* Don't expand at all -- do quote removal */
#define W_COMPASSIGN    0x008000        /* Compound assignment */
#define W_ASSNBLTIN     0x010000        /* word is a builtin command that takes assignments */
#define W_ASSIGNARG     0x020000        /* word is assignment argument to command */
#define W_HASQUOTEDNULL 0x040000        /* word contains a quoted null character */
#define W_DQUOTE        0x080000        /* word should be treated as if double-quoted */
#define W_NOPROCSUB     0x100000        /* don't perform process substitution */
#define W_SAWQUOTEDNULL 0x200000        /* word contained a quoted null that was removed */
#define W_ASSIGNASSOC   0x400000        /* word looks like associative array assignment */
#define W_ASSIGNARRAY   0x800000        /* word looks like a compound indexed array assignment */
#define W_ARRAYIND      0x1000000       /* word is an array index being expanded */
#define W_ASSNGLOBAL    0x2000000       /* word is a global assignment to declare (declare/typeset -g) */
#define W_NOBRACE       0x4000000       /* Don't perform brace expansion */
#define W_COMPLETE      0x8000000       /* word is being expanded for completion */
#define W_CHKLOCAL      0x10000000      /* check for local vars on assignment */
#define W_NOASSNTILDE   0x20000000      /* don't do tilde expansion like an assignment statement */

/* Flags for the `pflags' argument to param_expand() and various */
/*    parameter_brace_expand_xxx functions; also used for string_list_dollar_at */
#define PF_NOCOMSUB     0x01    /* Do not perform command substitution */
#define PF_IGNUNBOUND   0x02    /* ignore unbound vars even if -u set */
#define PF_NOSPLIT2     0x04    /* same as W_NOSPLIT2 */
#define PF_ASSIGNRHS    0x08    /* same as W_ASSIGNRHS */
#define PF_COMPLETE     0x10    /* same as W_COMPLETE, sets SX_COMPLETE */

/* Possible values for subshell_environment */
#define SUBSHELL_ASYNC  0x01    /* subshell caused by `command &' */
#define SUBSHELL_PAREN  0x02    /* subshell caused by ( ... ) */
#define SUBSHELL_COMSUB 0x04    /* subshell caused by `command` or $(command) */
#define SUBSHELL_FORK   0x08    /* subshell caused by executing a disk command */
#define SUBSHELL_PIPE   0x10    /* subshell from a pipeline element */
#define SUBSHELL_PROCSUB 0x20   /* subshell caused by <(command) or >(command) */
#define SUBSHELL_COPROC 0x40    /* subshell from a coproc pipeline */
#define SUBSHELL_RESETTRAP 0x80 /* subshell needs to reset trap strings on first call to trap */

/* Possible values for command->flags. */
#define CMD_WANT_SUBSHELL  0x01 /* User wants a subshell: ( command ) */
#define CMD_FORCE_SUBSHELL 0x02 /* Shell needs to force a subshell. */
#define CMD_INVERT_RETURN  0x04 /* Invert the exit value. */
#define CMD_IGNORE_RETURN  0x08 /* Ignore the exit value.  For set -e. */
#define CMD_NO_FUNCTIONS   0x10 /* Ignore functions during command lookup. */
#define CMD_INHIBIT_EXPANSION 0x20 /* Do not expand the command words. */
#define CMD_NO_FORK        0x40 /* Don't fork; just call execve */
#define CMD_TIME_PIPELINE  0x80 /* Time a pipeline */
#define CMD_TIME_POSIX     0x100 /* time -p; use POSIX.2 time output spec. */
#define CMD_AMPERSAND      0x200 /* command & */
#define CMD_STDIN_REDIR    0x400 /* async command needs implicit </dev/null */
#define CMD_COMMAND_BUILTIN 0x0800 /* command executed by `command' builtin */
#define CMD_COPROC_SUBSHELL 0x1000
#define CMD_LASTPIPE        0x2000
#define CMD_STDPATH         0x4000      /* use standard path for command lookup */
#define CMD_TRY_OPTIMIZING  0x8000      /* try to optimize this simple command */

/* The conditional command, [[...]].  This is a binary tree -- we slipped
 *    a recursive-descent parser into the YACC grammar to parse it. */
#define COND_AND        1
#define COND_OR         2
#define COND_UNARY      3
#define COND_BINARY     4
#define COND_TERM       5
#define COND_EXPR       6

/* Possible command errors */
#define CMDERR_DEFAULT  0
#define CMDERR_BADTYPE  1
#define CMDERR_BADCONN  2
#define CMDERR_BADJUMP  3

#define CMDERR_LAST     3

/* Defines for flags argument to sh_modcase.  These need to agree with what's
 *    in lib/sh/casemode.c */
#define CASE_LOWER      0x0001
#define CASE_UPPER      0x0002
#define CASE_CAPITALIZE 0x0004
#define CASE_UNCAP      0x0008
#define CASE_TOGGLE     0x0010
#define CASE_TOGGLEALL  0x0020
#define CASE_UPFIRST    0x0040
#define CASE_LOWFIRST   0x0080

#define CASE_USEWORDS   0x1000

/* Declarations for functions defined in lib/sh/fmtulong.c */
#define FL_PREFIX     0x01    /* add 0x, 0X, or 0 prefix as appropriate */
#define FL_ADDBASE    0x02    /* add base# prefix to converted value */
#define FL_HEXUPPER   0x04    /* use uppercase when converting to hex */
#define FL_UNSIGNED   0x08    /* don't add any sign */

/* declarations for functions defined in lib/sh/makepath.c */
#define MP_DOTILDE      0x01
#define MP_DOCWD        0x02
#define MP_RMDOT        0x04
#define MP_IGNDOT       0x08

/* declarations for functions defined in lib/sh/pathcanon.c */
#define PATH_CHECKDOTDOT        0x0001
#define PATH_CHECKEXISTS        0x0002
#define PATH_HARDPATH           0x0004
#define PATH_NOALLOC            0x0008

/* declarations for functions defined in lib/sh/tmpfile.c */
#define MT_USETMPDIR            0x0001
#define MT_READWRITE            0x0002
#define MT_USERANDOM            0x0004

/* Flags for search_for_command */
#define CMDSRCH_HASH            0x01
#define CMDSRCH_STDPATH         0x02
#define CMDSRCH_TEMPENV         0x04

/* Welcome to the world of Un*x, where everything is slightly backwards. */
#define FLAG_ON '-'
#define FLAG_OFF '+'

/* Some defines for calling file status functions. */
#define FS_EXISTS         0x1
#define FS_EXECABLE       0x2
#define FS_EXEC_PREFERRED 0x4
#define FS_EXEC_ONLY      0x8
#define FS_DIRECTORY      0x10
#define FS_NODIRS         0x20
#define FS_READABLE       0x40

/* Possible values for b_flag. */
#undef B_EOF
#undef B_ERROR          /* There are some systems with this define */
#undef B_UNBUFF

#define B_EOF           0x01
#define B_ERROR         0x02
#define B_UNBUFF        0x04
#define B_WASBASHINPUT  0x08
#define B_TEXT          0x10
#define B_SHAREDBUF     0x20    /* shared input buffer */

/* Defines controlling the fashion in which jobs are listed. */
#define JLIST_STANDARD       0
#define JLIST_LONG           1
#define JLIST_PID_ONLY       2
#define JLIST_CHANGED_ONLY   3
#define JLIST_NONINTERACTIVE 4

/* I looked it up.  For pretty_print_job ().  The real answer is 24. */
#define LONGEST_SIGNAL_DESC 24

/* Defines for the wait_for functions and for the wait builtin to use */
#define JWAIT_PERROR            0x01
#define JWAIT_FORCE             0x02

/* The max time to sleep while retrying fork() on EAGAIN failure */
#define FORKSLEEP_MAX   16

/* We keep an array of jobs.  Each entry in the array is a linked list
 *    of processes that are piped together.  The first process encountered is
 *       the group leader. */

/* Values for the `running' field of a struct process. */
#define PS_DONE         0
#define PS_RUNNING      1
#define PS_STOPPED      2
#define PS_RECYCLED     4

/* Values for the FLAGS field in the JOB struct below. */
#define J_FOREGROUND 0x01 /* Non-zero if this is running in the foreground.  */
#define J_NOTIFIED   0x02 /* Non-zero if already notified about job state.   */
#define J_JOBCONTROL 0x04 /* Non-zero if this job started under job control. */
#define J_NOHUP      0x08 /* Don't send SIGHUP to job if shell gets SIGHUP. */
#define J_STATSAVED  0x10 /* A process in this job had had status saved via $! */
#define J_ASYNC      0x20 /* Job was started asynchronously */
#define J_PIPEFAIL   0x40 /* pipefail set when job was started */


#define NO_PIDSTAT (ps_index_t)-1

#define NO_JOB  -1      /* An impossible job array index. */
#define DUP_JOB -2      /* A possible return value for get_job_spec (). */
#define BAD_JOBSPEC -3  /* Bad syntax for job spec. */

/* A value which cannot be a process ID. */
#define NO_PID (pid_t)-1

#define ANY_PID (pid_t)-1

/* Possible states for the parser that require it to do special things. */
#define PST_CASEPAT     0x000001        /* in a case pattern list */
#define PST_ALEXPNEXT   0x000002        /* expand next word for aliases */
#define PST_ALLOWOPNBRC 0x000004        /* allow open brace for function def */
#define PST_NEEDCLOSBRC 0x000008        /* need close brace */
#define PST_DBLPAREN    0x000010        /* double-paren parsing */
#define PST_SUBSHELL    0x000020        /* ( ... ) subshell */
#define PST_CMDSUBST    0x000040        /* $( ... ) command substitution */
#define PST_CASESTMT    0x000080        /* parsing a case statement */
#define PST_CONDCMD     0x000100        /* parsing a [[...]] command */
#define PST_CONDEXPR    0x000200        /* parsing the guts of [[...]] */
#define PST_ARITHFOR    0x000400        /* parsing an arithmetic for command - unused */
#define PST_ALEXPAND    0x000800        /* OK to expand aliases - unused */
#define PST_EXTPAT      0x001000        /* parsing an extended shell pattern */
#define PST_COMPASSIGN  0x002000        /* parsing x=(...) compound assignment */
#define PST_ASSIGNOK    0x004000        /* assignment statement ok in this context */
#define PST_EOFTOKEN    0x008000        /* yylex checks against shell_eof_token */
#define PST_REGEXP      0x010000        /* parsing an ERE/BRE as a single word */
#define PST_HEREDOC     0x020000        /* reading body of here-document */
#define PST_REPARSE     0x040000        /* re-parsing in parse_string_to_word_list */
#define PST_REDIRLIST   0x080000        /* parsing a list of redirections preceding a simple command name */
#define PST_COMMENT     0x100000        /* parsing a shell comment; used by aliases */
#define PST_ENDALIAS    0x200000        /* just finished expanding and consuming an alias */

/* States we can be in while scanning a ${...} expansion.  Shared between
 *    parse.y and subst.c */
#define DOLBRACE_PARAM  0x01
#define DOLBRACE_OP     0x02
#define DOLBRACE_WORD   0x04

#define DOLBRACE_QUOTE  0x40    /* single quote is special in double quotes */
#define DOLBRACE_QUOTE2 0x80    /* single quote is semi-special in double quotes */

/* Flag values for quote_string_for_globbing */
#define QGLOB_CVTNULL   0x01    /* convert QUOTED_NULL strings to '\0' */
#define QGLOB_FILENAME  0x02    /* do correct quoting for matching filenames */
#define QGLOB_REGEXP    0x04    /* quote an ERE for regcomp/regexec */
#define QGLOB_CTLESC    0x08    /* turn CTLESC CTLESC into CTLESC for BREs */
#define QGLOB_DEQUOTE   0x10    /* like dequote_string but quote glob chars */

/* Values for COMPSPEC actions.  These are things the shell knows how to
 *    build internally. */
#define CA_ALIAS        (1<<0)
#define CA_ARRAYVAR     (1<<1)
#define CA_BINDING      (1<<2)
#define CA_BUILTIN      (1<<3)
#define CA_COMMAND      (1<<4)
#define CA_DIRECTORY    (1<<5)
#define CA_DISABLED     (1<<6)
#define CA_ENABLED      (1<<7)
#define CA_EXPORT       (1<<8)
#define CA_FILE         (1<<9)
#define CA_FUNCTION     (1<<10)
#define CA_GROUP        (1<<11)
#define CA_HELPTOPIC    (1<<12)
#define CA_HOSTNAME     (1<<13)
#define CA_JOB          (1<<14)
#define CA_KEYWORD      (1<<15)
#define CA_RUNNING      (1<<16)
#define CA_SERVICE      (1<<17)
#define CA_SETOPT       (1<<18)
#define CA_SHOPT        (1<<19)
#define CA_SIGNAL       (1<<20)
#define CA_STOPPED      (1<<21)
#define CA_USER         (1<<22)
#define CA_VARIABLE     (1<<23)

/* Values for COMPSPEC options field. */
#define COPT_RESERVED   (1<<0)          /* reserved for other use */
#define COPT_DEFAULT    (1<<1)
#define COPT_FILENAMES  (1<<2)
#define COPT_DIRNAMES   (1<<3)
#define COPT_NOQUOTE    (1<<4)
#define COPT_NOSPACE    (1<<5)
#define COPT_BASHDEFAULT (1<<6)
#define COPT_PLUSDIRS   (1<<7)
#define COPT_NOSORT     (1<<8)

#define COPT_LASTUSER   COPT_NOSORT

#define PCOMP_RETRYFAIL (COPT_LASTUSER << 1)
#define PCOMP_NOTFOUND  (COPT_LASTUSER << 2)

/* Values for ITEMLIST -> flags */
#define LIST_DYNAMIC            0x001
#define LIST_DIRTY              0x002
#define LIST_INITIALIZED        0x004
#define LIST_MUSTSORT           0x008
#define LIST_DONTFREE           0x010
#define LIST_DONTFREEMEMBERS    0x020

#define EMPTYCMD        "_EmptycmD_"
#define DEFAULTCMD      "_DefaultCmD_"
#define INITIALWORD     "_InitialWorD_"

/* Values for flags argument to do_redirections */
#define RX_ACTIVE       0x01    /* do it; don't just go through the motions */
#define RX_UNDOABLE     0x02    /* make a list to undo these redirections */
#define RX_CLEXEC       0x04    /* set close-on-exec for opened fds > 2 */
#define RX_INTERNAL     0x08
#define RX_USER         0x10
#define RX_SAVCLEXEC    0x20    /* set close-on-exec off in restored fd even though saved on has it on */
#define RX_SAVEFD       0x40    /* fd used to save another even if < SHELL_FD_BASE */

#define NO_PIPE -1
#define REDIRECT_BOTH -2

#define NO_VARIABLE -1

/* Values that can be returned by execute_command (). */
#define EXECUTION_FAILURE 1
#define EXECUTION_SUCCESS 0

/* Usage messages by builtins result in a return status of 2. */
#define EX_BADUSAGE     2

#define EX_MISCERROR    2

/* Special exit statuses used by the shell, internally and externally. */
#define EX_RETRYFAIL    124
#define EX_WEXPCOMSUB   125
#define EX_BINARY_FILE  126
#define EX_NOEXEC       126
#define EX_NOINPUT      126
#define EX_NOTFOUND     127

#define EX_SHERRBASE    256     /* all special error values are > this. */

#define EX_BADSYNTAX    257     /* shell syntax error */
#define EX_USAGE        258     /* syntax error in usage */
#define EX_REDIRFAIL    259     /* redirection failed */
#define EX_BADASSIGN    260     /* variable assignment error */
#define EX_EXPFAIL      261     /* word expansion failed */
#define EX_DISKFALLBACK 262     /* fall back to disk command from builtin */

/* Flag values that control parameter pattern substitution. */
#define MATCH_ANY       0x000
#define MATCH_BEG       0x001
#define MATCH_END       0x002

#define MATCH_TYPEMASK  0x003

#define MATCH_GLOBREP   0x010
#define MATCH_QUOTED    0x020
#define MATCH_ASSIGNRHS 0x040
#define MATCH_STARSUB   0x080

/* Constants which specify how to handle backslashes and quoting in
 *    expand_word_internal ().  Q_DOUBLE_QUOTES means to use the function
 *       slashify_in_quotes () to decide whether the backslash should be
 *          retained.  Q_HERE_DOCUMENT means slashify_in_here_document () to
 *             decide whether to retain the backslash.  Q_KEEP_BACKSLASH means
 *                to unconditionally retain the backslash.  Q_PATQUOTE means that we're
 *                   expanding a pattern ${var%#[#%]pattern} in an expansion surrounded
 *                      by double quotes. Q_DOLBRACE means we are expanding a ${...} word, so
 *                         backslashes should also escape { and } and be removed. */
#define Q_DOUBLE_QUOTES  0x001
#define Q_HERE_DOCUMENT  0x002
#define Q_KEEP_BACKSLASH 0x004
#define Q_PATQUOTE       0x008
#define Q_QUOTED         0x010
#define Q_ADDEDQUOTES    0x020
#define Q_QUOTEDNULL     0x040
#define Q_DOLBRACE       0x080
#define Q_ARITH          0x100  /* expanding string for arithmetic evaluation */
#define Q_ARRAYSUB       0x200  /* expanding indexed array subscript */

/* Flag values controlling how assignment statements are treated. */
#define ASS_APPEND      0x0001
#define ASS_MKLOCAL     0x0002
#define ASS_MKASSOC     0x0004
#define ASS_MKGLOBAL    0x0008  /* force global assignment */
#define ASS_NAMEREF     0x0010  /* assigning to nameref variable */
#define ASS_FORCE       0x0020  /* force assignment even to readonly variable */
#define ASS_CHKLOCAL    0x0040  /* check local variable before assignment */
#define ASS_NOEXPAND    0x0080  /* don't expand associative array subscripts */
#define ASS_NOEVAL      0x0100  /* don't evaluate value as expression */
#define ASS_NOLONGJMP   0x0200  /* don't longjmp on fatal assignment error */

/* Flags for the string extraction functions. */
#define SX_NOALLOC      0x0001  /* just skip; don't return substring */
#define SX_VARNAME      0x0002  /* variable name; for string_extract () */
#define SX_REQMATCH     0x0004  /* closing/matching delimiter required */
#define SX_COMMAND      0x0008  /* extracting a shell script/command */
#define SX_NOCTLESC     0x0010  /* don't honor CTLESC quoting */
#define SX_NOESCCTLNUL  0x0020  /* don't let CTLESC quote CTLNUL */
#define SX_NOLONGJMP    0x0040  /* don't longjmp on fatal error */
#define SX_ARITHSUB     0x0080  /* extracting $(( ... )) (currently unused) */
#define SX_POSIXEXP     0x0100  /* extracting new Posix pattern removal expansions in extract_dollar_brace_string */
#define SX_WORD         0x0200  /* extracting word in ${param op word} */
#define SX_COMPLETE     0x0400  /* extracting word for completion */
#define SX_STRIPDQ      0x0800  /* strip double quotes when extracting double-quoted string */

/* Flags for skip_to_delim */
#define SD_NOJMP        0x001   /* don't longjmp on fatal error. */
#define SD_INVERT       0x002   /* look for chars NOT in passed set */
#define SD_NOQUOTEDELIM 0x004   /* don't let single or double quotes act as delimiters */
#define SD_NOSKIPCMD    0x008   /* don't skip over $(, <(, or >( command/process substitution; parse them as commands */
#define SD_EXTGLOB      0x010   /* skip over extended globbing patterns if appropriate */
#define SD_IGNOREQUOTE  0x020   /* single and double quotes are not special */
#define SD_GLOB         0x040   /* skip over glob patterns like bracket expressions */
#define SD_NOPROCSUB    0x080   /* don't parse process substitutions as commands */
#define SD_COMPLETE     0x100   /* skip_to_delim during completion */
#define SD_HISTEXP      0x200   /* skip_to_delim during history expansion */
#define SD_ARITHEXP     0x400   /* skip_to_delim during arithmetic expansion */

/* Values for character flags in syntax tables */
#define CWORD		0x0000	/* nothing special; an ordinary character */
#define CSHMETA		0x0001	/* shell meta character */
#define CSHBRK		0x0002	/* shell break character */
#define CBACKQ		0x0004	/* back quote */
#define CQUOTE		0x0008	/* shell quote character */
#define CSPECL		0x0010	/* special character that needs quoting */
#define CEXP		0x0020	/* shell expansion character */
#define CBSDQUOTE	0x0040	/* characters escaped by backslash in double quotes */
#define CBSHDOC		0x0080	/* characters escaped by backslash in here doc */
#define CGLOB		0x0100	/* globbing characters */
#define CXGLOB		0x0200	/* extended globbing characters */
#define CXQUOTE		0x0400	/* cquote + backslash */
#define CSPECVAR	0x0800	/* single-character shell variable name */
#define CSUBSTOP	0x1000	/* values of OP for ${word[:]OPstuff} */
#define CBLANK		0x2000	/* whitespace (blank) character */

/* Flags for var_context->flags */
#define VC_HASLOCAL     0x01
#define VC_HASTMPVAR    0x02
#define VC_FUNCENV      0x04    /* also function if name != NULL */
#define VC_BLTNENV      0x08    /* builtin_env */
#define VC_TEMPENV      0x10    /* temporary_env */

/* The various attributes that a given variable can have. */
/* First, the user-visible attributes */
#define att_exported    0x0000001       /* export to environment */
#define att_readonly    0x0000002       /* cannot change */
#define att_array       0x0000004       /* value is an array */
#define att_function    0x0000008       /* value is a function */
#define att_integer     0x0000010       /* internal representation is int */
#define att_local       0x0000020       /* variable is local to a function */
#define att_assoc       0x0000040       /* variable is an associative array */
#define att_trace       0x0000080       /* function is traced with DEBUG trap */
#define att_uppercase   0x0000100       /* word converted to uppercase on assignment */
#define att_lowercase   0x0000200       /* word converted to lowercase on assignment */
#define att_capcase     0x0000400       /* word capitalized on assignment */
#define att_nameref     0x0000800       /* word is a name reference */

#define attmask_user    0x0000fff

/* Internal attributes used for bookkeeping */
#define att_invisible   0x0001000       /* cannot see */
#define att_nounset     0x0002000       /* cannot unset */
#define att_noassign    0x0004000       /* assignment not allowed */
#define att_imported    0x0008000       /* came from environment */
#define att_special     0x0010000       /* requires special handling */
#define att_nofree      0x0020000       /* do not free value on unset */
#define att_regenerate  0x0040000       /* regenerate when exported */

#define attmask_int     0x00ff000

/* Internal attributes used for variable scoping. */
#define att_tempvar     0x0100000       /* variable came from the temp environment */
#define att_propagate   0x0200000       /* propagate to previous scope */

#define attmask_scope   0x0f00000

/* Tokentype */
/*enum e_tokentype
{
	IF = 258,
	THEN = 259,
	ELSE = 260,
	ELIF = 261,
	FI = 262,
	CASE = 263,
	ESAC = 264,
	FOR = 265,
	SELECT = 266,
	WHILE = 267,
	UNTIL = 268,
	DO = 269,
	DONE = 270,
	FUNCTION = 271,
	COPROC = 272,
	COND_START = 273,
	COND_END = 274,
	COND_ERROR = 275,
	IN = 276,
	BANG = 277,
	TIME = 278,
	TIMEOPT = 279,
	TIMEIGN = 280,
	WORD = 281,
	ASSIGNMENT_WORD = 282,
	REDIR_WORD = 283,
	NUMBER = 284,
	ARITH_CMD = 285,
	ARITH_FOR_EXPRS = 286,
	COND_CMD = 287,
	AND_AND = 288,
	OR_OR = 289,
	GREATER_GREATER = 290,
	LESS_LESS = 291,
	LESS_AND = 292,
	LESS_LESS_LESS = 293,
	GREATER_AND = 294,
	SEMI_SEMI = 295,
	SEMI_AND = 296,
	SEMI_SEMI_AND = 297,
	LESS_LESS_MINUS = 298,
	AND_GREATER = 299,
	AND_GREATER_GREATER = 300,
	LESS_GREATER = 301,
	GREATER_BAR = 302,
	BAR_AND = 303,
	yacc_EOF = 304
};
*/
/* Tokens.  */
#define IF 258
#define THEN 259
#define ELSE 260
#define ELIF 261
#define FI 262
#define CASE 263
#define ESAC 264
#define FOR 265
#define SELECT 266
#define WHILE 267
#define UNTIL 268
#define DO 269
#define DONE 270
#define FUNCTION 271
#define COPROC 272
#define COND_START 273
#define COND_END 274
#define COND_ERROR 275
#define IN 276
#define BANG 277
#define TIME 278
#define TIMEOPT 279
#define TIMEIGN 280
#define WORD 281
#define ASSIGNMENT_WORD 282
#define REDIR_WORD 283
#define NUMBER 284
#define ARITH_CMD 285
#define ARITH_FOR_EXPRS 286
#define COND_CMD 287
#define AND_AND 288
#define OR_OR 289
#define GREATER_GREATER 290
#define LESS_LESS 291
#define LESS_AND 292
#define LESS_LESS_LESS 293
#define GREATER_AND 294
#define SEMI_SEMI 295
#define SEMI_AND 296
#define SEMI_SEMI_AND 297
#define LESS_LESS_MINUS 298
#define AND_GREATER 299
#define AND_GREATER_GREATER 300
#define LESS_GREATER 301
#define GREATER_BAR 302
#define BAR_AND 303
#define yacc_EOF 304
#endif
