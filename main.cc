/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2021 Ali Alwan <aalwan99@aalwan99-XPS-15-9570>
 * 
 * Passwrd_PostQuantum is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Passwrd_PostQuantum is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

void printTime(double seconds)
{
	if (seconds < 1 )
		cout << "Instantly" << endl;
	else if(seconds > 31536000)
	{
		double years = seconds/31536000;
		if(years > 1000000000)
			cout << round(years/1000000000) << " billion years" << endl;
		else if(years > 1000000)
			cout << round(years/1000000) << " million years" << endl;
		else if(years > 1000)
			cout << round(years/1000) << " thousand years" << endl;
		else
			cout << round(years) << " years" << endl;
	}
	else if (seconds > 86400)
		cout << round(seconds/86400) << " days" << endl;
	else if (seconds > 3600)
		cout << round(seconds/3600) << " hours" << endl;
	else if (seconds > 60)
		cout << round(seconds/60) << " minutes" << endl;
	else
		cout << round(seconds) << " seconds" << endl;
}

bool CheckWord(string& search)
{
    int offset; 
    string line;
    ifstream Myfile;
    Myfile.open ("rockyou.txt");

    if (Myfile.is_open())
    {
        while (!Myfile.eof())
        {
            getline(Myfile,line);
            if ((offset = line.find(search, 0)) != string::npos) 
            {
                Myfile.close();
                return true;
            }
        }
        Myfile.close();
    }

    return false;
}

void printStrongNess(string& input) 
{
	int n = input.length();
	int p = 0;
	string normalChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
	bool hasLower = false;
	bool hasUpper = false;
	bool hasNumber = false;
	bool hasSpecialChar = false;
	for (int i = 0; i < n; i++) 
	{
		if (islower(input[i]))
			hasLower = true;
		if (isupper(input[i]))
			hasUpper = true;
		if (isdigit(input[i]))
			hasNumber = true;
		size_t special = input.find_first_not_of(normalChars);
		if (special != string::npos)
			hasSpecialChar = true;
	}

	if(hasLower == true)
		p += 26;
	if(hasUpper == true)
		p += 26;
	if(hasNumber == true)
		p += 10;
	if(hasSpecialChar == true)
		p += 32;
	
	double speed = 10000000000; // 10 billion searches a second
	
	double computations = pow(p,n);
	double quan_computations = pow(computations,0.5);
	
	double entropy = floor(log2(computations)) + 1;
	double qentropy = floor(log2(quan_computations)) + 1;
	
	double seconds = computations / speed;
	double qseconds = quan_computations / speed;

	if(CheckWord(input) == true)
		seconds = qseconds = 0;

	cout << "A Classical Computer will break this password in: ";
	printTime(seconds);
	cout << "Password Entropy: " << entropy << " bits" << endl;
	cout << "\nA Quantum Computer will break this password in: ";
	printTime(qseconds);
	cout << "Password Entropy: " << qentropy << " bits" << endl;
	
}


int main()
{
	string input;
	cout << "Welcome to The Post-Quantum Password Cracker!" << endl;
	cout << "Please enter a password: ";
	cin >> input;
	cout << "\n";
	printStrongNess(input);
	while (1)
	{
		cout << "\n\n";
		cout << "To Continue Enter Another Password or Enter '1' to EXIT" << endl;
		cin >> input;
		if(input == "1")
			break;
		cout << "\n";
		printStrongNess(input);
	}
	
	return 0;
}

