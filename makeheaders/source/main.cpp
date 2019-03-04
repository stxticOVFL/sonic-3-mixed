#include <stdio.h>
#include <vector>
#include <string>
#include <time.h>
#include <unordered_map>
#include <tuple>
#include <utility>
#include <regex>
#include <sys/types.h>
#include <sys/stat.h>
#if !MSVC
    #include <dirent.h>
	#include <unistd.h>
    #include "iscript.h"
    #include "crc32.h"
    #include "md5.h"
#else
    #include <stdlib.h>
    #include <stdafx.h>
    #include <dirent.h>
    #include <direct.h>
	#include <io.h>
    #include <iscript.h>
    #include <crc32.h>
    #include <md5.h>
#endif

using namespace std;

void createDir(const char* dir) {
#if defined _MSC_VER
    _mkdir(dir);
#elif defined __GNUC__
    mkdir(dir, 0777);
#endif
}

struct VARIABLE {
    std::string class_type;
    std::string variable_name;
};

struct CLASSFILE {
    std::vector<std::string>    includes;
    std::string                 class_name;
    std::string                 parent_class_name;
    std::string                 file_name;
    std::vector<VARIABLE>       public_vars;
    std::vector<VARIABLE>       private_vars;
    std::vector<VARIABLE>       protected_vars;
    std::vector<std::string>    public_funcs;
    std::vector<std::string>    private_funcs;
    std::vector<std::string>    protected_funcs;
    vector<string>              classes_needed;
};

vector<pair<string, int>> ObjectVariables;
vector<string>            ObjectFunctions;
vector<int>               ObjectFunctionsType;
int                       InitialVarCount;

int class_count_alpha = 0;
bool any_class_changed = false;

int FindChar(char* str, char c) {
    char* strln = str;
    do {
        if (*strln == c)
            return strln - str;
        strln++;
    } while (*strln != 0);
    return -1;
}
int FindLastChar(char* str, char c) {
    char* strln = str + strlen(str);
    do {
        if (*strln == c)
            return strln - str;
        strln--;
    } while (strln != str);
    return -1;
}

string replaceFirstOccurrence(string& s,
    const string& toReplace,
    const string& replaceWith) {
    std::size_t pos = s.find(toReplace);
    if (pos == string::npos) return s;
    return s.replace(pos, toReplace.length(), replaceWith);
}

void print_class(const char* directory, CLASSFILE data) {
    string class_name(data.class_name);
    if (class_name == string("[HEYSTOP]"))
        return;
    if (class_name == string(""))
        return;

    FILE *fp;
    char filename[300];

    string direc = string(directory);
    if (direc.find("ImpostorEngine2") == std::string::npos)
        direc = replaceFirstOccurrence(direc, "source", "include");
    else
        direc = replaceFirstOccurrence(direc, "source", "gen");

    struct stat st = {0};
    if (direc.find("gen") != std::string::npos) {
        if (stat(direc.substr(0, direc.find("gen") + 3).c_str(), &st) == -1) {
            createDir(direc.substr(0, direc.find("gen") + 3).c_str());
        }
    }

    if (stat(direc.c_str(), &st) == -1) {
        createDir(direc.c_str());
    }

    sprintf(filename, "%s%s.h", direc.c_str(), data.file_name.c_str());
    //printf("%s\n", filename);
    fp = fopen(filename, "wb");
    if (!fp) {
        printf("Could not open: %s\n", filename);
        return;
    }

    class_count_alpha++;

    std::transform(class_name.begin(), class_name.end(), class_name.begin(), [](unsigned char c) -> unsigned char { return ::toupper(c); });

    //printf("==================\n");
    //printf("= %s.h\n", data.class_name.c_str());
    //printf("==================\n");
    //printf("\n");
    //printf("\n");
    fprintf(fp, "#ifndef %s_H\n", class_name.c_str());
    fprintf(fp, "#define %s_H\n", class_name.c_str());
    fprintf(fp, "\n");
    fprintf(fp, "#define PUBLIC\n");
    fprintf(fp, "#define PRIVATE\n");
    fprintf(fp, "#define PROTECTED\n");
    fprintf(fp, "#define STATIC\n");
    fprintf(fp, "#define VIRTUAL\n");
    fprintf(fp, "\n");
    for (int i = 0; i < data.classes_needed.size(); i++) {
        fprintf(fp, "class %s;\n", data.classes_needed[i].c_str());
    }
    fprintf(fp, "\n");

    for (std::vector<std::string>::iterator it = data.includes.begin(); it != data.includes.end(); ++it) {
        fprintf(fp, "#include %s\n", (*it).c_str());
    }
    fprintf(fp, "\n");
    fprintf(fp, "class %s%s%s {\n", data.class_name.c_str(), data.parent_class_name != string("") ? " : public " : "", data.parent_class_name != string("") ? data.parent_class_name.c_str() : "");
    bool damada = 0;
    if (data.private_vars.size() > 0 || data.private_funcs.size() > 0) {
        fprintf(fp, "private:\n");
        bool yamero = 0;
        for (std::vector<VARIABLE>::iterator it =
            data.private_vars.begin(); it !=
            data.private_vars.end(); ++it) {
            fprintf(fp, "    %s %s\n", (*it).class_type.c_str(), (*it).variable_name.c_str());
            yamero = 1;
        }

        if (yamero)
            fprintf(fp, "\n");

        for (std::vector<string>::iterator it =
            data.private_funcs.begin(); it !=
            data.private_funcs.end(); ++it) {
            fprintf(fp, "    %s\n", (*it).c_str());
        }
        damada = 1;
    }
    if (data.public_vars.size() > 0 || data.public_funcs.size() > 0) {
        if (damada)
            fprintf(fp, "\n");

        fprintf(fp, "public:\n");
        bool yamero = 0;
        for (std::vector<VARIABLE>::iterator it =
            data.public_vars.begin(); it !=
            data.public_vars.end(); ++it) {
            fprintf(fp, "    %s %s\n", (*it).class_type.c_str(), (*it).variable_name.c_str());
            yamero = 1;
        }

        if (yamero)
            fprintf(fp, "\n");

        for (std::vector<string>::iterator it =
            data.public_funcs.begin(); it !=
            data.public_funcs.end(); ++it) {
            fprintf(fp, "    %s\n", (*it).c_str());
        }
    }
    if (data.protected_vars.size() > 0 || data.protected_funcs.size() > 0) {
        if (damada)
            fprintf(fp, "\n");

        fprintf(fp, "protected:\n");
        bool yamero = 0;
        for (std::vector<VARIABLE>::iterator it =
            data.protected_vars.begin(); it !=
            data.protected_vars.end(); ++it) {
            fprintf(fp, "    %s %s\n", (*it).class_type.c_str(), (*it).variable_name.c_str());
            yamero = 1;
        }

        if (yamero)
            fprintf(fp, "\n");

        for (std::vector<string>::iterator it =
            data.protected_funcs.begin(); it !=
            data.protected_funcs.end(); ++it) {
            fprintf(fp, "    %s\n", (*it).c_str());
        }
    }
    fprintf(fp, "};\n");

    fprintf(fp, "\n");
    fprintf(fp, "#endif /* %s_H */\n", class_name.c_str());

    fclose(fp);
}

vector<string> ClassNames;
string find_classname(char* filename) {
    FILE *fp;
    fp = fopen(filename, "rb");
    if (!fp) {
        printf("Could not load file (find_classname): %s!\n", filename);
        exit(-69);
    }
    //

    bool in_interface = false;
    bool in_interfaced = false;
    int  in_variables = 0;

    // printf("find: %s\n", filename);

    while (true) {
        char first_token[255];
        if (fscanf(fp, "%s", first_token) <= 0) {
            break;
        }

        if (!strcmp(first_token, "#if")) {
            char rest_of_line[255];
            fscanf(fp, "%c", rest_of_line); // clears space
            fgets(rest_of_line, 255, fp);
            rest_of_line[strcspn(rest_of_line, "\r\n")] = 0; rest_of_line[strcspn(rest_of_line, "\n")] = 0;

            if (!strncmp(rest_of_line, "INTERFACE", 9)) {
                in_interface = true;
                in_interfaced = true;
            }
        }
        else {
            if (!in_interfaced) {
                fclose(fp);
                return string("");
            }
        }
        if (!strcmp(first_token, "#endif")) {
            char rest_of_line[255];
            fgets(rest_of_line, 255, fp);
            if (in_interface) {
                in_interface = false;
                in_variables = 0;
            }
        }
        else if (!strcmp(first_token, "class")) {
            char rest_of_line[255];
            fscanf(fp, "%s", rest_of_line);
            fclose(fp);

            return string(rest_of_line);
        }
    }
    return string("");
}

CLASSFILE load_class(char* filename) {
    FILE *fp;
    CLASSFILE test;
    fp = fopen(filename, "rb");
    if (!fp) {
        printf("Could not load file (load_class): %s!\n", filename);
        exit(-69);
    }
    //printf("Loading file: %s\n", filename);

    bool in_interface = false;
    bool in_interfaced = false;
    int  in_variables = 0;

    char ObjectName[256];
    int found = FindLastChar(filename, '/');
    memset(ObjectName, 0, 256);
    strcpy(ObjectName, filename + found + 1);
    int nextfind = FindChar(ObjectName, '.');
    memset(ObjectName + nextfind, 0, 256 - nextfind);

    test.file_name = string(ObjectName);

    int brackscope = 0;

    while (true) {
        char first_token[255];
        if (fscanf(fp, "%s", first_token) <= 0)
            break;

        if (!strcmp(first_token, "#if")) {
            char rest_of_line[255];
            fscanf(fp, "%c", rest_of_line); // clears space
            fgets(rest_of_line, 255, fp);
            rest_of_line[strcspn(rest_of_line, "\r\n")] = 0; rest_of_line[strcspn(rest_of_line, "\n")] = 0;

            if (!strncmp(rest_of_line, "INTERFACE", 9)) {
                in_interface = true;
                in_interfaced = true;
            }
        }
        else {
            if (!in_interfaced) {
                test.class_name = string("[HEYSTOP]");
                break;
            }
        }
        if (!strcmp(first_token, "#endif")) {
            char rest_of_line[255];
            fgets(rest_of_line, 255, fp);
            if (in_interface) {
                in_interface = false;
                in_variables = 0;
            }
        }
        else if (!strcmp(first_token, "#include")) {
            char rest_of_line[255];
            fscanf(fp, "%c", rest_of_line); // clears space
            fgets(rest_of_line, 255, fp);
            rest_of_line[strcspn(rest_of_line, "\r\n")] = 0; rest_of_line[strcspn(rest_of_line, "\n")] = 0;

            if (in_interface)
                test.includes.push_back(rest_of_line);
        }
        else if (!strcmp(first_token, "need_t")) {
            char rest_of_line[255];
            fscanf(fp, " ");
            fscanf(fp, "%[^;]", rest_of_line);

            test.classes_needed.push_back(string(rest_of_line));
        }
        else if (!strcmp(first_token, "class")) {
            if (test.class_name.empty()) {
                char rest_of_line[255];
                fscanf(fp, "%s", rest_of_line);

                test.class_name = std::string(rest_of_line);

                fgets(rest_of_line, 255, fp);
                rest_of_line[strcspn(rest_of_line, "\r\n")] = 0; rest_of_line[strcspn(rest_of_line, "\n")] = 0;

                char enws[255];
                if (sscanf(rest_of_line, " : public %s", enws) > 0) {
                    test.parent_class_name = std::string(enws);
                }

                in_variables = 1;
            }
        }
        else if (!strcmp(first_token, "{") || !strcmp(first_token, "}") || !strcmp(first_token, "};")) {
            if (!strcmp(first_token, "};")) {
                if (brackscope > 0) {
                    char rest_of_line[255];
                    fscanf(fp, "%c", rest_of_line); // clears space
                    fgets(rest_of_line, 255, fp);
                    rest_of_line[strcspn(rest_of_line, "\r\n")] = 0; rest_of_line[strcspn(rest_of_line, "\n")] = 0;

                    if (in_interface) {
                        if (in_variables == 1)
                            test.private_vars.push_back(VARIABLE { string(first_token), string() });
                        else if (in_variables == 2)
                            test.public_vars.push_back(VARIABLE { string(first_token), string() });
                        else if (in_variables == 3)
                            test.protected_vars.push_back(VARIABLE { string(first_token), string() });
                    }
                    brackscope--;
                }
                else {
                    in_variables = 0;
                    continue;
                }
            }
        }
        else if (!strcmp(first_token, "private:")) {
            in_variables = 1;
        }
        else if (!strcmp(first_token, "public:")) {
            in_variables = 2;
        }
        else if (!strcmp(first_token, "protected:")) {
            in_variables = 3;
        }
        else if (in_variables) {
            char nom[255];
            sscanf(first_token, "%[A-Za-z0-9_]", nom);

            if (!strcmp(nom, "struct") || !strcmp(nom, "enum"))
                brackscope++;

            char rest_of_line[255];
            fscanf(fp, "%c", rest_of_line); // clears space
            fgets(rest_of_line, 255, fp);
            rest_of_line[strcspn(rest_of_line, "\r\n")] = 0; rest_of_line[strcspn(rest_of_line, "\n")] = 0;

            for (int i = 0; i < ClassNames.size(); i++) {
                if (string(nom) == ClassNames[i]) {
                    test.classes_needed.push_back(string(nom));
                    break;
                }
            }

            if (in_interface) {
                if (in_variables == 1)
                    test.private_vars.push_back(VARIABLE { string(first_token), string(rest_of_line) });
                else if (in_variables == 2)
                    test.public_vars.push_back(VARIABLE { string(first_token), string(rest_of_line) });
                else if (in_variables == 3)
                    test.protected_vars.push_back(VARIABLE { string(first_token), string(rest_of_line) });
            }
        }
        else if ((!strcmp(first_token, "PUBLIC") || !strcmp(first_token, "PRIVATE") || !strcmp(first_token, "PROTECTED")) && !in_interface) {
            char* rest_of_line = (char*)malloc(512);
            fscanf(fp, "%c", rest_of_line); // clears space
            fgets(rest_of_line, 512, fp);
            rest_of_line[strcspn(rest_of_line, "\r\n")] = 0; rest_of_line[strcspn(rest_of_line, "\n")] = 0;

            bool statik = false;
            bool virtua = false;
            if (!strncmp(rest_of_line, "STATIC", 6)) {
                statik = true;
                char temp[512];
                sprintf(temp, "%s", rest_of_line + 7);
                strcpy(rest_of_line, temp);
            }
            if (!strncmp(rest_of_line, "VIRTUAL", 7)) {
                virtua = true;
                char temp[512];
                sprintf(temp, "%s", rest_of_line + 8);
                strcpy(rest_of_line, temp);
            }

            if (FindChar(rest_of_line, ':') < 0) {
                printf("\x1b[1;32mFatal Error: \x1b[0mCould not find class name for line '%s'.\n", rest_of_line);
                exit(1);
            }

            char* wherefunc = strstr(rest_of_line, (test.class_name + "::").c_str());
            if (!wherefunc) {
                printf("\x1b[1;32mFatal Error: \x1b[0mIncorrect class name `%.*s` (should be `%s`.)\n", FindChar(rest_of_line, ':'), rest_of_line, test.class_name.c_str());
                exit(1);
            }
            char* function_name = wherefunc + test.class_name.size() + 2;
            int ind = strlen(function_name) - 2;
            char* couldbe = strstr(function_name, ": ");
            if (couldbe != NULL) {
                ind = couldbe - function_name - 1;
            }
            if (function_name[ind] != ' ')
                ind++;
            function_name[ind] = ';';
            function_name[ind + 1] = 0;

            char type[500];
            if (wherefunc - rest_of_line > 0) {
                sprintf(type, "%s", rest_of_line);
                //printf("%s\n", type);
                type[wherefunc - rest_of_line] = 0;
            }
            else {
                sprintf(type, "%s", "");
            }

            char finalfunname[500];
            if (statik)
                sprintf(finalfunname, "%s%s%s", "static ", type, function_name);
            else if (virtua)
                sprintf(finalfunname, "%s%s%s", "virtual ", type, function_name);
            else
                sprintf(finalfunname, "%s%s", type, function_name);

            if (!strcmp(first_token, "PRIVATE"))
                test.private_funcs.push_back(string(finalfunname));
            else if (!strcmp(first_token, "PUBLIC"))
                test.public_funcs.push_back(string(finalfunname));
            else if (!strcmp(first_token, "PROTECTED"))
                test.protected_funcs.push_back(string(finalfunname));

            free(rest_of_line);
        }
        else if (!strcmp(first_token, "//") && !in_interface) {
            char rest_of_line[512];
            fscanf(fp, "%c", rest_of_line); // clears space
            fgets(rest_of_line, 512, fp);
            rest_of_line[strcspn(rest_of_line, "\r\n")] = 0; rest_of_line[strcspn(rest_of_line, "\n")] = 0;
        }
        else {
            //printf(">>>>>>>>>> %s\n", first_token);
            //break;
        }
    }

    fclose(fp);
    return test;
}

bool prelistdir(const char *name, int indent) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return false;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            sprintf(path, "%s/%s", name, entry->d_name);
            prelistdir(path, indent + 2);
        }
        else if (indent == 0) {
            continue;
        }
        else if (strstr(entry->d_name, ".cpp")) {
            char path[1024];
            sprintf(path, "%s/%s", name, entry->d_name);

            char newname[1024];
            sprintf(newname, "%s", name);
            size_t sz = strlen(name);
            if (newname[sz - 1] != '/') {
                newname[sz] = '/';
                newname[sz + 1] = 0;
            }

            string str = find_classname(path);
            if (str != "") {
                ClassNames.push_back(str);
            }
        }
    }
    closedir(dir);
    return true;
}
void listdir(const char *name, int indent) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            sprintf(path, "%s/%s", name, entry->d_name);
            listdir(path, indent + 2);
        }
        else if (indent == 0) {
            continue;
        }
        else if (strstr(entry->d_name, ".cpp")) {
            char path[1024];
            sprintf(path, "%s/%s", name, entry->d_name);

            char newname[1024];
            sprintf(newname, "%s", name);
            size_t sz = strlen(name);
            if (newname[sz - 1] != '/') {
                newname[sz] = '/';
                newname[sz + 1] = 0;
            }

            // printf("list: %s\n", path);

            print_class(newname, load_class(path));
        }
    }
    closedir(dir);
}

struct ClassHash {
    uint32_t FilenameHash;
    uint32_t InterfaceChecksum;
};
vector<ClassHash> ClassHashes;
int GetClassHash(uint32_t filenameHash) {
    for (int i = 0; i < ClassHashes.size(); i++) {
        if (ClassHashes[i].FilenameHash == filenameHash)
            return i;
    }
    return -1;
}
int PutClassHash(uint32_t filenameHash, uint32_t checkSum) {
    int idx = GetClassHash(filenameHash);
    if (idx >= 0) {
        ClassHashes[idx].FilenameHash = filenameHash;
        ClassHashes[idx].InterfaceChecksum = checkSum;
        return 0;
    }

    ClassHash ch;
    ch.FilenameHash = filenameHash;
    ch.InterfaceChecksum = checkSum;
    ClassHashes.push_back(ch);
    return 1;
}
void LoadClassHashTable() {
    #if MSVC
    FILE* f = fopen("../makeheaders.bin", "rb");
    #else
	FILE* f = fopen("makeheaders.bin", "rb");
    #endif
    if (f) {
        for (;;) {
            ClassHash ch;
            if (fread(&ch, sizeof(ClassHash), 1, f) <= 0)
                break;

            ClassHashes.push_back(ch);
        }
        fclose(f);
    }
}
void SaveClassHashTable() {
    #if MSVC
	FILE* f = fopen("../makeheaders.bin", "wb");
    #else
	FILE* f = fopen("makeheaders.bin", "wb");
    #endif
    if (f) {
        for (int i = 0; i < ClassHashes.size(); i++) {
            fwrite(&ClassHashes[i], sizeof(ClassHash), 1, f);
        }
        fclose(f);
    }
}

bool MakeHeader(char* filename) {
    if (FindChar(filename, '.') < 0) {
        PrintHeader(stderr, "error: ", PrintColor::Red);
        fprintf(stderr, "Could not find '.' in '%s'!\n", filename);
        exit(-69);
        return false;
    }

    bool didChange = false;

    FILE* f = fopen(filename, "rb");
    if (!f) {
        PrintHeader(stderr, "error: ", PrintColor::Red);
        fprintf(stderr, "Could not open file '%s'!\n", filename);
        exit(-69);
    }

    int interfaceStart = -1;
    int interfaceEnd = -1;

    int found, nextfind;
    char* HeaderName = (char*)calloc(1, 256);

    found = FindLastChar(filename, '/');
    nextfind = FindChar(filename + found + 1, '.');
    strncpy(HeaderName, filename + found + 1, nextfind);
    memset(HeaderName + nextfind, 0, 256 - nextfind);

    // printf("HeaderName: %s (%d)\n", HeaderName, strlen(HeaderName));

    int ifScope = 0;
    while (true) {
        int64_t tokenStart = ftell(f);

        char first_token[255];
        if (fscanf(f, "%s", first_token) <= 0) {
            // printf("reached EOF\n");
            break;
        }

        if (!strcmp(first_token, "#if")) {
            fscanf(f, " ");
            char rest_of_line[255];
            fgets(rest_of_line, 255, f);
            rest_of_line[strcspn(rest_of_line, "\n")] = 0;
            rest_of_line[strcspn(rest_of_line, "\r\n")] = 0;

            if (!strncmp(rest_of_line, "INTERFACE", 9)) {
                interfaceStart = ftell(f);
            }

            ifScope++;
        }
        else if (!strcmp(first_token, "#endif")) {
            ifScope--;
            if (ifScope == 0) {
                interfaceEnd = tokenStart;
                break;
            }
        }
    }

    // get function descriptors
    // rewind(f);
    uint32_t FDChecksum = 0x00000000;
    while (true) {
        char rest_of_line[1024];
        if (!fgets(rest_of_line, 1024, f)) {
            // printf("reached EOF\n");
            break;
        }

        // printf("rest_of_line: %s\n", rest_of_line);

        if ((!strncmp(rest_of_line, "PUBLIC", 6) || !strncmp(rest_of_line, "PRIVATE", 7) || !strncmp(rest_of_line, "PROTECTED", 9))) {
            rest_of_line[strcspn(rest_of_line, "\r\n")] = 0; rest_of_line[strcspn(rest_of_line, "\n")] = 0;

            // printf("rest_of_line: %s\n", rest_of_line);

            FDChecksum = crc32_inc(rest_of_line, strlen(rest_of_line), FDChecksum);
        }
    }

    if (interfaceStart == -1) {
        return false;
    }
    if (interfaceStart != -1 && interfaceEnd == -1) {
        PrintHeader(stderr, "error: ", PrintColor::Red);
        fprintf(stderr, "Missing matching #endif in file '%s'!\n", filename);
        exit(-69);
        return false;
    }

    char* interfaceField = (char*)calloc(1, interfaceEnd - interfaceStart + 1);
    fseek(f, interfaceStart, SEEK_SET);
    fread(interfaceField, interfaceEnd - interfaceStart, 1, f);

    uint32_t Namehash = crc32(filename, strlen(filename));

    uint32_t Checksum = 0x00000000;
    uint32_t ComparisonHash = 0x00000000;

    int idx = -1;
    if ((idx = GetClassHash(Namehash)) != -1)
        ComparisonHash = ClassHashes[idx].InterfaceChecksum;

    Checksum = crc32_inc(interfaceField, interfaceEnd - interfaceStart, FDChecksum);
	didChange = Checksum != ComparisonHash;

    // printf("%s: %X\n", HeaderName, FDChecksum);
    // printf("%X\n", Checksum);
    // printf("%X\n", ComparisonHash);

    if (!didChange) {
        SaveClassHashTable();
        return didChange;
    }

    PutClassHash(Namehash, Checksum);

    // if (stat(genfilenamebase, &st) == -1)
    //     didChange = true;

    /*
    while (true) {
        char first_token[255];
        if (fscanf(fp, "%s", first_token) <= 0)
            break;

        if (!strcmp(first_token, "#if")) {
            char rest_of_line[255];
            fscanf(fp, "%c", rest_of_line); // clears space
            fgets(rest_of_line, 255, fp);
            rest_of_line[strcspn(rest_of_line, "\r\n")] = 0; rest_of_line[strcspn(rest_of_line, "\n")] = 0;

            if (!strncmp(rest_of_line, "INTERFACE", 9)) {
                in_interface = true;
                in_interfaced = true;
            }
        }
        else {
            if (!in_interfaced) {
                test.class_name = string("[HEYSTOP]");
                break;
            }
        }
        if (!strcmp(first_token, "#endif")) {
            char rest_of_line[255];
            fgets(rest_of_line, 255, fp);
            if (in_interface) {
                in_interface = false;
                in_variables = 0;
            }
        }
    }

    uint32_t Namehash = crc32(filename, strlen(filename));

    uint32_t Checksum = 0x00000000;
    uint32_t ComparisonHash = 0x00000000;
    if ((idx = GetObjectHash(Namehash)) != -1) {
        ComparisonHash = ObjectHashes[idx].Checksum;
        ObjectID = ObjectHashes[idx].ObjectID;
        SKOnly = (bool)ObjectHashes[idx].SKOnly;
    }

    FILE* f = fopen(fullname, "rb");
    if (f) {
        Checksum = crc32_file(f);
    	noChange = Checksum == ComparisonHash;
        fclose(f);
    }

    char objectNameCopy[256];
    memset(objectNameCopy, 0, 256);
    strncpy(objectNameCopy, filename, FindLastChar(filename, '.'));

    const char* extension = "obj";

    char genfilenamebase[1024];
    memset(genfilenamebase, 0, 1024);
    strcpy(genfilenamebase, parent);
    strcat(genfilenamebase, "/Gen");
    strcat(genfilenamebase, fullname + startindex);
    memset(genfilenamebase + (strlen(genfilenamebase) - strlen(extension)), 0, 1024 - (strlen(genfilenamebase) - strlen(extension)));
    strcat(genfilenamebase, "cpp");

    if (stat(genfilenamebase, &st) == -1)
        noChange = false;

    memset(genfilenamebase + (strlen(genfilenamebase) - strlen(extension)), 0, 1024 - (strlen(genfilenamebase) - strlen(extension)));

    if (noChange)
        goto DONE;

    PrintHeader(stdout, "Converting ImpostorScript: ", PrintColor::Green);
    printf("%s\n", filename);

    char genfolder[1024];
    memset(genfolder, 0, 1024);
    strcpy(genfolder, parent);
    strcat(genfolder, "/Gen/");
    strcat(genfolder, fullname + startindex);
    memset(genfolder + (strlen(genfolder) - strlen(filename) - 1), 0, 1024 - (strlen(genfolder) - strlen(filename) - 1));

    if (stat(genfolder, &st) == -1)
        createDir(genfolder);

    ObjectID = ParseIScript(fullname, genfilenamebase, objectNameCopy);
    PutObjectHash(Namehash, Checksum, ObjectID, SKOnly);

    DONE:
    SaveObjectHashTable();

    if (ObjectID < 0)
        ObjectID = ExtraObjectIndex++;

    ObjectNamesAndIDs.push_back(tuple<string, string, int>{ string(genfilenamebase + startindex + strlen("/Gen/")), string(objectNameCopy), ObjectID });
    //*/
    return didChange;
}
bool ListClassDir(const char* name, const char* parent, int indent) {
    DIR* dir;
    struct dirent* entry;

    if (!(dir = opendir(name)))
        return false;

    char path[1024];
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        sprintf(path, "%s/%s", name, entry->d_name);

        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, "Gen") == 0) continue;

            ListClassDir(path, parent, indent + 2);
        }
        else if (strstr(entry->d_name, ".cpp")) {
            if (MakeHeader(path)) {
                char newname[1024];
                sprintf(newname, "%s", name);
                size_t sz = strlen(name);
                if (newname[sz - 1] != '/') {
                    newname[sz] = '/';
                    newname[sz + 1] = 0;
                }

                print_class(newname, load_class(path));
            }
        }
    }
    closedir(dir);
    return true;
}

struct ObjectHash {
    uint32_t FilenameHash;
    uint32_t Checksum;
    uint32_t ObjectID;
    uint8_t  Unk1;
    uint8_t  Unk2;
    uint8_t  Unk3;
    uint8_t  SKOnly;
};
vector<ObjectHash> ObjectHashes;
int GetObjectHash(uint32_t filenameHash) {
    for (int i = 0; i < ObjectHashes.size(); i++) {
        if (ObjectHashes[i].FilenameHash == filenameHash)
            return i;
    }
    return -1;
}
int PutObjectHash(uint32_t filenameHash, uint32_t checkSum, uint32_t objectID, bool skOnly) {
    int idx = GetObjectHash(filenameHash);
    if (idx >= 0) {
        ObjectHashes[idx].FilenameHash = filenameHash;
        ObjectHashes[idx].Checksum = checkSum;
        ObjectHashes[idx].ObjectID = objectID;
        ObjectHashes[idx].SKOnly = (uint8_t)skOnly;
        return 0; // returns if this is a new value inserted
    }

    ObjectHash oh;
    oh.FilenameHash = filenameHash;
    oh.Checksum = checkSum;
    oh.ObjectID = objectID;
    oh.Unk1 = 0;
    oh.Unk2 = 0;
    oh.Unk3 = 0;
    oh.SKOnly = (uint8_t)skOnly;
    ObjectHashes.push_back(oh);
    return 1;
}
void LoadObjectHashTable() {
    #if MSVC
    FILE* f = fopen("../ie2_objtable.bin", "rb");
    #else
	FILE* f = fopen("ie2_objtable.bin", "rb");
    #endif
    if (f) {
        for (;;) {
            ObjectHash oh;
            if (fread(&oh, sizeof(ObjectHash), 1, f) <= 0)
                break;

            ObjectHashes.push_back(oh);
        }
        fclose(f);
    }
}
void SaveObjectHashTable() {
    #if MSVC
	FILE* f = fopen("../ie2_objtable.bin", "wb");
    #else
	FILE* f = fopen("ie2_objtable.bin", "wb");
    #endif
    if (f) {
        for (int i = 0; i < ObjectHashes.size(); i++) {
            fwrite(&ObjectHashes[i], sizeof(ObjectHash), 1, f);
        }
        fclose(f);
    }
}

bool compareObjectNamesAndIDs(tuple<string, string, int> i1, tuple<string, string, int> i2) {
	return (get<2>(i1) < get<2>(i2));
}

int ExtraObjectIndex = 0x400;
vector<tuple<string, string, int>> ObjectNamesAndIDs;
void ConvertIScriptToC(char* fullname, const char* parent, int startindex, char* filename) {
    if (FindChar(filename, '.') < 0)
        return;

    int idx;
    struct stat st;
    int     ObjectID = -1;
    bool    SKOnly = false;

    bool noChange = false;

    uint32_t Namehash = crc32(filename, strlen(filename));

    uint32_t Checksum = 0x00000000;
    uint32_t ComparisonHash = 0x00000000;
    if ((idx = GetObjectHash(Namehash)) != -1) {
        ComparisonHash = ObjectHashes[idx].Checksum;
        ObjectID = ObjectHashes[idx].ObjectID;
        SKOnly = (bool)ObjectHashes[idx].SKOnly;
    }

    FILE* f = fopen(fullname, "rb");
    if (f) {
        Checksum = crc32_file(f);
    	noChange = Checksum == ComparisonHash;
        fclose(f);
    }

    char objectNameCopy[256];
    memset(objectNameCopy, 0, 256);
    strncpy(objectNameCopy, filename, FindLastChar(filename, '.'));

    const char* extension = "obj";
	int extensionLength = 3;

    char genfilenamebase[1024];
    memset(genfilenamebase, 0, 1024);
    strcpy(genfilenamebase, parent);
    strcat(genfilenamebase, "/Gen");
    strcat(genfilenamebase, fullname + startindex);
    memset(genfilenamebase + (strlen(genfilenamebase) - extensionLength), 0, 1024 - (strlen(genfilenamebase) - extensionLength));
    strcat(genfilenamebase, "cpp");

    if (stat(genfilenamebase, &st) == -1)
        noChange = false;

    memset(genfilenamebase + (strlen(genfilenamebase) - extensionLength), 0, 1024 - (strlen(genfilenamebase) - extensionLength));

    if (noChange)
        goto DONE;

    PrintHeader(stdout, "Converting ImpostorScript: ", PrintColor::Green);
    printf("%s\n", filename);

    char genfolder[1024];
    memset(genfolder, 0, 1024);
    strcpy(genfolder, parent);
    strcat(genfolder, "/Gen/");
    strcat(genfolder, fullname + startindex);
    memset(genfolder + (strlen(genfolder) - strlen(filename) - 1), 0, 1024 - (strlen(genfolder) - strlen(filename) - 1));

    if (stat(genfolder, &st) == -1)
        createDir(genfolder);

    ObjectID = ParseIScript(fullname, genfilenamebase, objectNameCopy);
    PutObjectHash(Namehash, Checksum, ObjectID, SKOnly);

    DONE:
    SaveObjectHashTable();

    if (ObjectID < 0)
        ObjectID = ExtraObjectIndex++;

    ObjectNamesAndIDs.push_back(tuple<string, string, int>{ string(genfilenamebase + startindex + strlen("/Gen/")), string(objectNameCopy), ObjectID });
}
bool ListObjectDir(const char* name, const char* parent, int indent) {
    DIR* dir;
    struct dirent* entry;

    if (!(dir = opendir(name)))
        return false;

    char path[1024];
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        sprintf(path, "%s/%s", name, entry->d_name);

        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, "Gen") == 0) continue;

            ListObjectDir(path, parent, indent + 2);
        }
        else if (strstr(entry->d_name, ".obj") || strstr(entry->d_name, ".ie2")) {
            ConvertIScriptToC(path, parent, strlen(parent), entry->d_name);
        }
    }
    closedir(dir);

    return true;
}
void MakeObjectListing(char* fullpath) {
    PrintHeader(stdout, "Generating Object Listing...\n", PrintColor::Green);

	sort(ObjectNamesAndIDs.begin(), ObjectNamesAndIDs.end(), compareObjectNamesAndIDs);

    char* fullasspath = (char*)calloc(1, 1024);
    sprintf(fullasspath, "%s/Gen", fullpath);

    struct stat st;
    if (stat(fullasspath, &st) == -1)
        createDir(fullasspath);

    sprintf(fullasspath, "%s/Gen/ObjectListing.h", fullpath);
    //printf("%s\n", fullasspath);
    //#include "Spring.h"

    const char* template1 = "#ifndef OBJECTLISTING_H\n#define OBJECTLISTING_H\n\n%s\nObject* GetNewObjectFromID(int ID);\nObject* GetNewObjectFromCRC32(uint32_t Hash);\n\n#endif /* OBJECTLISTING_H */";
    const char* template2 = "#include \"ObjectListing.h\"\n\nObject* GetNewObjectFromID(int ID) {\n    switch (ID) {\n%s\n        default:\n            break;\n    }\n    return NULL;\n}\n\nObject* GetNewObjectFromCRC32(uint32_t Hash) {\n    switch (Hash) {\n%s\n        default:\n            break;\n    }\n    return NULL;\n}";
    const char* temp2 = "        case 0x%02XU:\n\
            return new %s();\n\
            break;\n";

    MD5_CTX* ctx = (MD5_CTX*)malloc(sizeof(MD5_CTX));
    memset(ctx, 0, sizeof(MD5_CTX));
    unsigned char* md5Data = (unsigned char*)calloc(1, 17);
    char* md5String = (char*)calloc(1, 100);

    string includes;
    string sauce;
	string sauceHash;
    char* ObjectListSourcePart = (char*)calloc(1, 8024);
    for (int i = 0; i < ObjectNamesAndIDs.size(); i++) {
        includes += "#include \"" + get<0>(ObjectNamesAndIDs[i]) + "h\"";

        MD5_Init(ctx);
        MD5_Update(ctx, get<1>(ObjectNamesAndIDs[i]).c_str(), get<1>(ObjectNamesAndIDs[i]).length());
        MD5_Final(md5Data, ctx);

        sprintf(md5String, "%X", crc32((char*)md5Data, 16));

        includes += "\t\t\t// ";
        includes += md5String;

        includes += "\n";

        sprintf(ObjectListSourcePart, temp2, get<2>(ObjectNamesAndIDs[i]), get<1>(ObjectNamesAndIDs[i]).c_str());
        sauce += ObjectListSourcePart;

		sprintf(ObjectListSourcePart, temp2, crc32((char*)md5Data, 16), get<1>(ObjectNamesAndIDs[i]).c_str());
		sauceHash += ObjectListSourcePart;
    }

    includes += "\n\n";

    includes += "enum {\n";
    for (int i = 0; i < ObjectNamesAndIDs.size(); i++) {
        includes += "    ";
        includes += "Obj_" + get<1>(ObjectNamesAndIDs[i]) + " = ";
        sprintf(ObjectListSourcePart, "0x%03X", get<2>(ObjectNamesAndIDs[i]));
        includes += ObjectListSourcePart;
        includes += ",\n";
    }
    includes += "};\n";

    char* ObjectListHeader = (char*)calloc(1, 12024);
    sprintf(ObjectListHeader, template1, includes.c_str());
    //printf("%s\n\n\n", ObjectListHeader);
    FILE* f = fopen(fullasspath, "wb");
    if (!f) {
        printf("\x1b[1;31mFatal Error:\x1b[0m Could not open file '%s'!\n", fullasspath);
        return;
    }
    fprintf(f, "%s", ObjectListHeader);
    fclose(f);



    sprintf(fullasspath, "%s/Gen/ObjectListing.cpp", fullpath);
    //printf("%s\n", fullasspath);

    char* ObjectListSource = (char*)calloc(1, 30720);
    sprintf(ObjectListSource, template2, sauce.c_str(), sauceHash.c_str());
    //printf("%s\n\n\n", ObjectListSource);
    f = fopen(fullasspath, "wb");
    if (!f) {
        printf("\x1b[1;31mFatal Error:\x1b[0m Could not open file '%s'!\n", fullasspath);
        return;
    }
    fprintf(f, "%s", ObjectListSource);
    fclose(f);

    free(fullasspath);
    free(ObjectListSourcePart);
    free(ObjectListHeader);
    free(ObjectListSource);
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        printf("No source code path!\n");
        printf("Usage:\n");
		printf("    %s [options] path\n", argv[0]);
        return 0;
    }

    char finalpath[256];

    printf("\n");
    // printf("Desired Directory: '%s' (%s)\n", argv[1], argv[1][0] == '/' ? "ABSOLUTE" : "RELATIVE");

    if (argv[1][0] == '/') {
        sprintf(finalpath, "%s%s", argv[1], "");
    }
    else {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        sprintf(finalpath, "%s/%s%s", cwd, argv[1], "");
    }
    #if MSVC
    _fullpath(finalpath, argv[1], 256);
    #else
    realpath(argv[1], finalpath);
    #endif
    // printf("Final Directory: '%s'\n", finalpath);

    clock_t start, stop;
    start = clock();

    LoadClassHashTable();
    if (prelistdir(finalpath, 0)) {
        ListClassDir(finalpath, finalpath, 0);
    }
    SaveClassHashTable();

    sprintf(finalpath, "%s%s", finalpath, "/Game/Objects");

    // Create Gen if not already there
    char* fullasspath = (char*)malloc(1024);
    sprintf(fullasspath, "%s/Gen", finalpath);
    struct stat st;
    if (stat(fullasspath, &st) == -1)
        createDir(fullasspath);

    LoadObjectHashTable();

    InitAll();
    if (ListObjectDir(finalpath, finalpath, 0))
        MakeObjectListing(finalpath);
    GarbageCollect();

    stop = clock();
    PrintHeader(stdout, "makeheaders: ", PrintColor::Green);
    printf("Generated %d header(s) in %.3f milliseconds.\n\n", class_count_alpha, (stop - start) * 1000.f / CLOCKS_PER_SEC);

    return 0;
}
