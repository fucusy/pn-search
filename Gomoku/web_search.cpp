#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "game.h"

using namespace std;

void tokenize(const std::string& s, const char delim,
              std::vector<std::string>& out)
{
    std::string::size_type beg = 0;
    for (auto end = 0; (end = s.find(delim, end)) != std::string::npos; ++end)
    {
        out.push_back(s.substr(beg, end - beg));
        beg = end + 1;
    }

    out.push_back(s.substr(beg));
}


string parse_parameter(char* url, string parameter_name){
    // url is like "stepsString=_h8_g8_g7_f6_i7_h7_j6_g9&color=BLACK&level=HIGH&randomBegin=true"
    string url_s = string(url);
    auto parameter_position = url_s.find(parameter_name);
    if(parameter_position ==string::npos){
        return "";
    }else{
        auto start_position = parameter_name.size()+1; // +1, because the = after the parameter name
        auto sub_url = url_s.substr(parameter_position);
        auto and_position = sub_url.find("&");
        if(and_position == string::npos){
            return sub_url.substr(start_position);
        }else{
            auto value_length = and_position - start_position;
            return sub_url.substr(start_position, value_length);
        }
    }
}

coords next_step(bool player_starts, vector<string> history) {
    game g(player_starts); // create a game
    g.init(history);
    auto next_move = g.engine_->get_response();
    return next_move;
}
/** -- for testing purpose **/
/**
int main(int argc, char** argv) { // the optional console arguments is a path to a logged game file for debug purposes
    vector <string> history;
    auto first_step = next_step(false, history);
    if (first_step.to_string() == "h8") {
        cout << "TEST PASS" << endl;
    } else {
        cout << "first step should be h8, but it is " << first_step.to_string() << endl;
    }

    string url = "stepsString=_h8_g8_g7_f6_i7_h7_j6_g9&color=BLACK&level=HIGH&randomBegin=true";
    char char_url[url.size() + 1];
    strcpy(char_url, url.c_str());
    string value = parse_parameter(char_url, "color");
    if(value == "BLACK"){
        cout << "TEST PASS" << endl;
    }else{
        cout << "value should be BLACK, but it is " << value << endl;
    }
}
**/

int main(int argc, char** argv) { // the optional console arguments is a path to a logged game file for debug purposes
    char* query = getenv("QUERY_STRING");
    cout << "Content-Type: application/json" << endl;
    cout << endl;

    srand(unsigned(time(nullptr))); // initialize random number generator
    string steps_str = parse_parameter(query, "stepsString");
    vector<string> steps;
    if(steps_str.size() > 0){
        tokenize(steps_str.substr(1), '_', steps);
    }
    bool player_starts = false; // ai starts the first game
    game g(player_starts); // create a game
    g.init(steps);
    auto next_move = g.engine_->get_response();
	cout << "{\"x\":" << std::to_string(next_move.x) <<",\"y\":" << std::to_string(next_move.y) << "}" << endl;
}