#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "ml.h" 

struct ML *ML_new(const struct ConfigML *conf) {  
  struct ML *self = (struct ML *) malloc(sizeof(struct ML));
  struct Request *req = Request_new();
  struct Service *service = Service_new(req);

  self->conf = conf;
  self->service = service;
  self->token = Token_new(service);
  self->user = User_new(service);
  self->token->conf = conf;
  self->Authorize_url = Authorize_url; 
  return self; 
}

void ML_destroy(struct ML *self) { 
  Service_destroy(self->service);
  free(self);
}

char *Authorize_url(const struct ML *self) {
  assert(self->conf->app_id != NULL && self->conf->redirect_url != NULL);
  char *url;
  asprintf(&url, "%s%sclient_id=%s&redirect_uri=%s&response_type=code", 
    self->conf->country, 
    ML_URL_AUTHORIZATION,
    self->conf->app_id,
    self->conf->redirect_url);
  return url;
}

