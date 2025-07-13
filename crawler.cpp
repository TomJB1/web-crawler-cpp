#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <stdexcept>
#include <cpr/cpr.h>

class bad_link : public std::exception {
private:
    std::string message;
public:

    bad_link(const char* msg) : message(msg) {}

    const char* what() const noexcept {
        return message.c_str();
    }
};

class Url {
    public:
        std::string protocol;
        std::string domain;
        std::string path;

        Url(std::string url) {
            // TODO automattically split url
        }

        std::string link() {
            return protocol + std::string("://") + domain + path;
        }
};

std::string get_page(std::string url) {

    static std::string USER_AGENT = "BrandisBot";
    static std::string EXTENDED_USER_AGENT = USER_AGENT + " (+https://tombrandis.uk)";

    static std::array<std::string, 4> ALLOWED_CONTENT_TYPE = {"text/html", "application/xhtml+xml", "text/plain", "text/markdown"};

    cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Header{{"User-agent", EXTENDED_USER_AGENT}});

    if(r.status_code != 200) {
        std::cout << ("failed - status code:" + r.status_code);
        throw bad_link(("failed - status code: " + std::to_string(r.status_code)).c_str());
    }
    if(!std::count(std::begin(ALLOWED_CONTENT_TYPE), std::end(ALLOWED_CONTENT_TYPE), r.header["content-type"].substr(0, r.header["content-type"].find(';'))) ) { // substring to find part before ';' - the actual content type
        throw bad_link(("failed - content type: " + r.header["content-type"]).c_str());
    }
    return r.text;
}

int main() {
    Url test("https://tombrandis.uk/tes2t.txt");
    test.protocol = "https";
    test.domain = "tombrandis.uk";
    test.path = "/tes2t.txt";

    std::cout << test.link();

    try {
        std::cout << get_page("https://tombrandis.uk/tes2t.txt");
    }
    catch (bad_link& e) {
        std::cout << e.what();
    }
    
}