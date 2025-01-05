#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <string>
#include <curl/curl.h>

void SendNumbers(const std::string& webhookURL, const std::string& filePath) {

    CURL* curl = curl_easy_init();

    if (curl) {
        curl_mime* mime = curl_mime_init(curl);
        curl_mimepart* part;

        curl_easy_setopt(curl, CURLOPT_URL, webhookURL.c_str());

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "file");
        curl_mime_filedata(part, filePath.c_str());

        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);


        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 120L);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 200L);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cout << "ERROR: " << curl_easy_strerror(res) << std::endl;
        }

        curl_mime_free(mime);
        curl_easy_cleanup(curl);
    }
}
