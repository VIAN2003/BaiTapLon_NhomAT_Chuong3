#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Ham dem so khoang trang trong chuoi
int countSpaces(const char* str) {
    int count = 0;
    while (*str) {
        if (*str == ' ') {
            count++;
        }
        str++;
    }
    return count;
}

// Ham xoa khoang trang thua
void removeExtraSpaces(char* str) {
    char* dst = str;
    while (*str) {
        if (!isspace(*str) || (str > str && !isspace(*(str - 1)))) {
            *dst++ = *str;
        }
        str++;
    }
    *dst = '\0';
}

// Ham doi ky tu dau tien cua moi tu thanh chu in hoa va thay doi ky tu khac thanh chu thuong
void capitalizeWords(char* str) {
    int inWord = 0;
    while (*str) {
        if (isspace(*str)) {
            inWord = 0;
        } else {
            if (!inWord) {
                *str = toupper(*str);
            } else {
                *str = tolower(*str);
            }
            inWord = 1;
        }
        str++;
    }
}

// Ham tim kiem ten trong chuoi ho ten
int findName(const char* fullName, const char* name) {
    return strstr(fullName, name) != NULL;
}

// Ham cat chuoi ho ten thanh chuoi ho lot va chuoi ten
void splitName(const char* fullName, char* lastName, char* firstName) {
    const char* space = strrchr(fullName, ' ');
    if (space != NULL) {
        strncpy(lastName, fullName, space - fullName);
        lastName[space - fullName] = '\0';
        strcpy(firstName, space + 1);
    } else {
        strcpy(lastName, "");
        strcpy(firstName, fullName);
    }
}

// Ham chen tu vao mot vi tri bat ky trong chuoi
void insertWord(char* str, const char* word, int position) {
    int strLen = strlen(str);
    int wordLen = strlen(word);
    
    // Kiem tra vi tri hop le
    if (position < 0 || position > strLen) {
        printf("Vi tri khong hop le.\n");
        return;
    }
    
    // Dich chuoi goc de tao cho cho tu moi
    memmove(str + position + wordLen, str + position, strLen - position + 1);
    memcpy(str + position, word, wordLen);
}

// Ham xoa mot tu trong chuoi
void removeWord(char* str, const char* word) {
    char* pos;
    int len = strlen(word);
    
    while ((pos = strstr(str, word)) != NULL) {
        memmove(pos, pos + len, strlen(pos + len) + 1);
    }
}

// Ham liet ke so lan xuat hien cua moi ky tu trong chuoi
void countCharacterOccurrences(const char* str) {
    int count[256] = {0};  // Dem so lan xuat hien cua moi ky tu (0-255)
    const char* ptr = str;
    
    while (*ptr) {
        count[(unsigned char)*ptr]++;
        ptr++;
    }

    printf("So lan xuat hien cua moi ky tu:\n");
    for (int i = 0; i < 256; i++) {
        if (count[i] > 0) {
            printf("'%c': %d lan\n", i, count[i]);
        }
    }
}

// Ham tim ky tu xuat hien nhieu nhat trong chuoi
char findMostFrequentChar(const char* str) {
    int count[256] = {0};  // Dem so lan xuat hien cua moi ky tu (0-255)
    char mostFrequent = '\0';
    int maxCount = 0;
    
    while (*str) {
        count[(unsigned char)*str]++;
        str++;
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] > maxCount) {
            maxCount = count[i];
            mostFrequent = (char)i;
        }
    }

    return mostFrequent;
}

int main() {
    char str[200], name[50], fullName[100], lastName[50], firstName[50];
    int position, choice;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Dem so khoang trang trong chuoi\n");
        printf("2. Xoa khoang trang thua trong chuoi\n");
        printf("3. Doi ky tu dau tien cua moi tu thanh chu in hoa va thay doi ky tu khac thanh chu thuong\n");
        printf("4. Tim kiem ten trong chuoi ho ten\n");
        printf("5. Cat chuoi ho ten thanh ho lot va ten\n");
        printf("6. Chen tu vao mot vi tri bat ky trong chuoi\n");
        printf("7. Xoa mot tu trong chuoi\n");
        printf("8. Liet ke so lan xuat hien cua moi ky tu trong chuoi\n");
        printf("9. Tim ky tu xuat hien nhieu nhat trong chuoi\n");
        printf("0. Thoat\n");
        printf("Chon mot tuy chon: ");
        scanf("%d", &choice);
        getchar();  // Doc ky tu newline con sot lai trong buffer
        
        switch (choice) {
            case 1:
                printf("Nhap chuoi: ");
                fgets(str, sizeof(str), stdin);
                str[strcspn(str, "\n")] = '\0';  // Xoa ky tu newline neu co
                printf("So khoang trang trong chuoi: %d\n", countSpaces(str));
                break;
            
            case 2:
                printf("Nhap chuoi: ");
                fgets(str, sizeof(str), stdin);
                str[strcspn(str, "\n")] = '\0';  // Xoa ky tu newline neu co
                removeExtraSpaces(str);
                printf("Chuoi sau khi xoa khoang trang thua: \"%s\"\n", str);
                break;
            
            case 3:
                printf("Nhap chuoi: ");
                fgets(str, sizeof(str), stdin);
                str[strcspn(str, "\n")] = '\0';  // Xoa ky tu newline neu co
                removeExtraSpaces(str);
                capitalizeWords(str);
                printf("Chuoi sau khi thay doi ky tu: \"%s\"\n", str);
                break;
            
            case 4:
                printf("Nhap ho ten: ");
                fgets(fullName, sizeof(fullName), stdin);
                fullName[strcspn(fullName, "\n")] = '\0';  // Xoa ky tu newline neu co
                
                printf("Nhap ten can tim: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';  // Xoa ky tu newline neu co
                
                if (findName(fullName, name)) {
                    printf("Ten nay da nhap dung\n");
                } else {
                    printf("Ten nay da nhap sai\n");
                }
                break;
            
            case 5:
                printf("Nhap ho ten: ");
                fgets(fullName, sizeof(fullName), stdin);
                fullName[strcspn(fullName, "\n")] = '\0';  // Xoa ky tu newline neu co
                
                splitName(fullName, lastName, firstName);
                printf("Ho lot: \"%s\"\n", lastName);
                printf("Ten: \"%s\"\n", firstName);
                break;
            
            case 6:
                printf("Nhap chuoi: ");
                fgets(str, sizeof(str), stdin);
                str[strcspn(str, "\n")] = '\0';  // Xoa ky tu newline neu co
                
                printf("Nhap tu can chen: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';  // Xoa ky tu newline neu co
                
                printf("Nhap vi tri chen tu: ");
                scanf("%d", &position);
                getchar();  // Doc ky tu newline con sot lai trong buffer
                
                insertWord(str, name, position);
                printf("Chuoi sau khi chen tu: \"%s\"\n", str);
                break;
            
            case 7:
                printf("Nhap chuoi: ");
                fgets(str, sizeof(str), stdin);
                str[strcspn(str, "\n")] = '\0';  // Xoa ky tu newline neu co
                
                printf("Nhap tu can xoa: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';  // Xoa ky tu newline neu co
                
                removeWord(str, name);
                printf("Chuoi sau khi xoa tu: \"%s\"\n", str);
                break;
            
            case 8:
                printf("Nhap chuoi: ");
                fgets(str, sizeof(str), stdin);
                str[strcspn(str, "\n")] = '\0';  // Xoa ky tu newline neu co
                
                countCharacterOccurrences(str);
                break;
            
            case 9:{
                printf("Nhap chuoi: ");
                fgets(str, sizeof(str), stdin);
                str[strcspn(str, "\n")] = '\0';  // Xoa ky tu newline neu co
                
                char mostFrequent = findMostFrequentChar(str);
                printf("Ky tu xuat hien nhieu nhat la: '%c'\n", mostFrequent);
                break;
        	}
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            
            default:
                printf("Tuy chon khong hop le.\n");
        }
        
    } while (choice != 0);

    return 0;
}

