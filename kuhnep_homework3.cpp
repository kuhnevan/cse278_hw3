/*
 * Copyright 2016 kuhnep@miamioh.edu
 */

/* 
 * File:   homework3.cpp
 * Created on September 20, 2016, 11:29 AM
 */

#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

std::string fixSpacing(std::string line) {
    int spaceCount = 0;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            spaceCount++;
            if (spaceCount > 1) {
                line = line.replace(i, 1, "&nbsp;");
                // Go up five indexes so that it doesn't check string i put in
                i += 5;
            }
        } else {
            spaceCount = 0;
        }
    }
    return line;
}

std::string convertEmoticon(std::string line) {    
    if (line.find(":-)") != std::string::npos) {
        return "<img src=\"http://ceclnx01.cec.miamiOH.edu/"
                "~raodm/hw3/smile.png\">";
    } else if (line.find(":-(") != std::string::npos) {
        return string("<img src=\"http://ceclnx01.cec.miamiOH.edu/"
                "~raodm/hw3/frown.png\">");
    } else if (line.find(":-|") != std::string::npos) {
        return "<img src=\"http://ceclnx01.cec.miamiOH.edu/"
                "~raodm/hw3/normal.png\">";
    } else if (line.find(":++") != std::string::npos) {
        return "<img src=\"http://ceclnx01.cec.miamiOH.edu/"
                "~raodm/hw3/cpp.png\">";
    } else {
        return line;
    }
}

std::string convertAllEmoticons(std::string line) {
    int index = 0;
    int firstIndex;
    int lastIndex;
    while (line.find_first_not_of(' ', index) != std::string::npos) {
        firstIndex = line.find_first_not_of(' ', index);
        lastIndex = line.find(' ', firstIndex);
        std::string oldText = line.substr(firstIndex, lastIndex - firstIndex);
        std::string newText = convertEmoticon(oldText);
        if (oldText.compare(newText) != 0) {
            line.replace(firstIndex, oldText.size(), newText);
        }
        index = firstIndex + newText.size();
    }
    return line;
}

std::string convertHandle(std::string line) {
    int index = 0;
    int firstIndex;
    int lastIndex;
    while (line.find('@', index) != std::string::npos) {
        firstIndex = line.find('@', index);
        std::string oldHandle;
        if (line.find(' ', firstIndex) != std::string::npos) {
            lastIndex = line.find(' ', firstIndex);
            oldHandle = line.substr(firstIndex,  lastIndex - firstIndex);
        } else {
            oldHandle = line.substr(firstIndex);
        }
        std::stringstream ss;
        ss << "<a href=\"https://www.twitter.com/"  
                    << oldHandle.substr(1)
                    << "\">"
                    << oldHandle
                    << "</a>";
        std::string newHandle = ss.str();
        line = line.replace(firstIndex, oldHandle.size(), newHandle);
        index = firstIndex + newHandle.size();
    }
    return line;
}

std::string convertHashtag(std::string line) {
    int index = 0;
    int firstIndex;
    int lastIndex;
    while (line.find('#', index) != std::string::npos) {
        firstIndex = line.find('#', index);
        std::string oldHashtag;
        if (line.find(' ', firstIndex) != std::string::npos) {
            lastIndex = line.find(' ', firstIndex);
            oldHashtag = line.substr(firstIndex, lastIndex - firstIndex);
        } else {
            oldHashtag = line.substr(firstIndex);
        }
        std::stringstream ss;
        ss << "<a href=\"https://www.twitter.com/hashtag/" 
                << oldHashtag.substr(1)
                << "\">"
                << oldHashtag
                << "</a>";
        std::string newHashtag = ss.str();
        line.replace(firstIndex, oldHashtag.size(), newHashtag);
        index = firstIndex + newHashtag.size();
    }
    return line;
}

std::string processTweet(std::string line) {
    line = fixSpacing(line);
    line = convertHandle(line);
    line = convertHashtag(line);
    line = convertAllEmoticons(line);
    std::string tagUpper = "<div class=\"tweet\">";
    std::string tagLower = "</div>";
    return tagUpper + "\n" + line + "\n" + tagLower;
}

/*
 * 
 */
int main(int argc, char *argv[]) {
    std::ifstream inFile(argv[1]);
    std::ofstream outFile(argv[2]);
    std::string input;
    outFile <<  "<!DOCTYPE html>\n"
            << "<html>\n"
            << "<head>\n" 
            << "<link type=\"text/css\" rel=\"stylesheet\" "
            << "href=\"http://ceclnx01.cec.miamiOH.edu/"
            << "~raodm/hw3/tweets.css\"/>\n" 
            << "</head>\n" 
            << "<body>\n";
    while (std::getline(inFile, input)) {
        outFile << processTweet(input) << std::endl;
    }
    outFile << "</body>\n"
            << "</html>\n";
    return 0;
}

