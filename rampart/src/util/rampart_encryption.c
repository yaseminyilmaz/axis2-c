/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#include <stdio.h>
#include <axis2_utils.h>
#include <oxs_ctx.h>
#include <oxs_error.h>
#include <oxs_utility.h>
#include <rampart_encryption.h>
#include <oxs_token_encrypted_data.h>
#include <oxs_token_encrypted_key.h>
#include <oxs_token_encryption_method.h>
#include <oxs_token_data_reference.h>
#include <oxs_token_cipher_data.h>
#include <oxs_token_cipher_value.h>
#include <oxs_token_key_info.h>
#include <oxs_token_key_name.h>
#include <oxs_key.h>
#include <rampart_action.h>
#include <rampart_constants.h>
#include <oxs_token_reference_list.h>
#include <axis2_array_list.h>
#include <oxs_axiom.h>
#include <oxs_asym_ctx.h>

/*Private functions*/
/*
 * Get encryption parts. Get node list to be encrypted. If nothing is found use the body.
 * If body is specified in the encryption parts encrypt the immediate child of <body>
 **/

static axis2_status_t 
rampart_enc_get_nodes_to_encrypt(const axis2_env_t *env,
    rampart_actions_t *actions,
    axiom_soap_envelope_t *soap_envelope,
    axis2_array_list_t *nodes_to_encrypt
);



/*Public functions*/
AXIS2_EXTERN axis2_status_t AXIS2_CALL
rampart_enc_encrypt_message(const axis2_env_t *env,
    axis2_msg_ctx_t *msg_ctx,
    rampart_actions_t *actions,
    axiom_soap_envelope_t *soap_envelope,
    axiom_node_t *sec_node)
{
    axis2_array_list_t *nodes_to_encrypt = NULL;
    axis2_array_list_t *id_list = NULL;
    axis2_status_t status = AXIS2_FAILURE;
    axis2_char_t *enc_sym_algo = NULL;
    axis2_char_t *enc_asym_algo = NULL;
    axis2_char_t *certificate_file = NULL;
    oxs_key_t *session_key = NULL;
    oxs_asym_ctx_t *asym_ctx = NULL;
    int i = 0;
    /*Get nodes to be encrypted*/
    nodes_to_encrypt = axis2_array_list_create(env, 5);
    status = rampart_enc_get_nodes_to_encrypt(env, actions, soap_envelope, nodes_to_encrypt);

    /*Get the symmetric encryption algorithm*/
    enc_sym_algo = RAMPART_ACTIONS_GET_ENC_SYM_ALGO(actions, env); 

    /*Generate the  session key*/
    session_key = oxs_key_create_key(env);
    status = OXS_KEY_FOR_ALGO(session_key, env, enc_sym_algo); 

    /*Create a list to store EncDataIds. This will be used in building the ReferenceList*/
    id_list = axis2_array_list_create(env, 5);

    /*Repeat until all encryption parts are encrypted*/
    for(i=0 ; i < AXIS2_ARRAY_LIST_SIZE(nodes_to_encrypt, env); i++){
        axiom_node_t *node_to_enc = NULL;
        axiom_node_t *parent_of_node_to_enc = NULL;
        axiom_node_t *enc_data_node = NULL;
        oxs_ctx_t *enc_ctx = NULL;
        axis2_char_t *id = NULL;
        axis2_status_t enc_status = AXIS2_FAILURE;
        
        /*Get the node to be encrypted*/
        node_to_enc = (axiom_node_t *)AXIS2_ARRAY_LIST_GET(nodes_to_encrypt, env, i);
        /*Create the encryption context for OMXMLSEC*/
        enc_ctx = oxs_ctx_create(env);
        /*Set the key*/
        OXS_CTX_SET_KEY(enc_ctx, env, session_key);
        /*Create an empty EncryptedDataNode*/
        parent_of_node_to_enc = AXIOM_NODE_GET_PARENT(node_to_enc, env);
        id = oxs_util_generate_id(env,(axis2_char_t*)OXS_ENCDATA_ID);
        enc_data_node = oxs_token_build_encrypted_data_element(env, parent_of_node_to_enc, OXS_TYPE_ENC_ELEMENT, id );
        enc_status = oxs_xml_enc_encrypt_node(env, enc_ctx, node_to_enc, enc_data_node);
        AXIS2_ARRAY_LIST_ADD(id_list, env, id);
        if(AXIS2_FAILURE == enc_status){
            return AXIS2_FAILURE;
        }
    }
    /*Get the asymmetric key encryption algorithm*/
    enc_asym_algo = RAMPART_ACTIONS_GET_ENC_KT_ALGO(actions, env);
    /*Get the certificate file name*/
    certificate_file = RAMPART_ACTIONS_GET_ENC_KEY_FILE(actions, env);
    /*Create asymmetric encryption context*/
    asym_ctx = oxs_asym_ctx_create(env);
    oxs_asym_ctx_set_algorithm(asym_ctx, env, enc_asym_algo);
    oxs_asym_ctx_set_file_name(asym_ctx, env, certificate_file);
    oxs_asym_ctx_set_operation(asym_ctx, env, OXS_ASYM_CTX_OPERATION_PUB_ENCRYPT);
    /*Encrypt the session key*/
    oxs_xml_enc_encrypt_key(env, asym_ctx, sec_node,session_key);    


    return AXIS2_SUCCESS;
}


AXIS2_EXTERN axis2_status_t AXIS2_CALL
rampart_enc_decrypt_message(const axis2_env_t *env,
    axis2_msg_ctx_t *msg_ctx,
    rampart_actions_t *actions,
    axiom_soap_envelope_t *soap_envelope,
    axiom_node_t *sec_node)
{

    return AXIS2_SUCCESS;
}

/*Private function implementations*/
static axis2_status_t  
rampart_enc_get_nodes_to_encrypt(const axis2_env_t *env,
    rampart_actions_t *actions,
    axiom_soap_envelope_t *soap_envelope,
    axis2_array_list_t *nodes_to_encrypt)
{
    axis2_array_list_t *str_list =  NULL;
    axis2_char_t *encryption_parts = NULL;
    int size, i = 0;

    /*Get encryption parts*/
    encryption_parts =  AXIS2_STRDUP(RAMPART_ACTIONS_GET_ENCRYPTION_PARTS(actions, env), env);
    /*If no encryption parts are specified use body as default*/
    if((!encryption_parts) || (0 == AXIS2_STRCMP(encryption_parts, " "))){
        axiom_soap_body_t *body = NULL;
        axiom_node_t *body_node = NULL;

        AXIS2_LOG_INFO(env->log, "[rampart][rampart_encryption] No encryption parts specified. Using the body as default");
        body = AXIOM_SOAP_ENVELOPE_GET_BODY(soap_envelope, env);
        body_node = AXIOM_SOAP_BODY_GET_BASE_NODE(body, env);
        AXIS2_ARRAY_LIST_ADD(nodes_to_encrypt, env, body_node);
        return AXIS2_SUCCESS;
    }

    /*Tokenize*/
    str_list = axis2_tokenize(env, encryption_parts, ' ');
    size = AXIS2_ARRAY_LIST_SIZE(str_list, env);
    /*Find the node and add to the list*/
    for(i=0 ; i < size ; i++ ){
        /*TODO*/
    }
    return AXIS2_SUCCESS;
}
