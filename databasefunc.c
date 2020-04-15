#include "databasefunc.h"


void run_database(struct Character base[100], size_t *size) {
    printf("Welcome to the RDB(Rusinovich DataBase)!\tVerison 1.0.0\n\n");
    int command;
    while(1) {
        list_menu(&command);
        switch(command) {
            case 1:
                input_data(base, size);
                break;
            case 2:
                remove_data(base, size);
                break;
            case 3:
                print_data(base, size);
                break;
            case 4:
                find_data(base, size);
                break;
            case 5:
                sort_data(base, size);
                break;
        }
    }
}

void list_menu(int *command) {
    printf("1. ADD\n");
    printf("2. REMOVE\n");
    printf("3. PRINT\n");
    printf("4. SEARCH\n");
    printf("5. SORT\n");
    printf("Choose your command > ");
    scanf("%d", command);
}

void choose_input(int *command) {
    printf("Choose input type:\n \
            1. keyboard \
            2. file\n");
    printf("Your input > ");
    scanf("%d", command);
}

void check_and_read(struct Character base[100], size_t *size, FILE *file, const int *line_number) {
    int cur, prev, isFirst = 1, i = 0, spaces = 0, eolc = 0;
    char buffer[40];
    while((cur = getc(file)) != EOF) {
        if(isFirst) {
            if(!isalpha(cur)) {
                printf("File does not match to the template\n");
                return;
            }
            isFirst = 0;
        }
        if(cur == ' ' || cur == '\n') {
            spaces++;
        }
        else {
            buffer[i] = cur;
            ++i;
        }
        if(spaces == 1 && cur == ' ') {
            strcpy(base[*size].name, buffer);
            memset(buffer, 0, strlen(buffer));
            i = 0;
        }
        if(spaces == 2 && cur == ' ') {
            if(strcmp("JEDI", buffer) && strcmp("SITH", buffer)) {
               printf("Class must be \"SITH\" or \"JEDI\"\n");
               return; 
            }
            strcpy(base[*size].warrior_class, buffer);
            memset(buffer, 0, strlen(buffer));
            i = 0;
        }
        if(spaces == 3 && cur == ' ') {
            strcpy(base[*size].saber, buffer);
            memset(buffer,0,strlen(buffer));
            i = 0;
        }
        if(spaces == 4 && cur == ' ') {
            if(atoi(buffer) < 1 || atoi(buffer) > 100) {
                printf("Level must be greater than 1 and less than 100\n");
                return;
            }
            base[*size].level = atoi(buffer);
            memset(buffer,0,strlen(buffer));
            i = 0;
        }
        if(spaces == 5 && cur == '\n') {
            if(atoi(buffer) < 100 || atoi(buffer) > 10e6) {
                printf("Midichlorians must be greater than 100 and less than 10^6\n");
                return;
            }
            i = 0;
            base[*size].midichlorians = atoi(buffer);
            memset(buffer,0,strlen(buffer));
            spaces = 0;
            (*size)++;
        }
        if(cur == '\n')
            eolc++;
        if(eolc == *line_number)
            break;
        prev = cur;
    }
}

void input_data(struct Character base[100], size_t *size) {
    int command, i;
    int line_number;

    choose_input(&command);
    if(command == READ_FROM_KEYBOARD) {
        char level[5];
        char midichlor[10];
        printf("Enter number of input lines: ");
        scanf("%d", &line_number); 
        for(i = 0; i < line_number; ++i) {
            printf("Enter name : ");
            scanf("%s", base[*size].name);
            while(1) {
                printf("Enter class : ");
                scanf("%s", base[*size].warrior_class);
                if(strcmp(base[*size].warrior_class, "JEDI") && strcmp(base[*size].warrior_class, "SITH")) {
                    printf("Class must be \"SITH\" or \"JEDI\"\n");
                    continue;
                }
                break;
            }
            printf("Enter saber color : ");
            scanf("%s", base[*size].saber);
            while(1) {
                printf("Enter level : ");
                scanf("%s", level);
                if(atoi(level) == 0) {
                    printf("Level must be integer number and not 0\n");
                    continue;
                }
                else if(atoi(level) < 1 || atoi(level) > 100) {
                    printf("Level must be greater than 1 and less than 100\n");
                    continue;
                }
                base[*size].level = atoi(level);
                memset(level, 0, sizeof(level));
                break;
            }
            while(1) {
                printf("Enter midichlorians : ");
                scanf("%s", midichlor);
                if(atoi(midichlor) == 0) {
                    printf("Midichlorians must be integer number and not 0\n");
                    continue;
                }
                else if(atoi(midichlor) < 100 || atoi(midichlor) > 10e6) {
                    printf("Midichlorians must be greater than 100 and less than 10^6\n");
                    continue;
                }
                base[*size].midichlorians = atoi(midichlor);
                memset(midichlor, 0, sizeof(midichlor));
                break;
            }
            (*size)++;
        }
    }
    if(command == READ_FROM_FILE) {
        char filename[30];
        int i;

        printf("TEMPLATE FOR INPUT DATA IN FILE MUST BE:\n");
        printf("NAME WARRIOR_CLASS SABER LEVEL MIDICHLORIANS\n");

        printf("Enter input file name : ");
        scanf("%s", filename);

        FILE *file = fopen(filename, "r");

        if(!file) {
            printf("Cannot find this file\n");
            return;
        }

        printf("Enter number of input lines from file : ");
        scanf("%d", &line_number); 

        for(i = 0; i < line_number; ++i)
            check_and_read(base, size, file, &line_number);

        fclose(file);
    }
}

void print_frame() {
    int i;
    printf(LEFT_UPPER_CORNER);
    for(i = 0; i < 91; ++i) {
        if(i == 12 || i == 33 || i == 43 || i == 59 || i == 71 || i == 100)
            printf(UPPER_HANDLE);
        else
            printf(LINE);
    }
    printf(RIGHT_UPPER_CORNER);
    printf("%s   NUMBER   %s        NAME        %s  CLASS  %s     SABER     %s   LEVEL   %s   MIDICHLORIANS   %s\n", SEP, SEP, SEP, SEP, SEP, SEP, SEP);
    printf(LEFT_SEP);
    for(i = 1; i < 92; ++i) {
        if(i == 13 || i == 34 || i == 44 || i == 60 || i == 72 || i == 101)
            printf(HANDLE);
        else
            printf(LINE);
    }
    printf(RIGHT_SEP);
}

void print_frame_to_file(FILE *file) {
    int i;
    fputs(LEFT_UPPER_CORNER, file);
    for(i = 0; i < 91; ++i) {
        if(i == 12 || i == 33 || i == 43 || i == 59 || i == 71 || i == 100)
            fputs(UPPER_HANDLE, file);
        else
            fputs(LINE, file);
    }
    fputs(RIGHT_UPPER_CORNER, file);
    fprintf(file, "%s   NUMBER   %s        NAME        %s  CLASS  %s     SABER     %s   LEVEL   %s   MIDICHLORIANS   %s\n", SEP, SEP, SEP, SEP, SEP, SEP, SEP);
    fputs(LEFT_SEP, file);
    for(i = 1; i < 92; ++i) {
        if(i == 13 || i == 34 || i == 44 || i == 60 || i == 72 || i == 101)
            fputs(HANDLE, file);
        else
            fputs(LINE, file);
    }
    fputs(RIGHT_SEP, file);
}

void print_table(const struct Character base[100], const size_t *size) {
    int i, j;
    for(i = 0; i < *size; ++i) {
        printf("%s      %d     %s      %8s      %s   %4s  %s   %7s     %s    %3zu    %s       %6zu      %s\n", SEP, i + 1, SEP, base[i].name, SEP, base[i].warrior_class, SEP, base[i].saber, SEP, base[i].level, SEP, base[i].midichlorians, SEP);
        if(i != *size - 1) {
            printf(LEFT_SEP);
            for(j = 1; j < 92; ++j) {
                if(j == 13 || j == 34 || j == 44 || j == 60 || j == 72 || j == 101)
                    printf(HANDLE);
                else
                    printf(LINE);
            }
            printf(RIGHT_SEP);
        }
    }
}

void print_table_to_file(const struct Character base[100], const size_t *size, FILE *file) {
    int i, j;
    for(i = 0; i < *size; ++i) {
        fprintf(file, "%s      %d     %s      %8s      %s   %4s  %s   %7s     %s    %3zu    %s       %6zu      %s\n", SEP, i + 1, SEP, base[i].name, SEP, base[i].warrior_class, SEP, base[i].saber, SEP, base[i].level, SEP, base[i].midichlorians, SEP);
        if(i != *size - 1) {
            fputs(LEFT_SEP, file);
            for(j = 1; j < 92; ++j) {
                if(j == 13 || j == 34 || j == 44 || j == 60 || j == 72 || j == 101)
                    fputs(HANDLE, file);
                else
                    fputs(LINE, file);
            }
            fputs(RIGHT_SEP, file);
        }
    }
}

void print_lower_frame() {
    int i;
    printf(LEFT_LOWER_CORNER);
    for(i = 0; i < 91; ++i) {
        if(i == 12 || i == 33 || i == 43 || i == 59 || i == 71 || i == 100)
            printf(LOWER_HANDLE);
        else
            printf(LINE);
    }
    printf(RIGHT_LOWER_CORNER);
}

void print_lf_to_file(FILE *file) {
    int i;
    fputs(LEFT_LOWER_CORNER, file);
    for(i = 0; i < 91; ++i) {
        if(i == 12 || i == 33 || i == 43 || i == 59 || i == 71 || i == 100)
            fputs(LOWER_HANDLE, file);
        else
            fputs(LINE, file);
    }
    fputs(RIGHT_LOWER_CORNER, file);
}

void print_data(const struct Character base[100], const size_t *size) {
    int output_type;
    char filename[30];
    printf("1. Print to console\n");
    printf("2. Print to file\n");
    printf("Choose output type: ");
    scanf("%d", &output_type);
    if(output_type == 1) {
        print_frame();
        print_table(base, size);
        print_lower_frame();
    }
    else if(output_type == 2) {
        int i;

        printf("Enter output file name : ");
        scanf("%s", filename);
        
        FILE *file = fopen(filename, "w");

        print_frame_to_file(file);
        print_table_to_file(base, size, file);
        print_lf_to_file(file);
        fclose(file);
    }
    else {
        printf("Choose output type 1 or 2");
        return;
    }
}

void remove_data(struct Character base[100], size_t *size) {
    size_t i, j;
    int row, value;

    char obj[30];

    print_data(base, size);
    printf("1. NUMBER\n");
    printf("2. NAME\n");
    printf("3. CLASS\n");
    printf("4. SABER\n");
    printf("5. LEVEL\n");
    printf("6. MIDICHLORIANS\n");
    printf("Choose row(number) to delete : ");
    scanf("%d", &row);
    while(1) {
        if(row < 1 || row > 5) {
            printf("Choose row from 1 to 6\n");
            continue;
        }
        break;
    }
    switch (row) {
        case 1:
            printf("Enter number of line : ");
            scanf("%d", &value);
            while(1) {
                if(value < 1 || value > *size) {
                    printf("Line with this number does not exist. Please choose line from 1 to %zu", *size);
                    continue;
                }
                break;
            }
            for(i = value - 1; i < *size; ++i) {
                base[i] = base[i + 1];
            }
            (*size)--;
            break;
        case 2:
            printf("Enter name : ");
            scanf("%s", obj);
            for(i = 0; i < *size; ++i) {
                if(!strcmp(obj, base[i].name)) {
                    for(j = i; j < *size; ++j) {
                        base[j] = base[j + 1];
                    }
                    (*size)--;
                }
            }
            break;
        case 3:
            printf("Enter warrior class : ");
            scanf("%s", obj);
            for(i = 0; i < *size; ++i) {
                if(!strcmp(obj, base[i].name)) {
                    for(j = i; j < *size; ++j) {
                        base[j] = base[j + 1];
                    }
                    (*size)--;
                }
            }
            break;
        case 4:
            printf("Enter color saber : ");
            scanf("%s", obj);
            for(i = 0; i < *size; ++i) {
                if(!strcmp(obj, base[i].name)) {
                    for(j = i; j < *size; ++j) {
                        base[j] = base[j + 1];
                    }
                    (*size)--;
                }
            }
            break;
        case 5:
            printf("Enter level : ");
            scanf("%d", &value);
            for(i = 0; i < *size; ++i) {
                if(value == base[i].level) {
                    for(j = i; j < *size; ++j) {
                        base[j] = base[j + 1];
                    }
                    (*size)--;
                }
            }
            break;
        case 6:
            printf("Enter midichlorians : ");
            scanf("%d", &value);
            for(i = 0; i < *size; ++i) {
                if(value == base[i].midichlorians) {
                    for(j = i; j < *size; ++j) {
                        base[j] = base[j + 1];
                    }
                    (*size)--;
                }
            }
            break;
    }
}

void find_data(struct Character base[100], const size_t *size) {
    int i, j, row, line;
    char obj[30];

    printf("1. NUMBER\n");
    printf("2. NAME\n");
    printf("3. CLASS\n");
    printf("4. SABER\n");
    printf("5. LEVEL\n");
    printf("6. MIDICHLORIANS\n");
    printf("Choose row(number) : ");
    scanf("%d", &row);
    while(1) {
        if(row < 1 || row > 5) {
            printf("Choose row from 1 to 6\n");
            continue;
        }
        break;
    }
    switch(row) {
        case 1:
            printf("Enter number of line : ");
            scanf("%d", &line);
            while(1) {
                if(line < 1 || line > *size) {
                    printf("Line with this number does not exist. Please choose line from 1 to %zu", *size);
                    continue;
                }
                break;
            }
            print_frame();
            printf("%s      %d     %s      %8s      %s   %4s  %s   %7s     %s    %3zu    %s       %6zu      %s\n", SEP, line, SEP, base[line - 1].name, SEP, base[line - 1].warrior_class, SEP, base[line - 1].saber, SEP, base[line - 1].level, SEP, base[line - 1].midichlorians, SEP);
            printf(LEFT_LOWER_CORNER);
            for(i = 0; i < 91; ++i) {
                if(i == 12 || i == 33 || i == 43 || i == 59 || i == 71 || i == 100)
                    printf(LOWER_HANDLE);
                else
                    printf(LINE);
            }
            printf(RIGHT_LOWER_CORNER);
            break;
        case 2:
            printf("Enter name : ");
            scanf("%s", obj);
            print_frame();
            for(i = 0; i < *size; ++i) {
                if(!strcmp(obj, base[i].name)) {
                    printf("%s      %d     %s      %8s      %s   %4s  %s   %7s     %s    %3zu    %s       %6zu      %s\n", SEP, i + 1, SEP, base[i].name, SEP, base[i].warrior_class, SEP, base[i].saber, SEP, base[i].level, SEP, base[i].midichlorians, SEP);
                    if(i != *size - 1) {
                        printf(LEFT_SEP);
                        for(j = 1; j < 92; ++j) {
                            if(j == 13 || j == 34 || j == 44 || j == 60 || j == 72 || j == 101)
                                printf(HANDLE);
                            else
                                printf(LINE);
                        }
                        printf(RIGHT_SEP);
                    }
                }
            }
            printf(LEFT_LOWER_CORNER);
            for(i = 0; i < 91; ++i) {
                if(i == 12 || i == 33 || i == 43 || i == 59 || i == 71 || i == 100)
                    printf(LOWER_HANDLE);
                else
                    printf(LINE);
            }
            printf(RIGHT_LOWER_CORNER);
            break;
        case 3:
            printf("Enter warrior class : ");
            scanf("%s", obj);
            print_frame();
            for(i = 0; i < *size; ++i) {
                if(!strcmp(obj, base[i].warrior_class)) {
                    printf("%s      %d     %s      %8s      %s   %4s  %s   %7s     %s    %3zu    %s       %6zu      %s\n", SEP, i + 1, SEP, base[i].name, SEP, base[i].warrior_class, SEP, base[i].saber, SEP, base[i].level, SEP, base[i].midichlorians, SEP);
                    if(i != *size - 1) {
                        printf(LEFT_SEP);
                        for(j = 1; j < 92; ++j) {
                            if(j == 13 || j == 34 || j == 44 || j == 60 || j == 72 || j == 101)
                                printf(HANDLE);
                            else
                                printf(LINE);
                        }
                        printf(RIGHT_SEP);
                    }
                }
            }
            printf(LEFT_LOWER_CORNER);
            for(i = 0; i < 91; ++i) {
                if(i == 12 || i == 33 || i == 43 || i == 59 || i == 71 || i == 100)
                    printf(LOWER_HANDLE);
                else
                    printf(LINE);
            }
            printf(RIGHT_LOWER_CORNER);
            break;
        case 4:
            printf("Enter color saber : ");
            scanf("%s", obj);
            print_frame();
            for(i = 0; i < *size; ++i) {
                if(!strcmp(obj, base[i].saber)) {
                    printf("%s      %d     %s      %8s      %s   %4s  %s   %7s     %s    %3zu    %s       %6zu      %s\n", SEP, i + 1, SEP, base[i].name, SEP, base[i].warrior_class, SEP, base[i].saber, SEP, base[i].level, SEP, base[i].midichlorians, SEP);
                    if(i != *size - 1) {
                        printf(LEFT_SEP);
                        for(j = 1; j < 92; ++j) {
                            if(j == 13 || j == 34 || j == 44 || j == 60 || j == 72 || j == 101)
                                printf(HANDLE);
                            else
                                printf(LINE);
                        }
                        printf(RIGHT_SEP);
                    }
                }
            }
            printf(LEFT_LOWER_CORNER);
            for(i = 0; i < 91; ++i) {
                if(i == 12 || i == 33 || i == 43 || i == 59 || i == 71 || i == 100)
                    printf(LOWER_HANDLE);
                else
                    printf(LINE);
            }
            printf(RIGHT_LOWER_CORNER);
            break;
        case 5:
            printf("Enter level : ");
            scanf("%d", &line);
            print_frame();
            for(i = 0; i < *size; ++i) {
                if(line == base[i].level) {
                    printf("%s      %d     %s      %8s      %s   %4s  %s   %7s     %s    %3zu    %s       %6zu      %s\n", SEP, i + 1, SEP, base[i].name, SEP, base[i].warrior_class, SEP, base[i].saber, SEP, base[i].level, SEP, base[i].midichlorians, SEP);
                    if(i != *size - 1) {
                        printf(LEFT_SEP);
                        for(j = 1; j < 92; ++j) {
                            if(j == 13 || j == 34 || j == 44 || j == 60 || j == 72 || j == 101)
                                printf(HANDLE);
                            else
                                printf(LINE);
                        }
                        printf(RIGHT_SEP);
                    }
                }
            }
            printf(LEFT_LOWER_CORNER);
            for(i = 0; i < 91; ++i) {
                if(i == 12 || i == 33 || i == 43 || i == 59 || i == 71 || i == 100)
                    printf(LOWER_HANDLE);
                else
                    printf(LINE);
            }
            printf(RIGHT_LOWER_CORNER);
            break;
        case 6:
            printf("Enter midichlorians : ");
            scanf("%d", &line);
            print_frame();
            for(i = 0; i < *size; ++i) {
                if(line == base[i].midichlorians) {
                    printf("%s      %d     %s      %8s      %s   %4s  %s   %7s     %s    %3zu    %s       %6zu      %s\n", SEP, i + 1, SEP, base[i].name, SEP, base[i].warrior_class, SEP, base[i].saber, SEP, base[i].level, SEP, base[i].midichlorians, SEP);
                    if(i != *size - 1) {
                        printf(LEFT_SEP);
                        for(j = 1; j < 92; ++j) {
                            if(j == 13 || j == 34 || j == 44 || j == 60 || j == 72 || j == 101)
                                printf(HANDLE);
                            else
                                printf(LINE);
                        }
                        printf(RIGHT_SEP);
                    }
                }
            }
            printf(LEFT_LOWER_CORNER);
            for(i = 0; i < 91; ++i) {
                if(i == 12 || i == 33 || i == 43 || i == 59 || i == 71 || i == 100)
                    printf(LOWER_HANDLE);
                else
                    printf(LINE);
            }
            printf(RIGHT_LOWER_CORNER);
            break;
    }
}

void alg_sort(struct Character base[100], const size_t *size, int field) {
    int i, j, key; 
    char key_char[30];
    switch(field) {
        case 1:
            for (i = 1; i < *size; i++) { 
                strcpy(key_char, base[i].name); 
                j = i - 1; 
        
                while (j >= 0 && base[j].name > key_char) { 
                    strcpy(base[j + 1].name, base[j].name); 
                    j = j - 1; 
                } 
                strcpy(base[j + 1].name, key_char); 
            }
            print_data(base, size); 
            break;
        case 2:
            for (i = 1; i < *size; i++) { 
                strcpy(key_char, base[i].warrior_class); 
                j = i - 1; 
        
                while (j >= 0 && base[j].warrior_class > key_char) { 
                    strcpy(base[j + 1].warrior_class, base[j].warrior_class); 
                    j = j - 1; 
                } 
                strcpy(base[j + 1].warrior_class, key_char); 
            }
            print_data(base, size);
            break;
        case 3:
            for (i = 1; i < *size; i++) { 
                strcpy(key_char, base[i].saber); 
                j = i - 1; 
        
                while (j >= 0 && base[j].saber > key_char) { 
                    strcpy(base[j + 1].saber, base[j].saber); 
                    j = j - 1; 
                } 
                strcpy(base[j + 1].saber, key_char); 
            }
            print_data(base, size);
            break;
        case 4:
            for (i = 1; i < *size; i++) { 
                key = base[i].level; 
                j = i - 1; 
        
                while (j >= 0 && base[j].level > key) { 
                    base[j + 1].level = base[j].level;  
                    j = j - 1; 
                } 
                base[j + 1].level = key;
            }
            print_data(base, size);
            break;
        case 5:
            for (i = 1; i < *size; i++) { 
                key = base[i].midichlorians; 
                j = i - 1; 
        
                while (j >= 0 && base[j].midichlorians > key) { 
                    base[j + 1].midichlorians = base[j].midichlorians;  
                    j = j - 1; 
                } 
                base[j + 1].midichlorians = key;
            }
            print_data(base, size);
            break;
    }
}

void sort_data(struct Character base[100], const size_t *size) {
    int row;
    printf("1. NAME\n");
    printf("2. CLASS\n");
    printf("3. SABER\n");
    printf("4. LEVEL\n");
    printf("5. MIDICHLORIANS\n");
    printf("Choose row(number) : ");
    scanf("%d", &row);
    while(1) {
        if(row < 1 || row > 5) {
            printf("Choose row from 1 to 5");
            continue;
        }
        break;
    }
    alg_sort(base, size, row);
}
