#pragma once
#include <json-c/json.h>
#include "request.h"


struct Service {
  struct Request *client; 
  char *accessToken;
};

struct Service *Service_new(struct Request *);
void Service_destroy(struct Service *);

/*
 * Token - Services
*/

struct Token {
  const struct Service *service;
  const struct ConfigML *conf;
  json_object *(*getAccessToken)(const struct Token *, const char *);
  void (*refreshAccessToken)(const struct Token *, const char *);
};

#define ML_SET_ACCESS_TOKEN(tokenNew) ml->service->accessToken = tokenNew;
#define ML_GET_TOKEN_BY_SERVICE(ml) ml->service->accessToken;
#define ML_GET_TOKEN_BY_CODE(ml, code) ml->token->getAccessToken(ml->token, code) 
#define ML_GET_TOKEN_REFRESH(ml, tokenOld) ml->token->refreshAccessToken(ml->token, tokenOld)

struct Token *Token_new(const struct Service *);
json_object *Token_get(const struct Token *, const char *);
void Token_refresh(const struct Token *, const char *);


/*
 * User - Services
*/

struct User {
  const struct Service *service;

  void (*get)(const struct User *);
  void (*getPaymentMethods)(const struct User *);
  void (*getBrands)(const struct User *);
  void (*getPromotionPacks)(const struct User *);
  void (*getListingTypes)(const struct User *);
  void (*update)(const struct User *);
};

#define ML_GET_USER(ml) ml->user->get(ml->user);
#define ML_GET_USER_PAYMENTMETHODS(ml) ml->user->getPaymentMethods(ml->user);
#define ML_GET_USER_BRANDS(ml) ml->user->getBrands(ml->user);
#define ML_GET_USER_PROMOTIONPACKS(ml) ml->user->getPromotionPacks(ml->user);
#define ML_GET_USER_LISTINGTYPES(ml) ml->user->getListingTypes(ml->user);
#define ML_GET_USER_UPDATE(ml) ml->user->update(ml->user);

struct User *User_new(const struct Service *);
void User_get(const struct User *);
void User_paymentMethods(const struct User *);
void User_brands(const struct User *);
void User_promotionPacks(const struct User *);
void User_listingTypes(const struct User *);
void User_update(const struct User *);