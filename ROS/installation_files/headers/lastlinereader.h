#pragma once

/*
        Code taken from: https://stackoverflow.com/questions/11876290/c-fastest-way-to-read-only-last-line-of-text-file
        pre-req: file must not have multiple endline character at the end with empty lines.
*/

#include <fstream>

std::string lastLineOfFile(std::string file_name)
{
        std::string result = "";
        std::ifstream fin(file_name);

        if (fin.is_open()) {
                fin.seekg(0, std::ios_base::end);      //Start at end of file
                char ch = ' ';                        //Init ch not equal to '\n'
                while (ch != '\n') {
                        fin.seekg(-2, std::ios_base::cur); //Two steps back, this means we
                                                          //will NOT check the last character
                        if ((int)fin.tellg() <= 0) {        //If passed the start of the file,
                                fin.seekg(0);                 //this is the start of the line
                                break;
                        }
                        fin.get(ch);                      //Check the next character
                }

                std::getline(fin, result);
                fin.close();
        }

        return result;
}