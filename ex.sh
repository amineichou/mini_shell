clear && gcc -g minishell.c -lreadline  parsing/sanitize_synthax/*.c parsing/*.c parsing/analyser/*.c parsing/test/*.c parsing/tools/*.c expanding/*.c  exec/*.c  -fsanitize=address  -o minishell  -lreadline && ./minishell