#include <stdlib.h>
#include <string.h>
#include "request.h"

struct Request *Request_new(void) {
  CURL *curl;
  if (!(curl=curl_easy_init())) return NULL;

  struct Request *self = (struct Request *) malloc(sizeof( struct Request));
  /*
   * Configuración headers default - Request
  */
  self->headers = NULL;
  self->headers = curl_slist_append(self->headers, HEADER_ACCEPT);
  self->headers = curl_slist_append(self->headers, HEADER_CONTENT_TYPE);
  self->headers = curl_slist_append(self->headers, HEADER_USER_AGENT);
  
  /*
   * Configuración de optiones default - Request
  */
  self->context = curl;
  curl_easy_setopt(self->context, CURLOPT_HTTPHEADER, self->headers);
  curl_easy_setopt(self->context, CURLOPT_FOLLOWLOCATION, 1);
  curl_easy_setopt(self->context, CURLOPT_TIMEOUT, 20);
  curl_easy_setopt(self->context, CURLOPT_MAXREDIRS, 1); 
  curl_easy_setopt(self->context, CURLOPT_WRITEFUNCTION, curl_callback);
  /*
   * Method's
  */
  self->get = Request_get;
  self->post = Request_post;
  self->delete = Request_delete;
  self->destroy = Request_destroy;
  return self;
}

void Request_destroy(struct Request *self) {
  curl_easy_cleanup(self->context); 
  curl_slist_free_all(self->headers);
  free(self);
}

struct Response Request_post(const struct Request *self, const char *url, const char *data) {
  struct Response res = {NULL, 0};
  CURLcode status;
  curl_easy_setopt(self->context, CURLOPT_URL, url );
  curl_easy_setopt(self->context, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(self->context, CURLOPT_WRITEDATA, (void *) &res);
  curl_easy_setopt(self->context, CURLOPT_POSTFIELDSIZE, (long) strlen(data));
  curl_easy_setopt(self->context, CURLOPT_POSTFIELDS, data);
  status = curl_easy_perform(self->context);
  res.status = status; 
  return res;
}

CURLcode Request_get(const struct Request *self, const char *url) { 
  struct Response res = {
    .payload = NULL,
    .size = 0
  };
  CURLcode status;
  curl_easy_setopt(self->context, CURLOPT_URL, "www.google.com");
  curl_easy_setopt(self->context, CURLOPT_CUSTOMREQUEST, "GET");
  curl_easy_setopt(self->context, CURLOPT_WRITEDATA, &res);
  status = curl_easy_perform(self->context);
  printf("Status: %d \n", status);
  return status;  
}

CURLcode Request_delete(const struct Request *self, const char *url) {
  struct Response *res;
  CURLcode status;  
  curl_easy_setopt(self->context, CURLOPT_URL, url );
  curl_easy_setopt(self->context, CURLOPT_CUSTOMREQUEST, "DELETE");
  curl_easy_setopt(self->context, CURLOPT_WRITEDATA, &res);
  status = curl_easy_perform(self->context);  
  return status;  
}

size_t curl_callback(void *contents, size_t size, size_t nmemb, void *userp) {
  
  size_t realsize = size * nmemb;                             /* calculate buffer size */
  struct Response *res = (struct Response *) userp;   /* cast pointer to fetch struct */
  printf("%d", res->size);
  /* expand buffer */
  res->payload = (char *) realloc(res->payload, res->size + realsize + 1);

  /* check buffer */
  if (res->payload == NULL) {
    /* this isn't good */
    fprintf(stderr, "ERROR: Failed to expand buffer in curl_callback");
    /* free buffer */
    free(res->payload);
    /* return */
    return -1;
  }

  /* copy contents to buffer */
  memcpy(&(res->payload[res->size]), contents, realsize);

  /* set new buffer size */
  res->size += realsize;

  /* ensure null termination */
  res->payload[res->size] = 0;

  /* return size */
  return realsize;
}
