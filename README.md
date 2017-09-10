# ml-sdk-c
MercadoLibre API for C ANSI-99

## Usage

```c

#include <stdio.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include "ml.h"

int main(void) {
  printf("ML-SDK-C 1.0.0 \n");

  curl_global_init(CURL_GLOBAL_ALL);

  static struct ConfigML conf = {
    .app_id = "DDDDDDDDDDDDDDDDDDDDDDDd",
    .client_secret = "ZZZZZZZZZZZZZZZZZZZZZZZZZZZ",
    .redirect_url = "http://localhost:8080", 
    .country = ML_COUNTRY_AR
  };

  struct ML *ml = ML_new(&conf);
  char code[128] = {0};

  printf("URL_AUTH: %s \n\n", ml->Authorize_url(ml));

  printf("Code: ");
  scanf("%s", code);

  json_object *result_token = ML_GET_TOKEN_BY_CODE(ml, code);
  
  ML_destroy(ml);

  curl_global_cleanup();
  return 0;
}
```