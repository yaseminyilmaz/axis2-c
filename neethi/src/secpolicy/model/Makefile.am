TESTS =

noinst_LTLIBRARIES = librp_model.la

librp_model_la_SOURCES = algorithmsuite.c asymmetric_binding.c \
							binding_commons.c header.c element.c https_token.c layout.c \
							property.c rampart_config.c secpolicy.c security_context_token.c \
							signed_encrypted_elements.c signed_encrypted_parts.c signed_encrypted_items.c \
							supporting_tokens.c symmetric_asymmetric_binding_commons.c \
							symmetric_binding.c transport_binding.c ut.c wss10.c wss11.c x509_token.c \
							trust10.c issued_token.c saml_token.c token.c


librp_model_la_LIBADD  = ../../../../util/src/libaxutil.la


INCLUDES = -I$(top_builddir)/include \
			-I ../../../include \
			-I ../../../../util/include \
	        -I ../../../../axiom/include \
    	    -I ../../../../include
