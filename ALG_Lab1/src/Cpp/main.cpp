#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <utility>
#include <string>
#include <chrono>
using namespace std;
/**/

pair<int, vector<int>> naiveString(const string& text, const string& pattern)
{
	vector<int> ans;
	int n = text.length();
	int m = pattern.length();

	for (int i = 0; i < n - m + 1; i++)
	{
		int j = 0;
		while (j < m && text[i + j] == pattern[j])
		{
			j++;
		}
		if (j == m) 
		{ 
			ans.push_back(i);
		}
	}
	return { ans.size(), ans };
}
string readFile(const string& filename)
{
	ifstream file(filename);

	if (!file.is_open())
	{
		cerr << "Error: cannot open file " << filename << endl;
		return "";
	}

	string text;
	string line;

	while (getline(file, line))
	{
		text += line;
		text += '\n';
	}

	file.close();
	return text;
}
int main()
{
    string pattern;
    string pattern1;

    string text = readFile("randomText.txt");

    // 1
    if (text.empty())
    {
        cerr << "File is empty or could not be read." << endl;
        return 1;
    }

    cout << "Enter substring to search in file text: ";
    getline(cin, pattern);

    auto start = chrono::high_resolution_clock::now();
    pair<int, vector<int>> result = naiveString(text, pattern);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duration = end - start;

    cout << "Number of occurrences: " << result.first << endl;
    cout << "Positions of occurrences: ";
    for (int pos : result.second)
    {
        cout << pos << " ";
    }
    cout << endl;
    cout << "Execution time: " << duration.count() << " ms" << endl;
    
    // 2
    string text1;
    cout << "Enter text: ";
    getline(cin, text1);

    cout << "Enter substring to search in text1: ";
    getline(cin, pattern1);

    auto start1 = chrono::high_resolution_clock::now();
    pair<int, vector<int>> result1 = naiveString(text1, pattern1);
    auto end1 = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duration1 = end1 - start1;

    cout << "Number of occurrences: " << result1.first << endl;
    cout << "Positions of occurrences: ";
    for (int pos : result1.second)
    {
        cout << pos << " ";
    }
    cout << endl;
    cout << "Execution time: " << duration1.count() << " ms" << endl;

    return 0;
}