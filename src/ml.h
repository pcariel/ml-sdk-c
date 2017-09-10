#pragma once
#include "services.h"
#include "request.h"
/*
  Curl Header Default
*/
#define HEADER_USER_AGENT "User-Agent: ml-sdk-c/1.0.0;"
#define HEADER_ACCEPT "Accept: application/json;"
#define HEADER_ACCEPT "Accept: application/json;"
#define HEADER_CONTENT_TYPE "Content-Type: application/json;"

#define ML_URL_API_ENDPOINT "https://api.mercadolibre.com"
#define ML_URL_AUTHORIZATION "/authorization?"
#define ML_URL_TOKEN "https://api.mercadolibre.com/oauth/token?"
/*
  Mercadolibre - Country
*/

#define ML_COUNTRY_AR "https://auth.mercadolibre.com.ar"
#define ML_COUNTRY_VE "https://auth.mercadolibre.com.ve"

struct ConfigML{ 
  char app_id[128];
  char client_secret[128];
  char redirect_url[128];
  char country[128];
  char access_token[128];
};

struct ML {
  const struct ConfigML *conf;
  struct Service *service;
  struct Token *token;
  struct User *user;
  char *(*Authorize_url)(const struct ML *);

};



struct ML * ML_new(const struct ConfigML *);
char *Authorize_url(const struct ML *);
void ML_destroy(struct ML *);
