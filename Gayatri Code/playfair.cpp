//PlayFair Cipher

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class PlayfairCipher {
 private:
  static pair<vector<vector<char>>, unordered_map<char, pair<int, int>>>
  getKeyMatrixAndPositions(const string& key) {
    vector<vector<char>> keyMatrix(5, vector<char>(5));
    int i = 0, j = 0;
    unordered_set<char> set;
    unordered_map<char, pair<int, int>> position;

    for (char c : key) {
      if (c == 'j')
        c = 'i';

      if (set.find(c) != set.end())
        continue;

      set.insert(c);
      keyMatrix[i][j] = c;
      position[c] = {i, j};

      j++;
      if (j == 5) {
        j = 0;
        i++;
      }
    }

    for (char c = 'a'; c <= 'z'; c++) {
      if (c == 'j')
        continue;

      if (set.find(c) != set.end())
        continue;

      set.insert(c);
      keyMatrix[i][j] = c;
      position[c] = {i, j};

      j++;
      if (j == 5) {
        j = 0;
        i++;
      }
    }

    position[j] = position[i];

    return {keyMatrix, position};
  }

  static vector<string> getDiagrams(const string& text) {
    int n = text.size();
    int i = 0;
    vector<string> diagrams;

    while (i + 1 < n) {
      if (text[i] != text[i + 1]) {
        string d;
        d += tolower(text[i]);
        d += tolower(text[i + 1]);
        diagrams.push_back(d);

        i += 2;
      } else {
        string d;
        d += tolower(text[i]);
        d += 'x';
        diagrams.push_back(d);

        i++;
      }
    }

    if (i == n - 1) {
      string d;
      d += tolower(text[i]);
      d += 'x';
      diagrams.push_back(d);
    }

    return diagrams;
  }

 public:
  static string encrypt(const string& plaintext, const string& key) {
    auto [keyMatrix, position] = getKeyMatrixAndPositions(key);
    vector<string> diagrams = getDiagrams(plaintext);
    string ciphertext;

    for (string& diagram : diagrams) {
      auto [i0, j0] = position[diagram[0]];
      auto [i1, j1] = position[diagram[1]];

      if (i0 == i1) {
        diagram[0] = keyMatrix[i0][(j0 + 1) % 5];
        diagram[1] = keyMatrix[i0][(j1 + 1) % 5];
      } else if (j0 == j1) {
        diagram[0] = keyMatrix[(i0 + 1) % 5][j0];
        diagram[1] = keyMatrix[(i1 + 1) % 5][j0];
      } else {
        diagram[0] = keyMatrix[i0][j1];
        diagram[1] = keyMatrix[i1][j0];
      }

      ciphertext += diagram;
    }

    transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(),
              ::toupper);
    return ciphertext;
  }

  static string decrypt(const string& ciphertext, const string& key) {
    auto [keyMatrix, position] = getKeyMatrixAndPositions(key);
    vector<string> diagrams = getDiagrams(ciphertext);
    string plaintext;

    for (string& diagram : diagrams) {
      auto [i0, j0] = position[diagram[0]];
      auto [i1, j1] = position[diagram[1]];

      if (i0 == i1) {
        diagram[0] = keyMatrix[i0][(j0 - 1 + 5) % 5];
        diagram[1] = keyMatrix[i0][(j1 - 1 + 5) % 5];
      } else if (j0 == j1) {
        diagram[0] = keyMatrix[(i0 - 1 + 5) % 5][j0];
        diagram[1] = keyMatrix[(i1 - 1 + 5) % 5][j0];
      } else {
        diagram[0] = keyMatrix[i0][j1];
        diagram[1] = keyMatrix[i1][j0];
      }

      plaintext += diagram;
    }

    return plaintext;
  }
};

int main() {
  cout << "PlayFair Cipher:\n\n"
       << "Enter your choice:\n"
       << "1. Encrypt\n"
       << "2. Decrypt\n"
       << "> ";

  int choice;
  cin >> choice;

  switch (choice) {
    case 1: {
      cout << "Enter plaintext (lowercase): ";
      string plaintext;
      getline(cin, plaintext);  // buffer reset
      getline(cin, plaintext);
      plaintext.erase(remove_if(plaintext.begin(), plaintext.end(), ::isspace),
                      plaintext.end());

      cout << "Enter key (lowercase; should not contain both i and j): ";
      string key;
      cin >> key;

      string ciphertext = PlayfairCipher::encrypt(plaintext, key);

      cout << "Plaintext:  " << plaintext << "\n"
           << "Ciphertext: " << ciphertext << "\n";
    } break;

    case 2: {
      cout << "Enter ciphertext (uppercase without spaces): ";
      string ciphertext;
      cin >> ciphertext;

      cout << "Enter key (lowercase; should not contain both i and j): ";
      string key;
      cin >> key;

      string plaintext = PlayfairCipher::decrypt(ciphertext, key);

      cout << "Ciphertext: " << ciphertext << "\n"
           << "Plaintext:  " << plaintext << "\n";
    } break;

    default:
      cout << "Invalid choice!!\n";
      break;
  }

  return 0;
}
