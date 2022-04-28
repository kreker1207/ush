int mx_atoi(const char *str) {
    long num = 0;
    int check = 1;

    if (*str == '-') {
        check = -1;
    }

    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] == '-') {
            continue;
        }

        if (str[i] >= 48 && str[i] <= 57) {
            num = num * 10;
            num = num + str[i] - 48;
        }
        else {
            break;
        }
    }

    if ((check* num) < -2147483648) {
        unsigned int tmp = -2147483648;
        tmp -= num + 2147483648;;
        return tmp;
    }
    else if ((check* num) > 2147483647) {
        unsigned int tmp = 2147483647;
        tmp += num - 2147483647;
        return tmp;
    }
    return (int)num * check;
}
