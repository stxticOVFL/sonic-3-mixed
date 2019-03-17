#if INTERFACE
#include <Utils/Standard.h>
#include <Engine/IApp.h>

class IINI {
public:
    struct ConfigItems {
        char section[60];
        bool hasSection;
    	char key[60];
    	char value[60];
    };

    ConfigItems item[80];

    int count;
};
#endif

#include <Engine/IINI.h>
#include <algorithm>
#include <vector>

PUBLIC IINI::IINI(const char* filename) {
    char buf[120];
    char section[60];
    bool hasSection = false;
    char key[60];
    char value[60];

    count = 0;

    FILE* f;
	if ((f = fopen(filename, "rb")) == NULL) {
		IApp::Print(2, "Couldn't open file '%s'!", filename);
		return;
	}

	while (fgets(buf, sizeof(buf), f) != NULL) {
        if (buf[0] == '#') continue;

        if (sscanf(buf, "[%[^][]]", section) == 1) {
			hasSection = true;
		}
		else if (sscanf(buf, "%[^ =]= %s", key, value) == 2 ||
            sscanf(buf, "%[^ =]=%s", key, value) == 2 ||
            sscanf(buf, "%[^ =] = %s", key, value) == 2 ||
            sscanf(buf, "%[^ =] =%s", key, value) == 2) {
            if (hasSection) {
                strcpy(item[count].section, section);
            }
			strcpy(item[count].key, key);
			strcpy(item[count].value, value);
            item[count].hasSection = hasSection;
            // printf("[%s] %s = %s\n", item[count].section, item[count].key, item[count].value);
			count++;
		}
	}

    fclose(f);
}

PUBLIC std::string IINI::GetString(const char* section, const char* key) {
    std::string str;
    if (count == 0)
		return str;

	for (int x = 0; x < count; x++) {
		if (!strcmp(section, item[x].section)) {
    		if (!strcmp(key, item[x].key)) {
    			str = item[x].value;
    			return str;
    		}
        }
	}

	return str;
}
PUBLIC int IINI::GetString(const char* section, const char* key, char* dest) {
	if (count == 0)
		return 0;

	for (int x = 0; x < count; x++) {
        if (!strcmp(section, item[x].section)) {
    		if (!strcmp(key, item[x].key)) {
    			strcpy(dest, item[x].value);
    			return 1;
    		}
        }
	}

	return 0;
}
PUBLIC int IINI::GetInteger(const char* section, const char* key, int* dest) {
	if (count == 0)
		return 0;

	for (int x = 0; x < count; x++) {
        if (!strcmp(section, item[x].section)) {
    		if (!strcmp(key, item[x].key)) {
    			*dest = atoi(item[x].value);
    			return 1;
    		}
        }
	}

	return 0;
}
PUBLIC int IINI::GetBool(const char* section, const char* key, bool* dest) {
	if (count == 0)
		return 0;

	for (int x = 0; x < count; x++) {
        if (!strcmp(section, item[x].section)) {
    		if (!strcmp(key, item[x].key)) {
                *dest = !strcmp(item[x].value, "true") || !strcmp(item[x].value, "1");
    			return 1;
    		}
        }
	}

	return 0;
}

PUBLIC int IINI::SetString(const char* section, const char* key, char* value) {
    int where = -1;
	for (int x = 0; x < count; x++) {
		if (strcmp(section, item[x].section) == 0) {
    		if (strcmp(key, item[x].key) == 0) {
    			where = x;
                break;
    		}
        }
	}
    if (where < 0)
        where = count++;

    strcpy(item[where].section, section);
    strcpy(item[where].key, key);
    strcpy(item[where].value, value);
	return 1;
}
PUBLIC int IINI::SetInteger(const char* section, const char* key, int value) {
    int where = -1;
	for (int x = 0; x < count; x++) {
		if (strcmp(section, item[x].section) == 0) {
    		if (strcmp(key, item[x].key) == 0) {
    			where = x;
                break;
    		}
        }
	}
    if (where < 0)
        where = count++;

    strcpy(item[where].section, section);
    strcpy(item[where].key, key);
    sprintf(item[where].value, "%d", value);
	return 1;
}
PUBLIC int IINI::SetBool(const char* section, const char* key, bool value) {
    int where = -1;
	for (int x = 0; x < count; x++) {
		if (strcmp(section, item[x].section) == 0) {
    		if (strcmp(key, item[x].key) == 0) {
    			where = x;
                break;
    		}
        }
	}
    if (where < 0)
        where = count++;

    strcpy(item[where].section, section);
    strcpy(item[where].key, key);
    sprintf(item[where].value, "%d", value);
	return 1;
}

PUBLIC void IINI::Write(const char* filename) {

	FILE* f;
	if ((f = fopen(filename, "w")) == NULL) {
		IApp::Print(2, "Couldn't open file '%s' for writing!", filename);
		return;
	}

	//below is the virgin rdc way
	//enter if you dare
	/*fprintf(f, "[%s]\n", "display");
	for (int i = 0; i < count; i++)
	{
		IApp::Print(0, item[i].section);
		if (item[i].section[0] == 'd') //fuck you too!
		{
			if (item[i].section[1] == 'i') //fuck you too!
			{
				fprintf(f, "%s = %s\n", item[i].key, item[i].value);
			}
		}
	}

	fprintf(f, "[%s]\n", "input1");
	for (int i = 0; i < count; i++)
	{
		if (item[i].section[0] == 'i')
		{
			if (item[i].section[5] == '1')
			{
				fprintf(f, "%s = %s\n", item[i].key, item[i].value);
			}
		}
	}

	fprintf(f, "[%s]\n", "input2");
	for (int i = 0; i < count; i++)
	{
		if (item[i].section[0] == 'i')
		{
			if (item[i].section[5] == '2')
			{
				fprintf(f, "%s = %s\n", item[i].key, item[i].value);
			}
		}
	}

	fprintf(f, "[%s]\n", "audio");
	for (int i = 0; i < count; i++)
	{
		if (item[i].section[0] == 'a') //fuck you too!
		{
			fprintf(f, "%s = %s\n", item[i].key, item[i].value);
		}
	}

	fprintf(f, "[%s]\n", "dev");
	for (int i = 0; i < count; i++)
	{
		if (item[i].section[0] == 'd') //fuck you too!
		{
			if (item[i].section[1] == 'e') //fuck you too!
			{
				fprintf(f, "%s = %s\n", item[i].key, item[i].value);
			}
		}
	}//*/

	//the chad rmg way that took like 3 hours
	char sections[10][60]; //extend when needed
	char past[60];
	int k = 0;
	for (int i = 0; i < count; i++) {
		if (std::find(std::begin(sections), std::end(sections), item[i].section) == std::end(sections) && strcmp(past, item[i].section) != 0) {
			strcpy(past, item[i].section);
			//past = item[i].section;
			strcpy(sections[k], item[i].section);
			IApp::Print(0, "%s %s %s", sections[k], item[i].section, past);
			k++;
		}
	}

	if (strcmp(sections[0], sections[k - 1]) == 0)
		k--;

	for (int i = 0; i < k; i++) {
		fprintf(f, "[%s]\n", sections[i]);
		for (int j = 0; j < count; j++) {
			if (strcmp(sections[i], item[j].section) == 0)
				fprintf(f, "%s = %s\n", item[j].key, item[j].value);
		}
	}

	fclose(f);
}

PUBLIC void IINI::Cleanup() {

}
