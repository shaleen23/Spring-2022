/*
instructions:
Given a text file “data.txt”, write a program to copy the file into file “newdata.txt” by removing all comment lines (lines that begin with //) and extra spaces.
Place one space before and space after each token. Note that the cout<< is one token. Save it as Prog2
*/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  string file1, file2;

  file1 = "data.txt";
  file2 = "newdata.txt";

  ifstream input; // input file stream so that data.txt transfers to newdata.txt
  ofstream output; // output file stream so that newdata.txt is appended from data.txt

  input.open(file1); //open data.txt 
  output.open(file2); //open newdata.txt 

  string line = "";
  while (getline(input, line)) //while there is data in the data.txt file, keep reading the file
  {
    if (line != "") //if the current line in the file is not empty or null, continue and execute
    {
      // we want to remove all the comments, etc. from the data.txt file
      string str = "";
      int counter;
      for (int i = 0; i < line.length(); i++) //for loop to go through each character in the line
      {
        char ch = line[i]; //get the current character in the line
        if (ch == '/') //if the current character is a /
        {
          counter++;  //increment counter
        }
        else
        {
          str += ch; //otherwise add the character to the string
        }
      }

      if (str != "")
      {
        //removing extra spaces from the data.txt file
        string string1 = "";
        for (int i = 0; i < str.length() - 1; i++) //iterate through previous string
        {
          char ch = str[i]; //get the current character
          if (ch == ' ') //if the current character has a space
          {
            char ch1 = str[i + 1]; //get the next character
            if (ch1 != ' ') //if the next character does not have a space
            {
              if (string1 != "") //and if the new string is not empty
              {
                string1 += ' ';  //add a space to the new string
              }
            }
          }
          else
          {
            string1 += ch; //otherwise add the current character to the new string
          }
        }

        string1 += str[str.length() - 1]; //adding the last character to the string1
      
      string string2 = ""; 
      for (int i = 0; i < string1.length() - 1; i++) //loop through first string to remove extra spaces, characters, etc.
      {
        char ch = string1[i]; //get the current character
        if (ch == ' ') //if the current character in the string has a space
        {
          char ch1 = string1[i + 1]; //get the next character
          if (ch1 == '=' || ch1 == ',' || ch1 == ';') //if the next character has an equal sign, comma, or semicolon
          {
            if (ch1 == '=') //if it is an equals sign 
            {
              string2 += "="; //add it to the string2
              i++; //increment i to skip the next character
            }
            if (ch1 == ',') //if it is a comma
            {
              string2 += ","; //add it to the string2
              i++; //increment i to skip the next character
            }
            
          }
          else
          {
            string2 += " "; //if it is not an equal sign, comma, or semicolon, add a space to the string2
          }
        }
        else
        {
          string2 += ch; //if the current character is not empty, add it to the string2
        } 
      }
      string2 += string1[string1.length() - 1]; 

      //removing more spaces from the data.txt file
      string string3 = "";
      for (int i = 0; i < string2.length(); i++) //iterate through string2
      {
        char ch = string2[i]; //get the current character
        if (ch == '=') //if there is an equals sign in the string
        {
          char ch1 = string2[i+1]; //set the next character
          string3 += "="; //add the equals sign to the string
          if (ch1 == ' ') //if the next character is empty
          {
            i++; //increment i to skip the next character
          }
        }
        else
        {
          string3 += ch; //if there is no equals sign, add the current character to the string
        }
      }

      //copy the data from original file to the new file, but without the comments, extra spaces, etc.
      string string4 = ""; 
      for (int i = 0; i < string3.length(); i++) //iterate through string3
      {
        char ch = string3[i]; //ch is the current character in the string
        if (ch == ';') 
        {
          string4 += ";"; //add a semicolon to the new file
          output << string4; //copy the data from the new file to the new file
          output << endl; //add a new line to the new file
          string4 = ""; //reset the string4 to empty
        }
        else
        {
          if (!(ch == ' ' && string4 == "")) //if the character does not have a space and string4 is empty
          {
            string4 += ch; //add the character to string4
          }
        }
      }

      if (string4 != "") //if string4 is not empty, then append everything to the string4
      {
        output << string4;
        output << endl;
      }
    }
  }
  }
output << endl; //add extra line to newdata.txt file


input.close(); //close data.txt once everything is done
output.close(); //close newdata.txt once everything is done

// display the original file and then the new file with all the comments, spaces and extra spaces removed
cout << "data.txt file "<< "\n" << endl;
input.open(file1);

while (getline(input, line)) //while there is data in the data.txt file, print each line from the file
{
  cout << line << endl;
}
input.close(); //close data.txt 
cout << "\n\" newdata.txt:  " << "\n" << endl;
input.open(file2); //display the newdata.txt file

while (getline(input, line)) //while there is data in the newdata.txt file, print each line from the file
{
  cout << line << endl;
}


input.close(); //close output file

return 0;
}
