#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include "request.h"
#include "services.h"
#include "ml.h"

/*
 * Services
*/

struct Service *Service_new(struct Request *req) { 
  struct Service *service = (struct Service *) malloc(sizeof(struct Service));
  service->client = req;
  service->accessToken = NULL;
  return service;
}

void Service_destroy(struct Service *self) { 
   
  Request_destroy(self->client);
} 

/*
 * Token - Services
*/
struct Token *Token_new(const struct Service *service) {
  struct Token *token = (struct Token *) malloc(sizeof(struct Token));
  token->service = service;
  token->getAccessToken = Token_get;
  token->refreshAccessToken = Token_refresh; 
  return token;
}

json_object *Token_get(const struct Token *self, const char *code) {
  
  json_object *form;     
  form = json_object_new_object();
  json_object_object_add(form, "grant_type", json_object_new_string("authorization_code"));
  json_object_object_add(form, "client_id", json_object_new_string(self->conf->app_id));
  json_object_object_add(form, "client_secret", json_object_new_string(self->conf->client_secret));
  json_object_object_add(form, "code", json_object_new_string(code));
  json_object_object_add(form, "redirect_uri", json_object_new_string(self->conf->redirect_url));

  struct Response res = ML_REQUEST_POST(self, ML_URL_TOKEN, form);
  json_object_put(form);
  if (res.status != CURLE_OK) return NULL;
  enum json_tokener_error jerr = json_tokener_success;   
  json_object *result;
  result = json_tokener_parse_verbose(res.payload, &jerr);
  return result;
}

void Token_refresh(const struct Token *self, const char *token) { 
  char *url;

}

/*
 * User - Services
*/

struct User *User_new(const struct Service *service) { 
  struct User *user = (struct User *) malloc(sizeof(struct User));
  user->service = service;
  user->get = User_get;
  user->getPaymentMethods = User_paymentMethods;
  user->getBrands = User_brands;
  user->getPromotionPacks = User_promotionPacks;
  user->getListingTypes = User_listingTypes;
  user->update = User_update;
  return user;
} 

void User_get(const struct User *self) {
  
}

void User_paymentMethods(const struct User *self) {

}

void User_brands(const struct User *self) {
  
}

void User_promotionPacks(const struct User *self) {
    
}

void User_listingTypes(const struct User *self) {
      
}

void User_update(const struct User *self) {
  
}