clear && cc -g minishell.c  parsing/sanitize_synthax/*.c parsing/*.c parsing/analyser/*.c parsing/test/*.c parsing/tools/*.c expanding/*.c  exec/*.c   -o minishell  -lreadline && ./minishell