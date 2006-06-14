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

#ifndef WODEN_BINDING_ELEMENT_H
#define WODEN_BINDING_ELEMENT_H

/**
 * @file woden_binding_element.h
 * @brief Axis2 Binding Element Binding
 * This interface represents a WSDL &lt;binding&gt; element. 
 */

#include <axis2_allocator.h>
#include <axis2_env.h>
#include <axis2_error.h>
#include <axis2_string.h>
#include <axis2_utils.h>
#include <axis2_hash.h>
#include <axis2_qname.h>
#include <axis2_uri.h>
#include <axis2_array_list.h>
#include <woden/woden.h>
#include <woden_documentable_element.h>
#include <woden_configurable_element.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct woden_binding_element woden_binding_element_t;
typedef struct woden_binding_element_ops woden_binding_element_ops_t;
typedef union woden_binding_element_base woden_binding_element_base_t;

/** @defgroup woden_binding_element Binding Element
  * @ingroup axis2_binding
  * @{
  */

struct woden_binding_element_ops
{
   /** 
     * Deallocate memory
     * @return status code
     */
    axis2_status_t (AXIS2_CALL *
    free) (
            void *binding_element,
            const axis2_env_t *env);
 
    woden_obj_types_t (AXIS2_CALL *
    type) (
            void *binding_element,
            const axis2_env_t *env);

    /**
     * Set the QName that represents the <tt>name</tt> attribute of the  
     * &lt;binding&gt; element. 
     * 
     * @param qname the QName that identifies the binding.
     */
    axis2_status_t (AXIS2_CALL *
    set_qname) (
            void *binding_element,
            const axis2_env_t *env,
            axis2_qname_t *qname);

    axis2_qname_t *(AXIS2_CALL *
    get_qname) (
            void *binding_element,
            const axis2_env_t *env); 
 
    /**
     * Set the QName that represents the <tt>interface</tt> attribute of the 
     * &lt;binding&gt; element. This associates the binding with an interface.
     * 
     * @param qname the QName that identifies interface for this binding
     */
    axis2_status_t (AXIS2_CALL *
    set_interface_qname) (
            void *binding_element,
            const axis2_env_t *env,
            axis2_qname_t *qname);

    axis2_qname_t *(AXIS2_CALL *
    get_interface_qname) (
            void *binding_element,
            const axis2_env_t *env); 

    /**
     * Get the Interface Element identified by the QName specified in the
     * <tt>interface</tt> attribute of this &lt;binding&gt; element.
     * 
     * @return Interface Element the interface associated with this binding
     */
    void *(AXIS2_CALL *
    get_interface_element) (
            void *binding_element,
            const axis2_env_t *env);
  
    /**
     * Set the URI that represents the <tt>type</tt> attribute of the 
     * &lt;binding&gt; element. This indicates the type of concrete binding
     * extensions contained within this binding.
     * 
     * @param URI the URI indicating the concrete binding
     */
    axis2_status_t (AXIS2_CALL *
    set_type) (
            void *binding_element,
            const axis2_env_t *env,
            axis2_uri_t *type);

    axis2_uri_t *(AXIS2_CALL *
    get_type) (
            void *binding_element,
            const axis2_env_t *env); 
  
    axis2_status_t (AXIS2_CALL *
    add_binding_fault_element) (
            void *binding_element,
            const axis2_env_t *env,
            void *fault);

    axis2_array_list_t *(AXIS2_CALL *
    get_binding_fault_elements) (
            void *binding_element,
            const axis2_env_t *env);
 
    axis2_status_t (AXIS2_CALL *
    add_binding_op_element) (
            void *binding_element,
            const axis2_env_t *env,
            void *op);

    axis2_array_list_t *(AXIS2_CALL *
    get_binding_op_elements) (
            void *binding_element,
            const axis2_env_t *env);

};

union woden_binding_element_base
{
    woden_documentable_element_t documentable_element;
    woden_configurable_element_t configurable_element;
};

struct woden_binding_element
{
    woden_binding_element_base_t base;
    woden_binding_element_ops_t *ops;
};

AXIS2_EXTERN woden_binding_element_t * AXIS2_CALL
woden_binding_element_create(
        const axis2_env_t *env);

/************************Woden C Internal Methods******************************/
AXIS2_EXTERN axis2_status_t AXIS2_CALL
woden_binding_element_resolve_methods(
        woden_binding_element_t *binding_element,
        const axis2_env_t *env,
        axis2_hash_t *methods);
/************************End of Woden C Internal Methods***********************/

#define WODEN_BINDING_ELEMENT_FREE(binding_element, env) \
      (((woden_binding_element_t *) binding_element)->ops->\
         free (binding_element, env))

#define WODEN_BINDING_ELEMENT_SUPER_OBJS(binding_element, env) \
      (((woden_binding_element_t *) binding_element)->ops->\
         super_objs (binding_element, env))

#define WODEN_BINDING_ELEMENT_TYPE(binding_element, env) \
      (((woden_binding_element_t *) binding_element)->ops->\
         type (binding_element, env))

#define WODEN_BINDING_ELEMENT_SET_QNAME(binding_element, env, qname) \
      (((woden_binding_element_t *) binding_element)->ops->\
         set_qname (binding_element, env, qname))

#define WODEN_BINDING_ELEMENT_GET_QNAME(binding_element, env) \
      (((woden_binding_element_t *) binding_element)->ops->\
        get_qname  (binding_element, env))

#define WODEN_BINDING_ELEMENT_SET_INTERFACE_QNAME(binding_element, env, qname) \
      (((woden_binding_element_t *) binding_element)->ops->\
         set_interface_qname (binding_element, env, qname))

#define WODEN_BINDING_ELEMENT_GET_INTERFACE_QNAME(binding_element, env) \
      (((woden_binding_element_t *) binding_element)->ops->\
         get_interface_qname (binding_element, env))

#define WODEN_BINDING_ELEMENT_GET_INTERFACE_ELEMENT(binding_element, env) \
      (((woden_binding_element_t *) binding_element)->ops->\
        get_interface_element  (binding_element, env))

#define WODEN_BINDING_ELEMENT_SET_TYPE(binding_element, env, type) \
      (((woden_binding_element_t *) binding_element)->ops->\
         set_type (binding_element, env, type))

#define WODEN_BINDING_ELEMENT_GET_TYPE(binding_element, env) \
      (((woden_binding_element_t *) binding_element)->ops->\
        get_type  (binding_element, env))

#define WODEN_BINDING_ELEMENT_ADD_BINDING_FAULT_ELEMENT(binding_element, env, fault) \
      (((woden_binding_element_t *) binding_element)->ops->\
        add_binding_fault_element  (binding_element, env, fault))

#define WODEN_BINDING_ELEMENT_GET_BINDING_FAULT_ELEMENTS(binding_element, env) \
      (((woden_binding_element_t *) binding_element)->ops->\
        get_binding_fault_elements  (binding_element, env))

#define WODEN_BINDING_ELEMENT_ADD_BINDING_OP_ELEMENT(binding_element, env, op) \
      (((woden_binding_element_t *) binding_element)->ops->\
         add_binding_op_element (binding_element, env, op))

#define WODEN_BINDING_ELEMENT_GET_BINDING_OP_ELEMENTS(binding_element, env) \
      (((woden_binding_element_t *) binding_element)->ops->\
         get_binding_op_elements (binding_element, env))

/** @} */
#ifdef __cplusplus
}
#endif
#endif /* WODEN_BINDING_ELEMENT_H */
