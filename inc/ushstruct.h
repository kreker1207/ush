#ifndef USHS_H
#define USHS_H

typedef struct s__forwhich
{
    bool a;
    bool s;
}              t_for_which;


typedef struct s_for_cd
{
    //flags
   
    bool s;
    bool P;
    //errors
    bool folder_err;
    bool hyphen;
}              t_for_cd;

typedef struct s_echo
{
    ///flags
    bool n;
    bool e;
    bool E;
    ///errors
    bool folder_err;
    bool error;
}              t_for_echo;

typedef struct s__for_pwd
{
    bool L;
    bool P;
    //err
    bool error;
}              t_for_pwd;





typedef struct s_enviromentvariables /////PATH like obj
{
    char *home;

    char *oldpwd;
    
    char *pwd;
}              t_envvar;

#endif

