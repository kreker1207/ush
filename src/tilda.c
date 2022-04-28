#include "../inc/ush.h"

char *manage_tilda (char *path) {
    char *tilda_name = strdup("~");
    tilda_name = mx_strjoin(tilda_name, getenv("LOGNAME"));

    //В пути только ~
    if (!strcmp(path, "~")) {
        free(tilda_name);
        return getenv("HOME");
    }
    //В пути только ~username
    else if (!strcmp(path, tilda_name)) {
        free(tilda_name);
        return getenv("HOME");
    }
    //В пути только ~+
    else if (!strcmp(path, "~+")) {
        free(tilda_name);
        return getenv("PWD");
    }
    //В пути только ~-
    else if (!strcmp(path, "~-")) {
        free(tilda_name);
        return getenv("OLDPWD");
    }

    char *temp = strdup(path);
    int slash_ind = mx_get_char_index(path, '/');
    if (slash_ind <= 0) {
        return path;
    }

    //В пути ~/...
    if (!strncmp(path, "~", slash_ind)) {
        printf("TRUE %s %d\n", path, slash_ind);
        char *temp_str = strdup(getenv("HOME"));
        free(tilda_name);
        free(temp);
        return mx_strjoin(temp_str, &path[slash_ind]);
    }
    //В пути ~username/...
    else if (!strncmp(path, tilda_name, slash_ind)) {
        return mx_replace_substr(temp, tilda_name, getenv("HOME"));
    }
    //В пути ~+/...
    else if (!strncmp(path, "~+", slash_ind)) {
        free(tilda_name);
        return mx_replace_substr(temp, "~+", getenv("PWD"));
    }
    //В пути ~-/...
    else if (!strncmp(path, "~-", slash_ind)) {
        free(tilda_name);
        return mx_replace_substr(temp, "~-", getenv("OLDPWD"));
    }

    //Если нет выражений с ~, то возвращаем исходную строку
    free(tilda_name);
    return path;
}
