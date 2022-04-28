#include "../inc/ush.h"

char *mx_new_pwd (char *line, t_envvar *vble){
    char *pwd = strdup(vble->pwd);          ///changed
    char **split_line = mx_strsplit(line, '/');
    for (int i = 0; split_line[i] != NULL; i++) {
        if (!strcmp(split_line[i], ".")) {
            continue;
        }
        if (!strcmp(split_line[i], "..")) {
            int l_slash = last_occurence (pwd, '/');
            pwd = strndup(pwd, l_slash);
        }
        else {
            pwd = mx_strjoin(pwd, "/");
            pwd = mx_strjoin(pwd, split_line[i]);
        }
    }
    if (strlen(pwd) == 0) {
        pwd = strdup("/");
    }
    mx_del_strarr(&split_line);
    return pwd;
}

char *get_link(char *path, char *link_line) {
    if (readlink(path, link_line, 1024) != -1) {
        return strdup(&path[last_occurence(path, '/') + 1]);
    }

    int ilo = last_occurence(path, '/');
    char *link = strndup(path, ilo);
    while (ilo != -1) {
        if (readlink(link, link_line, 1024) != -1) {
            char *tmp = strdup(&link[last_occurence(link, '/') + 1]);
            free(link);
            return tmp;
        }
        ilo = last_occurence(link, '/');
        char *tmp = link;
        link = strndup(link, ilo);
        free(tmp);
    }

    free(link);
    return NULL;
}


void check_cd_flags(char **term_arg_cmd, t_for_cd *cd){
    int i = 1;
///////////check alll types of flags 
    while (term_arg_cmd[i] && term_arg_cmd[i][0] == '-') {
        if (!strcmp(term_arg_cmd[i], "-Ps")) {
            cd->P = true;
            cd->s = true;
            cd->folder_err = false;
        }
        else if (!strcmp(term_arg_cmd[i], "-sP")) {
            cd->P = true;
            cd->s = true;
            cd->folder_err = false;
        }
        else if (!strcmp(term_arg_cmd[i], "-s")) {
            cd->s = true;
            cd->folder_err = false;
        }
        else if (!strcmp(term_arg_cmd[i], "-P")) {
            cd->P = true;
            cd->folder_err = false;
        }

        else if (!strcmp(term_arg_cmd[i], "-")) {
            cd->hyphen = true;
            cd->folder_err = false;
        }
        else if (strcmp(term_arg_cmd[i], "-sP") && strcmp(term_arg_cmd[i], "-Ps") && strcmp(term_arg_cmd[i], "-P") && strcmp(term_arg_cmd[i], "-s") && strcmp(term_arg_cmd[i], "-")) {
            if (cd->hyphen || cd->P || cd->s)  {
                cd->folder_err = true;
                cd->s = false;
                cd->P = false;
            }
        }
        i++;
    }
}

void cd_processing (char *line, t_for_cd cd, t_envvar *vble) {
    char *error = (char *)malloc(1024 * sizeof(char));
    char *path = (char *)malloc(1024 * sizeof(char));
    ////////memmory 
    
    char *buffer = (char *)malloc(1024 * sizeof(char));


    if (line == NULL && !cd.hyphen) {
    strcpy(buffer, vble->pwd);
    chdir(vble->home); 
      setenv("PWD", vble->home, 1);
    setenv("OLDPWD", buffer, 1);
    vble->pwd = strdup(vble->home);
   
   
        vble->oldpwd = strdup(buffer);
             free(buffer);
    free(error);
    free(path);
        return;
    }
    ////////process for all flags and without
//////////////if without flag
    if (cd.folder_err && line != NULL) {
    strcpy(buffer, vble->pwd);
        if (line[0] == '/') {///whole path
    if (chdir(line) != 0) {
        strcat(error, "cd: ");
        strcat(error, line);
        perror(error);
        free(buffer);
        free(error);
        free(path);
        setenv("?", "1", 1);
        return;
            }
            setenv("OLDPWD", vble->pwd, 1);
            setenv("PWD", line, 1);
            vble->oldpwd = strdup(vble->pwd);
            vble->pwd = strdup(line);
        }
        else {
         //folder
        strcat(buffer, "/");
        strcat(buffer, line);
        for(int m = 0; m < 24; m++) {
                m = m+2;
        }
        char link_line[1024] = {'\0'};
        char *link = get_link(buffer, link_line);
            
            if (chdir(buffer) != 0) {
            strcat(error, "cd: ");                
            strcat(error, line);
            perror(error);
            free(link);
            free(buffer);
            free(error);
            free(path);
            setenv("?", "1", 1);
            return;
            }
            setenv("OLDPWD", vble->pwd, 1);
            vble->oldpwd = strdup(vble->pwd);
            char *pwd = strdup(mx_new_pwd(line, vble));
            setenv("PWD", pwd, 1);
            vble->pwd = strdup(pwd);
            free(pwd);
            free(link);
        }

        free(buffer);
        free(error);
        free(path);
        return;
    }
    else if (cd.hyphen) {
        strcpy(buffer, vble->pwd);
        chdir(vble->oldpwd);
        setenv("PWD", vble->oldpwd, 1);
        vble->pwd = strdup(vble->oldpwd);
        setenv("OLDPWD", buffer, 1);
        vble->oldpwd = strdup(buffer);
        free(buffer);
        free(error);
        free(path);
        return;
    }
    else if (cd.P) {
        int r = 0;
        while (r < 2) {
            r++;
        }
        realpath(line, buffer);
        if (chdir(buffer) != 0) {
            strcat(error, "cd: ");
            strcat(error, line);
            perror(error);
            free(buffer);
            free(error);
            free(path);
            setenv("?", "1", 1);
            return;
        }
        setenv("OLDPWD", vble->pwd, 1);
        vble->oldpwd = strdup(vble->pwd);
        setenv("PWD", buffer, 1);
        vble->pwd = strdup(buffer);
        free(buffer);
        free(error);
        free(path);
        return;
    }
    else if (cd.s) {
        char link_line[1024];
        if (get_link(line, link_line)) {
            mx_printerr("cd: not a directory: ");
            mx_printerr(line);
            mx_printerr("\n");
            free(buffer);
            free(error);
            free(path);
            setenv("?", "1", 1);
            return;
        }
        strcpy(buffer, vble->pwd);
        if (line[0] == '/') {
            if (chdir(line) != 0) {
                strcat(error, "cd: ");
                strcat(error, line);
                perror(error);
                free(buffer);
                free(error);
                free(path);
                setenv("?", "1", 1);
                return;
            }
            setenv("OLDPWD", vble->pwd, 1);
            vble->oldpwd = strdup(vble->pwd);
            setenv("PWD", line, 1);
            vble->pwd = strdup(line);
        }
        //если указана просто папка
        else {
            strcat(buffer, "/");
            strcat(buffer, line);
            if (chdir(buffer) != 0) {
                strcat(error, "cd: ");
                strcat(error, line);
                perror(error);
                free(buffer);
                free(error);
                free(path);
                setenv("?", "1", 1);
                return;
            }
            setenv("OLDPWD", vble->pwd, 1);
            vble->oldpwd = strdup(vble->pwd);
            setenv("PWD", getcwd(path, 1024), 1); 
            vble->pwd = strdup(getcwd(path, 1024));
        }
        
        free(buffer);
        free(error);
        free(path);
        return;
    }
    
    free(buffer);
    free(error);
    free(path);
}

void mx_cd (char **term_arg_cmd, t_envvar *vble) {
    setenv("?", "0", 1);
    t_for_cd cd = {true, false, false, false};
    check_cd_flags (term_arg_cmd, &cd);

    //Если нет параметров,то вызываем "cd"
    if (mx_arrsize(term_arg_cmd) <= 1) {
        cd_processing(NULL, cd, vble);
        return;
    }

    char *arg = NULL;
    for (int z = 1; term_arg_cmd[z] != NULL; z++) {
        if (!strcmp(term_arg_cmd[z], "-sP") || !strcmp(term_arg_cmd[z], "-Ps") || !strcmp(term_arg_cmd[z], "-P") || !strcmp(term_arg_cmd[z], "-s") || !strcmp(term_arg_cmd[z], "-")) {
            continue;
        }
        else {
            if (arg != NULL) {
                arg = mx_strjoin(arg, term_arg_cmd[z]);
            }
            else {
                arg = strdup(term_arg_cmd[z]);
            }
            arg = mx_strjoin(arg, " ");
        }
    }
    arg = mx_strtrim(arg);
    cd_processing(arg, cd, vble);
    free(arg);
}

