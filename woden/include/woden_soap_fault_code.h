/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WODEN_SOAP_FAULT_CODE_H
#define WODEN_SOAP_FAULT_CODE_H

/**
 * @file woden_soap_fault_code.h
 * @brief Axis2 Soap Fault Code Interface
 * This class represents the {soap fault code} property that forms part of the 
 * SOAP extensions to the WSDL <code>woden_binding_fault</code> component.
 * This property may contain either a QName representing the code or the xs:token #any.
 * <p>
 * This class will restrict the possible values to a QName reference or the string "#any".
 * It provides methods to query whether the property contains a QName or a token and 
 * methods to retrieve the property value of the appropriate type.
 * 
 * 
 */

#include <axutil_allocator.h>
#include <axutil_env.h>
#include <axutil_error.h>
#include <axutil_string.h>
#include <axutil_utils.h>
#include <axutil_hash.h>
#include <axutil_qname.h>
#include <woden.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct woden_soap_fault_code woden_soap_fault_code_t;
typedef struct woden_soap_fault_code_ops woden_soap_fault_code_ops_t;
struct woden_ext_element;

/** @defgroup woden_soap_fault_code Soap Fault Code
  * @ingroup woden
  * @{
  */

struct woden_soap_fault_code_ops
{
   /** 
     * Deallocate memory
     * @return status code
     */
    axis2_status_t (AXIS2_CALL *
    free) (
            void *soap_fault_code,
            const axutil_env_t *env);

    axis2_bool_t (AXIS2_CALL *
    is_qname) (
            void *soap_fault_code,
            const axutil_env_t *env);

    axis2_bool_t (AXIS2_CALL *
    is_token) (
            void *soap_fault_code,
            const axutil_env_t *env);

    axutil_qname_t *(AXIS2_CALL *
    get_qname) (
            void *soap_fault_code,
            const axutil_env_t *env);

    axis2_char_t *(AXIS2_CALL *
    get_token) (
            void *soap_fault_code,
            const axutil_env_t *env);


};

struct woden_soap_fault_code
{
    woden_soap_fault_code_ops_t *ops;
    
};

AXIS2_EXTERN woden_soap_fault_code_t * AXIS2_CALL
woden_soap_fault_code_create(
        const axutil_env_t *env,
        axis2_char_t *token,
        axutil_qname_t *code_qn);

AXIS2_EXTERN void * AXIS2_CALL
woden_soap_fault_code_get_soap_fault_code_any(
        const axutil_env_t *env);

#define WODEN_SOAP_FAULT_CODE_FREE(soap_fault_code, env) \
      (((woden_soap_fault_code_t *) soap_fault_code)->ops->\
         free (soap_fault_code, env))

#define WODEN_SOAP_FAULT_CODE_IS_QNAME(soap_fault_code, env) \
      (((woden_soap_fault_code_t *) soap_fault_code)->ops->\
         is_qname (soap_fault_code, env))

#define WODEN_SOAP_FAULT_CODE_IS_TOKEN(soap_fault_code, env) \
      (((woden_soap_fault_code_t *) soap_fault_code)->ops->\
         is_token (soap_fault_code, env))

#define WODEN_SOAP_FAULT_CODE_GET_QNAME(soap_fault_code, env) \
      (((woden_soap_fault_code_t *) soap_fault_code)->ops->\
         get_qname (soap_fault_code, env))

#define WODEN_SOAP_FAULT_CODE_GET_TOKEN(soap_fault_code, env) \
      (((woden_soap_fault_code_t *) soap_fault_code)->ops->\
         get_token (soap_fault_code, env))


/** @} */
#ifdef __cplusplus
}
#endif
#endif /* WODEN_SOAP_FAULT_CODE_H */
