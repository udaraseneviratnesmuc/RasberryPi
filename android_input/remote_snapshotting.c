#define CURL_STATICLIB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include </usr/include/curl/curl.h>
#include </usr/include/curl/stdcheaders.h>
#include </usr/include/curl/easy.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
   size_t written = fwrite(ptr, size, nmemb, stream);
   return written;
}

int main(void) {
   CURL *curl;
   FILE *fp;
   CURLcode res;

   char *url = "http://192.168.1.5:8080/photo.jpg"; 
   char outfilename[FILENAME_MAX] = "/root/Training/RasberryPi/trashables/snapshot.jpg";
   curl = curl_easy_init();
   if (curl) {
       fp = fopen(outfilename,"wb");
       curl_easy_setopt(curl, CURLOPT_URL, url);
       curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
       curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
       res = curl_easy_perform(curl);
       /* always cleanup */
       curl_easy_cleanup(curl);
       fclose(fp);
   }

 }
