#pragma once

#include<iostream>
#include<map>
#include<string>
#include<list>
#include<sstream>
#include<fstream> 
using namespace std;

void PushToResult(int count, list<string>& compressed_content, string& temp_str, map<string, int>& _map) {
	char s[12];
	itoa(count, s, 10);//comput now index will occupy how much space
	if (strlen(temp_str.c_str()) < strlen(s)) {//if compress occupy more space,choose original elem to save
		compressed_content.push_back(temp_str);
	}
	else {
		char s[12];
		itoa(_map[temp_str], s, 10);
		compressed_content.push_back(s);
	}
}

void Compress(string source, list<string>& compressed_content) {
	map<string, int> _map;
	int count = 0;
	for (; count < 256; count++) {
		_map[string(1, count)] = count;
	}

	string temp_str = "";
	temp_str += source[0];//put first into temp_str

	char temp_char;
	for (int i = 1; i < source.length(); i++) {
		temp_char = source[i];//temp_char start from second char
		string entry = temp_str + temp_char;
		if (_map.count(entry)) {//look up wheather it is in _map
			temp_str += temp_char;//if it is in _map,add next into temp_str
		}
		else {
			PushToResult(count, compressed_content, temp_str, _map);//push result except temp_char
			_map[entry] = count++;//push temp_str+temp_char into _map
			temp_str = temp_char;
		}
	}

	PushToResult(count, compressed_content, temp_str, _map);
}

string Decompress(list<string>& compressed_content) {
	map<int, string> _map;
	int count = 0;
	for (; count < 256; count++) {
		_map[count] = string(1, count);
	}
	stringstream ss;
	string temp_str = "";
	string temp_entry = "";
	//the same as compress to make _map,put first into temp_str
	int temp = atoi((compressed_content.front()).c_str());
	if (temp < 256) {
		ss << compressed_content.front();
		temp_str += compressed_content.front();
	}
	else {
		if (_map.count(temp)) {
			ss << _map[temp];
			temp_str += _map[temp];
		}
	}

	compressed_content.pop_front();

	for (list<string>::iterator iter = compressed_content.begin(); iter != compressed_content.end(); ++iter) {
		int temp = atoi((*iter).c_str());
		if (temp < 256) {//if not compressed
			ss << *iter;
			temp_entry = (*iter);
		}
		else {
			if (_map.count(temp)) {//if it is in _map
				ss << _map[temp];
				temp_entry = _map[temp];
			}
			else {//it must be same char ,like aaaaa..
				temp_entry += temp_entry[0];
				ss << temp_entry;
			}
		}

		temp_str += temp_entry[0];
		_map[count++] = temp_str;
		temp_str = temp_entry;
	}
	return ss.str();
}