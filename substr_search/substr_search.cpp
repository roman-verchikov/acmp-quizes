#include <stdio.h>
#include <string.h>

#define MAX_STRING_SIZE 50000U

char str[MAX_STRING_SIZE];
char substr[MAX_STRING_SIZE];

int main()
{
    freopen("INPUT.TXT", "rt", stdin);
    freopen("OUTPUT.TXT", "wt", stdout);

    scanf("%s\n%s", str, substr);

    char *p = str;
    size_t substr_len = strlen(substr);
    size_t str_len = strlen(str);
    while ((p - str) <= str_len) {
        if (!memcmp(p, substr, substr_len)) {
            printf("%d ", (int)(p - str));
        }

        p++;
    }

    return 0;
}
