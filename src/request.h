#pragma once
#include <curl/curl.h>
#include "ml.h"

#define ML_REQUEST_POST(self, url, data) self->service->client->post(self->service->client, url, json_object_to_json_string(data))
#define ML_REQUEST_GET(service) ;
#define ML_REQUEST_PUT(service) ;
#define ML_REQUEST_DELETE(service) ;

struct Request {
  CURL *context;
  struct curl_slist *headers;
  CURLcode (*get) (const struct Request *, const char *);
  struct Response (*post) (const struct Request *, const char *, const char *);
  CURLcode (*delete) (const struct Request *, const char *);
  void (*destroy) (struct Request *);
};

struct Response {
  char *payload;
  int size;
  CURLcode status;
};
size_t curl_callback (void *, size_t, size_t, void *);

struct Request *Request_new(void);
CURLcode Request_get(const struct Request *, const char *);
struct Response Request_post(const struct Request *, const char *, const char *);
CURLcode Request_delete(const struct Request *, const char *);
void Request_destroy(struct Request *);