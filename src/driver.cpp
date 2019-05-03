/*
 * driver.cpp
 *
 * Driver for the math parser program
 *
 * Lab3: You do not have to modify this file, but you may choose to do so
 *
 * If you do, note that your output is expected to match ours
 */

#include <iostream>
#include "expression.h"
#include "parser.h"

using std::cout;
using std::endl;

int main( )
{
    std::string input;
    input = "quick brown fox";
    //while(std::getline( std::cin, input )) {
        Parser parser( input );
        cout << "parsed";
        Isr *expr = parser.Parse( );
        if ( expr  && parser.fullParsed())
        {
            expr->ResetToStart();
            std::cout << expr->NextInstance( ) << "\n";
            std::cout << expr->NextInstance( ) << "\n";
            //for(int i = 0; i < expr->queries.size(); i++) {
              //  for(int j = 0; j < expr->queries[i]->queries.size(); j++) {
                //    std::cout << expr->queries[i]->queries[j] << "\n";
                //}
                std::cout << "\n";
            //}
            
            delete expr;
        }
        else
        {
            help_message();
        }
        
    }
