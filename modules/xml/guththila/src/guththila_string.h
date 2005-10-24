/*
 * Copyright 2004,2005 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GUTHTHILA_STRING_H
#define GUTHTHILA_STRING_H

#include <guththila_defines.h>
#include <guththila_allocator.h>
//#include "guththila_unicode.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct guththila_string
{
    void* (*guththila_string_strdup)(const void *ptr);
    int (*guththila_string_strcmp)(const guththila_char_t *s1, const guththila_char_t *s2);
    guththila_char_t *(*guththila_string_strndup)(const guththila_char_t *s1,size_t n);
    int  (*guththila_string_strlen)(const guththila_char_t *s);
    //guththila_char_t *(*guththila_string_strdup_unicode)(const guththila_char_t *s1,size_t n);
   // guththila_UTF8_char (*guththila_string_strlen_unicode)(const guththila_char_t *);
}guththila_string_t;

/**
*   if the parsed string is null a default string is created
*   otherwise the parsed string is returned. If there isn't enough 
*   memory for allocation NULL is returned.
*   @param string user defined allcator
*/

guththila_string_t *
    guththila_string_create(guththila_allocator_t *allocator, guththila_string_t *string);
    
#define guththila_strdup(string, ptr) ((string)->guththila_string_strdup(ptr))
#define guththila_strcmp(string, s1, s2) ((string)->guththila_string_strcmp(s1, s2))
#define guththila_strndup(string,s1,n) ((string)->guththila_string_strndup(s1,n))
#define guththila_strlen(string,s1) ((string)->guththila_string_strlen(s1))
//#define guththila_strdup_unicode(string,s1,n) ((string)->guththila_string_strdup(s1,n))
//#define guththila_strlen_unicode(string,s1) ((string)->guththila_string_strlen_unicode(s1))

#ifdef __cplusplus
}
#endif

#endif /* GUTHTHILA_STRING_H */
