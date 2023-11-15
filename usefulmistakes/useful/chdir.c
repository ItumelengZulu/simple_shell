void change_directory(const char *directory) {
    if (directory == NULL) {
        fprintf(stderr, "cd: missing argument\n");
    } else if (chdir(directory) != 0) {
        perror("cd");
    }
}
