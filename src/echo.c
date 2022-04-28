#include "../inc/ush.h"

void check_echo_flags(char **term_arg_cmd, t_for_echo *echo) {
    if (term_arg_cmd[1][0] == '-' ) {
        for (int j = mx_strlen(term_arg_cmd[1]); j >= 1; j--) {
            if (term_arg_cmd[1][j] == 'n') {
                echo->n = true;
                echo->folder_err = false;
            }
            else if (term_arg_cmd[1][j] == 'e') {
                if (!echo->E) {
                    echo->e = true;
                    echo->folder_err = false;
                }
            }
            else if (term_arg_cmd[1][j] == 'E') {
                if (!echo->e) {
                    echo->E = true;
                    echo->folder_err = false;
                }
            }
        }
    }      
}



void echo_main_proccess(char **term_arg_cmd, t_for_echo echo) {
    int t = 1;
    char *output;
    /*

 for(int i = 0; i < mx_strlen(buf); i++) {
                    if(cur==0){
                        if(buf[i]!='\\') dst[j++] = buf[i];
                        else cur = 1;
                    }
                    else if(cur==1){

                        switch(buf[i]){
                            case 'b': 
                                dst[j++]='\b';
                                break;

                            case 't':
                                dst[j++]='\t';
                                break;

                            case 'v': 
                                dst[j++]='\v'; 
                                break;
                
                            case 'a': 
                                dst[j++]='\a'; 
                                break;
                            
                            case '0': 
                                cur = 2; 
                                clen = 0; 
                                code[clen++]='0'; 
                                break;

                            case '\\': 
                                dst[j++]='\\'; 
                                break;



*/
    if (!echo.folder_err) {
        t = 2;
    }
    for (int i = t; term_arg_cmd[i] != NULL; i++) {
        output = term_arg_cmd[i];
        if (!echo.E && strstr(term_arg_cmd[i], "\\")) {
            output = process_incomands(term_arg_cmd[i], echo);
        }
        mx_printstr(output);
        if(term_arg_cmd[i+1] != NULL)
        mx_printstr(" ");

        if (strstr(term_arg_cmd[i],"\\c")) {
            break;
        }
/*        if (term_arg_cmd[i + 1]) {
            printf(" ");
        }
*/
    }
    if(!echo.n) {
        mx_printstr("\n");   
    }
}

void mx_echo(char **term_arg_cmd) {
    setenv("?", "0", 1);
    if (mx_arrsize(term_arg_cmd) == 1) {
        mx_printstr("\n");
        return;
    }
    t_for_echo echo = {false, false, false, true, false};
    check_echo_flags(term_arg_cmd, &echo);
    echo_main_proccess(term_arg_cmd, echo);
}
