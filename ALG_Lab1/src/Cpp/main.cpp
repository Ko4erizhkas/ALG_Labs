#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <utility>
#include <string>
#include <chrono>
using namespace std;
/**/

tuple<int, vector<int>, int, int> naiveString(const string& text, const string& pattern)
{
	vector<int> ans;
    vector<int> js;
	int n = text.length();
	int m = pattern.length();

    int j_center = 0;
    int j_help = 0;

	for (int i = 0; i < n - m + 1; i++)
	{
        int j = 0;
        while (j < m && text[i + j] == pattern[j])
		{
			j++;
            //запихнуть j в массив, ниже посчитать среднее и колво в массиве
            js.push_back(j);
		}
		if (j == m) 
		{ 
			ans.push_back(i);
		}
	}
    if (!js.empty())
    {
        for (int x : js)
        {
            j_help += x;
        }
        j_center = j_help / js.size();
    }
	return { ans.size(), ans, j_center, js.size()};
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
    auto result = naiveString(text, pattern);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duration = end - start;

    cout << "Number of occurrences: " << get<0>(result) << endl;
    cout << "Positions of occurrences: ";
    for (int pos : get<1>(result))
    {
        cout << pos << " ";
    }
    cout << endl;
    // j_center (see in function -> naivString)
    cout << get<2>(result) << endl;
    // js.size() (see in function -> naivString)
    cout << get<3>(result);
    cout << endl;
    cout << "Execution time: " << duration.count() << " ms" << endl;
    
    // 2
    string text1;
    cout << "Enter text: ";
    getline(cin, text1);

    cout << "Enter substring to search in text1: ";
    getline(cin, pattern1);

    auto start1 = chrono::high_resolution_clock::now();
    auto result1 = naiveString(text1, pattern1);
    auto end1 = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duration1 = end1 - start1;

    cout << "Number of occurrences: " << get<0>(result1)<< endl;
    cout << "Positions of occurrences: ";
    for (int pos : get<1>(result1))
    {
        cout << pos << " ";
    }
    cout << endl;
    // j_center (see in function -> naivString)
    cout << get<2>(result1) << endl;
    // js.size() (see in function -> naivString)
    cout << get<3>(result1);
    cout << endl;
    cout << "Execution time: " << duration1.count() << " ms" << endl;

    return 0;
}