sudo cp -r ./Web/* /Library/WebServer/Documents/gomoku/
cd Gomoku
rm web_search.cgi
g++  *.cpp -o web_search.cgi -std=c++17
cp web_search.cgi /Library/WebServer/CGI-Executables/