/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:07:57 by thblack-          #+#    #+#             */
/*   Updated: 2025/10/29 15:41:37 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <signal.h>

// CODES FOR ERROR TRACKING
// SUCCESSFUL EXECUTION
# define OK 1
// UNSUCCEFUL EXECUTION
# define KO 0

// MINISHELL

typedef enum {
	ERR_ARG_MAX, // Arguments exceeds ARG_MAX
	ERR_CMD_NOF, // Command not found
	ERR_CON_REF, // Connection refused
	ERR_PERDENY, // Permission denied (file or directory)
	ERR_SSHDENY, // Permission denied (publickey)
	ERR_F_D_NOF, // File or directory not found
	ERR_DIR_NOF, // Directory not found
	ERR_OVERWRI, // File already exist
	ERR_OPT_NOF, // Option not found
	ERR_BFD_NOF, // File descriptor not found, bad fd
	ERR_SYX_TOK, // Syntax error near unexpected token
	ERR_SYX_EOF, // Unexpected end of file
	ERR_SYX_AOP, // Invalid arthmetic operator
	ERR_ZERODIV, // Division by 0
	ERR_AM_RDIR, // Ambiguous redirect
	ERR_BAD_SUB, // Bad substitution, unsupported syntax
	ERR_SIGSEGV, // Segmentation fault
	ERR_DEV_NOF, // Device not found
	ERR_RALLOCF, // Resource allocation fail
	ERR_MALLOCF, // Malloc fail, out of memory
	ERR_REM_NOF, // Unable to connect to remote host
} e_error;

// typedef enum {
// 	SPACE,
// 	TAB,
// 	NEWLINE,
// 	PIPE,
// 	AMP,
// 	COLON,
// 	OPEN_BRACKET,
// 	CLOSE_BRACKET,
// 	LESS_THAN,
// 	MORE_THAN
// } e_metachar;

typedef enum {
	TOKEN_CTRL, // Control operator
	TOKEN_RDIR, // Redirect operator
	TOKEN_BTIN, // Builtin command
	TOKEN_RWRD, // Reserved word
} e_token;

typedef enum {
	NEWLINE,
	PIPE,
	DBLPIPE,
	AMP,
	DBLAMP,
	COLON,
	DBLCOLON,
	COLONAMP,
	DBLCOLONAMP,
	PIPEAMP,
	OPEN_BRACKET,
	CLOSE_BRACKET
} e_control;

typedef enum {
	LESS_THAN,
	MORE_THAN,
	DBL_LESS_THAN,
	DBL_MORE_THAN,
} e_redirect;

typedef enum {
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
} e_builtin;

// typedef enum {
// } e_resword;

typedef struct s_cmd {
	// e_metachar	metachar;
	e_token		token;
	e_control	ctrl;
	e_redirect	redir;
	e_builtin	builtin;
	// e_resword	resword;
} t_cmd;

#endif
