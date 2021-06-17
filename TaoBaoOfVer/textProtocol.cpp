#include "textProtocol.h"
#include <iostream>

//
//int main() {
//    cout << __cplusplus<<endl;
//    char buffer[100]= "a{AK44:insdfsdfjlsejfwehnoisf_934do ws2}00a{AK47:10002423}000";
//    Text text(buffer, 100);
//   cout<<text.getValue("AK47");
//}


Text::Text(char* buffer, int Size)
{
	buf = buffer;
	size = Size;
}

bool Text::empty()
{
    return !*buf;
}

void Text::clear()
{
    *buf = 0;
    sended = false;
}

char* Text::buffer()
{
    return buf;
}

 void Text::getString(string tag, string& ans)
{
    string n = "\\{"+tag+":[\\w ]+(?=\\})";
    regex Regex(n.c_str());
    cmatch result;
    regex_search(buf, result, Regex);
    if (result.size() == 0) { 
        cout << tag << " wrong" << endl; 
    }
    string temp ((char*)&result[0].str()[tag.size() + 2]);
        ans=""+temp;
     
}

void Text::getStrings(string tag, set<string>&v)
{
    string n = "\\{" + tag + ":[\\w ]+(?=\\})";
    regex Regex(n.c_str());
    cmatch result;
    regex_search(buf, result, Regex);
    if (result.size() == 0) {
        cout << tag << " wrong" << endl;
    }
    for (int i = 0; i < result.size(); i++) {
        string ans((char*)&result[0].str()[tag.size() + 2]);
        v.insert(ans);
    }
    return ;

}

void Text::setString(string tag, string info)
{
    string temp(" {" + tag + ":" + info + "}");
    memcpy(buf + strlen(buf), &temp[0],temp.size()+1);

}

long long Text::getValue(string Tag)
{
    string temp;
    getString(Tag, temp);
    return atoll(temp.c_str());
}

void Text::sendInfo()
{
    sended = true;
}

bool Text::infoReady()
{
    return sended;
}
