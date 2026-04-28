char* mergeCharacters(char* s, int k) {
    int n = strlen(s);
    char* result = (char*)malloc((n + 1) * sizeof(char));
    strcpy(result, s);

    int changed = 1;

    while (changed) {
        changed = 0;
        n = strlen(result);

        int letters[26];
        for (int i = 0; i < 26; i++)
            letters[i] = -1;

        for (int i = 0; i < n; i++) {
            int idx = result[i] - 'a';

            if (letters[idx] != -1 && i - letters[idx] <= k) {
                
                // remove current character (merge right into left)
                for (int t = i; t < n; t++)
                    result[t] = result[t + 1];

                changed = 1;
                break;  // restart after one merge
            }

            letters[idx] = i;
        }
    }

    return result;
}
