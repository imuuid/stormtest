#include "mongoose.h"
#include <shellapi.h>
#include <string>
#include <random>
#include "main.h"


//Generate random string for routing
std::string new_String() {
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(str.begin(), str.end(), generator);
    std::string s = "/" + str.substr(0, 16);
    return s;
}

//Bind random port between 9000-9999
std::string new_Port() {
    std::random_device seed;
    std::mt19937 gen{ seed() };
    std::uniform_int_distribution dist{ 9000, 9999 };
    int guess = dist(gen);
    std::string newurl = "http://localhost:" + std::to_string(guess);
    return newurl;
}

//Set value when recive a POST request
static std::string url = new_Port();
static std::string route = new_String();
static void fn(struct mg_connection* c, int ev, void* ev_data, void* fn_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message* hm = (struct mg_http_message*)ev_data;
        if (mg_http_match_uri(hm, route.c_str())) {
            mg_http_reply(c, 200, "", html);
            char nameBuf[100] = "";
            char surnameBuf[100] = "";
            char closeBuf[100] = "";

            //Get fields value
            int checkName = mg_http_get_var(&hm->body, "name", nameBuf, sizeof(nameBuf));
            int checkSurname = mg_http_get_var(&hm->body, "surname", surnameBuf, sizeof(surnameBuf));
            int checkClose = mg_http_get_var(&hm->body, "nick", closeBuf, sizeof(closeBuf));

            if (checkName > 0 && checkSurname > 0) {
                keyB = atoi(surnameBuf);
                fDelay = atoi(nameBuf);
            }
            else if (checkClose > 0) exit(0);  
        }
    }
}

//Start WebServer
int startServer() {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);  
    std::string newurl = url + route;
    //Open Browser
    ShellExecute(0, 0, newurl.c_str(), 0, 0, SW_SHOW);
    mg_http_listen(&mgr, url.c_str(), fn, &mgr);
    for (;;) mg_mgr_poll(&mgr, 1000);                       
    mg_mgr_free(&mgr);  
    return 0;
}