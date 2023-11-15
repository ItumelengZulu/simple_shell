int tokenize_input(char *input, char *args[]) {
    int argc = 0;

    while (*input != '\0' && argc < MAX_ARGUMENTS - 1) {
        while (*input == ' ' || *input == '\t' || *input == '\n') {
            *input++ = '\0';
        }

        args[argc++] = input;

        while (*input != '\0' && *input != ' ' && *input != '\t' && *input != '\n') {
            input++;
        }
    }

    args[argc] = NULL;
    return argc;
}
