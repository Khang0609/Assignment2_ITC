#include <iostream>
using namespace std;

int getIndex(char char_arr[], int size, char target)
{
    for (int i = 0; i < size; i++)
    {
        if (target == char_arr[i])
        {
            return i;
        }
    }
    return -1;
}

bool isValid(string &word)
{
    // The input word must contain only 12 target), ' and spaces.
    char valid_char[14] = {'a', 'e', 'i', 'o', 'u', 'p', 'k', 'h', 'l', 'm', 'n', 'w', '\'', ' '};
    for (char letter : word)
    {
        if (getIndex(valid_char, 14, letter) == -1)
        {
            return false;
        }
    }
    return true;
}

void consonantConvert(string &word, int length)
{
    char cur, before;
    for (int count = 1; count < length; count++)
    {
        cur = word[count];
        before = word[count - 1];
        if ((before == 'e' || before == 'i') && cur == 'w')
        {
            word[count] = 'v';
        }
    }
}

string finalConvert(string &word, int len) {
    string result = "";
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    string vowel_sounds[] = {"ah", "eh", "ee", "oh", "oo"};
    
    string groups[] = {"ai", "ae", "ao", "au", "ei", "eu", "iu", "oi", "ou", "ui"};
    string group_sounds[] = {"eye", "eye", "ow", "ow", "ay", "eh-oo", "ew", "oy", "ow", "ooey"};

    int i = 0;

    while (i < len) {
        char cur = word[i];
        
        // 1. Handle Separators (Space, Apostrophe)
        if (cur == ' ' || cur == '\'') {
            result += cur;
            i++;
            continue;
        }

        // 2. Check Consonants
        int vIndex = getIndex(vowels, 5, cur);
        if (vIndex == -1) {
            // It is a consonant. 
            result += cur;
            i++;
        } 
        else {
            // 3. It is a Vowel. Check for Groups first.
            bool groupFound = false;
            
            // Check if we have room for a group (i+1 < len)
            if (i + 1 < len) {
                string potentialGroup = "";
                potentialGroup += cur;
                potentialGroup += word[i+1];
                
                for (int g = 0; g < 10; g++) {
                    if (groups[g] == potentialGroup) {
                        result += group_sounds[g];
                        i += 2; // Skip both letters
                        groupFound = true;
                        break;
                    }
                }
            }

            // 4. If no group, single vowel sound
            if (!groupFound) {
                result += vowel_sounds[vIndex];
                i++; // Skip one letter
            }

            // 5. HYPHEN RULE
            if (i < len) {
                char nextChar = word[i]; // 'i' is already pointing to the next char
                if (nextChar != ' ' && nextChar != '\'') {
                    result += "-";
                }
            }
        }
    }
    return result;
}

string lowerString(string &str)
{
    string result = "";
    for (char c : str)
    {
        result += string(1, tolower(c));
    }
    return result;
}

int main()
{
    string word;
    int length;
    getline(cin, word);
    string remain = word;
    word = lowerString(word);
    bool valid_word = isValid(word);
    if (!valid_word){
        cout << remain << " contains invalid characters.";
        return 0;
    }
    length = word.length();

    string pronunciation = word;

    // Check for the consonant
    consonantConvert(pronunciation, length);

    // Change all vowel left.
    string result = finalConvert(pronunciation, length);

    cout << result << endl;

    return 0;
}